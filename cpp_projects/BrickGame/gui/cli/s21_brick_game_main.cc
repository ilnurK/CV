#include "s21_brick_game_main.h"

int main() {
  WINDOW *menu_win;
  int choice, highlight = 1;
  initscr();
  cbreak();
  noecho();
  int win_y = 22, win_x = 25;
  menu_win = newwin(win_y, win_x, 0, 0);
  keypad(menu_win, TRUE);
  bool flag_not_quit = true;
  while (flag_not_quit) {
    clear();
    refresh();
    MenuDisplay(menu_win, highlight);
    choice = wgetch(menu_win);
    ChooseChoice(choice, &highlight, &flag_not_quit);
  }
  delwin(menu_win);
  endwin();
  return 0;
}

void ChooseChoice(int choice, int *highlight, bool *flag_not_quit) {
  int win_y = 22, win_x = 25;
  if (choice == KEY_UP_) {
    if (*highlight == 1) {
      *highlight = MENU_EXIT;
    } else {
      *highlight -= 1;
    }
  } else if (choice == KEY_DOWN_) {
    if (*highlight == MENU_EXIT) {
      *highlight = 1;
    } else {
      *highlight += 1;
    }
  } else if (choice == 10) {
    clear();
    if (*highlight == MENU_SNAKE) {
      mvprintw(5, 5, "Snake starts...");
      refresh();
      getch();
      WINDOW *snake_win = newwin(win_y, win_x, 0, 0);
      SnakeViewCLI::SnakeCLI(snake_win);
      delwin(snake_win);
    } else if (*highlight == MENU_TETRIS) {
      mvprintw(5, 5, "Tetris starts...");
      refresh();
      getch();
      WINDOW *tetris_win = newwin(win_y, win_x, 0, 0);
      TetrisCLI(tetris_win);
      delwin(tetris_win);
    } else {
      mvprintw(5, 5, "See you again");
      *flag_not_quit = false;
    }
    getch();
    refresh();
  } else if (choice == KEY_QUIT_) {
    *flag_not_quit = false;
  }
}

void MenuDisplay(WINDOW *menu_win, int highlight) {
  int x, y, start_y, start_x;

  getmaxyx(menu_win, y, x);
  start_y = y / 2 - 3;
  start_x = x / 2 - 10;

  mvwprintw(menu_win, start_y, start_x, "Choose The Game:");

  if (highlight == MENU_SNAKE) {
    wattron(menu_win, A_REVERSE);
  }
  mvwprintw(menu_win, start_y + 1, start_x, "1. Snake");
  wattroff(menu_win, A_REVERSE);

  if (highlight == MENU_TETRIS) {
    wattron(menu_win, A_REVERSE);
  }
  mvwprintw(menu_win, start_y + 2, start_x, "2. Tetris");
  wattroff(menu_win, A_REVERSE);

  if (highlight == MENU_EXIT) {
    wattron(menu_win, A_REVERSE);
  }
  mvwprintw(menu_win, start_y + 3, start_x, "3. Quit");
  wattroff(menu_win, A_REVERSE);
  wrefresh(menu_win);
}