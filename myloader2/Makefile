CC=gcc
CFLAGS =-m32 -O2 -Wall -Werror -fno-builtin
CFLAGS +=-I./include

ASFLAGS=-m32

CSRC=$(shell find src/ -name "*.c")
SSRC=$(shell find src/ -name "*.S")
#ALL=$(CSRC:.c=) $(SSRC:.S=)

OBJS=$(CSRC:.c=.o)

loader: $(OBJS) src/start.o
	ld -o loader -e start -Ttext 0x100000 -m elf_i386 src/start.o $(OBJS)

clean:
	-rm -f loader src/start.o $(OBJS) 2> /dev/null
