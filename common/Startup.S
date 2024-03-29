//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC70xx (Analog Devices)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Startup file.
//*
//*     Version: 5.0.0
//*
//*     Copyright (c) 2003-2015, scmRTOS Team
//*
//*     Permission is hereby granted, free of charge, to any person
//*     obtaining  a copy of this software and associated documentation
//*     files (the "Software"), to deal in the Software without restriction,
//*     including without limitation the rights to use, copy, modify, merge,
//*     publish, distribute, sublicense, and/or sell copies of the Software,
//*     and to permit persons to whom the Software is furnished to do so,
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2015
//*     ADuC70xx port maintenance: Anton B. Gusev aka AHTOXA, Copyright (c) 2011-2015
//*
//******************************************************************************
//*
//*     Startup file modified by the author of this repository.
//*
//******************************************************************************

#define MODE_USER       0x10
#define MODE_FIQ        0x11
#define MODE_IRQ        0x12
#define MODE_SVC        0x13
#define MODE_ABORT      0x17
#define MODE_UND        0x1B
#define MODE_SYS        0x1F

#define NIRQ            0x80
#define NFIQ            0x40
#define THUMB           0x20

    .code 32
//-----------------------------------------------------------------------------
//     Vector table and reset entry.
//-----------------------------------------------------------------------------
    .section .vectors,"ax"
    .global _start
_start:
        LDR     PC, ResetAddr       /* Reset                 */
        LDR     PC, UndefAddr       /* Undefined instruction */
        LDR     PC, SWIAddr         /* Software interrupt    */
        LDR     PC, PAbortAddr      /* Prefetch abort        */
        LDR     PC, DAbortAddr      /* Data abort            */
        NOP                         /* Reserved              */
        LDR     PC, IRQAddr         /* IRQ interrupt         */
        LDR     PC, FIQAddr         /* FIQ interrupt         */
ResetAddr:
        .word ResetHandler
UndefAddr:
        .word UndefHandler
SWIAddr:
        .word SWIHandler
PAbortAddr:
        .word PAbortHandler
DAbortAddr:
        .word DAbortHandler
IRQAddr:
        .word IRQHandler
FIQAddr:
        .word FIQHandler
    .ltorg

//-----------------------------------------------------------------------------
//     Reset handler. Program starts here.
//-----------------------------------------------------------------------------
    .section .text, "ax"
ResetHandler:
//-----------------------------------------------------------------------------
//     Setup stack for each mode.
//-----------------------------------------------------------------------------
        MSR     CPSR_c, #MODE_SYS | NIRQ | NFIQ     // switch to system mode, IRQ & FIQ disabled
        LDR     SP, =__stack_sys
        MSR     CPSR_c, #MODE_FIQ | NIRQ | NFIQ     // switch to fiq mode, IRQ & FIQ disabled
        LDR     SP, =__stack_fiq
        MSR     CPSR_c, #MODE_SVC | NIRQ | NFIQ     // switch to supervisor mode, IRQ & FIQ disabled
        LDR     SP, =__stack_svc
        MSR     CPSR_c, #MODE_UND | NIRQ | NFIQ     // switch to undefined mode, IRQ & FIQ disabled
        LDR     SP, =__stack_und
        MSR     CPSR_c, #MODE_ABORT | NIRQ | NFIQ   // switch to abort mode, IRQ & FIQ disabled
        LDR     SP, =__stack_abort
        MSR     CPSR_c, #MODE_IRQ | NIRQ | NFIQ     // switch to irq mode, IRQ & FIQ disabled
        LDR     SP, =__stack_irq
        MSR     CPSR_c, #MODE_SYS                   // switch to system mode, IRQ & FIQ enabled
        LDR     SP, =__stack_sys
//-----------------------------------------------------------------------------
//     Clear .bss section.
//-----------------------------------------------------------------------------
        LDR     R1, =__bss_start
        LDR     R2, =__bss_end
        MOV     R3, #0
bss_clear_loop:
        CMP     R1, R2
        STRLO   R3, [R1], #+4
        BLO     bss_clear_loop
//-----------------------------------------------------------------------------
//     Copy initialized variables to .data section.
//-----------------------------------------------------------------------------
        LDR     R1,=_data_image                     // data image start
        LDR     R2,=_data                           // destination
        LDR     R3,=_edata                          // end of destination
data_copy_loop:
        CMP     R2,R3
        LDRLO   R0,[R1],#4
        STRLO   R0,[R2],#4
        BLO     data_copy_loop
//-----------------------------------------------------------------------------
//     Branch to main(). No return from main() expected.
//-----------------------------------------------------------------------------
        LDR     R2,=main
        BX      R2
//-----------------------------------------------------------------------------
//     Exit function. We should never reach this function.
//-----------------------------------------------------------------------------
    .section .text.weakExitFunction, "ax"
    .global ExitFunction
    .weak ExitFunction
ExitFunction:
        B       ExitFunction

//-----------------------------------------------------------------------------
//     Default exception handlers.
//-----------------------------------------------------------------------------
    .section .text.weakIRQHandler, "ax"
    .weak IRQHandler
IRQHandler:
        B       IRQHandler

    .section .text.weakFIQHandler, "ax"
    .weak FIQHandler
FIQHandler:
        B       FIQHandler

    .section .text.weakUndefHandler, "ax"
    .weak UndefHandler
UndefHandler:
        B       UndefHandler

    .section .text.weakSWIHandler, "ax"
    .weak SWIHandler
SWIHandler:
        B       SWIHandler

    .section .text.weakPAbortHandler, "ax"
    .weak PAbortHandler
PAbortHandler:
        B       PAbortHandler

    .section .text.weakDAbortHandler, "ax"
    .weak DAbortHandler
DAbortHandler:
        B       DAbortHandler

    .ltorg
