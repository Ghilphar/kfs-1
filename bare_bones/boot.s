section .multiboot
align 4
dd 0x1BADB002                   ; Multiboot magic number
dd 0x00000003                   ; Flags for memory info and align page
dd -(0x1BADB002 + 0x00000003)   ; Checksum -- magic number and flags should add up to zero

; The multiboot standard does not define the value of the stack pointer register
; (esp) and it is up to the kernel to provide a stack. This allocates room for a
; small stack by creating a symbol at the bottom of it, then allocating 16384
; bytes for it, and finally creating a symbol at the top. The stack grows
; downwards on x86. The stack is in its own section so it can be marked nobits,
; which means the kernel file is smaller because it does not contain an
; uninitialized stack. The stack on x86 must be 16-byte aligned according to the
; System V ABI standard and de-facto extensions. The compiler will assume the
; stack is properly aligned and failure to align the stack will result in
; undefined behavior.

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

; The bootloader will search for this symbol to initiate the kernel
section .text
global _start
_start:
    ; To set up a stack, we set the esp register to point to the top of the
    ; stack (as it grows downwards on x86 systems). This is necessarily done
    ; in assembly as languages such as C cannot function without a stack.
    mov esp, stack_top

    ; Enter the high-level kernel. 
    extern kernel_main
    call kernel_main

    ; If the system has nothing more to do, put the computer into an
    ; infinite loop. This is done by disabling interrupts with cli (clear interrupt 
    ; enable in eflags) and then waiting for the next interrupt with hlt 
    ; (halt instruction). Since they are disabled, this will lock up the computer. 
    ; If the halt instruction ever wakes up due to a non-maskable interrupt occurring 
    ; or due to system management mode, we jump back to the halt instruction.

    cli

loop:
    hlt
    jmp 1b
