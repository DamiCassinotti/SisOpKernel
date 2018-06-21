.text
.globl task_exec
task_exec:
	push %ebp
	movl %esp, %ebp
	movl 12(%ebp), %esp
	call *8(%ebp)
	movl %ebp, %esp
	leave
	ret

.globl task_swap
task_swap:
	push %ebp
	push %ebx
	push %edi
	push %esi

	mov 20(%esp), %ecx
    mov %esp, $eax
    mov %ecx, %esp

	pop %esi
	pop %edi
	pop %ebx
	pop %ebp
	ret
