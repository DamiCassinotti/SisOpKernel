#include "decls.h"
#include "sched.h"

#define MAX_TASK 10

static struct Task Tasks[MAX_TASK];
static struct Task *current;

void sched_init() {
	current = &Tasks[0];
    current->status = RUNNING;
}

void spawn(void (*entry)(void)) {
    for (int i = 0; i < MAX_TASK; i++) {
		struct Task *task = &Tasks[i];
		if (task->status == FREE) {
			task->status = READY;
			uint8_t* stack = &(task->stack[4096]);
			size_t size = sizeof(struct TaskFrame);
    		stack -= size;
    		task->frame = (struct TaskFrame *) stack;
			task->frame->edi = 0;
		    task->frame->esi = 0;
		    task->frame->ebp = 0;
		    task->frame->esp = 0;
		    task->frame->ebx = 0;
		    task->frame->edx = 0;
		    task->frame->ecx = 0;
		    task->frame->eax = 0;
		    task->frame->padding = 0;
			task->frame->eip = (uint32_t) entry;
			task->frame->eflags |= 0x200;
			task->frame->cs = 8;
			return;
		}
	}
}

void sched(struct TaskFrame *tf) {
	int i = 0;
	while (i < MAX_TASK && Tasks[i].status != RUNNING)
		i++;
	if (i == MAX_TASK)
		return;
	current->status = READY;
	current->frame = tf;
	i++;
	// No genera ciclo infinito porque por lo menos un task está en running
	while (Tasks[i].status != READY) {
		i++;
		if (i == MAX_TASK)
			i = 0;
	}
	current = &Tasks[i];
	current->status = RUNNING;
	asm("movl %0, %%esp\n"
	    "popa\n"
	    "iret\n"
	    :
	    : "g"(current->frame)
	    : "memory");
}
