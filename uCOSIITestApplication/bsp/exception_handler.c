/*
 * 	exception_handler.c
 */


#include <includes.h>

/*
*********************************************************************************************************
*                                          OS_CPU_ExceptHndlr()
*
* Description : Handle exceptions by reading function pointer from the VIC and call the function.
*
* Argument(s) : except_id     ARM exception type:
*
*                                  OS_CPU_ARM_EXCEPT_RESET             0x00
*                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
*                                  OS_CPU_ARM_EXCEPT_SWI               0x02
*                                  OS_CPU_ARM_EXCEPT_PREFETCH_ABORT    0x03
*                                  OS_CPU_ARM_EXCEPT_DATA_ABORT        0x04
*                                  OS_CPU_ARM_EXCEPT_ADDR_ABORT        0x05
*                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
*                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
*
* Return(s)   : none.
*
* Caller(s)   : OS_CPU_ARM_EXCEPT_HANDLER(), which is declared in os_cpu_a.s.
*********************************************************************************************************
*/

void  OS_CPU_ExceptHndlr (CPU_DATA except_id)
{
    CPU_FNCT_VOID  pfnct;
    CPU_INT32U    *sp;
                                                                       /* If this exception is either an IRQ or FIQ        */
    if ((except_id == OS_CPU_ARM_EXCEPT_IRQ) || (except_id == OS_CPU_ARM_EXCEPT_FIQ))
    {
        pfnct = (CPU_FNCT_VOID)READREG32(VICADDRESS);                   /* Read the interrupt vector from the VIC           */

        if (pfnct != (CPU_FNCT_VOID)0)                                  /* Make sure we don't have a NULL pointer           */
        {
        	(*pfnct)();                                                 /* Execute the ISR for the interrupting device      */
            WRITEREG32(VICADDRESS, 1);                                  /* Acknowlege the VIC interrupt                     */
        }
    }
    else
    {
    	/* For other exception types just dump the registers from the current stack. */
        sp = (CPU_INT32U *)OSTCBCur->OSTCBStkPtr;
        APP_TRACE_INFO(("\nCPU_ARM_EXCEPTION #%d trapped.\n", except_id));
        APP_TRACE_INFO(("R0  : 0x%08x\n", *(sp + 0x01)));
        APP_TRACE_INFO(("R1  : 0x%08x\n", *(sp + 0x02)));
        APP_TRACE_INFO(("R2  : 0x%08x\n", *(sp + 0x03)));
        APP_TRACE_INFO(("R3  : 0x%08x\n", *(sp + 0x04)));
        APP_TRACE_INFO(("R4  : 0x%08x\n", *(sp + 0x05)));
        APP_TRACE_INFO(("R5  : 0x%08x\n", *(sp + 0x06)));
        APP_TRACE_INFO(("R6  : 0x%08x\n", *(sp + 0x07)));
        APP_TRACE_INFO(("R7  : 0x%08x\n", *(sp + 0x08)));
        APP_TRACE_INFO(("R8  : 0x%08x\n", *(sp + 0x09)));
        APP_TRACE_INFO(("R9  : 0x%08x\n", *(sp + 0x0A)));
        APP_TRACE_INFO(("R10 : 0x%08x\n", *(sp + 0x0B)));
        APP_TRACE_INFO(("R11 : 0x%08x\n", *(sp + 0x0C)));
        APP_TRACE_INFO(("R12 : 0x%08x\n", *(sp + 0x0D)));
        APP_TRACE_INFO(("SP  : 0x%08x\n",   (unsigned int)sp));
        APP_TRACE_INFO(("LR  : 0x%08x\n", *(sp + 0x0E)));
        APP_TRACE_INFO(("PC  : 0x%08x\n", *(sp + 0x0F)));
        APP_TRACE_INFO(("CPSR: 0x%08x\n", *(sp + 0x00)));

		/* Infinite loop on other exceptions if they get here.     */
		/* Could be replaced by other behavior (reboot, etc.)      */
        while (TRUE) {
            ;
        }
    }
}
