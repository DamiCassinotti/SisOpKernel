#include "decls.h"
#include "sched.h"

#define COUNTLEN 20
#define TICKS (1ULL << 15)
#define DELAY(x) (TICKS << (x))
#define USTACK_SIZE 4096

static volatile char *const VGABUF = (volatile void *) 0xb8000;

static uintptr_t esp;
static uint8_t stack1[USTACK_SIZE] __attribute__((aligned(4096)));
static uint8_t stack2[USTACK_SIZE] __attribute__((aligned(4096)));

static void exit() {
    uintptr_t tmp = esp;
	esp = 0;
    task_swap(&tmp);
}

static void yield() {
    if (esp)
        task_swap(&esp);
}

static void contador_yield(unsigned lim, uint8_t linea, char color) {
    char counter[COUNTLEN] = {'0'};  // ASCII digit counter (RTL).

    while (lim--) {
        char *c = &counter[COUNTLEN];
        volatile char *buf = VGABUF + 160 * linea + 2 * (80 - COUNTLEN);

        unsigned p = 0;
        unsigned long long i = 0;

        while (i++ < DELAY(6))  // Usar un entero menor si va demasiado lento.
            ;

        while (counter[p] == '9') {
            counter[p++] = '0';
        }

        if (!counter[p]++) {
            counter[p] = '1';
        }

        while (c-- > counter) {
            *buf++ = *c;
            *buf++ = color;
        }

        yield();
    }
}

void contador_run() {
	// Configurar stack1 y stack2 con los valores apropiados.
	uintptr_t *a = (uintptr_t *) &stack1[USTACK_SIZE];
	uintptr_t *b = (uintptr_t *) &stack2[USTACK_SIZE];

	*(--a) = 0x2F;
	*(--a) = 0;
	*(--a) = 100;

	*(--b) = 0x4F;
	*(--b) = 1;
	*(--b) = 85;
	*(--b) = (uintptr_t) exit;
	*(--b) = (uintptr_t) contador_yield;
	*(--b) = 0;
	*(--b) = 0;
	*(--b) = 0;
	*(--b) = 0;

	// Actualizar la variable estática ‘esp’ para que apunte
	// al del segundo contador.
	esp = (uintptr_t) b;

	// Lanzar el primer contador con task_exec.
	task_exec((uintptr_t) contador_yield, (uintptr_t) a);

    //contador_yield(1000, 0, 0x2F);
    //contador_yield(1000, 1, 0x4F);
}

static void contador1() {
    contador_yield(50000000, 2, 0x2F);
}

static void contador2() {
    contador_yield(50000000, 3, 0x6F);
}

static void contador3() {
    contador_yield(50000000, 4, 0x4F);
}

void contador_spawn() {
    spawn(contador1);
    spawn(contador2);
    spawn(contador3);
}
