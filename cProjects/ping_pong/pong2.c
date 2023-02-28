#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

void DrawStaticObj(char field[Y][X]);
void Init(TRacket*, TRacket*, TBall*);
void CheckInput(char*, int*, TRacket*, TRacket*, TBall*);
void MoveRacket(char, TRacket*);
int BallMove(int*, TBall*, TRacket, TRacket, char field[Y][X]);
void AfterWinInit(TBall*, int*, int, TRacket, char field[Y][X]);
void LooseCam(char field[Y][X], TBall, TRacket);
void CheckChangeDirection(TBall*, TRacket);
void PrintPause(char field[Y][X]);
void DrawDynamicObj(char field[Y][X], TBall, TRacket, TRacket, TScore, TScore);
void DrawScore(char field[Y][X], int, int, TScore);
void FieldPrint(char field[Y][X]);
void CheckScore(int*, TScore, TScore);
void CheckWinner(char field[Y][X], TScore, TScore);
void FieldPrintEnd(char field[Y][X]);

int main(void) {
    initscr();

    char field[Y][X];
    TRacket racket_left = {.size = 3,
                           .thin = 1,
                           .symbol = '{',
                           .x = 1,
                           .key_up = 'a',
                           .key_down = 'z',
                           .key_up_alt = 'A',
                           .key_down_alt = 'Z'};
    TRacket racket_right = {.size = 3,
                            .thin = 1,
                            .symbol = '}',
                            .x = X - 2,
                            .key_up = 'k',
                            .key_down = 'm',
                            .key_up_alt = 'K',
                            .key_down_alt = 'M'};
    TBall ball = {.symbol = 'o', .speed = 1};
    TScore score_left = {.value = 0, .y = 0, .x = 5};
    TScore score_right = {.value = 0, .y = 0, .x = X - 5};
    Init(&racket_left, &racket_right, &ball);

    int delay = 1;
    halfdelay(delay);

    int flag_game_status = flag_game_start;
    char key = ' ';
    while (key != 'q' && flag_game_status != flag_game_end) {
        clock_t start = clock();
        DrawStaticObj(field);
        while (clock() - start < 50) {
            CheckInput(&key, &flag_game_status, &racket_left, &racket_right,
                       &ball);
        }
        clear();
        if (flag_game_status != flag_game_pause) {
            int flag_score = BallMove(&flag_game_status, &ball, racket_left,
                                      racket_right, field);
            (flag_score != 0)
                ? (flag_score == 1) ? score_right.value++ : score_left.value++
                : 0;
            halfdelay(delay);
        } else {
            PrintPause(field);
        }
        DrawDynamicObj(field, ball, racket_left, racket_right, score_left,
                       score_right);
        CheckScore(&flag_game_status, score_left, score_right);
        FieldPrint(field);
        refresh();
    }
    CheckWinner(field, score_left, score_right);
    endwin();
    FieldPrintEnd(field);
    return 0;
}

void DrawStaticObj(char field[Y][X]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if ((y == 0 || y == Y - 1) && (x == 0 || x == X - 1)) {
                field[y][x] = border_corner;
            } else if ((y == 0 || y == Y - 1) && (x > 1 || x < X - 2)) {
                field[y][x] = border_horizontal;
            } else if ((y > 0 || y < Y - 1) && (x == 0 || x == X - 1)) {
                field[y][x] = border_vertical;
            } else if (x == X / 2 - 1) {
                field[y][x] = symbol_net;
            } else {
                field[y][x] = field_cell;
            }
        }
    }
}

void Init(TRacket* racket_left, TRacket* racket_right, TBall* ball) {
    racket_left->y = Y / 2 - racket_left->size / 2;
    racket_right->y = Y / 2 - racket_right->size / 2;

    srand(time(NULL));
    int rand_define = rand() % 2;
    ball->y = (rand_define) ? racket_left->y + rand() % racket_left->size
                            : racket_right->y + rand() % racket_left->size;
    ball->x = (rand_define) ? racket_left->x + 1 : racket_right->x - 1;
}

void CheckInput(char* key, int* flag_game_status, TRacket* racket_left,
                TRacket* racket_right, TBall* ball) {
    *key = getch();
    if (*key == 'p') {
        *flag_game_status = (*flag_game_status == flag_game_pause)
                                ? flag_game_play
                                : flag_game_pause;
    }
    if (*flag_game_status != flag_game_pause) {
        MoveRacket(*key, racket_left);
        MoveRacket(*key, racket_right);
    }
    if (*key == '=' && ball->speed < 5) {
        ball->speed++;
    } else if (*key == '-' && ball->speed > 1) {
        ball->speed--;
    } else if (*key == '0') {
        ball->speed = 1;
    }
}

void MoveRacket(char key, TRacket* racket) {
    if ((key == racket->key_up || key == racket->key_up_alt) &&
        (racket->y > 1)) {
        racket->y -= 1;
    } else if ((key == racket->key_down || key == racket->key_down_alt) &&
               (racket->y < Y - 1 - racket->size)) {
        racket->y += 1;
    }
}

