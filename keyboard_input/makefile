GCC = gcc
LD = ld
NASM = nasm

CFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

all: myos.iso

myos.iso: kernel
	mkdir -p isodir/boot/grub
	cp mykernel.bin isodir/boot/mykernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

kernel: boot.o kernel.o link.ld
	$(LD) -m elf_i386 -T link.ld -o mykernel.bin boot.o kernel.o

kernel.o: kernel.c
	$(GCC) $(CFLAGS) -c kernel.c -o kernel.o

boot.o: boot.s
	$(NASM) -f elf32 boot.s -o boot.o

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f *.o
	rm -f mykernel.bin
	rm -f myos.iso
	rm -rf isodir

.PHONY: all run clean
