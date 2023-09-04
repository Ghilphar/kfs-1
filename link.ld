ENTRY(_start)
SECTIONS {
    . = 0x100000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
/* The linker define how differents sections of the program laid out on memory  */
/* This is necessary to control where your code and data are place on memory  */
/* The linker is essential for combining multiple object files into a single executable */
/* Resolving symbols and addresses, defining the memory layout of the program. */