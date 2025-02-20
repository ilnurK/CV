#include "s21_brick_games_main.h"

namespace s21 {

void BrickGamesNcurses::Menu() {
  menu_win_ = newwin(win_y_, win_x_, 0, 0);
  keypad(menu_win_, TRUE);
  while (!is_quit_) {
    clear();
    ShowMenu();
    choice_ = wgetch(menu_win_);
    ChooseGame();
    wrefresh(menu_win_);
  }
  delwin(menu_win_);
}

void BrickGamesNcurses::ShowMenu() {
  int y_max, x_max;
  getmaxyx(menu_win_, y_max, x_max);
  int y = y_max / 2 - 3;
  int x = x_max / 2 - 10;

  mvwprintw(menu_win_, y, x, "Choose The Game:");
  if (highlight_ == MENU_SNAKE) {
    wattron(menu_win_, A_REVERSE);
  }
  mvwprintw(menu_win_, y + 1, x, "1. Snake");
  wattroff(menu_win_, A_REVERSE);

  if (highlight_ == MENU_TETRIS) {
    wattron(menu_win_, A_REVERSE);
  }
  mvwprintw(menu_win_, y + 2, x, "2. Tetris");
  wattroff(menu_win_, A_REVERSE);

  if (highlight_ == MENU_RACE) {
    wattron(menu_win_, A_REVERSE);
  }

  mvwprintw(menu_win_, y + 3, x, "3. Race");
  wattroff(menu_win_, A_REVERSE);

  if (highlight_ == MENU_EXIT) {
    wattron(menu_win_, A_REVERSE);
  }

  mvwprintw(menu_win_, y + 4, x, "4. Quit");
  wattroff(menu_win_, A_REVERSE);

  wrefresh(menu_win_);
}

void BrickGamesNcurses::ChooseGame() {
  if (choice_ == KEY_UP_) {
    if (highlight_ == 1) {
      highlight_ = MENU_EXIT;
    } else {
      highlight_ -= 1;
    }
  } else if (choice_ == KEY_DOWN_) {
    if (highlight_ == MENU_EXIT) {
      highlight_ = 1;
    } else {
      highlight_ += 1;
    }
  } else if (choice_ == KEY_ENTER_) {
    clear();
    std::unique_ptr<CliViewBase> view;
    if (highlight_ == MENU_SNAKE) {
      view = std::make_unique<CliView<SnakeController, SnakeStates>>();
      mvprintw(sub_y_, sub_x_, "Snake starts...");
    } else if (highlight_ == MENU_TETRIS) {
      view = std::make_unique<CliView<TetrisController, S21TetrisStates>>();
      mvprintw(sub_y_, sub_x_, "Tetris starts...");
    } else if (highlight_ == MENU_RACE) {
      view = std::make_unique<CliView<RaceCController, RaceStates>>();
      mvprintw(sub_y_, sub_x_, "Race starts...");
    } else {
      mvprintw(sub_y_, sub_x_, "See you again");
      is_quit_ = true;
    }

    if (!is_quit_) {
      refresh();
      getch();
      WINDOW *new_win = newwin(win_y_, win_x_, 0, 0);
      if (view.get()) {
        view->Play(new_win);
      }
      delwin(new_win);
    }
    refresh();
    getch();
  } else if (choice_ == KEY_QUIT_) {
    is_quit_ = true;
  }
}
}  // namespace s21

int main() {
  initscr();
  cbreak();
  noecho();
  try {
    s21::BrickGamesNcurses app{};
    app.Menu();
  } catch (const std::exception &e) {
    printw("Error occured %s", e.what());
    refresh();
    getch();
  }
  endwin();

  return 0;
}
