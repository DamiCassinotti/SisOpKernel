CFLAGS := -g -std=c99 -Wall -Wextra -Wpedantic -m32 -O1 -ffreestanding -fasm
QEMU := qemu-system-i386 -serial mon:stdio
KERN := kern2
BOOT := -kernel $(KERN) $(QEMU_EXTRA)

kern2: boot.o kern2.o decls.o lib/string.o
	ld -m elf_i386 -Ttext 0x100000 --entry _start $^ -o $@
	# Verificar imagen Multiboot v1.
	grub-file --is-x86-multiboot $@

%.o: %.S
	$(CC) $(CFLAGS) -c $<

qemu: $(KERN)
	$(QEMU) $(BOOT)

qemu-gdb: $(KERN)
	$(QEMU) -kernel $(KERN) -S -gdb tcp:127.0.0.1:7508 $(BOOT)

gdb:
	gdb -q -s $(KERN) -n -ex 'target remote 127.0.0.1:7508'

clean:
	rm -f $(KERN) *.o core

.PHONY: qemu qemu-gdb gdb clean
