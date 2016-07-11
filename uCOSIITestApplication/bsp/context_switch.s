/*********************************************************************************************************
                                               uC/OS-II
                                         The Real-Time Kernel


                             (c) Copyright 1992-2007, Micrium, Weston, FL
                                          All Rights Reserved

                                           Generic ARM Port

 File      : context_switch.s  (originally OS_CPU_A.ASM)
 Version   : V1.82
 By        : Jean J. Labrosse
             Jean-Denis Hatier

 For       : ARM7 or ARM9
 Mode      : ARM or Thumb
 Toolchain : IAR's EWARM V4.11a and higher

 Changes   : JDH

********************************************************************************************************/


/********************************************************************************************************
                                           PUBLIC FUNCTIONS
*********************************************************************************************************/

/* External references. */
.extern    OSRunning
.extern    OSPrioCur
.extern    OSPrioHighRdy
.extern    OSTCBCur
.extern    OSTCBHighRdy
.extern    OSIntNesting
.extern    OSIntExit
.extern    OSTaskSwHook

/* Functions declared in this file. */
/*.global    OS_CPU_SR_Save */
/*.global    OS_CPU_SR_Restore */
.global    OSStartHighRdy
.global    OSCtxSw
.global    OSIntCtxSw



/*********************************************************************************************************
                                                EQUATES
*********************************************************************************************************/

.set OS_CPU_ARM_CONTROL_INT_DIS,        0xC0                     /* Disable both FIQ and IRQ. */
.set OS_CPU_ARM_CONTROL_FIQ_DIS,        0x40                     /* Disable FIQ. */
.set OS_CPU_ARM_CONTROL_IRQ_DIS,        0x80                     /* Disable IRQ. */
.set OS_CPU_ARM_CONTROL_THUMB,          0x20                     /* Set THUMB mode. */
.set OS_CPU_ARM_CONTROL_ARM,            0x00                     /* Set ARM mode. */

.set OS_CPU_ARM_MODE_MASK,              0x1F
.set OS_CPU_ARM_MODE_USR,               0x10
.set OS_CPU_ARM_MODE_FIQ,               0x11
.set OS_CPU_ARM_MODE_IRQ,               0x12
.set OS_CPU_ARM_MODE_SVC,               0x13
.set OS_CPU_ARM_MODE_ABT,               0x17
.set OS_CPU_ARM_MODE_UND,               0x1B
.set OS_CPU_ARM_MODE_SYS,               0x1F

.set OS_CPU_ARM_EXCEPT_RESET,           0x00
.set OS_CPU_ARM_EXCEPT_UNDEF_INSTR,     0x01
.set OS_CPU_ARM_EXCEPT_SWI,             0x02
.set OS_CPU_ARM_EXCEPT_PREFETCH_ABORT,  0x03
.set OS_CPU_ARM_EXCEPT_DATA_ABORT,      0x04
.set OS_CPU_ARM_EXCEPT_ADDR_ABORT,      0x05
.set OS_CPU_ARM_EXCEPT_IRQ,             0x06
.set OS_CPU_ARM_EXCEPT_FIQ,             0x07

/*********************************************************************************************************
                                      CODE GENERATION DIRECTIVES
*********************************************************************************************************/

.text
.arm

/*
*********************************************************************************************************
                                           START MULTITASKING
                                       void OSStartHighRdy(void)

 Note(s) : 1) OSStartHighRdy() MUST:
              a) Call OSTaskSwHook() then,
              b) Set OSRunning to TRUE,
              c) Switch to the highest priority task.
                   1. SP = OSTCBHighRdy->OSTCBStkPtr
                   2. Pop context for task

*********************************************************************************************************
*/
OSStartHighRdy:
                                                                /* Change to SVC mode. */
    MSR     CPSR_c, #(OS_CPU_ARM_CONTROL_INT_DIS | OS_CPU_ARM_MODE_SVC)

    LDR     R0,=OSTaskSwHook                                    /* Call OSTaskSwHook() */
    MOV     LR, PC
    BX      R0

    LDR     R0,=OSRunning                                       /* Set OSRunning = TRUE */
    MOV     R1, #1
    STRB    R1, [R0]

                                                                /* SWITCH TO HIGHEST PRIORITY TASK: */
    LDR     R0, =OSTCBHighRdy                                   /*  Get highest priority task TCB address, */
                                                                /*  R0 now has a pointer to a Task Control Block
                                                                    The first value in a TCB is a pointer to the task's stack.  */

    LDR     R0, [R0]                                            /*  Get stack pointer, */
                                                                /*  R0 now has the pointer to the stack
                                                                    deferencing it gives the address of stack */

    LDR     SP, [R0]                                            /*  Switch to the new stack, */
                                                                /*  Load the stack address into SP */

    LDR     R0, [SP], #4                                        /*  Pop new task's CPSR, */
                                                                /*  First value on the stack is the task's CPSR.
                                                                    Read the CPSR into R0.
                                                                    Set the current mode's SPSR to the task's CPSR.  */
    MSR     SPSR_cxsf, R0

    LDMFD   SP!, {R0-R12, LR, PC}^                              /*  Pop new task's context */
                                                                /*  Load registers from the stack
                                                                    The last value on the stack is the task address.
                                                                    The task address is used to set the PC.
                                                                    The ^ sets CPSR with the task's CPSR which was in SPSR. */


