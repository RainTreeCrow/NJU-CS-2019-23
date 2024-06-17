#include "x86.h"
#include "device.h"

extern TSS tss;
extern ProcessTable pcb[MAX_PCB_NUM];
extern int current;

extern int displayRow;
extern int displayCol;

void GProtectFaultHandle(struct StackFrame *sf);
void timerHandle(struct StackFrame *sf);
void syscallHandle(struct StackFrame *sf);

void syscallWrite(struct StackFrame *sf);
void syscallPrint(struct StackFrame *sf);
void syscallFork(struct StackFrame *sf);
void syscallSleep(struct StackFrame *sf);
void syscallExit(struct StackFrame *sf);

void irqHandle(struct StackFrame *sf) { // pointer sf = esp
	/* Reassign segment register */
	asm volatile("movw %%ax, %%ds"::"a"(KSEL(SEG_KDATA)));
	/*TODO Save esp to stackTop */
	uint32_t tmpStackTop = pcb[current].stackTop;
    pcb[current].prevStackTop = pcb[current].stackTop;
    pcb[current].stackTop = (uint32_t)sf;

	switch(sf->irq) {
		case -1:
			break;
		case 0xd:
			GProtectFaultHandle(sf);
			break;
		case 0x20:
			timerHandle(sf);
			break;
		case 0x80:
			syscallHandle(sf);
			break;
		default:assert(0);
	}
	/*TODO Recover stackTop */
	pcb[current].stackTop = tmpStackTop;
}

void GProtectFaultHandle(struct StackFrame *sf) {
	assert(0);
	return;
}

void timerHandle(struct StackFrame *sf) {
    for (int i = 0; i < MAX_PCB_NUM; i++) {
        if (pcb[i].state == STATE_BLOCKED) {
            pcb[i].sleepTime--;
            if (pcb[i].sleepTime == 0)
                pcb[i].state = STATE_RUNNABLE;
        }
    }
    pcb[current].timeCount++;
    if (pcb[current].timeCount > MAX_TIME_COUNT) {
        pcb[current].state = STATE_RUNNABLE;
        pcb[current].timeCount = 0;
        for (int i = (current + 1) % MAX_PCB_NUM; i != current;
            i = (i + 1) % MAX_PCB_NUM) {
            if (pcb[i].state == STATE_RUNNABLE) {
                current = i;
                break;
            }
        }
        pcb[current].state = STATE_RUNNING;
        pcb[current].timeCount = 0;
    }
    uint32_t tmpStackTop = pcb[current].stackTop;
    pcb[current].stackTop = pcb[current].prevStackTop;
    tss.esp0 = (uint32_t)&(pcb[current].stackTop);
    asm volatile("movl %0, %%esp"::"m"(tmpStackTop));
        // switch kernel stack
    asm volatile("popl %gs");
    asm volatile("popl %fs");
    asm volatile("popl %es");
    asm volatile("popl %ds");
    asm volatile("popal");
    asm volatile("addl $8, %esp");
    asm volatile("iret");
    return;
}

void syscallHandle(struct StackFrame *sf) {
	switch(sf->eax) { // syscall number
		case 0:
			syscallWrite(sf);
			break; // for SYS_WRITE
		/*TODO Add Fork,Sleep... */
        case 1:
            syscallFork(sf);
            break; // for SYS_FORK
        case 3:
            syscallSleep(sf);
            break; // for SYS_SLEEP
        case 4:
            syscallExit(sf);
            break; // for SYS_EXIT
		default:break;
	}
}

void syscallWrite(struct StackFrame *sf) {
	switch(sf->ecx) { // file descriptor
		case 0:
			syscallPrint(sf);
			break; // for STD_OUT
		default:break;
	}
}

void syscallPrint(struct StackFrame *sf) {
	int sel = sf->ds; // segment selector for user data
	char *str = (char*)sf->edx;
	int size = sf->ebx;
	int i = 0;
	int pos = 0;
	char character = 0;
	uint16_t data = 0;
	asm volatile("movw %0, %%es"::"m"(sel));
	for (i = 0; i < size; i++) {
		asm volatile("movb %%es:(%1), %0":"=r"(character):"r"(str+i));
		if(character == '\n') {
			displayRow++;
			displayCol=0;
			if(displayRow==25){
				displayRow=24;
				displayCol=0;
				scrollScreen();
			}
		}
		else {
			data = character | (0x0c << 8);
			pos = (80*displayRow+displayCol)*2;
			asm volatile("movw %0, (%1)"::"r"(data),"r"(pos+0xb8000));
			displayCol++;
			if(displayCol==80){
				displayRow++;
				displayCol=0;
				if(displayRow==25){
					displayRow=24;
					displayCol=0;
					scrollScreen();
				}
			}
		}
		//asm volatile("int $0x20"); //XXX Testing irqTimer during syscall
		//asm volatile("int $0x20":::"memory"); //XXX Testing irqTimer during syscall
	}
	
	updateCursor(displayRow, displayCol);
	//TODO take care of return value
	return;
}

void syscallFork(struct StackFrame *sf) {
    int newPcbIndex = -1;
    for (int i = 0; i < MAX_PCB_NUM; i++) {
        if (pcb[i].state == STATE_DEAD) {
            newPcbIndex = i;
            break;
        }
    }
    if (newPcbIndex != -1) {
        enableInterrupt();
        for (int j = 0; j < 0x100000; j++)
            *(uint8_t*)(j + (newPcbIndex + 1) * 0x100000) =
                *(uint8_t*)(j + (current + 1) * 0x100000);
        disableInterrupt();
        for (int j = 0; j < sizeof(ProcessTable); j++)
        	*((uint8_t*)(&pcb[newPcbIndex]) + j) =
        		*((uint8_t*)(&pcb[current]) + j);
        pcb[newPcbIndex].stackTop = (uint32_t)&(pcb[newPcbIndex].regs);
        pcb[newPcbIndex].prevStackTop = (uint32_t)&(pcb[newPcbIndex].stackTop);
        pcb[newPcbIndex].state = STATE_RUNNABLE;
        pcb[newPcbIndex].timeCount = 0;
        pcb[newPcbIndex].sleepTime = 0;
        pcb[newPcbIndex].pid = newPcbIndex;
        pcb[newPcbIndex].regs.ss = USEL(2 + 2 * newPcbIndex);
        pcb[newPcbIndex].regs.cs = USEL(1 + 2 * newPcbIndex);
        pcb[newPcbIndex].regs.ds = USEL(2 + 2 * newPcbIndex);
        pcb[newPcbIndex].regs.es = USEL(2 + 2 * newPcbIndex);
        pcb[newPcbIndex].regs.fs = USEL(2 + 2 * newPcbIndex);
        pcb[newPcbIndex].regs.gs = USEL(2 + 2 * newPcbIndex);
        pcb[newPcbIndex].regs.eax = 0;
        pcb[current].regs.eax = newPcbIndex;
    }
    else
        pcb[current].regs.eax = -1;
    putChar('F');
    return;
}

void syscallSleep(struct StackFrame *sf) {
    pcb[current].state = STATE_BLOCKED;
    pcb[current].sleepTime = sf->ecx;
    pcb[current].timeCount = MAX_TIME_COUNT;
    asm volatile("int $0x20");
    putChar('S');
    return;
}

void syscallExit(struct StackFrame *sf) {
    pcb[current].state = STATE_DEAD;
    asm volatile("int $0x20");
    putChar('E');
    return;
}

