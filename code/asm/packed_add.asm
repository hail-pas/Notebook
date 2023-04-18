; void add_four_floats(float x[4], float y[4])
; x[i] += y[i] for i in range(0..4)

        global  add_four_floats

        section .text


add_four_floats:
    movdqa      xmm0, [rdi]     ; rdi存储的是数组地址
    movdqa      xmm1, [rsi]

    addps       xmm0, xmm1
    movdqa      [rdi], xmm0
    ret
