section .text
global kernel_main:

VIDEO_ADDR equ 0xb8000
COLOR equ 0x0f

kernel_main:
	pusha
	mov edx, VIDEO_ADDR
	mov DWORD [edx], 0x0f320f34
	popa
	ret 
