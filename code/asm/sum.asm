; -----------------------------------------------------------------------------
; A 64-bit function that returns the sum of the elements in a floating-point
; array. The function has prototype:
;
;   double sum(double[] array, uint64_t length)
;   xmm register
; -----------------------------------------------------------------------------

        global  sum
        extern  printf
        section .text

sum:
    xorpd   xmm0, xmm0  ; 将 XMM0 寄存器清零，XMM0 寄存器是用于执行 SSE 指令的寄存器
                        ; 在这里，将其用作累加器，用于计算数组元素的和
    cmp     rsi, 0      ; 比较参数 rsi 中的值是否为 0, rsi 为累加个数
    je      done

next:
    addsd   xmm0, [rdi]     ; 从地址 rdi 指向的内存中读取一个双精度浮点数，加到 xmm0 中
                            ; rdi 是双精度浮点数组地址
    add     rdi, 8          ; rdi 加上 8，指向数组中的下一个元素
    dec     rsi
    jnz     next

done:
    ret
