#include "decls.h"

#define SHIFT_CODE '^'

// static unsigned ticks;
//
// void timer() {
//     if (++ticks == 15) {
//         vga_write("Transcurrieron 15 ticks", 20, 0x07);
//     }
// }

/**
 * Handler para el timer (IRQ0). Escribe un carácter cada segundo.
 */
static const uint8_t hz_ratio = 18;  // Default IRQ0 freq (18.222 Hz).

void timer() {
    static char chars[81];
    static unsigned ticks;
    static int8_t line = 20;
    static uint8_t idx = 0;

    if (++ticks % hz_ratio == 0) {
        chars[idx] = '.';
        chars[++idx] = '\0';
        vga_write(chars, line, 0x07);
    }

    if (idx >= sizeof(chars)) {
        line++;
        idx = 0;
    }
}

/**
 * Mapa de "scancodes" a caracteres ASCII en un teclado QWERTY.
 */
static char klayout[128] = {
    0,   0,   '1', '2', '3', '4', '5', '6', '7', '8',             // 0-9
    '9', '0', 0,   0,   0,   0,   'q', 'w', 'e', 'r',             // 10-19
    't', 'y', 'u', 'i', 'o', 'p', 0,   0,   0,   0,               // 20-29
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0,   0,          // 30-40
    0, SHIFT_CODE,   0,   'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 0, SHIFT_CODE};  // 41-54

static const uint8_t KBD_PORT = 0x60;

/**
 * Handler para el teclado (IRQ1).
 *
 * Imprime la letra correspondiente por pantalla.
 */
void keyboard() {
    uint8_t code;
    static char chars[81];
    static uint8_t idx = 0;
	static uint8_t is_shift_pressed = 0;

    asm volatile("inb %1,%0" : "=a"(code) : "n"(KBD_PORT));

	if (code & 0x80) {
		code = code & 0x7F; //Tiro el bit mas significativo
		if (klayout[code] == SHIFT_CODE)
			is_shift_pressed = 0;
	} else {
		if (code >= sizeof(klayout) || !klayout[code])
	        return;

		if (klayout[code] == SHIFT_CODE) {
			is_shift_pressed = 1;
			return;
		}

	    if (idx == 80) {
			code = code;
	        while (idx--)
	            chars[idx] = ' ';
	    }

		chars[idx++] = klayout[code];
		if (is_shift_pressed)
	    	chars[idx - 1] -= 32;
	    vga_write(chars, 19, 0x0A);
	}
}
