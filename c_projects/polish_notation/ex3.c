#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int idx;
    char* arr;
} Tarr1;

void inputFunc1(Tarr1* input) {
    input->size = 1;
    input->arr = malloc(input->size * sizeof(char));
    input->idx = 0;
    char inp = ' ';
    while (inp != '\n') {
        scanf("%c", &inp);
        if (inp != '\n') {
            input->arr[input->idx] = inp;
            (input->idx)++;
        }
    }
    int sum = 0;
    for (int i = 0; i < input->idx; i++, sum++);
    printf("Addres - %i\n", sum);
}

void outputFunc1(Tarr1 input) {
    for (int i = 0; i < input.idx; i++) {
        printf("%c", input.arr[i]);
    }
    printf("\n");
}

int main() {
    Tarr1* input = malloc(32);
    printf("Addres - %ld\n", sizeof(*input));
    inputFunc1(input);
    outputFunc1(*input);
    free(input->arr);
    free(input);
    return 0;
}