int BallMove(int* flag_game_status, TBall* ball, TRacket racket_left,
             TRacket racket_right, char field[Y][X]) {
    int flag_score = 0;
    if (*flag_game_status != flag_game_pause) {
        int y = ball->y + ball->speed * ball->direction_y;
        if (y > 0 && y < Y - 1) {
            ball->y = y;
        } else {
            ball->y = (y <= 0) ? 1 : Y - 2;
        }

        int x = ball->x + ball->speed * ball->direction_x;
        if (x > -1 && x < X) {
            ball->x = x;
        } else {
            ball->x = (x < 0) ? 0 : X - 1;
        }
    }
    if (ball->x == 0) {  // При ударе о левую границу, победа правого игрока
        flag_score = right;
        AfterWinInit(ball, flag_game_status, flag_score, racket_left, field);
    } else if (ball->x ==
               X - 1) {  // При ударе о правую границу, победа левого игрока
        flag_score = left;
        AfterWinInit(ball, flag_game_status, flag_score, racket_right, field);
    }
    CheckChangeDirection(ball, racket_left);
    CheckChangeDirection(ball, racket_right);
    if (ball->y == 1 ||
        ball->y == Y - 2) {  // При ударе о верхнюю или нижнюю границу изменение
                             // направления по Y
        ball->direction_y = -ball->direction_y;
    }
    return flag_score;
}

void AfterWinInit(TBall* ball, int* flag_game_status, int flag_score,
                  TRacket racket, char field[Y][X]) {
    LooseCam(field, *ball, racket);
    *flag_game_status = flag_game_pause;
    ball->x = (flag_score == left) ? racket.x - 1 : racket.x + 1;
    int rand_val = rand() % racket.size;
    ball->y = racket.y + rand_val;
    ball->direction_y = (rand_val == racket.size / 2) ? 0
                        : (rand_val == 0)             ? up
                                                      : down;
    ball->direction_x = (flag_score == left) ? left : right;
}

void LooseCam(char field[Y][X], TBall ball, TRacket racket) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (x == ball.x && y == ball.y) {
                field[y][x] = ball.symbol;
            } else if (x == racket.x && y > racket.y - 1 &&
                       y < racket.y + racket.size) {
                field[y][x] = racket.symbol;
            }
        }
    }
    clear();
    FieldPrint(field);
    clock_t start = clock();
    refresh();
    while ((clock() - start) / CLOCKS_PER_SEC < 2) {
        continue;
    }
}

void CheckChangeDirection(TBall* ball, TRacket racket) {
    // При ударе о ракетку
    int knock_zone = (racket.x > X / 2) ? racket.x - 1 : racket.x + 1;
    if ((ball->x == knock_zone) &&
        (ball->y > racket.y - 1 && ball->y < racket.y + racket.size)) {
        ball->direction_x = (racket.x > X / 2) ? left : right;
        if (ball->direction_y == 0) {
            if (ball->y == racket.y) {
                ball->direction_y = up;
            } else if (ball->y == racket.y + racket.size - 1) {
                ball->direction_y = down;
            }
        } else if (ball->y == racket.y + racket.size / 2) {
            ball->direction_y = 0;
        }
    }
}

void PrintPause(char field[Y][X]) {
    char* pause = "PAUSE";
    int i = 0;
    for (int x = X / 2 - 3; pause[i] != '\0'; x++, i++) {
        field[Y / 2][x] = pause[i];
    }
}

void DrawDynamicObj(char field[Y][X], TBall ball, TRacket racket_left,
                    TRacket racket_right, TScore score_left,
                    TScore score_right) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (x == ball.x && y == ball.y) {
                field[y][x] = ball.symbol;
            } else if (x == racket_left.x && y > racket_left.y - 1 &&
                       y < racket_left.y + racket_left.size) {
                field[y][x] = racket_left.symbol;
            } else if (x == racket_right.x && y > racket_right.y - 1 &&
                       y < racket_right.y + racket_right.size) {
                field[y][x] = racket_right.symbol;
            } else if (y == score_left.y && x == score_left.x) {
                DrawScore(field, y, x, score_left);
            } else if (y == score_right.y && x == score_right.x) {
                DrawScore(field, y, x, score_right);
            }
        }
    }
}

void DrawScore(char field[Y][X], int y, int x, TScore score) {
    if (score.value < 10) {
        field[y][x - 1] = '0';
        field[y][x] = score.value + '0';
    } else {
        field[y][x - 1] = score.value / 10 + '0';
        field[y][x] = score.value % 10 + '0';
    }
}

void FieldPrint(char field[Y][X]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printw("%c", field[y][x]);
        }
        printw("\n");
    }
}

void CheckScore(int* flag_game_status, TScore score_left, TScore score_right) {
    int max_score = 21;
    if (score_right.value == max_score || score_left.value == max_score) {
        *flag_game_status = flag_game_end;
    }
}

void CheckWinner(char field[Y][X], TScore score_left, TScore score_right) {
    int i = 0, offset;
    char* phrase;
    if (score_left.value > score_right.value) {
        phrase = "YOU WON!";
        offset = X / 4 + 3;
    } else if (score_right.value > score_left.value) {
        phrase = "YOU WON!";
        offset = -X / 2 + X / 4 + 5;
    } else {
        phrase = "DRAW!!!";
        offset = 3;
    }
    for (int x = X / 2 - offset; phrase[i] != '\0'; x++, i++) {
        field[Y / 2][x] = phrase[i];
    }
}

void FieldPrintEnd(char field[Y][X]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printf("%c", field[y][x]);
        }
        printf("\n");
    }
}