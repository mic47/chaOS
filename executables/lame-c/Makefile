MAIN    = lame-c.elf
TO_ADDR = 0x8008000

CPU       = cortex-m0
LDSCRIPT  = ../chaos-executable.ld

# TODO should I (make and) use `arm-chaos-eabi-*`?
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

CFLAGS = -mcpu=$(CPU) -mthumb -g -std=c11 -W -Wall -pedantic

LDFLAGS = -T$(LDSCRIPT) -nostdlib -nostartupfiles

# --------------------------------------------------------

default: $(MAIN)

$(MAIN): $(MAIN:.elf=.o)
	$(LD) $(LDFLAGS) -o $@ $<
	# $(OBJCOPY) --strip-all -R .ARM.attributes $@
	$(SIZE) $(MAIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

flash: $(MAIN)
	st-flash write $(MAIN) $(TO_ADDR)
