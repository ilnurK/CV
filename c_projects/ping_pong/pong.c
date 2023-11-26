#include "pong.h"

int main(void) {
  initscr();
  int delay = 1;
  halfdelay(delay);

  char field[Y][X];
  TRacket racket_left = {.size = 3,
                         .thin = 1,
                         .symbol = LEFT_RACKET,
                         .x = 1,
                         .key_up = KEY_LEFT_RACKET_UP,
                         .key_down = KEY_LEFT_RACKET_DOWN,
                         .key_up_alt = KEY_LEFT_RACKET_UP_ALT,
                         .key_down_alt = KEY_LEFT_RACKET_DOWN_ALT};
  TRacket racket_right = {.size = 3,
                          .thin = 1,
                          .symbol = RIGHT_RACKET,
                          .x = X - 2,
                          .key_up = KEY_RIGHT_RACKET_UP,
                          .key_down = KEY_RIGHT_RACKET_DOWN,
                          .key_up_alt = KEY_RIGHT_RACKET_UP_ALT,
                          .key_down_alt = KEY_RIGHT_RACKET_DOWN_ALT};
  TBall ball = {.symbol = SYMBOL_BALL, .speed = 1};
  TScore score_left = {.val = 0, .y = 0, .x = 5};
  TScore score_right = {.val = 0, .y = 0, .x = X - 5};
  int game_status = GAME_START;
  char key = ' ';
  StartGame(&racket_left, &racket_right, &ball);

  while (key != '\e' && game_status != GAME_END) {
    DrawStaticObj(field);
    clock_t start = clock();
    while (clock() - start < 50) {
      key = CheckInput(&game_status, &ball);
    }
    clear();
    if (game_status != GAME_PAUSE) {
      RacketMove(key, &racket_left);
      RacketMove(key, &racket_right);
      int score = BallMove(&game_status, &ball);
      if (score != 0) {
        game_status = GAME_PAUSE;
        (score == LEFT) ? score_left.val++ : score_right.val++;
        DrawDynamicObj(field, ball, racket_left, racket_right, score_left,
                       score_right);
        HoldMoment(field);
        AfterGoalMove(score, racket_left, racket_right, &ball);
      }
      CheckChangeDirection(&ball, racket_left, racket_right);
    } else {
      PrintText(field, "PAUSE", Y / 2, X / 2 - 3);
    }
    DrawDynamicObj(field, ball, racket_left, racket_right, score_left,
                   score_right);
    CheckScore(&game_status, score_left, score_right);
    FieldPrint(field);
    refresh();
  }
  WinnerPrint(field, score_left, score_right);
  endwin();
  PrintAtExit(field);
  return 0;
}

void DrawStaticObj(char field[Y][X]) {
  for (int y = 0; y < Y; y++) {
    for (int x = 0; x < X; x++) {
      if ((y == 0 || y == Y - 1) && (x == 0 || x == X - 1)) {
        field[y][x] = BORDER_CORNER;
      } else if ((y == 0 || y == Y - 1) && (x > 1 || x < X - 2)) {
        field[y][x] = BORDER_HORIZONTAL;
      } else if ((y > 0 || y < Y - 1) && (x == 0 || x == X - 1)) {
        field[y][x] = BORDER_VERTICAL;
      } else if (x == X / 2 - 1) {
        field[y][x] = SYMBOL_NET;
      } else {
        field[y][x] = FIELD_CELL;
      }
    }
  }
}

void StartGame(TRacket *racket_left, TRacket *racket_right, TBall *ball) {
  racket_left->y = Y / 2 - racket_left->size / 2;
  racket_right->y = Y / 2 - racket_right->size / 2;

  srand(time(NULL));
  int rand_define = rand() % 2;
  ball->y = (rand_define) ? racket_left->y + rand() % racket_left->size
                          : racket_right->y + rand() % racket_left->size;
  ball->x = (rand_define) ? racket_left->x + 1 : racket_right->x - 1;
}

char CheckInput(int *game_status, TBall *ball) {
  char key = getch();
  if (key == KEY_PAUSE || key == KEY_PAUSE_ALT) {
    *game_status = (*game_status == GAME_PAUSE) ? GAME_START : GAME_PAUSE;
  }
  if (key == KEY_GAME_SPEED_INC && ball->speed < 10) {
    ball->speed++;
  } else if (key == KEY_GAME_SPEED_DEC && ball->speed > 1) {
    ball->speed--;
  } else if (key == KEY_GAME_SPEED_STD) {
    ball->speed = 1;
  }
  return key;
}

