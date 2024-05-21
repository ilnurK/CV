#include "s21_snake_CLI.h"

void SnakeViewCLI::SnakeCLI(WINDOW* snake_win) {
  keypad(snake_win, TRUE);
  SnakeViewCLI view;
  view.Draw(snake_win);
  endwin();
}

void SnakeViewCLI::Draw(WINDOW* win) {
  status_ = s21::GameStatus::ON_AIR;
  DrawCycle(win);
  sc_.WriteScore();
  wclear(win);
  if (status_ == s21::GameStatus::WIN) {
    mvwprintw(win, 8, 0, "Congratulations!\n");
  } else {
    mvwprintw(win, 8, 4, "GAME\n");
    mvwprintw(win, 9, 4, "OVER\n");
  }
  wrefresh(win);
  wgetch(win);
}

void SnakeViewCLI::DrawCycle(WINDOW* win) {
  int key_in{KEY_NULL_}, std_time{std_speed_};
  wtimeout(win, std_time);
  bool is_pause = false;
  while (status_ == s21::GameStatus::ON_AIR && key_in != KEY_QUIT_) {
    key_in = wgetch(win);
    s21::Keys key = keys[key_in];
    if (key != s21::Keys::PAUSE && !is_pause) {
      s21::Dirs dir = static_cast<s21::Dirs>(key);

      if (key != s21::Keys::NULL_KEY && dir != sc_.GetDirection()) {
        napms(std_time / 2);
        status_ = sc_.SetState(s21::SnakeStates::SHIFTING, dir);
      } else {
        if (dir == sc_.GetDirection()) {
          ;
        } else {
          status_ = sc_.SetState(s21::SnakeStates::MOVING);
        }
      }
      if (status_ == s21::GameStatus::LEVEL_UP) {
        std_speed_ = static_cast<int>(0.8 * std_speed_);
        status_ = s21::GameStatus::ON_AIR;
      }
      if (key == s21::Keys::ACTION) {
        std_time = std_speed_ / 10;
        wtimeout(win, std_time);
      } else {
        std_time = std_speed_;
        wtimeout(win, std_time);
      }
      wclear(win);
      DrawField(win);
      wrefresh(win);
    } else if (key == s21::Keys::PAUSE && is_pause) {
      is_pause = false;
    } else {
      is_pause = true;
    }
  }
}

void SnakeViewCLI::DrawHorizontalFrame(WINDOW* win) {
  wprintw(win, "%c", FIELD_CORNER_);
  for (size_t x{1}; x < sc_.width + 1; ++x) {
    wprintw(win, "%c", FIELD_HORIZONTAL_);
  }
  wprintw(win, "%c\n", FIELD_CORNER_);
}

void SnakeViewCLI::DrawField(WINDOW* win) {
  DrawHorizontalFrame(win);
  for (size_t y{}; y < sc_.height; ++y) {
    wprintw(win, "%c", FIELD_VERTICAL_);
    for (size_t x{}; x < sc_.width; ++x) {
      wprintw(win, "%c", sc_.GetField()[y * sc_.width + x]);
    }
    wprintw(win, "%c\n", FIELD_VERTICAL_);
  }
  DrawHorizontalFrame(win);
  DrawSideMenu(win);
}

void SnakeViewCLI::DrawSideMenu(WINDOW* win) {
  size_t score = sc_.GetScore();
  highscore_ = (score > highscore_) ? score : highscore_;
  int y = 6, x = 13;
  mvwprintw(win, y, x, "  SCORE  \n");
  mvwprintw(win, y + 1, x, "    %lu  \n", score);
  mvwprintw(win, y + 2, x, "HIGHSCORE\n");
  mvwprintw(win, y + 3, x, "    %lu  \n", highscore_);
  mvwprintw(win, y + 4, x, "  LEVEL  \n");
  mvwprintw(win, y + 5, x, "    %lu  \n", sc_.GetLevel());
}