/*
*********************************************************************************************************
                         PERFORM A CONTEXT SWITCH (From task level) - OSCtxSw()

 Note(s) : 1) OSCtxSw() is called in SVC mode with BOTH FIQ and IRQ interrupts DISABLED.

           2) The pseudo-code for OSCtxSw() is:
              a) Save the current task's context onto the current task's stack,
              b) OSTCBCur->OSTCBStkPtr = SP
              c) Call OSTaskSwHook()
              d) Set OSPrioCur = OSPrioHighRdy
              e) set OSTCBCur  = OSTCBHighRdy
              f) set SP        = OSTCBHighRdy->OSTCBStkPtr
              g) Restore the new task's context from the new task's stack,
              h) Return to new task's code.

           3) Upon entry:
              OSTCBCur      points to the OS_TCB of the task to suspend,
              OSTCBHighRdy  points to the OS_TCB of the task to resume.

   This function is #defined to OS_TASK_SW() in the C code.

*********************************************************************************************************
*/
OSCtxSw:
    /* SAVE CURRENT TASK'S CONTEXT: */
    		//  Push return address
	STMFD	sp!, {lr}
    		//  Push a value for LR slot.
	STMFD	sp!, {lr}
    		//  Push registers
	STMFD	sp!, {r0-r12}
    		//  Get current CPSR
	MRS		r0, cpsr
    		//  Push current CPSR
    STMFD	sp!, {r0}

    /* Set OSTCBCur->OSTCBStkPtr = SP */
    		// Get the current TCB address
	LDR     r0,=OSTCBCur
    		// Dereference TCB address to get OSTCBStkPtr
    LDR		r1, [r0]
    		// Store SP in OSTCBStkPtr
	STR		sp, [r1]
    /* Call OSTaskSwHook() */
	LDR     r0,=OSTaskSwHook
    MOV     lr, pc
	BX      r0

    /* Set OSPrioCur = OSPrioHighRdy */
	LDR     r0,=OSPrioCur
    LDR     r1,=OSPrioHighRdy
    LDRB    r2, [r1]
    STRB    r2, [r0]
    /* Set OSTCBCur = OSTCBHighRdy */
	LDR     r0,=OSTCBCur
    LDR     r1,=OSTCBHighRdy
    LDR     r2, [r1]
    STR     r2, [r0]
    /* Set SP = OSTCBHighRdy->OSTCBStkPtr */
	LDR		sp, [r2]
    /* RESTORE NEW TASK'S CONTEXT: */
    /*    Pop new task's CPSR, */
	LDMFD   sp!, {r0}
    MSR     spsr_cxsf, r0
    /*    Pop new task's context. */
	LDMFD   sp!, {r0-r12, lr, pc}^
/*
*********************************************************************************************************
                     PERFORM A CONTEXT SWITCH (From interrupt level) - OSIntCtxSw()

 Note(s) : 1) OSIntCtxSw() is called in SVC mode with BOTH FIQ and IRQ interrupts DISABLED.

           2) The pseudo-code for OSCtxSw() is:
              a) Call OSTaskSwHook()
              b) Set OSPrioCur = OSPrioHighRdy
              c) Set OSTCBCur  = OSTCBHighRdy
              d) Set SP        = OSTCBHighRdy->OSTCBStkPtr
              e) Restore the new task's context from the new task's stack,
              f) Return to new task's code.

           3) Upon entry:
              OSTCBCur      points to the OS_TCB of the task to suspend,
              OSTCBHighRdy  points to the OS_TCB of the task to resume.
*********************************************************************************************************
*/
OSIntCtxSw:
    LDR     R0,=OSTaskSwHook                                    /* Call OSTaskSwHook() */
    MOV     LR, PC
    BX      R0

    LDR     R0,=OSPrioCur                                       /* Set OSPrioCur = OSPrioHighRdy */
    LDR     R1,=OSPrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0,=OSTCBCur                                        /* Set OSTCBCur = OSTCBHighRdy */
    LDR     R1,=OSTCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     SP, [R2]                                            /* Set SP = OSTCBHighRdy->OSTCBStkPtr */

                                                                /* RESTORE NEW TASK'S CONTEXT: */
    LDMFD   SP!, {R0}                                           /*    Pop new task's CPSR, */
    MSR     SPSR_cxsf, R0

    LDMFD   SP!, {R0-R12, LR, PC}^                              /*    Pop new task's context. */


/*    END*/
.end

