export PREFIX := $(HOME)/opt/cross
export PATH := $(PREFIX)/bin:$(PATH)
export TARGET := i686-elf


BINUTILS_VERSION := 2.35
GCC_VERSION := 10.4.0
GMP_VERSION := 6.2.1
MPFR_VERSION := 4.2.0
MPC_VERSION := 1.2.1
M4_VERSION := 1.4.19

FLEX := flex-2.6.4
TEXINFO := texinfo-6.8
BISON := bison-3.7.4
GRUB := grub-2.06
BINUTILS := binutils-$(BINUTILS_VERSION)
GCC := gcc-$(GCC_VERSION)
M4 := m4-$(M4_VERSION)
GMP := gmp-$(GMP_VERSION)
MPFR := mpfr-$(MPFR_VERSION)
MPC := mpc-$(MPC_VERSION)

all: $(TEXINFO) $(BINUTILS) $(M4) $(GMP) $(MPFR) $(MPC) $(GCC) $(BISON) $(FLEX) $(GRUB) 

$(TEXINFO):
	mkdir -p $(PREFIX)
	wget -nc https://ftp.gnu.org/gnu/texinfo/texinfo-6.8.tar.gz -P $(PREFIX)
	tar xvzf $(PREFIX)/texinfo-6.8.tar.gz -C $(PREFIX)
	mkdir -p $(PREFIX)/build-texinfo
	cd $(PREFIX)/build-texinfo && ../texinfo-6.8/configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers
	$(MAKE) -C $(PREFIX)/build-texinfo
	$(MAKE) -C $(PREFIX)/build-texinfo install

$(BINUTILS):
	mkdir -p $(PREFIX)
	wget -nc https://ftp.gnu.org/gnu/binutils/$(BINUTILS).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(BINUTILS).tar.gz -C $(PREFIX)
	mkdir -p $(PREFIX)/build-binutils
	cd $(PREFIX)/build-binutils && ../$(BINUTILS)/configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror
	$(MAKE) -C $(PREFIX)/build-binutils
	$(MAKE) -C $(PREFIX)/build-binutils install

$(M4):
	wget -nc https://ftp.gnu.org/gnu/m4/$(M4).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(M4).tar.gz -C $(PREFIX)
	cd $(PREFIX)/$(M4) && ./configure --prefix="$(PREFIX)"
	$(MAKE) -C $(PREFIX)/$(M4)
	$(MAKE) -C $(PREFIX)/$(M4) install
	
$(GMP):
	wget -nc https://ftp.gnu.org/gnu/gmp/$(GMP).tar.bz2 -P $(PREFIX)
	tar xvf $(PREFIX)/$(GMP).tar.bz2 -C $(PREFIX)
	cd $(PREFIX)/$(GMP) && ./configure --prefix="$(PREFIX)"
	$(MAKE) -C $(PREFIX)/$(GMP)
	$(MAKE) -C $(PREFIX)/$(GMP) install

$(MPFR):
	wget -nc https://ftp.gnu.org/gnu/mpfr/$(MPFR).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(MPFR).tar.gz -C $(PREFIX)
	cd $(PREFIX)/$(MPFR) && ./configure --prefix="$(PREFIX)" --with-gmp="$(PREFIX)"
	$(MAKE) -C $(PREFIX)/$(MPFR)
	$(MAKE) -C $(PREFIX)/$(MPFR) install

$(MPC):
	wget -nc https://ftp.gnu.org/gnu/mpc/$(MPC).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(MPC).tar.gz -C $(PREFIX)
	cd $(PREFIX)/$(MPC) && ./configure --prefix="$(PREFIX)" --with-gmp="$(PREFIX)" --with-mpfr="$(PREFIX)"
	$(MAKE) -C $(PREFIX)/$(MPC)
	$(MAKE) -C $(PREFIX)/$(MPC) install

#--with-gmp="$(PREFIX)" --with-mpfr="$(PREFIX)" --with-mpc="$(PREFIX)"
$(GCC):
	wget -nc https://ftp.gnu.org/gnu/gcc/$(GCC)/$(GCC).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(GCC).tar.gz -C $(PREFIX)
	mkdir -p $(PREFIX)/build-gcc
	cd $(PREFIX)/build-gcc && ../configure --target="$(TARGET)" --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers --with-gmp="$(PREFIX)" --with-mpfr="$(PREFIX)" --with-mpc="$(PREFIX)"
	$(MAKE) -C $(PREFIX)/build-gcc all-gcc	
	$(MAKE) -C $(PREFIX)/build-gcc all-target-libgcc
	$(MAKE) -C $(PREFIX)/build-gcc install-gcc
	$(MAKE) -C $(PREFIX)/build-gcc install-target-libgcc

$(BISON):
	wget -nc https://ftp.gnu.org/gnu/bison/bison-3.7.4.tar.gz -P $(PREFIX)
	tar xvzf $(PREFIX)/bison-3.7.4.tar.gz -C $(PREFIX)
	cd $(PREFIX)/bison-3.7.4 &&	./configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls
	$(MAKE) -C $(PREFIX)/bison-3.7.4
	$(MAKE) -C $(PREFIX)/bison-3.7.4 install

$(FLEX):
	wget -nc https://github.com/westes/flex/releases/download/v2.6.4/flex-2.6.4.tar.gz -P $(PREFIX)
	tar xvzf $(PREFIX)/flex-2.6.4.tar.gz -C $(PREFIX)
	cd $(PREFIX)/flex-2.6.4 &&	./configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls
	$(MAKE) -C $(PREFIX)/flex-2.6.4
	$(MAKE) -C $(PREFIX)/flex-2.6.4 install

$(GRUB):
	wget -nc https://ftp.gnu.org/gnu/grub/grub-2.06.tar.xz -P $(PREFIX)
	tar -xvf $(PREFIX)/grub-2.06.tar.xz -C $(PREFIX)
	cd $(PREFIX)/grub-2.06 && ./configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror
	$(MAKE) -C $(PREFIX)/grub-2.06
	$(MAKE) -C $(PREFIX)/grub-2.06 install

.PHONY: clean
clean:
	rm -rf $(PREFIX)/$(TEXINFO)
	rm -rf $(PREFIX)/$(BINUTILS)
	rm -rf $(PREFIX)/$(M4)
	rm -rf $(PREFIX)/$(GMP)
	rm -rf $(PREFIX)/$(MPFR)
	rm -rf $(PREFIX)/$(MPC)
	rm -rf $(PREFIX)/$(GCC)
	rm -rf $(PREFIX)/$(BISON)
	rm -rf $(PREFIX)/$(FLEX)
	rm -rf $(PREFIX)/$(GRUB)