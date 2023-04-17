    global main
    extern puts
    section .text

main:
    push    rdi
    push    rsi
    sub     rsp, 8

    mov     rdi, [rsi]
    call    puts

    add     rsp, 8
    pop     rsi
    pop     rdi

    add     rsi, 8
    dec     rdi
    jnz     main

    ret

; nasm -f elf64 -g cmain_echo.asm -o cmain_echo.o
; gcc -fno-pie -no-pie cmain_echo.o -o cmain_echo

