#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int idx;
    char* arr;
} Tarr;

int inputFunc(Tarr* input) {
    int flag_error = 0;
    input->size = 1;
    input->arr = malloc(input->size * sizeof(char));
    input->idx = 0;
    char inp = ' ';
    while (inp != '\n' && flag_error != -1) {
        scanf("%c", &inp);
        if (inp != '\n') {
            input->arr[input->idx] = inp;
            // input->idx += 1;
            if ((input->idx)++ > input->size) {
                input->size *= 2;
                Tarr* temp = realloc(input, sizeof(input + input->size));
                if (temp != NULL) {
                    input = temp;
                    char* temp = realloc(input->arr, input->size);
                    if (temp != NULL) {
                        input->arr = temp;
                    }
                    else flag_error = -1;
                } else {
                    flag_error = -1;
                }
            }
        }
    }
    return flag_error;
}

void outputFunc(Tarr input) {
    for (int i = 0; i < input.idx; i++) {
        printf("%c", input.arr[i]);
    }
    printf("\n");
}

int main() {
    Tarr* input = (Tarr*)malloc(sizeof(Tarr));
    printf("sizeof - %ld\n", sizeof(input));
    if (inputFunc(input) == 0) {
        outputFunc(*input);
        printf("\nsizeof - %ld\n", sizeof(input));
        printf("\nsizeof arr - %ld\n", sizeof(input->arr));
    } else {
        printf("n/a");
    }
    free(input->arr);
    free(input);
    return 0;
}