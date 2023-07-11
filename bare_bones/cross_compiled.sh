#!/bin/bash

set -xeu
if [ -z "$TARGET" ]; then
    echo "Must provide TARGET in environment" 1>&2
    exit 1
fi
if [ -z "$PREFIX" ]; then
    echo "Must provide PREFIX in environment" 1>&2
    exit 1
fi

export PREFIX="$HOME/mycross_cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"



mkdir $PREFIX
cd $PREFIX

wget https://github.com/westes/flex/releases/download/v2.6.4/flex-2.6.4.tar.gz
wget https://ftp.gnu.org/gnu/bison/bison-3.7.4.tar.gz
wget https://ftp.gnu.org/gnu/m4/m4-1.4.19.tar.gz
wget https://ftp.gnu.org/gnu/grub/grub-2.06.tar.xz
wget https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.gz
wget https://ftp.gnu.org/gnu/texinfo/texinfo-6.8.tar.gz

tar xvzf flex-2.6.4.tar.gz
tar xvzf bison-3.7.4.tar.gz
tar xvzf m4-1.4.19.tar.gz
tar -xvf grub-2.06.tar.xz
tar xvzf binutils-2.35.tar.gz
tar xvzf texinfo-6.8.tar.gz

cd binutils-2.35
./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

cd m4-1.4.19
./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make
make install
cd ..

cd texinfo-6.8
./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make
make install
cd ..

cd bison-3.7.4
./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make
make install
cd ..

cd flex-2.6.4
./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make
make install
cd ..

cd grub-2.06
./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..