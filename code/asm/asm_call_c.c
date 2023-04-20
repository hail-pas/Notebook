#include <stdio.h>

extern int print();

int print(char * s) {
	printf("Hello World\n");
    printf("%s", s);
	return 0;
}
