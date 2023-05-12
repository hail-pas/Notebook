#include <assert.h>

#include "./hanoi.c"

int main(int argc, char *argv[]) {
    hanoi_nr(3, 'A', 'B', 'C');
    return 0;
}