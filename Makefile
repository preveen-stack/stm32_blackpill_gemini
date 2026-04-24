CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -g -Wall
LDFLAGS = -T stm32f411.ld --specs=nano.specs --specs=nosys.specs

all: blink.bin

blink.elf: main.c startup.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

blink.bin: blink.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.elf *.bin

# Flash using ST-Link
flash-stlink: blink.bin
	st-flash write blink.bin 0x08000000

# Flash using USB DFU (Blackpill BOOT0 button method)
# Note: You might need sudo on Linux; on macOS, it usually works.
flash-dfu: blink.bin
	dfu-util -a 0 -s 0x08000000:leave -D blink.bin

.PHONY: all clean flash-stlink flash-dfu
