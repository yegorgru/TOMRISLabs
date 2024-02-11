#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdlib.h> 

int main() {
    int n = -1;
    int c = -1;
    int a[100];
    while (n < 0 || c < 2) {
        printf("Enter n: ");
        scanf("%d", &n);
        printf("Enter c: ");
        scanf("%d", &c);
        if (n < 0 || c < 2) {
            printf("n should be >= 0, c >= 2\n");
        }
    }
    int i = 0;
    int x = n;
    int q = x / c;
    a[0] = x - q * c;
    while (q > 0) {
        ++i;
        x = q;
        q = x / c;
        a[i] = x - q * c;
    }
    printf("Result: ");
    for (; i >= 0; --i) {
        printf("%d", a[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}
