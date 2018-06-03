#define VGABUF ((volatile char *) 0xb8000)
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 25
#include <stdint.h>

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

void comienzo(void) {
	vga_write("Hello World!", 0, 48);

    while (1)
        asm("hlt");
}
