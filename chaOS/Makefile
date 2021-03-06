# changing these (and of course adding CPU-specific ld and header files) allows recompilation for
# various processors -- theoretically any ARM should work, but I have not tested anything other
# than my STM32F0 board
CPUFAMILY = cortex-m0
CPU       = stm32f0

MAIN      = main.elf
LDSCRIPT  = devices/$(CPU).ld

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
SIZE=arm-none-eabi-size

CFLAGS  = -std=c11 -lm -W -Wall -Wextra -pedantic
CFLAGS += -mcpu=$(CPUFAMILY) -mthumb -ffreestanding
CFLAGS += -DCPUFAMILY=$(CPUFAMILY) -DCPU=$(CPU) -include "devices/$(CPU).h"
CFLAGS += -O2 -ffunction-sections -fdata-sections
CFLAGS += -I. -I../cslibc/inc
DEBUG_CFLAGS = -DDEBUG -g3 -O0

LDFLAGS  = -T$(LDSCRIPT) -nostdlib -nodefaultlibs -nostartupfiles
LDFLAGS += --gc-sections

SRCS    = $(shell find -name '*.c' -not -name '*$(ISR_VECTOR_FN).c')
OBJS    = $(SRCS:.c=.o)
LIBSRCS = $(shell find ../cslibc/ -name '*.c')
LIBOBJS = $(LIBSRCS:.c=.o)
ISR_VECTOR_FN = -isr_vector

# --------------------------------------------------------

ifeq ($(NODEBUG),)
	CFLAGS += $(DEBUG_CFLAGS)
endif

# --------------------------------------------------------

default: $(MAIN)

$(MAIN): $(OBJS) $(LIBOBJS) devices/$(CPU)$(ISR_VECTOR_FN).o
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBOBJS) devices/$(CPU)$(ISR_VECTOR_FN).o
	$(SIZE) $(MAIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@

gdb: $(MAIN)
	arm-none-eabi-gdb --command=.gdb-startup $(MAIN)

.PHONY: clean

clean:
	find . -name '*.[od]' -exec rm -f '{}' \;
	rm -f *.elf
