.globl   add2
.type    add2,%function


add2:
    add r0, r0, r1
    bx lr



.globl   bad_add
.type    bad_add,%function


bad_add:
    mov r2, #0
    loop_start:
        cmp r2, r0
        beq end_1
        add r2, #1
        b loop_start

    end_1:
        mov r3, #0
        loop2_start:
            cmp r3, r1
            beq end_2
            add r2, #1
            add r3, #1
            b loop2_start
    
    end_2:
        mov r0, r2
        bx lr
