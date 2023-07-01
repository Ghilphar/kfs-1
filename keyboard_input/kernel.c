#include "keyboard_map.h"

/* there are 25 lines each of 80 columns; each element takes 2 bytes */
#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2

#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define BACKSPACE_KEY_CODE 0x0E
#define UP_ARROW_KEY_CODE 0x48
#define DOWN_ARROW_KEY_CODE 0x50
#define LEFT_ARROW_KEY_CODE 0x4B
#define RIGHT_ARROW_KEY_CODE 0x4D
#define ENTER_KEY_CODE 0x1C

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

/* current cursor location */
unsigned int current_loc = 0;
/* video memory begins at address 0xb8000 */
char *vidptr = (char*)0xb8000;

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

unsigned char color_table[8] = {
	0x07, // Gray
	0x04, // Red
	0x02, // Green
	0x01, // Blue
	0x0F, // Bright White
	0x0C, // Bright Red
	0x0A, // Bright Green
	0x09  // Bright Blue
};
unsigned char color = 0x00;

unsigned short get_cursor() {
    unsigned short pos = 0;
    write_port(0x3D4, 0x0F);
    pos |= read_port(0x3D5);
    write_port(0x3D4, 0x0E);
    pos |= ((unsigned short)read_port(0x3D5)) << 8;
    return pos;
}

void set_cursor(unsigned short pos) {
    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char)(pos & 0xFF));
    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void idt_init(void)
{
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler;
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
}

void kprint_newline(void)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void clear_screen(void)
{
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}
void scroll(void) {
    // pointer to the second line in video memory
    char *second = vidptr + COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT;

    // copy each line to the previous line
    for (int i = 0; i < (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i++) {
        vidptr[i] = second[i];
    }

    // clear the last line
    for (int i = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < LINES * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i += 2) {
        vidptr[i] = ' ';
        vidptr[i + 1] = 0x07;
    }

    // move the cursor to the beginning of the last line
    current_loc = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT;
}

void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;

    /* write EOI */
    write_port(0x20, 0x20);

	unsigned short cursor_pos = current_loc / 2;  // each cell has 2 bytes
    set_cursor(cursor_pos);
    status = read_port(KEYBOARD_STATUS_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if(keycode < 0)
            return;
		else if(keycode == 0x0F) {
			color++;
			if(color > 7) {
				color = 0;
			}
			return;
		}
        else if(keycode == BACKSPACE_KEY_CODE) {
            if (current_loc > 0) {
                current_loc -= 2;  // move cursor back by one character
                vidptr[current_loc] = ' ';  // clear the character
                vidptr[current_loc+1] = 0x07;  // and its color attribute
            }
            return;
        }
        else if(keycode == ENTER_KEY_CODE) {
            kprint_newline();
        }
        else if(keycode == UP_ARROW_KEY_CODE) {
			if (current_loc > COLUMNS_IN_LINE * 2 - 1) {
				current_loc = current_loc - COLUMNS_IN_LINE * 2;
			}
        }
        else if(keycode == DOWN_ARROW_KEY_CODE) {
            // Move the cursor down one line
			if (current_loc < SCREENSIZE - COLUMNS_IN_LINE * 2) {
				current_loc = current_loc + COLUMNS_IN_LINE * 2;
			}
        }
        else if(keycode == LEFT_ARROW_KEY_CODE) {
            // Move the cursor left one character
            if (current_loc > 0) {
                current_loc -= 2;
            }
        }
        else if(keycode == RIGHT_ARROW_KEY_CODE) {
            // Move the cursor right one character
            if (current_loc < SCREENSIZE - 2) {
                current_loc += 2;
            }
			else {
				kprint_newline();
			}
        }
        // Regular keys
        else {
            vidptr[current_loc++] = keyboard_map[(unsigned char) keycode];
            vidptr[current_loc++] = color_table[color];
        }
	    if (current_loc >= SCREENSIZE) {
            scroll();
        }
    }
}

void kmain(void)
{
	clear_screen();
	idt_init();
	kb_init();
    set_cursor(current_loc / 2);

	while(1);
}