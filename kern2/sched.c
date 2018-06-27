#include "decls.h"
#include "sched.h"

#define MAX_TASK 10

static struct Task Tasks[MAX_TASK];
static struct Task *current;

void sched_init() {
	current = &Tasks[0];
    current->status = RUNNING;
	for (int i = 1; i < MAX_TASK; i++) {
		struct Task *task = &Tasks[i];
		task->status = FREE;
	}
}

void spawn(void (*entry)(void)) {
    for (int i = 0; i < MAX_TASK; i++) {
		struct Task *task = &Tasks[i];
		if (task->status == FREE) {
			task->status = READY;
			task->frame->edi = 0;
		    task->frame->esi = 0;
		    task->frame->ebp = 0;
		    task->frame->esp = 0;
		    task->frame->ebx = 0;
		    task->frame->edx = 0;
		    task->frame->ecx = 0;
		    task->frame->eax = 0;
		    task->frame->padding = 0;
			task->frame->eflags = 0x200;
		}
	}
}

void sched(struct TaskFrame *tf) {
    // ...
}
