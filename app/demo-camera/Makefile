#
# This file is part of the Rainbow Pi project.
# Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
# This work is licensed under the MIT license, see the file LICENSE for details.
#
# Makefile
#

#
# Please visit our E-Shop at https://mvdevice.taobao.com/
#

CROSS_COMPILE    ?= arm-buildroot-linux-uclibcgnueabihf-

CPU = cortex-a7
FPU = fpv4-sp-d16

AS                = $(CROSS_COMPILE)as
LD                = $(CROSS_COMPILE)ld
CC                = $(CROSS_COMPILE)gcc
CXX               = $(CROSS_COMPILE)g++
CPP               = $(CC) -E
AR                = $(CROSS_COMPILE)ar
NM                = $(CROSS_COMPILE)nm
STRIP             = $(CROSS_COMPILE)strip
OBJCOPY           = $(CROSS_COMPILE)objcopy
OBJDUMP           = $(CROSS_COMPILE)objdump
RANLIB            = $(CROSS_COMPILE)ranlib
SIZE              = $(CROSS_COMPILE)size

TOP_DIR           = $(shell pwd)

CFLAGS_inc_path   += -I$(TOP_DIR)

# CFLAGS_inc_path   += -I$(TOP_DIR)external/jpeg-9a

# for H.264 hardware codec
CFLAGS_inc_path   += -I$(TOP_DIR)/../../prebuilt/include/cedar

CFLAGS += -std=gnu99 -mthumb -mabi=aapcs-linux -mlittle-endian
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -mcpu=$(CPU) -mtune=$(CPU) -mfpu=$(FPU) -mfloat-abi=hard

SRC_HAL += v4l2dev.c fbdev.c lcd.c netdbg.c usbdbg.c imutil.c timeutil.c cvtcolor.c font_8x8.c
OBJ_HAL += $(patsubst %.c,%.o,$(SRC_HAL))

CFLAGS            += -O2 -ggdb3 -DNDEBUG
CFLAGS            += $(CFLAGS_inc_path)

EXAMPLES += demo-camera

all: $(EXAMPLES)

.PHONY: clean

demo-camera: demo-camera.o $(OBJ_HAL)
	$(CC) $(CFLAGS) demo-camera.o $(OBJ_HAL) -o $@ -Wl,--start-group -ljpeg -lyuv -lm -Wl,--end-group

clean:
	rm -f *~ *.o $(EXAMPLES)
