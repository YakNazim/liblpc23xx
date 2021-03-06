/*! \file lpc23xx-vic.c
 */

/* Copyright (C) 2011 Keith Wilson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Except as contained in this notice, the names of the authors or their
 * institutions shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the authors.
 */

#include <stdint.h>

#include "lpc23xx.h"

#include "lpc23xx-util.h"
#include "lpc23xx-vic.h"

/*! \defgroup lpc23xx-vic Vectored Interrupt Controller for liblpc23xx
 * @{
 */


/*! \brief turn interrupts off at the CPU status register
 *
 * @return
 */
void vic_cpu_disable_interrupts() {
	vic_disableIRQ();
    vic_disableFIQ();
}

/*! \brief turn interrupts on at the CPU status register
 *
 */
void vic_cpu_enable_interrupts() {
	vic_enableIRQ();
	vic_enableFIQ();
}

/*! \brief Turn off IRQ 
 *
 * The IRQ bit in the CPSR must be cleared for IRQ ints 
 *
 * This function returns the value of cpsr prior to clear 
 */
uint32_t vic_disableIRQ(void) {
    uint32_t _cpsr;

    _cpsr = __get_cpsr();
    __set_cpsr(_cpsr | (1<<IRQ_BIT));
    return _cpsr;
}

/*! \brief Turn on IRQ
 */
uint32_t vic_enableIRQ(void) {
    uint32_t _cpsr;

    _cpsr = __get_cpsr();
    __set_cpsr(_cpsr & IRQ_MASK);
    return _cpsr;
}

/*! \brief Turn OFF FIQ
 */
uint32_t vic_disableFIQ(void) {
    uint32_t _cpsr;

    _cpsr = __get_cpsr();
    __set_cpsr(_cpsr | (1<<FIQ_BIT));
    return _cpsr;
}

/*! \brief Turn on FIQ
 */
uint32_t vic_enableFIQ(void) {
    uint32_t _cpsr;

    _cpsr = __get_cpsr();
    __set_cpsr(_cpsr & FIQ_MASK);
    return _cpsr;
}

//6-5.4, p 89 lpc23xx manual
void inline ENABLE_INT(vic_interrupts interrupt){
    VICIntEnable = interrupt;
}

//6-5.5, p 89 lpc23xx manual
void inline DISABLE_INT(vic_interrupts interrupt){
    VICIntEnClr = interrupt;
}

void inline SET_IRQ(vic_interrupts interrupt){
    VICIntSelect &= ~(interrupt);
}

void inline SET_FIQ(vic_interrupts interrupt){
    VICIntSelect |= interrupt;
}

void inline RAISE_INT(vic_interrupts interrupt){
    VICSoftInt = interrupt;
}
void inline CLR_SW_INT(vic_interrupts interrupt){
    VICSoftIntClr = interrupt;
}


//! @}

