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

	movl 20(%esp), %edx
    movl %esp, %eax
    movl (%edx), %esp
	movl %eax, (%edx)

	pop %esi
	pop %edi
	pop %ebx
	pop %ebp
	ret
