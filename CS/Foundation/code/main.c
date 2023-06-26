#include<stdio.h>
#include<math.h>

double func(int i){
    volatile double d[1] = {3.14};
    volatile double a[2];
    a[i] = 1073741824;
    return d[0];
}

int main(int argc, char const *argv[])
{
    /* code */
    int x = 1;
    unsigned u = (unsigned)pow(2, 63);

    printf("x = %u = %d\n", x, x);
    printf("u = %u = %d\n", u, u);
    return 0;
}
