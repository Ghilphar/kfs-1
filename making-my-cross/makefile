	PREFIX := $(HOME)/opt/cross
	TARGET := i686-elf
	PATH := $(PREFIX)/bin:$(PATH)

	BINUTILS_VERSION := 2.35
	GCC_VERSION := 10.4.0

	BINUTILS := binutils-$(BINUTILS_VERSION)
	GCC := gcc-$(GCC_VERSION)

	GMP_VERSION := 6.2.1
	MPFR_VERSION := 4.1.0
	MPC_VERSION := 1.2.1
	M4_VERSION := 1.4.18

	M4 := m4-$(M4_VERSION)
	GMP := gmp-$(GMP_VERSION)
	MPFR := mpfr-$(MPFR_VERSION)
	MPC := mpc-$(MPC_VERSION)

all: $(BINUTILS) $(GCC) #$(GMP) $(MPFR) $(MPC)

$(BINUTILS):
	mkdir -p $(PREFIX)
	wget -nc https://ftp.gnu.org/gnu/binutils/$(BINUTILS).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(BINUTILS).tar.gz -C $(PREFIX)
	rm $(PREFIX)/$(BINUTILS).tar.gz
	mkdir -p $(PREFIX)/$(BINUTILS)/build
	cd $(PREFIX)/$(BINUTILS)/build && ../configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror
	$(MAKE) -C $(PREFIX)/$(BINUTILS)/build
	$(MAKE) -C $(PREFIX)/$(BINUTILS)/build install

#$(M4):
#	wget -nc https://ftp.gnu.org/gnu/m4/$(M4).tar.gz -P $(PREFIX)
#	tar xvf $(PREFIX)/$(M4).tar.gz -C $(PREFIX)
#	cd $(PREFIX)/$(M4) && ./configure --prefix="$(PREFIX)"
#	$(MAKE) -C $(PREFIX)/$(M4)
#	$(MAKE) -C $(PREFIX)/$(M4) install
#	
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

$(GCC):
	wget -nc https://ftp.gnu.org/gnu/gcc/$(GCC)/$(GCC).tar.gz -P $(PREFIX)
	tar xvf $(PREFIX)/$(GCC).tar.gz -C $(PREFIX)
	rm $(PREFIX)/$(GCC).tar.gz
	mkdir -p $(PREFIX)/$(GCC)/build
	cd $(PREFIX)/$(GCC)/build && ../configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers --with-mpfr=$(brew --prefix mpfr) --with-mpc=$(brew --prefix libmpc)
	$(MAKE) -C $(PREFIX)/$(GCC)/build all-gcc	
	$(MAKE) -C $(PREFIX)/$(GCC)/build all-target-libgcc
	$(MAKE) -C $(PREFIX)/$(GCC)/build install-gcc
	$(MAKE) -C $(PREFIX)/$(GCC)/build install-target-libgcc

.PHONY: clean
clean:
	rm -rf $(PREFIX)