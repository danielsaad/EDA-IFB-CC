#include <stdio.h>

int main(void) {
    char *ptr;
    char v[] = {'a', 'b', 'a', 'c', 'a', 't', 'e', '\0'};
    ptr = v;
    printf("String original: %s\n", v);
    ptr[2] = 'd';
    printf("String modificada: %s\n", v);
    return 0;
}
