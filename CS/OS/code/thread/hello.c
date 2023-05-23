#include "thread.h"

void Thello(int id) {
    while (1) {
        // printf("%c", "_ABCDEF"[id]);
    }
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 10; i++) {
        create(Thello);
    }
    return 0;
}