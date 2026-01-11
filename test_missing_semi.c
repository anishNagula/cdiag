#include <stdio.h>

struct Foo {
    int x;
    int y;
}

void print(struct Foo f) {
    printf("%d %d\n", f.x, f.y);
}

int main() {
    struct Foo f;
    f.x = 10;
    f.y = 20;
    print(f);
    return 0;
}
