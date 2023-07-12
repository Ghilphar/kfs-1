#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

void clear_screen() {
    volatile char *video = (volatile char*)VGA_ADDRESS;
    int i = 0;
    while (i < BUFSIZE) {
        *video++ = ' ';
        *video++ = 0x07;
        i++;
    }
}

void kernel_main(void) {
    clear_screen();
    
    const char *str = "42";
    volatile char *video = (volatile char*)VGA_ADDRESS;
    while (*str != 0) {
        *video++ = *str++;
        *video++ = 0x07;
    }
}
