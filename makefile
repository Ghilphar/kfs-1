GCC = gcc
LD = ld
NASM = nasm

CFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

all: kernel

kernel: boot.o kernel.o link.ld
	$(LD) -m elf_i386 -T link.ld -o kernel boot.o kernel.o

kernel.o: kernel.c
	$(GCC) $(CFLAGS) -c kernel.c -o kernel.o

boot.o: boot.s
	$(NASM) -f elf32 boot.s -o boot.o

clean:
	rm -f *.o
	rm -f kernel

.PHONY: all clean
