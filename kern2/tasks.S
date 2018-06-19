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
