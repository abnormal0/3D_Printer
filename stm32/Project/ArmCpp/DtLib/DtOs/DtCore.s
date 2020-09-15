.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global PendSV_Handler
.type  PendSV_Handler, %function
PendSV_Handler:
    cpsid i
    mrs r0,psp
    ldr r1,=tn
    ldr r2,[r1]
    cbz r2,OsPull

OsPush:
    stmdb r0!, {r4-r11}
    str r0,[r2]

OsPull:
    ldr r0,=tr
    ldr r0,[r0]
    ldr r2,[r0]
    ldmia r2!, {r4-r11}
    msr psp,r2
    str r0,[r1]
    mov lr,#0xfffffffd
    cpsie i
    bx lr



