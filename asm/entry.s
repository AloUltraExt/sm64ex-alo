// assembler directives
.set noat      // allow manual use of $at
.set noreorder // don't insert nops after branches

#include "macros.inc"

.section .text, "ax"

glabel entry_point

entry_point:
    // Get main segment bss address and size
    lui   $t0, %hi(_mainSegmentBssStart)
    addiu $t0, %lo(_mainSegmentBssStart)
    lui   $t1, %hi(_mainSegmentBssSize)
    addiu $t1, %lo(_mainSegmentBssSize)
.clear_bytes:
    // Clear bss section until they are zeroed out
    sw    $zero, ($t0) // Clear 4 bytes
    sw    $zero, 4($t0) // Clear the next 4 bytes
    addi  $t0, $t0, 8 // Increment the address of bytes to clear
    addi  $t1, $t1, -8 // Subtract 8 bytes from the amount remaining
    bnez  $t1, .clear_bytes // Continue clearing until clear_bytes is 0
    nop
    // Get init function and idle thread stack
    lui   $sp, %hi(gIdleThreadStack)
    addiu $sp, %lo(gIdleThreadStack)
    lui   $t2, %hi(main_func)
    addiu $t2, %lo(main_func)
    jr    $t2 // Jump to the init function
    nop
