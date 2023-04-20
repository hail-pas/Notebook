        global  _start
        section .data


SYS_WRITE   equ 1
STD_OUT     equ 1
SYS_EXIT    equ 60
EXIT_CODE   equ 0
NEW_LINE    db  0xa
INPUT       db  "hello world!"

        section .text
_start:

    mov     rsi, INPUT
    xor     rcx, rcx
    cld
    mov     rdi, $ + 15         ; return address
    call    calculateStrLength
    xor     rax, rax
    xor     rdi, rdi
    jmp     reverseStr


calculateStrLength:
    cmp     byte [rsi], 0
    je      exitFromRoutine
    lodsb               ; load rsi firt byte to al(low 8 bit of rax), and move rsi next byte
    push    rax
    inc     rcx
    jmp     calculateStrLength


exitFromRoutine:
    push    rdi     ; push return address
    ret


reverseStr:
		cmp rcx, 0
		je printResult
		pop rax
		mov [OUTPUT + rdi], rax
		dec rcx
		inc rdi
		jmp reverseStr

printResult:
        mov rdx, rdi
		mov rax, 1
		mov rdi, 1
		mov rsi, OUTPUT
        syscall
		jmp printNewLine

printNewLine:
		mov rax, SYS_WRITE
		mov rdi, STD_OUT
		mov rsi, NEW_LINE
		mov rdx, 1
		syscall
		jmp exit

exit:
		mov rax, SYS_EXIT
		mov rdi, EXIT_CODE
		syscall

        section .bss

OUTPUT      resb    12

