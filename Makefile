#Makefile for a basic kernel module

CC:=gcc
#CC=arm-linux-gcc
SRCS_FLGS	:= -I$(IF_DIR) -static

IF_DIR 		:= interface
IF_SRCS 	:= $(wildcard $(IF_DIR)/*.c)
IF_OBJS 	:= $(IF_SRCS:.c=.o)
IF_DEPS		:= $(IF_SRCS:.c=.d)

TT_DIR		:= tetris
TT_SRCS		:= $(wildcard $(TT_DIR)/*.c)
TT_OBJS 	:= $(TT_SRCS:.c=.o)
TT_DEPS		:= $(TT_SRCS:.c=.d)

DD_DIR		:= driver
MDIR  	    :=$(shell pwd)/$(DD_DIR)
DD_SRCS		:= $(wildcard $(DD_DIR)/*.c)
obj-m	:= $(DD_SRCS:.c=.o)
KDIR 	   :=/work/achro5250/kernel-20130306

INSTALL_DIR	:= /nfsroot

EXE			:= tetris.out
EXE_FLGS	:= -lpthread

all: $(EXE)
#all: $(EXE) driver

driver:
 	$(MAKE) -C $(KDIR) SUBDIRS=$(MDIR) modules ARCH=arm

$(EXE):	$(TT_OBJS) $(IF_OBJS)
	$(CC) -o $@ $^ $(EXE_FLGS)

$(IF_OBJS) $(TT_OBJS):%.o:%.c
	$(CC) -MMD -c $< -o $@ $(SRCS_FLGS)

.PHONY: clean test install

test:
	echo $(PWD)

install:
	cp -a $(EXE) $(INSTALL_DIR)
	cp -a mod_all.sh $(INSTALL_DIR)
	cp -a $(DD_DIR)/*.ko $(INSTALL_DIR)

clean:
	-rm -rf $(EXE)
	-rm -rf $(IF_OBJS) $(IF_DEPS)
	-rm -rf $(TT_OBJS) $(TT_DEPS)
	-rm -rf $(obj-m)	
	-rm -rf $(DD_DIR)/*.ko
	-rm -rf $(DD_DIR)/*.mod.*
	-rm -rf $(DD_DIR)/Module.symvers
	-rm -rf $(DD_DIR)/modules.order
	-rm -rf $(DD_DIR)/.led*
	-rm -rf $(DD_DIR)/.tmp*

-include $(IF_DEPS) $(TT_DEPS)

