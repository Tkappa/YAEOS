#ifndef SCHEDULER
#define SCHEDULER
#include <pcb.h>

/*
 * Stops the running process and puts it in the readyQueue
 * Loads the first process in the ready queue and runs it
 */
void dispatch(state_t *to_save);

/* Gets called when there are no more ready processes and handles all possibilities*/
void noMoreReadyPcbs();

/* Increases the priority of all processes in the queue pointed by p by 1 */
void increasePriority(pcb_t *p, void *arg);

/* Suspends the running process and returns its address
 * Returns NULL if no processes are running
 * WARNING a dispatch should be called after this function, otherwise the processor will continue to
 * execute the previous code but the running process pointer won't point to the right process
 */
pcb_t *suspend();

/*
    Restores the running process, given the old area, adjusting the pc as necessary
 */
void restoreRunningProcess(state_t *oldarea);

/*
    Inserts a new process in the ready queue. If the new process has a greater priority than the
    current running process, the currently running process is suspendedand the state of the process,
    passed in the variable to_save, is saved in its pcb. This takes into account that if the cause
    of the interrupt was a device the pc register must be decremented by 4
    Returns 0 on successful insertion, -1 on failure
 */
int insertInReady(pcb_t *p, state_t *to_save);


/*
    This facility updates the time spent for the current running process in user mode.
    Substract the time gave from parameters (Hi and Low part of TOD)
    to the last time marked (with freezeLastTime) in the process, 
    and then adds it to the total user time.
*/
void userTimeAccounting(unsigned int TOD_Hi, unsigned int TOD_Low);

/*
    This facility updates the time spent for the argument-passed process in kernel mode.
    Substract the time gave from parameters (Hi and Low part of TOD)
    to the current TOD
    and then adds it to the total kernel time.

    If the process passed by argument is NULL nothing is updated.
*/
void kernelTimeAccounting(unsigned int TOD_Hi, unsigned int TOD_Low, pcb_t* process);


/*
    This facility freezes the lasttime variable to the current TOD.
    It is useful for calculating the user time.
*/
void freezeLastTime(pcb_t *p);

#endif // SCHEDULER
