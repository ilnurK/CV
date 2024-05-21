#include "s21_tetris_view.h"

#include <QGraphicsRectItem>

#include "../../bg_src/s21_bg_window.h"

namespace s21 {

TetrisView::TetrisView(MainWindow* window_in) : window_(window_in) {
  error_ = NULL_ERROR;
  tetris_ctrl_ = InitTetrisController(&error_);
  if (error_ == BAD_ALLOC) {
    throw std::runtime_error("tetris allocation error\n");
    window_->GetTimer()->stop();
  } else if (error_ == PATH_ERROR) {
    throw std::invalid_argument("path incorrect\n");
  }
  state_ = START;

  tetris_scene_.reset(new QGraphicsScene(window_->GetSceneRect(), nullptr));

  window_->GetView()->setScene(tetris_scene_.data());

  highscore_ = GetTetrisHighScore(tetris_ctrl_);

  window_->SetPlayingStatus(true);
  tetris_scene_->clear();
  InitNextFigureScene();

  window_->SetScore(GetTetrisScore(tetris_ctrl_));
  window_->SetHighScore(highscore_);
  window_->SetLevel(GetTetrisLevel(tetris_ctrl_));
}

void TetrisView::InitNextFigureScene() {
  window_->SetNextFigureVisible(true);
  QGraphicsView* nf_view = window_->GetNFView();
  nf_scene_.reset(new QGraphicsScene(0, 0, nf_view->viewport()->width(),
                                     nf_view->viewport()->height(), nullptr));
  nf_view->setScene(nf_scene_.data());
}

void TetrisView::DrawState() {
  Keys key = window_->GetKey();
  size_t old_level = GetTetrisLevel(tetris_ctrl_);
  size_t old_score = GetTetrisScore(tetris_ctrl_);
  bool is_pause = false;

  if (key != Keys::PAUSE && !is_pause) {
    if (key != Keys::NULL_KEY && key != Keys::UP) {
      state_ = SetTetrisState(tetris_ctrl_, SHIFTING, static_cast<S21Dirs>(key),
                              &error_);
    } else {
      state_ = SetTetrisState(tetris_ctrl_, state_,
                              static_cast<S21Dirs>(Keys::NULL_KEY), &error_);
    }
    tetris_scene_->clear();
    nf_scene_->clear();
    if ((state_ == GAME_OVER) || error_ != NULL_ERROR) {
      TetrisEndGame();
      window_->SetPlayingStatus(false);
    } else {
      ScoreCheck(old_score, old_level);
      DrawField();
      DrawNextFigure();
      window_->GetTimer()->start(state_speed_);
    }
  } else if (is_pause) {
    is_pause = false;
  } else {
    is_pause = true;
  }
}

void TetrisView::ScoreCheck(size_t old_score, size_t old_level) {
  score_ = GetTetrisScore(tetris_ctrl_);
  if (score_ > old_score) {
    window_->SetScore(score_);
    size_t level = GetTetrisLevel(tetris_ctrl_);
    if (level > old_level) {
      window_->SetLevel(level);
      state_speed_ *= 0.8;
    }
    if (score_ > highscore_) {
      window_->SetHighScore(score_);
    }
  }
}

void TetrisView::DrawField() {
  int wx = tetris_ctrl_->width, hy = tetris_ctrl_->height;
  for (int y = 0; y < hy; y++) {
    for (int x = 0; x < wx; x++) {
      S21XYPair xy = {x, y};
      char* find = GetFieldAt(tetris_ctrl_, xy);
      if (find && (*find == tetris_ctrl_->field_symb_fill ||
                   *find == tetris_ctrl_->fig_symb)) {
        tetris_scene_->addRect(x * wx, y * wx, wx - margin_, wx - margin_,
                               QPen(Qt::NoPen), QBrush(Qt::black));
      }
    }
  }
}

void TetrisView::DrawNextFigure() {
  S21Figure* nf = tetris_ctrl_->fsm->next_figure;
  int x_offset = nf->data[0].x;
  int x_middle = nf_scene_->width() / 2;
  double nf_scale = (nf_scene_->height() + 2) / tetris_ctrl_->fig_len;

  if (nf->type == SQUARE) {
    x_middle -= 1 * nf_scale;
  } else {
    x_middle -= tetris_ctrl_->fig_len / 2 * nf_scale;
  }

  int y_offset = 3;  // initial outfield min - 2
  for (size_t i = 0; i < tetris_ctrl_->fig_len; i++) {
    int x = x_middle + (nf->data[i].x - x_offset) * nf_scale;
    int y = (nf->data[i].y + y_offset) * nf_scale;
    nf_scene_->addRect(x, y, nf_scale - margin_, nf_scale - margin_,
                       QPen(Qt::NoPen), QBrush(Qt::black));
  }
}

void TetrisView::TetrisEndGame() {
  window_->GetTimer()->stop();
  for (QGraphicsItem* item : tetris_scene_->items()) {
    item->setVisible(false);
  }
  if (error_ == NULL_ERROR) {
    QFont font(window_->GetFontName(), 16, QFont::Bold);
    end_text_.reset(new QGraphicsTextItem("GAME\nOVER\n"));
    end_text_->setFont(font);
    end_text_->setDefaultTextColor(Qt::black);

    QRectF text_rect = end_text_->boundingRect();
    QPointF center = tetris_scene_->sceneRect().center();
    end_text_->setPos(center - QPointF(text_rect.width() / 2 - 1,
                                       text_rect.height() / 2 + 1));

    tetris_scene_->addItem(end_text_.data());
  } else {
    tetris_scene_->addText("No Fatal Error\n");
  }
  window_->SetNextFigureVisible(false);
}

TetrisView::~TetrisView() {
  if (score_ > highscore_) {
    try {
      WriteTetrisHighScore(tetris_ctrl_, &error_);
      if (error_ != NULL_ERROR) {
        throw std::invalid_argument("path incorrect\n");
      }
    } catch (std::invalid_argument& e) {
      std::cerr << e.what();
    }
  }
  DeleteController(tetris_ctrl_);
}

}  // namespace s21
