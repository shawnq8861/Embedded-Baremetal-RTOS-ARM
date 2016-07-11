/********************************************************************************************************
                                               uC/CPU
                                    CPU CONFIGURATION & PORT LAYER

                          (c) Copyright 2004-2007; Micrium, Inc.; Weston, FL

               All rights reserved.  Protected by international copyright laws.

               uC/CPU is provided in source form for FREE evaluation, for educational
               use or peaceful research.  If you plan on using uC/CPU in a commercial
               product you need to contact Micrium to properly license its use in your
               product.  We provide ALL the source code for your convenience and to
               help you experience uC/CPU.  The fact that the source code is provided
               does NOT mean that you can use it without paying a licensing fee.

               Knowledge of the source code may NOT be used to develop a similar product.

               Please help us continue to provide the Embedded community with the finest
               software available.  Your honesty is greatly appreciated.
********************************************************************************************************

********************************************************************************************************

                                            CPU PORT FILE
                                                 ARM

 Filename      : critical_section.s  (originally cpu_a.s)
 Version       : V1.17
 Programmer(s) : JJL
                 JDH
                 ITJ
********************************************************************************************************


********************************************************************************************************
                                           PUBLIC FUNCTIONS
********************************************************************************************************/

.global CPU_SR_Save
.global CPU_SR_Restore

/*********************************************************************************************************
                                                EQUATES
*********************************************************************************************************/

.set INTERRUPTS_DISABLE,      0xC0                            /* Disable both FIQ & IRQ */
.set FIQ_DISABLE,             0x40                            /* Disable FIQ */
.set IRQ_DISABLE,             0x80                            /* Disable IRQ */


/*********************************************************************************************************
                                      CODE GENERATION DIRECTIVES
*********************************************************************************************************/

.text
.arm

/*********************************************************************************************************
                                      CRITICAL SECTION FUNCTIONS

 Description : Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking, the
               state of the interrupt disable flag is stored in the local variable 'cpu_sr' & interrupts
               are then disabled ('cpu_sr' is allocated in all functions that need to disable interrupts).
               The previous interrupt state is restored by copying 'cpu_sr' into the CPU's status register.

 Prototypes  : CPU_SR  CPU_SR_Save   (void);
               void    CPU_SR_Restore(CPU_SR  cpu_sr);

 Note(s)     : (1) These functions are used in general like this :

                   void  Task (void  *p_arg)
                   {
                                                           / * Allocate storage for CPU status register * /
                   #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
                       CPU_SR  cpu_sr;
                   #endif

                            :
                            :
                       OS_ENTER_CRITICAL();               / * cpu_sr = CPU_SR_Save();                  * /
                            :
                            :
                       OS_EXIT_CRITICAL();                / * CPU_SR_Restore(cpu_sr);                  * /
                            :
                            :
                   }

*********************************************************************************************************/

/********************************************************************************

    Saves the current CPSR register to R0. Disables the interrupts.
    Returns the original value in R0 (the return register).

********************************************************************************/

CPU_SR_Save:
	// Read the current CPSR into return register
	MRS	r0, cpsr
	// Copy CPSR value for disabling int's
	ORR r1, r0, #IRQ_DISABLE
	// Disable IRQ (leave FIQ intact)
	MSR cpsr, r1
	// Branch back
	MOV pc, lr

/********************************************************************************

    Restore of CPSR register from the value passed in R0.

********************************************************************************/

CPU_SR_Restore:
    // Restore CPSR from parameter
    MSR cpsr, r0
	// Branch back
	MOV pc, lr


.end
