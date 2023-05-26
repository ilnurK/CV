#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* arr;
    int size;
    int idx;
    int cr;
} Tarr1;

void inputFunc1(Tarr1* input, char** arr) {
    char inp = ' ';
    while (inp != '\n') {
        inp = getchar();
        if (inp != '\n') {
            (*arr)[input->idx] = inp;
            if ((input->idx)++ > input->size) {
                input->size *= 2;
                *arr = realloc(*arr, input->size);
            }
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
    Tarr1 input = {.size = 2};
    input.arr = malloc(input.size), input.idx = 0;
    // printf("sizeof %lu\n", sizeof(&(input.arr)));
    inputFunc1(&input, &input.arr);
    outputFunc1(input);
    input.arr[2] = 'X';
    input.arr[20] = '&';
    // printf("sizeof %lu\n", sizeof((input.arr)));
    outputFunc1(input);

    free(input.arr);
    return 0;
}