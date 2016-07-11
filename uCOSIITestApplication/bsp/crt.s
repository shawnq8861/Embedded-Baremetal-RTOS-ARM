/****************************************************************************
*  Copyright (c) 2006 by Michael Fischer. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*  
*  1. Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the distribution.
*  3. Neither the name of the author nor the names of its contributors may 
*     be used to endorse or promote products derived from this software 
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
*  SUCH DAMAGE.
*
****************************************************************************
*
*  History:
*
*  03.31.06  mifi   First Version
*                   This version based on an example from Ethernut and
*                   "ARM Cross Development with Eclipse" from James P. Lynch
*
****************************************************************************/

/*
 * Some defines for the program status registers
 */

ARM_MODE_USER  = 0x10      /* Normal User Mode                             */
ARM_MODE_FIQ   = 0x11      /* FIQ Fast Interrupts Mode                     */
ARM_MODE_IRQ   = 0x12      /* IRQ Standard Interrupts Mode                 */
ARM_MODE_SVC   = 0x13      /* Supervisor Interrupts Mode                   */
ARM_MODE_ABORT = 0x17      /* Abort Processing memory Faults Mode          */
ARM_MODE_UNDEF = 0x1B      /* Undefined Instructions Mode                  */
ARM_MODE_SYS   = 0x1F      /* System Running in Priviledged Operating Mode */
ARM_MODE_MASK  = 0x1F
   
I_BIT          = 0x80      /* disable IRQ when I bit is set */
F_BIT          = 0x40      /* disable IRQ when I bit is set */
   
/*
 * Register Base Address
 */
          
.section .startup, "ax"
.global _startup	       /* the linker needs this symbol	*/
.code 32

_startup:
        
/****************************************************************************/
/*               Vector table and reset entry                               */
/****************************************************************************/
_vectors:
    ldr pc, ResetAddr              /* Reset                 */
    ldr pc, UndefAddr              /* Undefined instruction */
    ldr pc, SWIAddr                /* Software interrupt    */
    ldr pc, PAbortAddr             /* Prefetch abort        */
    ldr pc, DAbortAddr             /* Data abort            */
    ldr pc, ReservedAddr           /* Reserved              */
    ldr pc, uCOS_ExceptIrqHndlr    /* IRQ interrupt         */
    ldr pc, FIQAddr                /* FIQ interrupt         */


/* Jump Table for exceptions */
ResetAddr:     .word ResetHandler
UndefAddr:     .word UndefHandler
SWIAddr:       .word SWIHandler
PAbortAddr:    .word PAbortHandler
DAbortAddr:    .word DAbortHandler
ReservedAddr:  .word 0
IRQAddr:       .word IRQHandler
FIQAddr:       .word FIQHandler

/* uCOS IRQ exception handler address */
uCOS_ExceptIrqHndlr: .word OS_CPU_ARM_ExceptIrqHndlr

/*
 * exception type for reporting debug info
 */
EXCEPTION_TYPE_DABORT = 0x00  /* Data Abort                                */
EXCEPTION_TYPE_PABORT = 0x01  /* Prefetch Abort                            */

.ltorg

.section .init, "ax"
.code 32

.global ResetHandler
.global ExitFunction
.extern main

/****************************************************************************/
/*                           Reset handler                                  */
/****************************************************************************/
ResetHandler:
    /*
     * Setup a stack for each mode
     */    
    msr   CPSR_c, #ARM_MODE_UNDEF | I_BIT | F_BIT   /* Undefined Instruction Mode */     
    ldr   sp, =__stack_und_end

    msr   CPSR_c, #ARM_MODE_ABORT | I_BIT | F_BIT   /* Abort Mode */
    ldr   sp, =__stack_abt_end

    msr   CPSR_c, #ARM_MODE_FIQ | I_BIT | F_BIT     /* FIQ Mode */   
    ldr   sp, =__stack_fiq_end

    msr   CPSR_c, #ARM_MODE_IRQ | I_BIT | F_BIT     /* IRQ Mode */   
    ldr   sp, =__stack_irq_end

    msr   CPSR_c, #ARM_MODE_SVC | I_BIT | F_BIT     /* Supervisor Mode */
    ldr   sp, =__stack_svc_end

    msr   CPSR_c, #ARM_MODE_SYS | I_BIT | F_BIT     /* User and System Mode */
    ldr   sp, =__stack_sys_end

    /* 
     * Copy .data section (copy from ROM to RAM)
     */
    ldr     r1, =_etext
    ldr     r2, =__data_start
    ldr     r3, =__data_end
