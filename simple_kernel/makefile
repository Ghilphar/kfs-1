TARGET ?= i686-elf
PREFIX ?= $(HOME)/mycross_cross
PATH := $(PREFIX)/bin:$(PATH)
SHELL := env PATH=$(PATH) /bin/bash
export

all: texinfo binutils gcc

texinfo:
	mkdir -p $(PREFIX)
	cd $(PREFIX) && \
	wget https://ftp.gnu.org/gnu/texinfo/texinfo-6.8.tar.gz && \
	tar xvzf texinfo-6.8.tar.gz && \
	cd texinfo-6.8 && \
	./configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers && \
	make && \
	make install

binutils:
	mkdir -p $(PREFIX)
	cd $(PREFIX) && \
	wget https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.gz && \
	tar xvzf binutils-2.35.tar.gz && \
	cd binutils-2.35 && \
	./configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror && \
	make && \
	make install

gcc:
	mkdir -p $(PREFIX)
	cd $(PREFIX) && \
	wget https://ftp.gnu.org/gnu/gcc/gcc-10.4.0/gcc-10.4.0.tar.gz && \
	tar xvzf gcc-10.4.0.tar.gz && \
	cd gcc-10.4.0 \
	./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers \
	make all-gcc && \
	make all-target-libgcc && \
	make install-gcc && \
	make install-target-libgcc

clean:
	rm -rf $(PREFIX)
