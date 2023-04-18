; ----------------------------------------------------------------------------
; An implementation of the recursive function:
;
;   uint64_t factorial(uint64_t n) {
;       return (n <= 1) ? 1 : n * factorial(n-1);
;   }
; ----------------------------------------------------------------------------

        global  factorial

        section .text

factorial:
        cmp     rdi, 1      ; n <= 1?
        jnbe    L1          ; if not, go do a recurcive call

        mov     rax, 1      ; else store retvalue i to rax
        ret

L1:
        push    rdi         ; 当前的参数入栈保存
        dec     rdi         ; 将参数减一后作为参数调用自身, 返回值存储在 rax
        call    factorial   ; 递归调用
        pop     rdi         ;
        imul    rax, rdi
        ret
; nasm -felf64 factorial.asm -o factorial.o && gcc -std=c99 factorial.o factorial.c -o factorial && ./factorial && rm ./factorial.o && rm ./factorial