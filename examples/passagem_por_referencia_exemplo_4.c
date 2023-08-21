#include <stdio.h>

void min_max(int v[], int n, int *min, int *max) {
    *min = v[0];
    *max = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] < *min)
            *min = v[i];
        if (v[i] > *max)
            *max = v[i];
    }
}
int main(void) {
    int v[] = {10, 80, 5, -10, 45, -20, 100, 200, 10};
    int min, max;
    min_max(v, 9, &min, &max);
    printf("%d %d\n", min, max);
    return 0;
}
