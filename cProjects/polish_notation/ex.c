#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* arr;
    int size;
    int idx;
    int cr;
} Tarr1;

void inputFunc1(Tarr1* input) {
    int buff = 5;
    input->size = buff, input->idx = 0;
    char inp = ' ';
    while (inp != '\n') {
        inp = getchar();
        if (inp != '\n') {
            input->arr[input->idx] = inp;
            (input->idx)++;
        }
    }
}

void outputFunc1(Tarr1 input) {
    for (int i = 0; i < input.idx; i++) {
        printf("%c", input.arr[i]);
    }
    printf("\n");
}

int main() {
    Tarr1 input;
    int a;
    inputFunc1(&input);
    outputFunc1(input);
    printf("sizeof %lu\n", sizeof((input)));
    input.arr[2] = 'X';
    input.arr[20] = '&';
    outputFunc1(input);
    printf("sizeof %lu\n", sizeof((input)));

    // free(input.arr);
    return 0;
}
