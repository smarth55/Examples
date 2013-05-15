TEMPLATEROOT = /l/arm/STM32-Template

# additional compilation flags

CFLAGS += -g -I ../ff9/src/ff.h
ASFLAGS += -g
LDLIBS += -lm

# project files



OBJS= $(STARTUP) main.o
OBJS+= ff.o mmcbb.o 
OBJS+= stm32f10x_gpio.o stm32f10x_rcc.o 
OBJS+= stm32f10x_spi.o 

include $(TEMPLATEROOT)/Makefile.common