CFLAGS := -g -std=c99 -Wall -Wextra -Wpedantic -m32 -O1 -ffreestanding -fasm
QEMU := qemu-system-i386 -serial mon:stdio
KERN := kern0
BOOT := -kernel $(KERN)

kern0: boot.o kern0.o
	ld -m elf_i386 -Ttext 0x100000 --entry comienzo $^ -o $@
	# Verificar imagen Multiboot v1.
	grub-file --is-x86-multiboot $@

%.o: %.S
	$(CC) $(CFLAGS) -c $<

qemu: $(KERN)
	$(QEMU) $(BOOT)

qemu-gdb: $(KERN)
	$(QEMU) -kernel kern0 -S -gdb tcp:127.0.0.1:7508 $(BOOT)

gdb:
	gdb -q -s kern0 -n -ex 'target remote 127.0.0.1:7508'

clean:
	rm -f kern0 *.o core

.PHONY: qemu qemu-gdb gdb clean
