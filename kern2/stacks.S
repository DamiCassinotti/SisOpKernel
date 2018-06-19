#define USTACK_SIZE 4096

.data
        .align 4096
stack1:
        .space USTACK_SIZE
stack1_top:

        .p2align 12
stack2:
        .space USTACK_SIZE
stack2_top:

msg1:
        .asciz "vga_write() from stack1"
msg2:
        .asciz "vga_write() from stack2"

.text
.extern vga_write
.globl two_stacks
two_stacks:
        // Preámbulo estándar
        push %ebp
        movl %esp, %ebp

        // Registros para apuntar a stack1 y stack2.
        mov $stack1_top, %eax
        mov $stack2_top, %ebx   // Decidir qué registro usar.

        // Cargar argumentos a ambos stacks en paralelo. Ayuda:
        // usar offsets respecto a %eax ($stack1_top), y lo mismo
        // para el registro usado para stack2_top.
        movl $0x17, 8(%eax)
        movl $0x90, 8(%ebx)

        movl $12, 4(%eax)
        movl $13, 4(%ebx)

        movl $msg1, 0(%eax)
        movl $msg2, 0(%ebx)

        // Realizar primera llamada con stack1. Ayuda: usar LEA
        // con el mismo offset que los últimos MOV para calcular
        // la dirección deseada de ESP.
        leal 0(%eax), %esp
        call vga_write

        // Restaurar stack original. ¿Es %ebp suficiente?
        movl %ebp, %esp

        // Realizar segunda llamada con stack2.
        leal 0(%ebx), %esp
        call vga_write

        // Restaurar registros callee-saved, si se usaron.


        leave
        ret
