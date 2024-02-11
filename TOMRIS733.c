#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <cmath> 

int greatEq(const int* a, int n1, const int* b, int n2) {
    if (n1 > n2) return 1;
    if (n1 < n2) return 0;

    for (int i = n1 - 1; i >= 0; i--) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return 0;
    }

    return 1;
}

int* multConst(const int* number, int length, int constant, int c) {
    int* res = (int*)malloc((length + 1) * sizeof(int));
    int k = 0;
    for (int i = 0; i < length; i++) {
        int product = number[i] * constant + k;
        res[i] = product % c;
        k = product / c;
    }

    if (k > 0) {
        res[length] = k;
    }
    return res;
}

void plus(int* a, int n1, int* b, int n2, int** res, int* rlen, int c) {
    int maxLength = n1 > n2 ? n1 : n2;
    int carry = 0;

    *res = (int*)calloc(maxLength + 1, sizeof(int));

    int i = 0;
    for (; i < maxLength; i++) {
        int sum = carry;
        if (i < n1) {
            sum += a[n1 - 1 - i];
        }
        if (i < n2) {
            sum += b[n2 - 1 - i];
        }
        (*res)[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        (*res)[i] = carry;
        *rlen = maxLength + 1;
    }
    else {
        *rlen = maxLength;
    }
}

void minus(const int* a, int n1, const int* b, int n2, int* result, int c) {
    int k = 0, i = 0;

    for (; i < n2; i++) {
        int diff = a[i] - b[i] - k;
        if (diff < 0) {
            diff += 10;
            k = 1;
        }
        else {
            k = 0;
        }
        result[i] = diff;
    }

    for (; i < n1; i++) {
        int diff = a[i] - k;
        if (diff < 0) {
            diff += 10;
            k = 1;
        }
        else {
            k = 0;
        }
        result[i] = diff;
    }
}

void div(int* x, int n1, int* y, int n2, int* q, int* r, int c) {
    for (int j = 0; j <= (n1 - n2); j++) {
        q[j] = 0;
    }
    int* yByNum = multConst(y, n2, pow(c, (n1 - n2)), c);
    while (greatEq(x, (sizeof(x) / sizeof(x[0])), yByNum, (sizeof(yByNum) / sizeof(yByNum[0])))) {
        q[n1 - n2] = q[n1 - n2] + 1;
        int sizeX = (sizeof(x) / sizeof(x[0]));
        int sizeY = (sizeof(yByNum) / sizeof(yByNum[0]));
        int maxLength = sizeX > sizeY ? sizeX : sizeY;
        int* result = (int*)malloc(maxLength * sizeof(int));
        minus(x, sizeX, yByNum, sizeY, result, c);
        free(x);
        x = result;
    }
    for (int i = n1; i >= (n2 + 1); i--) {
        if (x[i] == y[n2]) {
            q[i - n2 - 1] = c - 1;
        }
        else {
            q[i - n2 - 1] = (x[i] * c + x[i - 1]) / y[n2];
        }
        while ((q[i - n2 - 1] * (y[n2] * c + y[n2 - 1])) > (x[i] * pow(c, 2) + x[i - 1] * c + x[i - 2])) {
            q[i - n2 - 1] -= 1;
        }
        int* yByQ = multConst(y, n2, q[i - n2 - 1], c);
        int* yByQByC = multConst(yByQ, n2, pow(c, (i - n2 - 1)), c);
        int sizeX = (sizeof(x) / sizeof(x[0]));
        int sizeY = (sizeof(yByQByC) / sizeof(yByQByC[0]));
        int maxLength = sizeX > sizeY ? sizeX : sizeY;
        int* result = (int*)malloc(maxLength * sizeof(int));
        minus(x, sizeX, yByQByC, sizeY, result, c);
        free(x);
        x = result;
        sizeX = (sizeof(x) / sizeof(x[0]));
        if (x[sizeX - 1] < 0) {
            int* yByC = multConst(y, n2, pow(c, (i - n2 - 1)), c);
            sizeY = (sizeof(yByC) / sizeof(yByC[0]));
            int* result = NULL;
            int resultLen = 0;
            plus(x, sizeX, yByC, sizeY, &result, &resultLen, c);
            free(x);
            x = result;
            q[i - n2 - 1] -= 1;
        }
    }
    r = x;
}

int main() {
    char x1[100], y1[100];
    int q[100], r[100];
    int c;
    int n1 = 0;
    int n2 = 0;

    printf("Enter c: ");
    scanf("%d", &c);

    printf("Enter x: ");
    scanf("%s", x1);

    printf("Enter y: ");
    scanf("%s", y1);

    int x[100], y[100];
    
    while (x1[n1] >= '0' && x1[n1] <= '9') {
        x[n1] = x1[n1] - '0';
        n1++;
    }

    while (y1[n2] >= '0' && y1[n2] <= '9') {
        y[n2] = y1[n2] - '0';
        n2++;
    }

    div(x, n1, y, n2, q, r, c);

    printf("Quotient q: ");
    int sizeQ = (sizeof(q) / sizeof(q[0]));
    for (int i = sizeQ - 1; i >= 0; i--) {
        printf("%d", q[i]);
    }
    printf("\n");

    printf("Remainder r: ");
    int sizeR = (sizeof(r) / sizeof(r[0]));
    for (int i = sizeR - 1; i >= 0; i--) {
        printf("%d", r[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}
