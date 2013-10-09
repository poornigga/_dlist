
TARGET = aes
FILES += ./*.c
OBJS += ./*.o

SHELL= /bin/sh
CC_OSX = clang
CC_LINUX = gcc

UNAME=$(shell uname)

FLAG=-g -Wall -o0

CC :=
ifeq ($(UNAME), Darwin)
	CC := $(CC_OSX)
else
	CC := $(CC_LINUX)
endif


$(TARGET):
	$(CC) $(FLAG) -o $(TARGET) $(FILES)

clean:
	rm -rf $(TARGET) $(OBJS) $(TARGET).dSYM

