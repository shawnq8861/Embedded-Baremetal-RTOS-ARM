    .global InterruptsDisable
    .global InterruptsEnable

    .set ARM_SR_FIQ_BIT,        0x40    /* disable FIQ when F bit is set */
    .set ARM_SR_IRQ_BIT,        0x80    /* disable IRQ when I bit is set */

    .text
    .arm

    .func InterruptsDisable
/* uint32_t InterruptsDisable(void);
    Per calling convention:
    r0 contains the return value

    return: the old cpsr value
 */
InterruptsDisable:
    mrs r0, cpsr            // read the cpsr

.L_CPU_SR_Save_Loop:
    /* Set IRQ & FIQ bits in CPSR to DISABLE all interrupts */
    orr     r1, r0, #(ARM_SR_IRQ_BIT | ARM_SR_FIQ_BIT)
    msr     cpsr_c, r1
    /* Confirm that CPSR contains the proper interrupt disable flags */
    mrs     r1, cpsr
    and     r1, r1, #(ARM_SR_IRQ_BIT | ARM_SR_FIQ_BIT)
    cmp     r1,     #(ARM_SR_IRQ_BIT | ARM_SR_FIQ_BIT)
    /* NOT properly DISABLED (try again) */
    bne     .L_CPU_SR_Save_Loop
    /* DISABLED, original CPSR contents returned in r0 */
    bx  lr
    .endfunc

    .func InterruptsEnable
/* void InterruptsEnable(uint32_t cpu_sr);
    Per calling convention:
    r0 contains the first function parameter

    Take the input parameter cpu_sr,
    extract the I and F bits,
    only enable IRQ or FIQ in cpsr if the bit is cleared in cpu_sr


    return: none
 */
InterruptsEnable:
    mrs r1, cpsr            // load the cpsr

    /* Keep everything but the F and I bits */
    and r1, r1, #~(ARM_SR_IRQ_BIT | ARM_SR_FIQ_BIT)

    /* Extract the F and I bits from cpu_sr parameter */
    and r0, r0, #(ARM_SR_IRQ_BIT | ARM_SR_FIQ_BIT)

    /* Set and combine the F and I bits based on cpu_sr parameter */
    orr r1, r0

    /* update the control bits in the cpsr -- interrupts now enabled */
    msr cpsr_c, r1

    bx  lr
    .endfunc

    .end

