#!/bin/bash

# ../../src should be compiled before calling this

gcc -m64 -nostdlib -nostdinc -nostartfiles -nodefaultlibs -O3 -ffast-math -mno-red-zone -fpack-struct -ffreestanding -undef -std=c99 -pedantic -Wall -Werror -I../../include -c -o hellostd.o hellostd.c
ld -T ../../bin/app.ld -o hellostd.app ../../bin/crt0.o hellostd.o ../../bin/libbarelibc.a
