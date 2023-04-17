; -----------------------------------------------------------------------------
; A 64-bit function that returns the maximum value of its three 64-bit integer
; arguments.  The function has signature:
;
;   int64_t maxofthree(int64_t x, int64_t y, int64_t z)
;
; Note that the parameters have already been passed in rdi, rsi, and rdx.  We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

        global maxofthree

        section .text

maxofthree:
        mov     rax, rdi        ; rax holds rdi - the first argument
        cmp     rax, rsi        ; rsi - the second argument, compare with the first
        cmovl   rax, rsi      ; compare mov, if less than move
        cmp     rax, rdx
        cmovl   rax, rdx
        ret
