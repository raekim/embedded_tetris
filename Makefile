#Makefile for a basic kernel module

CC=gcc
SRCS_FLGS	= -I$(IF_DIR)

IF_DIR 		:= interface
IF_SRCS 	:= $(wildcard $(IF_DIR)/*.c)
IF_OBJS 	:= $(IF_SRCS:.c=.o)
IF_DEPS		:= $(IF_SRCS:.c=.d)

TT_DIR		:= tetris
TT_SRCS		:= $(wildcard $(TT_DIR)/*.c)
TT_OBJS 	:= $(TT_SRCS:.c=.o)
TT_DEPS		:= $(TT_SRCS:.c=.d)

EXE				:= tetris.out
EXE_FLGS	:= -lpthread

all: $(EXE)

$(EXE):	$(TT_OBJS) $(IF_OBJS)
	$(CC) -o $@ $^ $(EXE_FLGS)

#all: $(IF_OBJS) $(TT_OBJS)

$(IF_OBJS) $(TT_OBJS):%.o:%.c
	$(CC) -MMD -c $< -o $@ $(SRCS_FLGS)

.PHONY: clean

clean:
	-rm -f $(IF_OBJS) $(IF_DEPS) $(TT_OBJS) $(TT_DEPS)

-include $(IF_DEPS) $(TT_DEPS)

# obj-m   := fpga_led_driver.o fpga_dot_driver.o fpga_push_switch_driver.o

# KDIR    :=/work/achro5250/kernel-20130306
# PWD     :=$(shell pwd)

# all: driver main

# driver:
# 	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules ARCH=arm

# main: main.o fpga_led_interface.o fpga_dot_interface.o fpga_switch_interface.o que.o Draw.o GameInfo.o Init.o Input.o Update.o
# 	arm-linux-gcc -static -o $@ $^ -lpthread

# que.o: que.c
# 	arm-linux-gcc -static -c -o $@ $< 
# Draw.o: Draw.c
# 	arm-linux-gcc -static -c -o $@ $< 
# GameInfo.o: GameInfo.c
# 	arm-linux-gcc -static -c -o $@ $< 
# Init.o: Init.c
# 	arm-linux-gcc -static -c -o $@ $< 
# Input.o: Input.c
# 	arm-linux-gcc -static -c -o $@ $< 

# Update.o: Update.c
# 	arm-linux-gcc -static -c -o $@ $< 

# fpga_dot_interface.o: fpga_dot_interface.c
# 	arm-linux-gcc -static -c -o $@ $< 

# fpga_led_interface.o: fpga_led_interface.c
# 	arm-linux-gcc -static -c -o $@ $< 

# fpga_switch_interface.o: fpga_switch_interface.c
# 	arm-linux-gcc -static -c -o $@ $< 

# main.o: main.c
# 	arm-linux-gcc -static -c -o $@ $<

# install:
# 	cp -a fpga_led_driver.ko /nfsroot
# 	cp -a fpga_dot_driver.ko /nfsroot
# 	cp -a fpga_push_switch_driver.ko /nfsroot
# 	cp -a main /nfsroot
# 	cp -a mod_all.sh /nfsroot
# clean:
# 	rm -rf *.ko
# 	rm -rf *.mod.*
# 	rm -rf *.o
# 	rm -rf Module.symvers
# 	rm -rf modules.order
# 	rm -rf .led*
# 	rm -rf .tmp*
