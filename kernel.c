#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200


// This is a simple run over the VGA buffer and set spaces in order to clear the screen
void clear_screen() {
    volatile char *video = (volatile char*)VGA_ADDRESS;
    int i = 0;
    while (i < BUFSIZE) {
        *video++ = ' ';
        *video++ = 0x07;
        i++;
    }
}

// The kernel main call the clear_scren function and print 42 on the writting on the VGA buffer
void kernel_main(void) {
    clear_screen();
    
    const char *str = "42";
    volatile char *video = (volatile char*)VGA_ADDRESS;
    while (*str != 0) {
        *video++ = *str++;
        *video++ = 0x07;
    }
}
