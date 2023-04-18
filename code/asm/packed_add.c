#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

float add_four_floats(float [], float []);

int main(int argc, char *argv[]) {
    float a[4] = {1.0, 2.0, 3.0, 4.0};
    float b[4] = {5.0, 6.0, 7.0, 8.0};
    add_four_floats(a, b);
    printf("%f\n%f\n%f\n%f\n", a[0], a[1], a[2], a[3]);
    return 0;
}