#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** arr;
    int size;
    int idx;
    int cr;
} Tarr;

Tarr inputToCorrect(int* flag_error);
int cheksForDigXSign(char inp);
void addChar(char inp, Tarr* output, int* flag_error);
void recordLexem(char inp, int* start_record, Tarr* output);
void addLexem(Tarr* output, int* start_record, int* flag_error);
void reSize(Tarr* output, int* flag_error);
void printOutput(Tarr output);

int main() {
    int flag_error = 0;
    Tarr output = inputToCorrect(&flag_error);
    if (flag_error == 0) {
        printOutput(output);
    } else {
        printf("n/a");
    }
    return 0;
}

Tarr inputToCorrect(int* flag_error) {
    int max_lexem_len = 5, buffer = 10, start_record = 0;
    // char* lexem = malloc(max_lexem_len * sizeof(char));
    // Tarr output = {
    // .arr = malloc(buffer * sizeof(lexem)), .size = buffer, .idx = 0};

    char** A = malloc(buffer * sizeof(char*));
    for (int i = 0; i < buffer; i++) {
        A[i] = malloc(max_lexem_len * sizeof(char));
    }
    char*** B = &A;
    Tarr output = {.arr = *B, .size = buffer, .idx = 0};
    char inp = ' ';
    while (*flag_error != -1 && inp != '\n') {
        inp = getchar();
        if (inp != '\n') {
            if (cheksForDigXSign(inp)) {
                start_record ? addLexem(&output, &start_record, flag_error) : 0;
                addChar(inp, &output, flag_error);
            } else {
                recordLexem(inp, &start_record, &output);
            }
        }
    }
    return output;
}

int cheksForDigXSign(char inp) {
    char* xsigns = "x+-*/^()";
    int flag_add = 0;
    if (inp >= '0' && inp <= '9') {
        flag_add = 1;
    } else {
        for (int i = 0; i < 8; i++) {
            if (inp == xsigns[i]) {
                flag_add = 1;
            }
        }
    }
    return flag_add;
}

void recordLexem(char inp, int* start_record, Tarr* output) {
    output->cr = (*start_record == 0) ? 0 : output->cr;
    output->arr[output->idx][output->cr] = inp;
    output->cr += 1;
    *start_record = 1;
}

void addLexem(Tarr* output, int* start_record, int* flag_error) {
    char lexems[][5] = {"sin", "cos", "tan", "ctg"};
    int flag_add = 0;
    for (int i = 0; i < 4; i++) {
        flag_add = (output->arr[output->idx] = lexems[i]) ? 1 : flag_add;
    }
    if (flag_add == 0) {
        *flag_error = 1;
    } else {
        output->idx += 1;
        (output->idx > output->size) ? reSize(output, flag_error) : 0;
        *start_record = 0;
    }
}

void addChar(char inp, Tarr* output, int* flag_error) {
    char inp_str[2] = {inp, '\0'};
    output->arr[output->idx] = inp_str;
    output->idx += 1;
    (output->idx > output->size) ? reSize(output, flag_error) : 0;
    printf("%s\n", output->arr[output->idx - 1]);
}

void reSize(Tarr* output, int* flag_error) {
    output->size *= 2;
    char** temp = realloc(output->arr, output->size);
    if (temp == NULL) {
        *flag_error = 1;
    } else {
        output->arr = temp;
    }
}

void printOutput(Tarr output) {
    for (int i = 0; i < output.idx; i++) {
        printf("%s\n", output.arr[i]);
    }
}
