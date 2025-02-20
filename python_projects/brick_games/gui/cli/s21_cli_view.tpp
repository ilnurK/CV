#include <ncurses.h>

#include "../../controllers/race/s21_race_controller.h"
#include "../../controllers/snake/s21_snake_controller.h"
#include "../../controllers/tetris/s21_tetris_controller.h"
#include "s21_cli_view.h"

namespace s21 {

template <typename C, typename S>
void CliView<C, S>::Play(WINDOW *win_in) {
    state_ = S::START;
    win_ = win_in;
    highscore_ = ctrl_.GetHighScore();
    keypad(win_, true);
    nodelay(win_, true);
    InitExtraInfo();
    is_pause_ = false;
    while (!IsEndState() && IsNotEndKey(key_in_)) {
        key_in_ = wgetch(win_);
        if (IsNotEndKey(key_in_)) {
            PlayFSM();
        }
    }

    if (score_ > highscore_) {
        ctrl_.SetHighScore(score_);
        ctrl_.WriteHighScore();
    }

    wclear(win_);
    if (state_ == S::WIN) {
        mvwprintw(win_, 8, 0, "Congratulations!\n");
    } else {
        mvwprintw(win_, 8, 4, "GAME\n");
        mvwprintw(win_, 9, 4, "OVER\n");
    }

    wrefresh(win_);
    wgetch(win_);
}

template <typename C, typename S>
void CliView<C, S>::InitExtraInfo() {
    if ((extra_info_size_ = ctrl_.GetAddInfoSize())) {
        extra_info_ = ctrl_.GetAddInfo();
        extra_info_char_ = ctrl_.GetAddInfoChar();
    }
}

template <typename C, typename S>
void CliView<C, S>::PlayFSM() {
    if ((key_in_ != KEY_PAUSE_ && key_in_ != KEY_PAUSE_L_) && !is_pause_) {
        dirs dir = KeysConvert();
        state_ = ctrl_.SetState(state_, dir);
        DrawField();
    } else if ((key_in_ == KEY_PAUSE_ || key_in_ == KEY_PAUSE_L_) &&
               is_pause_) {
        is_pause_ = false;
    } else {
        is_pause_ = true;
        mvwprintw(win_, y_side_ + 6, x_side_, "  PAUSE  \n");
        wrefresh(win_);
        key_in_ = KEY_NULL_;
    }
    flushinp();
    napms(delay_);
}

template <typename C, typename S>
dirs CliView<C, S>::KeysConvert() {
    auto it = keys_to_dir_.find(key_in_);
    dirs dir = NULL_DIR;
    if (it != keys_to_dir_.end()) {
        dir = it->second;
    }
    return dir;
}

template <typename C, typename S>
void CliView<C, S>::DrawField() {
    wclear(win_);

    size_t height{Controller<S>::field_height},
        width{Controller<S>::field_width};
    DrawHorizontalFrame(width);
    for (size_t y{}; y < height; ++y) {
        wprintw(win_, "%c", field_vertical_);
        for (size_t x{}; x < width; ++x) {
            wprintw(win_, "%c", ctrl_.GetField()[y * width + x]);
        }
        wprintw(win_, "%c\n", field_vertical_);
    }
    DrawHorizontalFrame(width);
    DrawSideMenu();

    wrefresh(win_);
}

template <typename C, typename S>
void CliView<C, S>::DrawHorizontalFrame(const size_t width) {
    wprintw(win_, "%c", field_corner_);
    for (size_t x{1}; x < width + 1; ++x) {
        wprintw(win_, "%c", field_horizontal_);
    }
    wprintw(win_, "%c\n", field_corner_);
}

template <typename C, typename S>
void CliView<C, S>::DrawSideMenu() {
    score_ = ctrl_.GetScore();
    level_ = ctrl_.GetLevel();

    delay_ = static_cast<size_t>(std_speed_ - double(level_) * 50);
    if ((key_in_ == KEY_ACTION_ && typeid(C) == typeid(SnakeController)) ||
        (key_in_ == KEY_UP_ && typeid(C) == typeid(RaceCController))) {
        delay_ /= 5;
    };

    mvwprintw(win_, y_side_, x_side_, "  SCORE  \n");
    mvwprintw(win_, y_side_ + 1, x_side_, "    %lu  \n", score_);
    mvwprintw(win_, y_side_ + 2, x_side_, "HIGHSCORE\n");
    size_t highscore = (score_ > highscore_) ? score_ : highscore_;
    mvwprintw(win_, y_side_ + 3, x_side_, "    %lu  \n", highscore);
    mvwprintw(win_, y_side_ + 4, x_side_, "  LEVEL  \n");
    mvwprintw(win_, y_side_ + 5, x_side_, "    %lu  \n", level_);
    if (ctrl_.GetAddInfoSize()) {
        mvwprintw(win_, y_side_ + 6, x_side_, "  NEXT  \n");
    } else if (typeid(C) == typeid(RaceCController)) {
        mvwprintw(win_, y_side_ + 6, x_side_, "  SPEED  \n");
        size_t speed = ctrl_.GetSpeed(delay_);
        mvwprintw(win_, y_side_ + 7, x_side_, "    %lu  \n", speed);
    }

    for (size_t i = 0; i < extra_info_size_; i++) {
        extra_info_ = ctrl_.GetAddInfo();
        mvwprintw(win_, y_side_ + 10 + extra_info_[i].first,
                  x_side_ + extra_info_[i].second, "%c", extra_info_char_);
    }
}

}  // namespace s21