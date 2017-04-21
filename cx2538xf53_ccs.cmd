//*****************************************************************************
//! @file       cx2538xf53_ccs.cmd
//! @brief      Cx2538xF53 linker file for Code Composer Studio.
//!
//! Revised     $Date$
//! Revision    $Revision$
//
//  This file is auto-generated.
//
//  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//****************************************************************************/

/* Retain interrupt vector table variable                                    */
--retain=g_pfnVectors
/* Override default entry point.                                             */
--entry_point ResetISR
/* Allow main() to take args                                                 */
--args 0x8
/* Suppress warnings and errors:                                             */
/* - 10063: Warning about entry point not being _c_int00                     */
/* - 16011, 16012: 8-byte alignment errors. Observed when linking in object  */
/*   files compiled using Keil (ARM compiler)                                */
--diag_suppress=10063,16011,16012

/* The following command line options are set as part of the CCS project.    */
/* If you are building using the command line, or for some reason want to    */
/* define them here, you can uncomment and modify these lines as needed.     */
/* If you are using CCS for building, it is probably better to make any such */
/* modifications in your CCS project and leave this file alone.              */
/*                                                                           */
/* --heap_size=0                                                             */
/* --stack_size=256                                                          */
/* --library=rtsv7M3_T_le_eabi.lib                                           */

/* The starting address of the application.  Normally the interrupt vectors  */
/* must be located at the beginning of the application.                      */
#define FLASH_BASE              0x00200000
#define FLASH_CCA_BASE          0x0027FFD4
#define RAM_NON_RETENTION_BASE  0x20000000
#define RAM_NON_RETENTION_SIZE  0x4000
#define RAM_RETENTION_BASE      (RAM_NON_RETENTION_BASE + RAM_NON_RETENTION_SIZE)
#define RAM_RETENTION_SIZE      0x4000

/* System memory map */

MEMORY
{
    /* Application stored in and executes from internal flash */
    FLASH (RX) : origin = FLASH_BASE, length = (FLASH_CCA_BASE - FLASH_BASE)
    /* Customer Configuration Area and Bootloader Backdoor configuration in flash */
    FLASH_CCA (RX) : origin = FLASH_CCA_BASE, length = 12
    /* Application uses internal RAM for data */
    /* 16 KB of RAM is retention. The stack, and all variables that need     */
    /* retention through PM2/3 must be in SRAM_RETENTION */
    SRAM_RETENTION (RWX) : origin = RAM_RETENTION_BASE, length = RAM_RETENTION_SIZE
    /* 16 KB of RAM is non-retention */
    SRAM_NON_RETENTION (RWX) : origin = RAM_NON_RETENTION_BASE, length = RAM_NON_RETENTION_SIZE
}

/* Section allocation in memory */

SECTIONS
{
    .intvecs    :   > FLASH_BASE
    .text       :   > FLASH
    .const      :   > FLASH
    .binit      :   > FLASH
    .cinit      :   > FLASH
    .pinit      :   > FLASH
    .init_array :   > FLASH
    .flashcca   :   > FLASH_CCA_BASE

    .vtable     :   > RAM_RETENTION_BASE
    .data       :   > SRAM_RETENTION
    .bss        :   > SRAM_RETENTION
    .sysmem     :   > SRAM_RETENTION
    .stack      :   > SRAM_RETENTION (HIGH)
    .nonretenvar:   > SRAM_NON_RETENTION

#ifdef __TI_COMPILER_VERSION__
#if __TI_COMPILER_VERSION__ >= 15009000
/*  Hide section from older compilers not supporting the "ramfunc" attribute.
    See http://processors.wiki.ti.com/index.php/Placing_functions_in_RAM */
    .TI.ramfunc : {} load=FLASH, run=SRAM_RETENTION, table(BINIT)
#endif
#endif
}

/* Create global constant that points to top of stack */
/* CCS: Change stack size under Project Properties    */
__STACK_TOP = __stack + __STACK_SIZE;
