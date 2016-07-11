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
*  31.03.06  mifi   First Version
*                   This version based on an example from Ethernut and
*                   "ARM Cross Development with Eclipse" from James P. Lynch
****************************************************************************/

/*
 * Some defines for the program status registers
 */
    ARM_MODE_USER  = 0x10       /* Normal User Mode                             */
    ARM_MODE_FIQ   = 0x11       /* FIQ Fast Interrupts Mode                     */
    ARM_MODE_IRQ   = 0x12       /* IRQ Standard Interrupts Mode                 */
    ARM_MODE_SVC   = 0x13       /* Supervisor Interrupts Mode                   */
    ARM_MODE_ABORT = 0x17       /* Abort Processing memory Faults Mode          */
    ARM_MODE_UNDEF = 0x1B       /* Undefined Instructions Mode                  */
    ARM_MODE_SYS   = 0x1F       /* System Running in Priviledged Operating Mode */
    ARM_MODE_MASK  = 0x1F

    I_BIT          = 0x80       /* disable IRQ when I bit is set */
    F_BIT          = 0x40       /* disable FIQ when F bit is set */

/*
 * Some defines for exception type
 */
	EXCEPTION_TYPE_DABORT = 0x00  // Data Abort
	EXCEPTION_TYPE_PABORT = 0x01  // Prefetch Abort

    .section .startup,"ax"
    .global _startup            /* the linker uses this symbol */
    .code 32

_startup:

/****************************************************************************/
/*               Vector table and reset entry                               */
/****************************************************************************/
_vectors:
    ldr pc, ResetAddr           /* Reset                 */
    ldr pc, UndefAddr           /* Undefined instruction */
    ldr pc, SWIAddr             /* Software interrupt    */
    ldr pc, PAbortAddr          /* Prefetch abort        */
    ldr pc, DAbortAddr          /* Data abort            */
    .word 0                     /* Reserved for checksum */
    ldr pc, [pc, #-0x0120]		/* VIC IRQ location		 */
    ldr pc, FIQAddr             /* FIQ interrupt         */


/* Jump Table for exceptions */
ResetAddr:     .word ResetHandler
UndefAddr:     .word UndefHandler
SWIAddr:       .word SWIHandler
PAbortAddr:    .word PAbortHandler
DAbortAddr:    .word DAbortHandler
IRQAddr:       .word IRQHandler
FIQAddr:       .word FIQHandler

   .section .init, "ax"
    .code 32

    .global ResetHandler
    .global ExitFunction
    .extern main
    .extern abortPrint

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

    msr   CPSR_c, #ARM_MODE_SYS | I_BIT | F_BIT     /* System and User Mode */
    ldr   sp, =__stack_sys_end

    msr   CPSR_c, #ARM_MODE_SVC | I_BIT | F_BIT     /* Supervisor Mode */
    ldr   sp, =__stack_svc_end


    /* imprint hardware stacks */
    ldr   r1, =__stack_start
    ldr     r0, =0xDEADBEEF
    ldr     r2, =__stack_end
.L_impr:
    cmp     r1, r2
    strlo   r0, [r1], #4 /* address = r1. If r1<r2, add 4 to r1*/
    blo     .L_impr    /* still using condition codes of CMP above*/


    /*
     * Copy .data section (copy from ROM to RAM)
     */
    ldr     r1, =_etext
    ldr     r2, =__data_start
    ldr     r3, =__data_end
.L_copyloop:
    cmp     r2, r3
    ldrlo   r0, [r1], #4
    strlo   r0, [r2], #4
    blo     .L_copyloop

    /*
     * zero .bss section
     */

    ldr   r1, =__bss_start
    ldr   r2, =__bss_end
    ldr   r3, =0
.L_bss_clear_loop:
    cmp   r1, r2
    strne r3, [r1], #+4
    bne   .L_bss_clear_loop


   /*
    * Enable Interrupts for the current ARM mode
    * TODO Use this method to enable interrupts until you have your
    *      InterruptsEnable and InterruptsDisable asm functions implemented
    */
// TODO Enable the I-bit in the cpsr.  See the msr instruction.

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
/*                         Default exception handlers                       */
/****************************************************************************/

UndefHandler:
    b UndefHandler

SWIHandler:
    b SWIHandler

PAbortHandler:
    //b PAbortHandler

    STMFD r13!, {r1}								   /* Push r1 onto the stack */
	MSR   CPSR_c, #ARM_MODE_SVC | I_BIT | F_BIT		/* switch to Supervisor Mode */
	MOV   r1, r14								 /* Save the SVC mode's lr to r1 */
	MSR   CPSR_c, #ARM_MODE_ABORT | I_BIT | F_BIT	/* switch back to Abort Mode */
	MOV   r14, r1				 /* Save the SVC mode's lr back to Abort mode lr */
	LDMFD r13!, {r1}									/* Pop r1 from the stack */
	STMFD r13!, {r0-r12, r14}				  /* Push the context onto the stack */
	SUB   r14, r14, #4				 /* Adjust lr to address where abort occured */
	MOV   r0, #EXCEPTION_TYPE_PABORT			  /* abortPrint() type parameter */
	MOV   r1, r14                 			   /* abortPrint() address parameter */
	BL abortPrint               					 /* Print the exception info */
	LDMFD r13!, {r0-r12, pc}^					   /* Pop the context and return */

DAbortHandler:
    //b DAbortHandler

    SUB r14, #4					/* Adjust LR                            */
	STMFD r13!, {r0-r12, r14}	/* Push the context onto the stack      */

	MOV r0, #EXCEPTION_TYPE_DABORT /* abortPrint() type parameter       */
	MOV r1, r14                 /*    abortPrint() address parameter    */
	SUB r1, #4					/* Adjust for the error address         */

	BL abortPrint               /* Print the exception info             */

	LDMFD r13!, {r0-r12, pc}^	/* Pop the context and return           */


IRQHandler:
    b IRQHandler

FIQHandler:
    b FIQHandler

.end    /*** EOF ***/

