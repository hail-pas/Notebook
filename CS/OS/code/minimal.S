#include <sys/syscall.h>

.global _start

_start:
    movq    $1, %rax
    movq    $1, %rdi
    movq    $message, %rsi
    movq    $(end - message), %rdx
    syscall

    movq    $60, %rax
    movq    $1, %rdi
    syscall

message:
    .ascii  "\033[01;31mHello, OS World\033[0m\n"
end:


# ssh -o 'HostKeyAlgorithms +ssh-rsa' sshtron.zachlatta.com