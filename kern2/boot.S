#include "multiboot.h"

#define KSTACK_SIZE 8192

.align 4
multiboot:
    .long MULTIBOOT_HEADER_MAGIC
    .long 0
    .long -(MULTIBOOT_HEADER_MAGIC)

.globl _start
_start:
    // Paso 1: Configurar el stack antes de llamar a kmain.
    movl $0, %ebp
    movl $kstack, %esp
    push %ebp

    // Paso 2: pasar la información multiboot a kmain. Si el
    // kernel no arrancó vía Multiboot, se debe pasar NULL.
    //
    // Usar una instrucción de comparación (TEST o CMP) para
    // comparar con MULTIBOOT_BOOTLOADER_MAGIC, pero no usar
    // un salto a continuación, sino una instrucción CMOVcc
    // (copia condicional).
    // ...
	cmp %eax, MULTIBOOT_BOOTLOADER_MAGIC
	movl 	%ecx, 	MULTIBOOT_INFO_MEMORY
	or		%ecx,	MULTIBOOT_INFO_BOOTDEV
	or		%ecx,	MULTIBOOT_INFO_CMDLINE
	or		%ecx,	MULTIBOOT_INFO_MODS
	or		%ecx,	MULTIBOOT_INFO_AOUT_SYMS
	or		%ecx,	MULTIBOOT_INFO_ELF_SHDR
	or		%ecx,	MULTIBOOT_INFO_MEM_MAP
	or		%ecx,	MULTIBOOT_INFO_DRIVE_INFO
	or		%ecx,	MULTIBOOT_INFO_CONFIG_TABLE
	or		%ecx,	MULTIBOOT_INFO_BOOT_LOADER_NAME
	or		%ecx,	MULTIBOOT_INFO_APM_TABLE
	or		%ecx,	MULTIBOOT_INFO_VIDEO_INFO
	CMOVE 	%ebx,	%ecx
	push 	%ebx

    call kmain
halt:
    hlt
    jmp halt

.data
.p2align 12
kstack:
    .space KSTACK_SIZE
