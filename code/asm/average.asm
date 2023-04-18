; ; -----------------------------------------------------------------------------
; ; 64-bit program that treats all its command line arguments as integers and
; ; displays their average as a floating point number.  This program uses a data
; ; section to store intermediate results, not that it has to, but only to
; ; illustrate how data sections are used.
; ; -----------------------------------------------------------------------------

        global  main
        extern  atoi
        extern  printf
        default rel

        section .text

main:
    dec     rdi
    jz      nothingToAverage
    mov     [count], rdi    ; save number of real arguments

accumulate:
    push    rdi
    push    rsi
    mov     rdi, [rsi+rdi*8]    ; argv[rdi]
    call    atoi
    pop     rsi
    pop     rdi
    add     [sum], rax

    dec     rdi
    jnz     accumulate


average:
    cvtsi2sd    xmm0, [sum]
    cvtsi2sd    xmm1, [count]

    divsd       xmm0, xmm1

    mov         rdi, format            ; 1st arg to printf
    mov         rax, 1

    sub         rsp, 8                 ; align stack pointer
    call        printf
    add         rsp, 8

    ret

nothingToAverage:
    mov         rdi, error
    xor         rax, rax
    call        printf
    ret


        section .data

count:  dq  0
sum:    dq  0
format: db  "%g", 10, 0
error:  db  "There are no command line arguments to calculate average", 10, 0
