#include "s21_tetris_CLI.h"

void TetrisCLI(WINDOW* tetris_win) {
  keypad(tetris_win, TRUE);
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);
  if (error == NULL_ERROR) {
    DrawTetrisCycle(tetris_win, tetris_ctrl, &error);
    DeleteController(tetris_ctrl);
  }
}

void DrawTetrisCycle(WINDOW* win, S21TetrisController* ctrl,
                     S21TetrisError* error) {
  S21TetrisStates state = SetTetrisState(ctrl, START, NULL_DIR, error);
  size_t highscore = InitTetrisHighScore(error);
  int key = 0, key_counter = 0;
  int timer = STANDART_SPEED;
  wtimeout(win, timer);
  bool is_pause = false;
  while (state != GAME_OVER && key != KEY_QUIT_) {
    size_t old_level = GetTetrisLevel(ctrl);
    key = wgetch(win);
    if (key != KEY_PAUSE_ && !is_pause) {
      state = KeyToState(key, ctrl, &key_counter, error);
      if (*error != NULL_ERROR) {
        state = GAME_OVER;
      } else {
        size_t level = GetTetrisLevel(ctrl);
        SetTimer(win, level, old_level, &timer);
        wclear(win);
        DrawField(win, ctrl, highscore, level);
        wrefresh(win);
      }
    } else if (key != KEY_NULL_ && is_pause) {
      is_pause = false;
    } else {
      is_pause = true;
    }
  }
  WriteHighScore(ctrl->fsm, error);
  if (*error != NULL_ERROR) {
    ErrorHandler(win, error);
  }
  if (state == GAME_OVER) {
    wclear(win);
    mvwprintw(win, 8, 4, "GAME\n");
    mvwprintw(win, 9, 4, "OVER\n");
    wrefresh(win);
    wgetch(win);
  }
}

S21TetrisStates KeyToState(int key, S21TetrisController* ctrl, int* key_counter,
                           S21TetrisError* error) {
  S21TetrisStates state;
  if (key != KEY_NULL_) {
    bool flag_real_key = true;

    S21Dirs dir = GetDir(key, &flag_real_key);

    if (flag_real_key && *key_counter < 2) {
      state = SetTetrisState(ctrl, SHIFTING, dir, error);
      *key_counter += 1;
    } else {
      state = SetTetrisState(ctrl, MOVING, NULL_DIR, error);
      *key_counter = 0;
    }
  } else {
    state = SetTetrisState(ctrl, MOVING, NULL_DIR, error);
    *key_counter = 0;
  }
  return state;
}

S21Dirs GetDir(int key, bool* flag_real_key) {
  S21Dirs dir = NULL_DIR;
  if (key == KEY_LEFT_) {
    dir = LEFT;
  } else if (key == KEY_RIGHT_) {
    dir = RIGHT;
  } else if (key == KEY_DOWN_) {
    dir = DOWN;
  } else if (key == KEY_ACTION_) {
    dir = ACTION;
  } else if (key == KEY_PAUSE_) {
    dir = NULL_DIR;
    *flag_real_key = false;
  } else {
    *flag_real_key = false;
  }
  return dir;
}

void DrawHorizontalFrame(WINDOW* win, size_t x) {
  wprintw(win, "%c", FIELD_CORNER_);
  for (size_t j = 1; j < x + 1; j++) {
    wprintw(win, "%c", FIELD_HORIZONTAL_);
  }
  wprintw(win, "%c\n", FIELD_CORNER_);
}

void DrawField(WINDOW* win, S21TetrisController* ctrl, size_t hscore,
               size_t level) {
  size_t x = FIELD_WIDTH, y = FIELD_HEIGHT;
  DrawHorizontalFrame(win, x);
  for (size_t j = 0; j < y; j++) {
    wprintw(win, "%c", FIELD_VERTICAL_);
    for (size_t i = 0; i < x; i++) {
      S21XYPair xy = {(int)i, (int)j};
      wprintw(win, "%c", *FieldAt(ctrl->fsm->field, xy));
    }
    wprintw(win, "%c\n", FIELD_VERTICAL_);
  }
  DrawHorizontalFrame(win, x);
  DrawSideMenu(win, ctrl, hscore, level);
}

void DrawSideMenu(WINDOW* win, S21TetrisController* ctrl, size_t hscore,
                  size_t level) {
  size_t score = GetTetrisScore(ctrl);
  hscore = (score > hscore) ? score : hscore;
  int y = 4, x = 13;
  mvwprintw(win, y, x, "  SCORE  \n");
  mvwprintw(win, y + 1, x, "    %lu  \n", score);
  mvwprintw(win, y + 2, x, "HIGHSCORE\n");
  mvwprintw(win, y + 3, x, "    %lu  \n", hscore);
  mvwprintw(win, y + 4, x, "  LEVEL  \n");
  mvwprintw(win, y + 5, x, "    %lu  \n", level);
  mvwprintw(win, y + 6, x, "   NEXT  \n");
  mvwprintw(win, y + 7, x, "  FIGURE \n");
  for (size_t i = 0; i < FIG_LEN; i++) {
    S21XYPair xy = ctrl->fsm->next_figure->data[i];
    mvwprintw(win, y + 10 + xy.y, x + xy.x, "%c", FIGURE_SYMBOL);
  }
}

void SetTimer(WINDOW* win, size_t level, size_t old_level, int* timer) {
  if (level - old_level) {
    *timer = (int)(0.8 * (*timer));
    wtimeout(win, *timer);
  }
}

void ErrorHandler(WINDOW* win, S21TetrisError* error) {
  wclear(win);
  if (*error == PATH_ERROR) {
    mvwprintw(win, 6, 4, "PATH_ERROR\n");
  } else if (*error == BAD_ALLOC) {
    mvwprintw(win, 6, 4, "BAD_ALLOC\n");
  }
  wrefresh(win);
  wgetch(win);
}