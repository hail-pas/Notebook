#include<stdio.h>

double func(int i){
    volatile double d[1] = {3.14};
    volatile double a[2];
    a[i] = 1073741824;
    return d[0];
}

int main(int argc, char const *argv[])
{
    /* code */
    int a = 0x80000000;
    int b = a/ -1;
    printf("%d\n", a);
    printf("%d\n", b);
    printf("%f\n", func(0));
    printf("%f\n", func(1));
    printf("%f\n", func(2));
    printf("%f\n", func(3));
    printf("%f\n", func(4));
    return 0;
}
