# **** GNU make manual: http://www.gnu.org/software/make/manual/make.html ****
# If you have questions about the follwing Makefile script, 
# please search the Internet, or RTFM.

# setting compiler and compile options
CC      = gcc
LD      = ld
CFLAGS  = -ggdb -MD -Wall -Wno-unused-result -Werror -fno-strict-aliasing -I./include -O2 -m32 

# jyy always knows what you have done (*^__^*)
GITFLAGS = -q --author='jyy <njujiangyy@gmail.com>' --no-verify --allow-empty

# target to compile
CFILES  = $(shell find src/ -name "*.c")
OBJS    = $(CFILES:.c=.o)

# test files
TESTFILE = testcase/c/matrix-mul
C_TEST_FILE_LIST = $(shell find testcase/c/ -name "*.c")
S_TEST_FILE_LIST = $(shell find testcase/asm/ -name "*.S")
TEST_FILE_LIST = $(C_TEST_FILE_LIST:.c=) $(S_TEST_FILE_LIST:.S=)

nemu: $(OBJS)
	$(CC) -o nemu $(OBJS) $(CFLAGS) -lreadline 

$(TEST_FILE_LIST):
	cd `dirname $@` && make

#loader: $(TESTFILE)
#	objcopy -S -O binary $(TESTFILE) loader
LOADER_DIR = ~/NEMU/kernel
loader:
	cd $(LOADER_DIR)&&make
	objcopy -S -O binary $(LOADER_DIR)/loader loader
	xxd -i loader >src/elf/loader.c
	rm loader


run: nemu $(TESTFILE)
	./nemu -d $(TESTFILE) 2>&1 | tee log.txt

q: nemu $(TESTFILE)
	./nemu -q -d $(TESTFILE) 2>&1 | tee log.txt

gdb: nemu $(TESTFILE)
	gdb --args ./nemu -dq $(TESTFILE)

test: nemu $(TEST_FILE_LIST)
	bash test.sh $(TEST_FILE_LIST)


STU_ID=131220070
SHARED_FOLDER=~/share

submit: clean
	cd testcase && make clean
	cd .. && tar cvj $(shell pwd | grep -o '[^/]*$$') > $(STU_ID).tar.bz2
	mv ../$(STU_ID).tar.bz2 $(SHARED_FOLDER) || rm ../$(STU_ID).tar.bz2

-include $(OBJS:.o=.d)

clean:
	-rm -f nemu $(OBJS) $(OBJS:.o=.d) log.txt 2> /dev/null
