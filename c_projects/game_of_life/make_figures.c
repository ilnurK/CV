#include <stdio.h>

#include "config.h"

void Figure0(FILE* fp, int y, int x);
void Figure1(FILE* fp, int y, int x);
void Figure2(FILE* fp, int y, int x);
void Figure3(FILE* fp, int y, int x);
void Figure4(FILE* fp, int y, int x);
void Figure5(FILE* fp, int y, int x);
void Figure6(FILE* fp, int y, int x);
void Figure7(FILE* fp, int y, int x);
void Figure8(FILE* fp, int y, int x);
void Figure9(FILE* fp, int y, int x);

int main() {
    char filename[6] = "0.txt";
    void (*funcs[10])(FILE*, int, int) = {Figure0, Figure1, Figure2, Figure3,
                                          Figure4, Figure5, Figure6, Figure7,
                                          Figure8, Figure9};
    for (int i = 0; i < 10; i++) {
        filename[0] = i + '0';
        FILE* fp = fopen(filename, "w");
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                funcs[i](fp, y, x);
            }
            // if (y != Y - 1) {
                // fprintf(fp, "%c", '\n');
            // }

        }
        fclose(fp);
    }
    return 0;
}

void Figure0(FILE* fp, int y, int x) {
    int rand_val = rand() % 10;
    char symb = (rand_val == 1) ? symbol_alive : symbol_empty;
    fprintf(fp, "%c", symb);
}

void Figure1(FILE* fp, int y, int x) {
    if ((y == Y / 2 || y == 3 || y == Y - 3) &&
        (x == X / 2 - 1 || x == X / 2 || x == X / 2 + 1)) {
        fprintf(fp, "%c", symbol_alive);
    } else {
        fprintf(fp, "%c", symbol_empty);
    }
}

void Figure2(FILE* fp, int y, int x) { ; }

void Figure3(FILE* fp, int y, int x) { ; }

void Figure4(FILE* fp, int y, int x) { ; }

void Figure5(FILE* fp, int y, int x) { ; }

void Figure6(FILE* fp, int y, int x) { ; }

void Figure7(FILE* fp, int y, int x) { ; }

void Figure8(FILE* fp, int y, int x) { ; }

void Figure9(FILE* fp, int y, int x) { ; }
