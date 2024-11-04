# Source files and headers
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

# Object files derived from source files
OBJ = ${C_SOURCES:.c=.o}

# Compiler and linker
CC = gcc
LD = ld
GDB = gdb

# Compiler flags
CFLAGS = -g -ffreestanding -m32 -I/usr/include  # Include path for headers # Added -m32 for 32-bit compilation

# Default target to create the OS image
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# Create kernel binary without ELF format
kernel.bin: boot/kernel_entry.o ${OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# For debugging purposes, create an ELF file
kernel.elf: boot/kernel_entry.o ${OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^

# Run the OS image using QEMU
run: os-image.bin
	qemu-system-x86_64 -drive format=raw,file=os-image.bin

# Debugging with GDB
debug: os-image.bin kernel.elf
	qemu-system-x86_64 -drive format=raw,file=os-image.bin &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for building object files
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm $< -f elf32 -o $@  # Changed to elf32 for 32-bit output

%.bin: %.asm
	nasm $< -f bin -o $@

# Clean up generated files
clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o

# Ensure proper error handling
errors:
	@echo "Check for errors in the build process."
	@if [ -f os-image.bin ]; then echo "Build successful!"; else echo "Build failed!"; fi

