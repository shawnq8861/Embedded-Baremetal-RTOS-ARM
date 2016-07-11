/*

Filename      : exception_handler_asm.s

*/

/*******************************************************************************************************
*
*    Exception Handling
*
********************************************************************************************************/

.extern    OS_CPU_ExceptHndlr

/* Functions related to exception handling. */
.global  OS_CPU_ARM_ExceptIrqHndlr


.set OS_CPU_ARM_CONTROL_INT_DIS,        0xC0                     /* Disable both FIQ and IRQ. */
.set OS_CPU_ARM_MODE_MASK,              0x1F
.set OS_CPU_ARM_MODE_SVC,               0x13

.set OS_CPU_ARM_EXCEPT_IRQ,             0x06


.text

/*
********************************************************************************************************
                                  INTERRUPT REQUEST EXCEPTION HANDLER

 Register Usage:  R0     Exception Type
                  R1
                  R2
                  R3     Return PC
********************************************************************************************************
*/
OS_CPU_ARM_ExceptIrqHndlr:
    SUB     LR, LR, #4                                          /* LR offset to return from this exception: -4.*/
    STMFD   SP!, {R0-R12, LR}                                   /* Push working registers.*/
    MOV     R3, LR                                              /* Save link register.*/

    MOV     R0, #OS_CPU_ARM_EXCEPT_IRQ                          /* Set exception ID to OS_CPU_ARM_EXCEPT_IRQ.*/

    MRS     R1, SPSR                                            /* Save CPSR (i.e. exception's SPSR).*/

                                                                /* DETERMINE IF WE INTERRUPTED A TASK OR ANOTHER LOWER PRIORITY EXCEPTION:*/
                                                                /*   SPSR.Mode = SVC                :  task,*/
                                                                /*   SPSR.Mode = FIQ, IRQ, ABT, UND :  other exceptions,*/
    AND     R2, R1, #OS_CPU_ARM_MODE_MASK
    CMP     R2,     #OS_CPU_ARM_MODE_SVC

    BNE     OS_CPU_ARM_ExceptHndlr_BreakExcept                  /* Branch to handle interrupting exception, else drop through to handle interrupting task */

/*
********************************************************************************************************
                                  EXCEPTION HANDLER: TASK INTERRUPTED

 Register Usage:  R0     Exception Type
                  R1	 Exception's SPSR
                  R2	 Exception's CPSR
                  R3     Return PC
                  R4     Exception's SP
********************************************************************************************************
*/
OS_CPU_ARM_ExceptHndlr_BreakTask:
    MRS     R2, CPSR                                            /* Save exception's CPSR. */
    MOV     R4, SP                                              /* Save exception's stack pointer. */

                                                                /* Change to SVC mode & disable interruptions. */
    MSR     CPSR_c, #(OS_CPU_ARM_CONTROL_INT_DIS | OS_CPU_ARM_MODE_SVC)

                                                                /* SAVE TASK'S CONTEXT ONTO TASK'S STACK: */
    STMFD   SP!, {R3}                                           /*   Push task's PC, */
    STMFD   SP!, {LR}                                           /*   Push task's LR, */
    STMFD   SP!, {R5-R12}                                       /*   Push task's R5-R12, */
    LDMFD   R4!, {R5-R9}                                        /*   Move task's R0-R4 from exception stack to task's stack. */
    STMFD   SP!, {R5-R9}
    STMFD   SP!, {R1}                                           /*   Push task's CPSR (i.e. exception SPSR). */

                                                                /* if (OSRunning == 1) */
    LDR     R1,=OSRunning
    LDRB    R1, [R1]
    CMP     R1, #1
    BNE     OS_CPU_ARM_ExceptHndlr_BreakTask_1

                                                                /* HANDLE NESTING COUNTER: */
    LDR     R3,=OSIntNesting                                    /*   OSIntNesting++ */
    LDRB    R4, [R3]
    ADD     R4, R4, #1
    STRB    R4, [R3]

    LDR     R3,=OSTCBCur                                        /*   OSTCBCur->OSTCBStkPtr = SP */
    LDR     R4, [R3]
    STR     SP, [R4]

OS_CPU_ARM_ExceptHndlr_BreakTask_1:
    MSR     CPSR_cxsf, R2                                       /* RESTORE INTERRUPTED MODE. */

                                                                /* EXECUTE EXCEPTION HANDLER: */
    LDR     R1, =OS_CPU_ExceptHndlr                             /* OS_CPU_ExceptHndlr(except_type = R0) */
    MOV     LR, PC
    BX      R1

                                                                /* Adjust exception stack pointer.  This is needed because */
                                                                /* exception stack is not used when restoring task context. */
    ADD     SP, SP, #(14 * 4)

                                                                /* Change to SVC mode & disable interruptions.*/
    MSR     CPSR_c, #(OS_CPU_ARM_CONTROL_INT_DIS | OS_CPU_ARM_MODE_SVC)

                                                                /* Call OSIntExit().  This call MAY never return if a ready*/
                                                                /*  task with higher priority than the interrupted one is*/
                                                                /*  found.*/
    LDR     R0,=OSIntExit
    MOV     LR, PC
    BX      R0
                                                                /* If here, then there was no task switch. */
                                                                /* Restore interrupted task's context and return. */
    LDMFD   SP!, {R0}                                           /*    Pop task's CPSR, */
    MSR     SPSR_cxsf, R0

    LDMFD   SP!, {R0-R12, LR, PC}^                              /*    Pop task's context. */

/*
********************************************************************************************************
                               EXCEPTION HANDLER: EXCEPTION INTERRUPTED

 Register Usage:  R0     Exception Type
                  R1
                  R2
                  R3
********************************************************************************************************
*/
OS_CPU_ARM_ExceptHndlr_BreakExcept:
    MRS     R2, CPSR                                            /* Save exception's CPSR.*/

                                                                /* Change to SVC mode & disable interruptions.*/
    MSR     CPSR_c, #(OS_CPU_ARM_CONTROL_INT_DIS | OS_CPU_ARM_MODE_SVC)

                                                                /* HANDLE NESTING COUNTER:*/
    LDR     R3,=OSIntNesting                                    /*   OSIntNesting++*/
    LDRB    R4, [R3]
    ADD     R4, R4, #1
    STRB    R4, [R3]

    MSR     CPSR_cxsf, R2                                       /* RESTORE INTERRUPTED MODE.*/

                                                                /* EXECUTE EXCEPTION HANDLER:*/
    LDR     R3,= OS_CPU_ExceptHndlr                             /* OS_CPU_ExceptHndlr(except_type = R0)*/
    MOV     LR, PC
    BX      R3

                                                                /* Change to SVC mode & disable interruptions.*/
    MSR     CPSR_c, #(OS_CPU_ARM_CONTROL_INT_DIS | OS_CPU_ARM_MODE_SVC)

                                                                /* HANDLE NESTING COUNTER:*/
    LDR     R3,=OSIntNesting                                    /*   OSIntNesting--*/
    LDRB    R4, [R3]
    SUB     R4, R4, #1
    STRB    R4, [R3]

    MSR     CPSR_cxsf, R2                                       /* RESTORE INTERRUPTED MODE.*/

                                                                /* RESTORE OLD CONTEXT:*/
    LDMFD   SP!, {R0-R12, PC}^                                  /* Pull working registers and return from exception.*/

.end
