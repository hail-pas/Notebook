#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

int64_t maxofthree(int64_t, int64_t, int64_t);

int main(int argc, char *argv[]) {
    printf("%lld\n", (long long int)maxofthree(1, -4, -7));
    printf("%lld\n", (long long int)maxofthree(2, -6, 1));
    printf("%lld\n", (long long int)maxofthree(2, 3, 1));
    return 0;
}

// nasm -f elf64 callmaxofthree.asm -o callmaxofthree.o && gcc callmaxofthree.o callmaxofthree.c -o callmaxofthree