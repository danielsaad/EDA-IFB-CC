#include <stdio.h>
#include <string.h>

void my_strcat(char *str1, const char *str2) {
    char *ptr = str1 + strlen(str1);
    while (*str2 != '\0') {
        *(ptr++) = *(str2++);
    }
    *ptr = '\0';
}

int main(void) {
    char str1[200] = "abra";
    char str2[200] = "cadabra";
    my_strcat(str1, str2);
    printf("%s\n", str1);
    return 0;
}