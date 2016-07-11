/*
 * timer1OSUtils.s
 *
 *  Created on: May 26, 2014
 *      Author: Shawn Quinn
 */

.set INT_DISABLED,          0xC0			// Disable both FIQ and IRQ
.set MODE_USER,				0x10			// User Mode
.set MODE_IRQ,              0x12			// IRQ Mode
.set MODE_SVC,              0x13			// Supervisor Mode
.set MODE_SYS,				0x1F			// Sys Mode
.set TIMER2_TC,				0xE0070008		// timer2 count register

.extern currStkPtr
.extern scheduler
.extern timer2EntryCt;
.extern timer2ExitCt;

.global getStackPtr
.global startFirstThread
.global switchCurrThread
.global timer1IRQHandler
.global SimpleIRQHandler

.code 32

/*
 *  Get the stack pointer value for the currently executing thread
 *
 */
getStackPtr:
  	STR		sp, [r0]				// Store sp into address passed into r0
    BX		lr						// return

/*
 *  Start first thread without saving previous context.
 *  Used to run the first thread the first time.
 *
 */
startFirstThread:
	MRS r0, cpsr;				// load CPSR into R0
	BIC r0, r0, #0x1F			// clear mode field
	ORR r0, r0, #0x10			// user mode code
	MSR spsr, r0				// store modified CPSR into SPSR
	LDR lr, =switchCurrThread	// load address of switch to current
	MOVS pc, lr					// branch for context switch

/*
 *  Switch to current thread without saving previous context.
 *  Pops the initial context setup up by the initialize_stack function.
 *  That means this function will act like a return to the thread.
 *
 */
switchCurrThread:
  	// Switch to the current thread's stack
	LDR		r0, =currStkPtr			// Load r0 with the address for currStkPtr
    LDR		sp, [r0]				// Load sp with the value stored at the address
    // sp now points to the thread's stack
    // Set SPSR to the CPSR for the thread
    LDMFD	sp!, {r0}				// Pop the first value from the stack into r0
    // That value was the CPSR for the thread
	MSR		spsr, r0				// Load SPSR with the CPSR value in r0

 	LDR		r0, =TIMER2_TC			// load addr of timer2 count
	LDR		r0, [r0]				// load timer 2 count value
	LDR		r1, =timer2ExitCt		// load addr of exit count
	STR		r0, [r1]				// store count value

    // Return to the last execution point in the thread
    LDMFD	sp!, {r0-r12, lr, pc}^	// Pop the rest of the regs and pc for the thread

/*
 *  Simple IRQ handler that calls hello_world from the SVC mode.
 *
 *  It saves the context on the IRQ stack.
 *  Switches to the SVC mode and calls hello. Resets SVC LR after call.
 *  Switches back to IRQ mode and pops the context and returns.
 *
 *  Used as an initial test.
 *
 */
SimpleIRQHandler:
    SUB		lr, lr, #4				// LR offset to return from this exception: -4
    STMFD	sp!, {r0-r12, lr}		// Push working registers
    MSR		cpsr_c, #(INT_DISABLED | MODE_SVC)	// Switch to SVC mode, ints disabled
    STMFD	sp!, {lr}				// Save LR before the call
    BL		hello_world				// Call hello_world, the branch w/ link overwrites LR
    LDMFD	sp!, {lr}				// Restore LR after the call
   	// Switch back to IRQ mode
	MSR		cpsr_c, #(INT_DISABLED | MODE_IRQ)
    LDMFD	sp!, {r0-r12, pc}^		// Pop the context and returning to interrupted code

/*
 *  Context switching interrupt handler.
 *
 *  This function switches threads on every timer1 interrupt.
 *
 */
timer1IRQHandler:
	// IRQ mode with IRQ stack
	SUB		lr, lr, #4				// Adjust LR back by 4 for use later
	STMFD	sp!, {r0-r2}			// Save registers r0-r2 for later retrieval

	LDR		r0, =TIMER2_TC			// load addr of timer2 count
	LDR		r0, [r0]				// load timer 2 count value
	LDR		r1, =timer2EntryCt		// load addr of entry count
	STR		r0, [r1]				// store count value

    MRS		r0, spsr				// Save thread's cpsr (IRQ's spsr) to r0
    MOV		r1, lr					// Save lr (which is the thread's pc) to r1
    MOV		r2, sp					// Save IRQ sp for use in SVC mode
    ADD		sp, sp, #12				// Reset the IRQ sp before switching modes

    // Change to SYS mode with interrupts enabled
    MSR		cpsr_c, #(MODE_SYS)	// "cpsr_c" = mask control bits

    // Save interrupted thread's context
    STMFD	sp!, {r1}				// Push thread's pc, i.e. IRQ's lr
    STMFD	sp!, {lr}				// Push thread's lr
    STMFD	sp!, {r3-r12}			// Push thread's r3-r12
    /*
     * Move task's r0-r2 from exception stack to task's stack by first
     * loading r3-r5 with r0-r2 that were saved on the irq stack, then
     * pushing them onto the task's stack, r2 has IRQ sp
     *
     */
	LDMFD	r2!, {r3-r5}			// Pop IRQ r0-r2 into thread's r3-r5 using saved IRQ sp
	STMFD	sp!, {r3-r5}			// Push r3-r5 onto thread's stack r0-r2
    STMFD	sp!, {r0}				// Push thread's cpsr (IRQ's spsr) to the thread stack
    MOV		r0, sp					// Save thread's stack pointer for call to switcher

	// Call the thread scheduler which sets currStkPtr and resets the timer
	BL	scheduler

	// Change to USER mode with interrupts enabled
    MSR		cpsr_c, #(MODE_USER)	// "cpsr_c" = mask control bits

	// Switch to the current thread by calling the function switchCurrThread
	B	switchCurrThread			// No need to use BL here, not returning
