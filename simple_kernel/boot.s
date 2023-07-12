section .multiboot
align 4
    dd 0x1BADB002           ; Multiboot magic number
    dd 0x0                  ; Flags
    dd -(0x1BADB002 + 0x0)  ; Checksum (magic number + flags + checksum should equal 0)

section .text
global _start
extern kernel_main

_start:
    cli
    call kernel_main
    hlt
