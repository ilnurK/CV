#include "../../../controllers/race/s21_race_controller.h"
#include "../../../controllers/snake/s21_snake_controller.h"
#include "../../../controllers/tetris/s21_tetris_controller.h"

namespace s21 {

// clang-format off
#include "s21_desktop_view.h"
#include "s21_bg_window.h"
// clang-format on

template <typename C, typename S>
DesktopView<C, S>::DesktopView(MainWindow* win_in) {
    state_ = S::START;
    highscore_ = ctrl_.GetHighScore();
    win_ = win_in;
    win_->SetPlayingStatus(true);
    WindowSetter();
    is_pause_ = false;
}

template <typename C, typename S>
void DesktopView<C, S>::WindowSetter() {
    scene_.reset(new QGraphicsScene(win_->GetSceneRect(), nullptr));
    win_->GetView()->setScene(scene_.data());
    scene_->clear();

    if ((extra_info_size_ = ctrl_.GetAddInfoSize())) {
        InitExtraInfoScene();
    } else {
        OffAddInfo();
    }
}

template <typename C, typename S>
void DesktopView<C, S>::InitExtraInfoScene() {
    extra_info_ = ctrl_.GetAddInfo();
    extra_info_char_ = ctrl_.GetAddInfoChar();
    win_->SetExtraViewVisible(true);
    QGraphicsView* extra_view = win_->GetExtraView();
    extra_scene_.reset(new QGraphicsScene(0, 0, extra_view->viewport()->width(),
                                          extra_view->viewport()->height(),
                                          nullptr));
    extra_view->setScene(extra_scene_.data());
}

template <typename C, typename S>
void DesktopView<C, S>::DrawExtraScene() {
    extra_scene_->clear();
    extra_info_ = ctrl_.GetAddInfo();

    int x_offset = GetExtraSceneXOffset(extra_info_);
    int x_middle = extra_scene_->width() / 2;
    double nf_scale = (extra_scene_->height() + 2) / extra_info_size_;
    int y_offset = 3;  // initial outfield min - 2
    for (size_t i{}; i < extra_info_size_; ++i) {
        int x = x_middle + (extra_info_[i].second - x_offset) * nf_scale;
        int y = (extra_info_[i].first + y_offset) * nf_scale;
        extra_scene_->addRect(x, y, nf_scale - margin_, nf_scale - margin_,
                              QPen(Qt::NoPen), QBrush(Qt::black));
    }
}

template <typename C, typename S>
size_t DesktopView<C, S>::GetExtraSceneXOffset(
    std::vector<std::pair<int, int>>& info) {
    size_t x_sum{};
    for (size_t i{}; i < extra_info_size_; ++i) {
        x_sum += info[i].second;
    }
    return x_sum / extra_info_size_ + 1;
}

template <typename C, typename S>
void DesktopView<C, S>::OffAddInfo() {
    win_->SetExtraViewVisible(false);
}

template <typename C, typename S>
void DesktopView<C, S>::Play() {
    if (!IsEndState()) {
        key_in_ = win_->GetKey();
        if ((key_in_ != Keys::PAUSE) && !is_pause_) {
            dirs dir = KeysConvert();
            state_ = ctrl_.SetState(state_, dir);
            DrawField();
            if (extra_info_size_) {
                DrawExtraScene();
            }
            LabelAndDelaySetter();
        } else if (key_in_ == Keys::PAUSE) {
            is_pause_ = (is_pause_) ? false : true;
        }
        win_->GetTimer()->start(delay_);
    } else {
        EndGame();
    }
}

template <typename C, typename S>
dirs DesktopView<C, S>::KeysConvert() {
    auto it = keys_to_dir_.find(key_in_);
    dirs dir = NULL_DIR;
    if (it != keys_to_dir_.end()) {
        dir = it->second;
    }
    return dir;
}

template <typename C, typename S>
void DesktopView<C, S>::DrawField() {
    scene_->clear();
    size_t height{Controller<S>::field_height},
        width{Controller<S>::field_width};
    for (size_t y{}; y < height; ++y) {
        for (size_t x{}; x < width; ++x) {
            char c = ctrl_.GetField()[y * width + x];
            SymbolHandle(c, y, x, width);
        }
    }
}

template <typename C, typename S>
void DesktopView<C, S>::SymbolHandle(const char c, const int y, const int x,
                                     const int wx) {
    if (ctrl_.IsFilledCell(c)) {
        scene_->addRect(x * wx, y * wx, wx - margin_, wx - margin_,
                        QPen(Qt::NoPen), QBrush(Qt::black));
    }
}

template <typename C, typename S>
void DesktopView<C, S>::LabelAndDelaySetter() {
    score_ = ctrl_.GetScore();
    level_ = ctrl_.GetLevel();
    delay_ = static_cast<size_t>(std_speed_ - double(level_) * 45);
    if ((key_in_ == Keys::ACTION && typeid(C) == typeid(SnakeController)) ||
        (key_in_ == Keys::UP && typeid(C) == typeid(RaceCController))) {
        delay_ /= 5;
    }

    win_->SetScore(score_);
    size_t hscore = (score_ > highscore_) ? score_ : highscore_;
    win_->SetHighScore(hscore);
    win_->SetLevel(level_);
    if (typeid(C) == typeid(RaceCController)) {
        size_t speed = ctrl_.GetSpeed(delay_);
        win_->SetSpeed(speed);
    }
}

template <typename C, typename S>
void DesktopView<C, S>::EndGame() {
    if (score_ > highscore_) {
        ctrl_.WriteHighScore();
    }

    win_->GetTimer()->stop();
    PrintEndGame();
    win_->SetPlayingStatus(false);
}

template <typename C, typename S>
void DesktopView<C, S>::PrintEndGame() {
    for (QGraphicsItem* item : scene_->items()) {
        item->setVisible(false);
    }

    QFont font(win_->GetFontName(), 16, QFont::Bold);
    end_text_.reset(new QGraphicsTextItem("GAME\nOVER\n"));
    end_text_->setFont(font);
    end_text_->setDefaultTextColor(Qt::black);

    QRectF text_rect = end_text_->boundingRect();
    QPointF center = scene_->sceneRect().center();
    end_text_->setPos(center - QPointF(text_rect.width() / 2 - 1,
                                       text_rect.height() / 2 + 1));

    scene_->addItem(end_text_.data());

    win_->SetExtraViewVisible(false);
}

}  // namespace s21
