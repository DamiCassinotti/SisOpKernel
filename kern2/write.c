#include "decls.h"

void __attribute__((regparm(2)))
vga_write_cyan(const char *s, int8_t linea) {
    vga_write(s, linea, 0xB0);
}