void RacketMove(char key, TRacket *racket) {
  if ((key == racket->key_up || key == racket->key_up_alt) && (racket->y > 1)) {
    racket->y -= 1;
  } else if ((key == racket->key_down || key == racket->key_down_alt) &&
             (racket->y < Y - 1 - racket->size)) {
    racket->y += 1;
  }
}

int BallMove(int *game_status, TBall *ball) {
  (*game_status != GAME_PAUSE) ? BallAutoMove(ball) : 0;
  int flag_score = (ball->x == 0) ? RIGHT : (ball->x == X - 1) ? LEFT : 0;
  return flag_score;
}

void BallAutoMove(TBall *ball) {
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

void HoldMoment(char field[Y][X]) {
  clear();
  PrintText(field, "<<<GOAL>>>", Y / 2, X / 2 - 5);
  FieldPrint(field);
  clock_t start = clock();
  refresh();
  while ((clock() - start) / CLOCKS_PER_SEC < 2) {
    continue;
  }
  clear();
}

void AfterGoalMove(int score, TRacket racket_left, TRacket racket_right,
                   TBall *ball) {
  TRacket racket = (score == RIGHT) ? racket_left : racket_right;
  ball->x = (score == LEFT) ? racket.x - 1 : racket.x + 1;
  int rand_val = rand() % racket.size;
  ball->y = racket.y + rand_val;
  ball->direction_y = (rand_val == racket.size / 2) ? 0
                      : (rand_val == 0)             ? UP
                                                    : DOWN;
  ball->direction_x = (score == LEFT) ? LEFT : RIGHT;
}

void CheckChangeDirection(TBall *ball, TRacket racket_left,
                          TRacket racket_right) {
  CheckTouchRacket(ball, racket_left);
  CheckTouchRacket(ball, racket_right);
  CheckTouchBorder(ball);
}

void CheckTouchRacket(TBall *ball, TRacket racket) {
  int knock_zone = (racket.x > X / 2) ? racket.x - 1 : racket.x + 1;
  if ((ball->x == knock_zone) &&
      (ball->y > racket.y - 1 && ball->y < racket.y + racket.size)) {
    ball->direction_x = (racket.x > X / 2) ? LEFT : RIGHT;
    if (ball->direction_y == 0) {
      if (ball->y == racket.y) {
        ball->direction_y = UP;
      } else if (ball->y == racket.y + racket.size - 1) {
        ball->direction_y = DOWN;
      }
    } else if (ball->y == racket.y + racket.size / 2) {
      ball->direction_y = 0;
    }
  }
}

void CheckTouchBorder(TBall *ball) {
  if (ball->y == 1 || ball->y == Y - 2) {
    ball->direction_y = -ball->direction_y;
  }
}

void PrintText(char field[Y][X], char *text, int y, int x_start) {
  int i = 0;
  for (int x = x_start; text[i] != '\0'; x++, i++) {
    field[y][x] = text[i];
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
  if (score.val < 10) {
    field[y][x - 1] = '0';
    field[y][x] = score.val + '0';
  } else {
    field[y][x - 1] = score.val / 10 + '0';
    field[y][x] = score.val % 10 + '0';
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

void CheckScore(int *game_status, TScore score_left, TScore score_right) {
  int max_score = 21;
  if (score_right.val == max_score || score_left.val == max_score) {
    *game_status = GAME_END;
  }
}

void WinnerPrint(char field[Y][X], TScore score_left, TScore score_right) {
  int offset;
  char *phrase;
  if (score_left.val > score_right.val) {
    phrase = "YOU WON!";
    offset = X / 4 + 3;
  } else if (score_right.val > score_left.val) {
    phrase = "YOU WON!";
    offset = -X / 2 + X / 4 + 5;
  } else {
    phrase = "DRAW!!!";
    offset = 3;
  }
  PrintText(field, phrase, Y / 2, X / 2 - offset);
}

void PrintAtExit(char field[Y][X]) {
  for (int y = 0; y < Y; y++) {
    for (int x = 0; x < X; x++) {
      printf("%c", field[y][x]);
    }
    printf("\n");
  }
}