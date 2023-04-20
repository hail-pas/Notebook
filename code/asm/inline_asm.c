#include <string.h>

int main(int argc, char *argv[]) {
	char* str = "Hello World\n";
	long len = strlen(str);
	int ret = 0;

	__asm__ volatile (
        "movq $1, %%rax\n\t"
		"movq $1, %%rdi\n\t"
		"movq %1, %%rsi\n\t"
		"movl %2, %%edx\n\t"
		"syscall"
		: "=g"(ret)
		: "g"(str), "g" (len)
    );

	return 0;
}