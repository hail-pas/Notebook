; %macro  PRINT 1
;     pusha
;     pushf ; 保留上下文
;     jmp     %%astr
; %%str   db  %1, 0
; %%strln equ $-%%str ; 当前位置 - %%str
; %%astr: _syscall_write  %%str, %%strln
;     popf
;     popa
; %endmacro

; %macro  _syscall_write  2
;     mov rax, 1
;     mov rdi, 1
;     mov rsi, %1
;     mov rdx, %2
;     syscall
; %endmacro

; ;         global  _start
; ;         section .text

; ; _start:
; ;     jmp label
; label: PRINT "Hello World!"


section .data
p: istruc person
      at name db "name"
      at age  db 25
    iend

section .text
_start:
    mov rax, [p + person.name]