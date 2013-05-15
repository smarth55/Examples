TEMPLATEROOT = /l/arm/STM32-Template

# compilation flags for gdb

CFLAGS  += -g -I ff9/src 
ASFLAGS += -g 
LDLIBS += -lm

# object files

vpath %.c ff9/src
vpath %.c ff9/src/option

OBJS=  $(STARTUP) main.o
OBJS += stm32f10x_gpio.o stm32f10x_rcc.o stm32f10x_spi.o stm32f10x_dma.o stm32f10x_i2c.o stm32f10x_dac.o stm32f10x_tim.o
OBJS += spi.o ff.o mmcbb.o misc.o core_cm3.o ST7735.o imgnsnd.o I2C.o eeprom.o audio.o

# include common make file

include $(TEMPLATEROOT)/Makefile.common


