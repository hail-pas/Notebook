#include <assert.h>
#include <stdio.h>

void hanoi_recursion(int n, char from, char to, char via) {
    if (n == 1) {
        printf("%c -> %c\n", from, to);
        return;
    }
    hanoi_recursion(n - 1, from, via, to);  // 将 n-1 个盘子从源柱子移动到辅助柱子上
    hanoi_recursion(1,     from, to,  via); // 将第 n 个盘子从源柱子移动到目标柱子上；
    hanoi_recursion(n - 1, via, to, from); //  n-1 个盘子从辅助柱子移动到目标柱子上
}


typedef  struct{
    int pc, n;
    char from, to, via;
} Frame;

#define call(...) ({ *(++top) = (Frame){.pc = 0, __VA_ARGS__}; })
#define ret() ({ top--; })
#define goto(loc) ({f->pc = (loc) - 1;})

void hanoi_nr(int n, char from, char to, char via) {
    Frame stk[64], *top = stk - 1;
    call(n, from, to, via);
    for (Frame *f; (f = top) >= stk ; f->pc++){
        n = f->n;
        from = f->from;
        to = f->to;
        via = f->via;
        switch (f->pc) {
            case 0: if (n == 1) {printf("%c -> %c\n", from, to); goto(4);} break;
            case 1: call(n-1, from, via, to); break;
            case 2: call(1, from, to, via); break;
            case 3: call(n-1, via, to, from); break;
            case 4: ret(); break;
            default: assert(0);
        }
    }
}
