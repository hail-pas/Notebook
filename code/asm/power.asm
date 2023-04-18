; -----------------------------------------------------------------------------
; A 64-bit command line application to compute x^y.
;
; Syntax: power x y
; x and y are (32-bit) integers
; -----------------------------------------------------------------------------

    global main
    extern printf
    extern puts
    extern atoi

    section .text

main:
    push    r12
    push    r13
    push    r14

    cmp     rdi, 3
    jne     error1

    mov     r12, rsi
    mov     rdi, [r12+16]
    call    atoi
    cmp     eax, 0
    jl      error2
    mov     r13d, eax

    mov     rdi, [r12+8]
    call    atoi
    mov     r14d, eax

    mov     eax, 1

check:
    test    r13d, r13d
    jz      gotit
    imul    eax, r14d
    dec     r13d
    jmp     check

gotit:
    mov     rdi, answer
    movsxd  rsi, eax
    xor     rax, rax
    call    printf
    jmp     done

error1:
    mov     edi, badArgumentCount
    call    puts
    jmp     done


error2:
    mov     edi, negativeExponent
    call    puts

done:
    pop     r14
    pop     r13
    pop     r12
    ret

answer:
    db      "%d", 10, 0

badArgumentCount:
    db      "Requires exactly two arguments", 10, 0

negativeExponent:
    db      "The exponent may not be negstive", 10, 0
