#include "decls.h"

void print_mbinfo(const struct multiboot_info *mbi) {
	if (mbi->flags & (1<<2)) {
        char buf[256] = "cmdline: ";
        char *cmdline = (void *) mbi->cmdline;
		strlcat(buf, cmdline, sizeof buf);
        vga_write(buf, 9, 0x07);
    }

	if (mbi->flags & (1<<6)) {
		char mem[256] = "Physical memory: ";
		char tmp[64] = "";
		uint64_t total_mem = mbi->mem_upper - mbi->mem_lower;
		if (fmt_int((total_mem >> 10) + 1, tmp, sizeof tmp)) {
			strlcat(mem, tmp, sizeof mem);
			strlcat(mem, "MiB total", sizeof mem);
		}
		if (fmt_int(mbi->mem_lower, tmp, sizeof tmp)) {
			strlcat(mem, " (", sizeof mem);
			strlcat(mem, tmp, sizeof mem);
			strlcat(mem, "KiB base, ", sizeof mem);
		}
		if (fmt_int(mbi->mem_upper, tmp, sizeof tmp)) {
			strlcat(mem, tmp, sizeof mem);
			strlcat(mem, "KiB extended)", sizeof mem);
		}
		vga_write(mem, 10, 0x07);
	}
}
