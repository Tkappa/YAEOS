# **DOCUMENTATION AND DESIGN CHOICES FOR YAEOS PROJECT**

---

## PCB design 

Fields used in PCB:

>- **p_next**: Pointer for the next element of the list. 
>- **p_parent, p_first_child, p_sib**: Pointers for tree hierarchy of processes
>- **p_s**: State of CPU process fields.
>- **p_priority**: Process' priority. 
Scheduler can increase priority by ageing policy.
>- **old_priority**: We keep track of the birth's priority of the pcb. 
'p_priority' field contains the priority interactively modified by scheduler's 
ageing policy. When priority restore is needed, old_priority is used.
>- **p_semKey**: Process' semaphore pointer.
>- **waitingOnIo**: 1 if process is waigint for IO, 0 otherwise
>- **childSem**: Semaphore used for blocking process when is waiting for a 
child. This semaphore will be managed by the child.
>- **waitingForChild**: 1 if process is waiting for a child (so the child will 
unblock parent when it terminate), 0 otherwise.
>- **usertime**: Process' time spent in user mode
>- **kerneltime**: Process' time spent in kernel mode
>- **lasttime**: Last TOD marker. We use it for keep track of last
 activation/deactivation 
>- **wallclocktime**: Process' TOD when starting. Used for calculating total 
 wallclocktime
>- **sysbk_new, sysbk_old, tlb_new, tlb_old, pgmtrap_new, pgmtrap_old**: 
Per-trap handler

---

## Scheduler

---

## Interrupts

---

## Syscalls 

### SYS1: Create process

Tries to allocate a new process, if succesful configures it with the parameters 
and returns 0, else returns -1.

Parameters configurations consists in setting times, hierarchy, priorities, 
trap handlers. 

In the end puts the new process in ready queue