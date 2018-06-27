#ifndef KERN2_DECL_H
#define KERN2_DECL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct multiboot_info;
/*
// mbinfo.c (ejercicio opcional kern2-meminfo)
void print_mbinfo(const struct multiboot_info *mbi);*/

// funcs.S
__attribute__((regparm(3))) void vga_write2(const char *s,
                                            int8_t linea,
                                            uint8_t color);

// kern2.c
void two_stacks_c(void);

// stacks.S
void two_stacks(void);

// write.c
void vga_write(const char *s, int8_t linea, uint8_t color);
__attribute__((regparm(2))) void vga_write_cyan(const char *s, int8_t linea);
bool fmt_int(uint64_t val, char *s, size_t bufsize);

// tasks.S
void task_exec(uintptr_t entry, uintptr_t stack);
void task_swap(uintptr_t *esp);

// contador.c
void contador_run();

// interrupts.c
void idt_init(void);
void idt_install(uint8_t code, void (*handler)(void));
void irq_init(void);

// idt_entry.S
void divzero(void);
void breakpoint(void);
void ack_irq(void);
void timer_asm(void);
// void keyboard_asm(void);


// handlers.c
void timer(void);
// void keyboard(void);

#endif