copyloop:   
    cmp     r2, r3
    ldrlo   r0, [r1], #4
    strlo   r0, [r2], #4
    blo     copyloop

    /*
     * Zero .bss section
     */
    ldr   r1, =__bss_start
    ldr   r2, =__bss_end
    ldr   r3, =0
bss_clear_loop:
    cmp   r1, r2
    strne r3, [r1], #+4
    bne   bss_clear_loop

    /* 
     * Enable FIQ and IRQ interrupts
     */ 
    mrs   r0, cpsr
    bic   r0, r0, #I_BIT | F_BIT
    msr   cpsr_c, r0
   
    /* 
     * Jump to main  
     */
    mov   r0, #0    /* No arguments */
    mov   r1, #0    /* No arguments */
    ldr   r2, =main
    mov   lr, pc
    bx    r2        /* And jump... */
                       
ExitFunction:
    nop
    nop
    nop
    b ExitFunction   
   

/****************************************************************************/
/*                         Default interrupt handlers                       */
/****************************************************************************/

UndefHandler:
    b UndefHandler
   
SWIHandler:
    b SWIHandler

/*
    Prefetch abort handler. Prints address of abort to serial port and parks
    in a loop.
*/
PAbortHandler:
/*    b PAbortHandler     >> Replace with your prefetch abort handler code. */

    /* GET VALUE OF LR                                                  */
    STMFD r13!, {r1}            /* Push R1 so we can use it             */
	MSR   CPSR_c, #ARM_MODE_SVC | I_BIT | F_BIT     /* Supervisor Mode  */
	MOV   r1, LR                  /* Get SVC LR                         */
	MSR   CPSR_c, #ARM_MODE_ABORT | I_BIT | F_BIT   /* Abort Mode       */
	MOV   LR, r1                  /*  abortPrint() address parameter    */
    LDMFD r13!, {r1}            /* POP R1                               */


	STMFD r13!, {r0-r12, r14}	/* Push the context onto the stack      */

	SUB lr, lr, #4				/* Adjust LR                            */
	MOV r0, #EXCEPTION_TYPE_PABORT /* abortPrint() type parameter       */
	MOV r1, lr                  /*    abortPrint() address parameter    */

	BL abortPrint               /* Print the exception info             */

PAbortParkLoop:
	b PAbortParkLoop
/* 	LDMFD r13!, {r0-r12, pc}^	Pop the context and return           */


/*
    Data abort handler. Prints address of instruction causing abort, then
    parks in a loop.
*/
DAbortHandler:
/*    b DAbortHandler     >> Replace with your data abort handler code. */
	SUB r14, #4					/* Adjust LR                            */
	STMFD r13!, {r0-r12, r14}	/* Push the context onto the stack      */

	MOV r0, #EXCEPTION_TYPE_DABORT /* abortPrint() type parameter       */
	MOV r1, r14                 /*    abortPrint() address parameter    */
	SUB r1, #4					/* Adjust for the error address         */

	BL abortPrint               /* Print the exception info             */

DAbortParkLoop:
	b DAbortParkLoop
/* 	LDMFD r13!, {r0-r12, pc}^	Pop the context and return           */


/* IRQHandler is not called. See IRQ exception vector above. */
IRQHandler:
    b IRQHandler
   
FIQHandler:
    b FIQHandler
   

.weak ExitFunction
.weak UndefHandler, PAbortHandler, DAbortHandler
.weak IRQHandler, FIQHandler

.ltorg

.end
/*** EOF ***/   
   

