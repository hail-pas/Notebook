section .text
global _start
_start:
    ; mov dword [rsp-4], `rld\n`
    ;                 ; Use back ticks instead of single quotes
    ;                 ; To parse the string like C. We can write safely
    ;                 ; in the 128 bytes below RSP because of the
    ;                 ; Linux red zone.
    ; mov dword [rsp-8], 'o Wo'
    ; mov dword [rsp-12],'Hell'
    push    dword `rld\n`
    push    dword 'o Wo'
    push    dword 'Hell'
    mov eax,1       ;Write system call number
    mov edi,eax     ;file descriptor (1 = stdout)
    lea rsi,[rsp];address of message on the stack
    mov edx,24      ;length of message
    ; 注意这里的24
    ; 原因在于 栈的单位为 8 字节，虽然上面push实际占用为 12 字节，但是占用3个栈单位，共3 * 8 = 24 字节
    syscall
    mov eax,1       ;Write system call number
    mov edi,eax     ;file descriptor (1 = stdout)
    lea rsi,[rsp + 20];address of message on the stack
    mov edx,4      ;length of message
    syscall
    mov eax,60      ;Exit system call
    xor edi,edi     ;RDI=0
    syscall

; rld\n
; o wo
; Hell
; resp
