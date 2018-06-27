#include "decls.h"

#define VGABUF ((volatile char *) 0xb8000)
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 25

void vga_write(const char *s, int8_t linea, uint8_t color) {
	volatile char *buf = VGABUF;
	if (linea >= 0)
		buf += SCREEN_WIDTH*linea;
	else
		buf += (SCREEN_HEIGHT + linea)*SCREEN_WIDTH;
	while(*s != 0) {
		*buf++ = *s++;
		*buf++ = color;
	}
}

void __attribute__((regparm(2)))
vga_write_cyan(const char *s, int8_t linea) {
    vga_write(s, linea, 0xB0);
}

// Escribe en ‘s’ el valor de ‘val’ en base 10 si su anchura
// es menor que ‘bufsize’. En ese caso devuelve true, caso de
// no haber espacio suficiente no hace nada y devuelve false.
static size_t int_width(uint64_t val) {
    size_t width = 0;
    while(val > 0) {
        width++;
        val /= 10;
    }
	return width;
}

bool fmt_int(uint64_t val, char *s, size_t bufsize) {
    size_t l = int_width(val);

    if (l >= bufsize)
        return false;

    s += l;
	s[0] = '\0';
    while(val > 0) {
        s -=1 ;
        s[0] = (char) ((val % 10) + 48);
        val /= 10;
	}
    return true;
}
