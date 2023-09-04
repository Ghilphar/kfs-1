section .multiboot
align 4
    dd 0x1BADB002           ; Multiboot magic number
    dd 0x0                  ; Flags
    dd -(0x1BADB002 + 0x0)  ; Checksum (magic number + flags + checksum should equal 0)

; This is a simple multiboot header.
; This  make the kernel multiboot-compliant bootloader
; Nothing invented.

section .text

; Global _start set the entry for the bootloader
global _start
extern kernel_main

_start:
    cli
    ; We call the kernel_main and halt the cpu
    call kernel_main
    hlt
