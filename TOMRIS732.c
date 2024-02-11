#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char x[100], y[100];
    int c;
    int s[100];

    printf("Enter c: ");
    scanf("%d", &c);

    printf("Enter x: ");
    scanf("%s", x);

    printf("Enter y: ");
    scanf("%s", y);

    int b = 0;
    for (int i = strlen(x) - 1; i >= 0; --i) {
        int sum = x[i] - y[i] + b;
        s[i] = (sum < 0 ? sum + c : sum) % c;
        b = sum >= 0 ? 0 : -1;
    }
    printf("Result: ");
    for (int i = 0; i < strlen(x); ++i) {
        printf("%d", s[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}
