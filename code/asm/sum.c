#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

double sum(double *, uint64_t);

int main(int argc, char *argv[]) {
    double a[] = {
        40.5, 26.7, 21.9, 1.5, -40.5, -23.4
    };

    printf("%20.7f\n", sum(a, 6));
    printf("%20.7f\n", sum(a, 2));
    printf("%20.7f\n", sum(a, 0));
    printf("%20.7f\n", sum(a, 3));

    return 0;
}
