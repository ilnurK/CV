#include "s21_tetris_tests.h"

TEST(S21TetrisTestController, TestSimpleInit1) {
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);

  S21TetrisStates state = SetTetrisState(tetris_ctrl, START, NULL_DIR, &error);
  if (!error) {
    EXPECT_EQ(state, MOVING);
    S21XYPair xy = {1, 2};
    EXPECT_EQ(FIELD_SYMBOL_EMPTY, *GetFieldAt(tetris_ctrl, xy));
    EXPECT_EQ(0, static_cast<int>(GetTetrisLevel(tetris_ctrl)));
  } else {
    std::cerr << "error occured\n";
  }

  DeleteController(tetris_ctrl);
}

TEST(S21TetrisTestController, TestSimpleInit2) {
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);

  SetTetrisState(tetris_ctrl, START, NULL_DIR, &error);
  if (!error) {
    S21TetrisStates state = SetTetrisState(tetris_ctrl, SHIFTING, LEFT, &error);

    EXPECT_EQ(state, MOVING);
  } else {
    std::cerr << "error occured\n";
  }
  DeleteController(tetris_ctrl);
}

TEST(S21TetrisTestController, TestSimpleInit3) {
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);

  if (!error) {
    SetTetrisState(tetris_ctrl, START, NULL_DIR, &error);
    S21TetrisStates state =
        SetTetrisState(tetris_ctrl, SHIFTING, RIGHT, &error);

    EXPECT_EQ(state, MOVING);
  } else {
    std::cerr << "error occured\n";
  }
  DeleteController(tetris_ctrl);
}

TEST(S21TetrisTestController, TestSimpleInit4) {
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);
  if (!error) {
    SetTetrisState(tetris_ctrl, START, NULL_DIR, &error);
    S21TetrisStates state = SetTetrisState(tetris_ctrl, SHIFTING, DOWN, &error);

    EXPECT_EQ(state, MOVING);
  } else {
    std::cerr << "error occured\n";
  }
  DeleteController(tetris_ctrl);
}

TEST(S21TetrisTestController, TestSimpleInit5) {
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);
  if (!error) {
    SetTetrisState(tetris_ctrl, START, NULL_DIR, &error);
    S21TetrisStates state =
        SetTetrisState(tetris_ctrl, SHIFTING, ACTION, &error);

    EXPECT_EQ(state, MOVING);
  } else {
    std::cerr << "error occured\n";
  }
  DeleteController(tetris_ctrl);
}

TEST(S21TetrisTestController, TestHighScore) {
  S21TetrisError error = NULL_ERROR;
  S21TetrisController* tetris_ctrl = InitTetrisController(&error);
  if (error == NULL_ERROR) {
    SetTetrisState(tetris_ctrl, START, NULL_DIR, &error);
    S21TetrisStates state =
        SetTetrisState(tetris_ctrl, SHIFTING, ACTION, &error);
    EXPECT_EQ(state, MOVING);

    size_t hs = 400;
    SetTetrisScore(tetris_ctrl, hs);
    WriteTetrisHighScore(tetris_ctrl, &error);
    if (!error) {
      EXPECT_EQ(hs, InitTetrisHighScore(&error));
      EXPECT_EQ(hs, GetTetrisScore(tetris_ctrl));
      EXPECT_EQ(hs, GetTetrisHighScore(tetris_ctrl));
    }
  }
  if (error != NULL_ERROR) {
    std::cout << error << " - error occured\n";
  }

  DeleteController(tetris_ctrl);
}

class S21TetrisFSMTest1 : public testing::Test {
 protected:
  S21TetrisFSM* fsm_;
  S21Field* field_;
  S21Figure* figure_;
  S21Figure* figure_next_;
  S21TetrisError error_;

  S21TetrisStates state_;

 protected:
  void SetUp() override {
    error_ = NULL_ERROR;
    fsm_ = (S21TetrisFSM*)calloc(1, sizeof(S21TetrisFSM));
    figure_ = InitNeedFigure(BAR, 0, 0, &error_);
    //+$$$$------+
    figure_next_ = InitNeedFigure(BAR, 4, 0, &error_);
    //+----$$$$--+
    field_ = InitField(&error_);
    if (!fsm_ || error_ != NULL_ERROR) {
      throw std::bad_alloc();
    }
    fsm_->field = field_;
    fsm_->cur_figure = figure_;
    fsm_->next_figure = figure_next_;
  }

  void TearDown() override { DeleteFSM(fsm_); }
};

TEST_F(S21TetrisFSMTest1, TestDeletion1) {
  try {
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    //+####------+

    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(BAR, 6, 4, &error_);
    //+------$$$$+

    fsm_->next_figure = figure_next_;
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    //+########--+

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(BAR, 6, 5, &error_);
    //+------$$$$+
    fsm_->next_figure = figure_next_;

    SetFSMState(fsm_, SHIFTING, ACTION, &error_);
    //+-------$--+
    //|-------$--|
    //|-------$--|
    //|-------$--|
    //~----------~
    //+########--+
    SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    //+--------$-+
    //|--------$-|
    //|--------$-|
    //|--------$-|
    //~----------~
    //+########--+
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    //|--------$-|
    //|--------$-|
    //|--------$-|
    //+########$-+
    EXPECT_EQ(state_, MOVING);

    SetFSMState(fsm_, SHIFTING, ACTION, &error_);
    //+-------$--+
    //|-------$--|
    //|-------$--|
    //|-------$--|
    //~----------~
    //|--------#-|
    //|--------#-|
    //|--------#-|
    //+#########-+

    SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    //+---------$+
    //|---------$|
    //|---------$|
    //|---------$|
    //~----------~
    //|--------#-|
    //|--------#-|
    //|--------#-|
    //+#########-+

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    //|--------#$|
    //|--------#$|
    //|--------#$|
    //+#########$+
    EXPECT_EQ(state_, MOVING);
    //|----------|
    //|--------##|
    //+--------##+
    // DrawField(fsm_);
    size_t need_score{100};
    EXPECT_EQ(fsm_->score, need_score);
    for (size_t x = 0; x < FIELD_WIDTH - 2; x++) {
      EXPECT_EQ(fsm_->field->data[FIELD_HEIGHT - 1]->data[x],
                FIELD_SYMBOL_EMPTY);
      EXPECT_EQ(fsm_->field->data[FIELD_HEIGHT - 1]->data[x],
                FIELD_SYMBOL_EMPTY);
    }

  } catch (...) {
    std::cout << "error in test\n";
  }
}

TEST_F(S21TetrisFSMTest1, TestGameOver1) {
  try {
    state_ = MOVING;
    while (state_ != GAME_OVER) {
      state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    }
    EXPECT_EQ(state_, GAME_OVER);
  } catch (...) {
    std::cout << "error in test\n";
  }
}

TEST_F(S21TetrisFSMTest1, TestDeletion2) {
  try {
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(SQUARE, 0, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(SQUARE, 2, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(SQUARE, 4, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(SQUARE, 6, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(BAR, 6, 5, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(BAR, 6, 5, &error_);
    fsm_->next_figure = figure_next_;

    SetFSMState(fsm_, SHIFTING, ACTION, &error_);
    state_ = SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);

    SetFSMState(fsm_, SHIFTING, ACTION, &error_);
    SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    size_t need_score{700};
    EXPECT_EQ(fsm_->score, need_score);
  } catch (...) {
    std::cout << "error in test\n";
  }
}

TEST_F(S21TetrisFSMTest1, TestTouch1) {
  // +----------+
  // |          |
  // ~          ~
  // |          |
  // |$$        |
  // |#$$       |
  // |#         |
  // |#         |
  // |#         |
  // +----------+
  try {
    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(LZSHAPE, 0, 5, &error_);
    fsm_->next_figure = figure_next_;

    SetFSMState(fsm_, MOVING, RIGHT, &error_);
    SetFSMState(fsm_, MOVING, RIGHT, &error_);
    SetFSMState(fsm_, MOVING, RIGHT, &error_);
    SetFSMState(fsm_, SHIFTING, ACTION, &error_);
    SetFSMState(fsm_, SHIFTING, LEFT, &error_);
    SetFSMState(fsm_, SHIFTING, LEFT, &error_);
    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);
    for (size_t y = FIELD_HEIGHT - 1; y > FIELD_HEIGHT - 6; y--) {
      EXPECT_TRUE(fsm_->field->data[y]->data[0] == FIELD_SYMBOL_FILLED);
    }

    EXPECT_TRUE(fsm_->field->data[FIELD_HEIGHT - 5]->data[1] ==
                FIELD_SYMBOL_FILLED);
    EXPECT_TRUE(fsm_->field->data[FIELD_HEIGHT - 4]->data[1] ==
                FIELD_SYMBOL_FILLED);
    EXPECT_TRUE(fsm_->field->data[FIELD_HEIGHT - 4]->data[2] ==
                FIELD_SYMBOL_FILLED);

  } catch (...) {
    std::cout << "error in test\n";
  }
}

TEST_F(S21TetrisFSMTest1, TestBorders1) {
  try {
    for (size_t x = 0; x < 10; x++) {
      state_ = SetFSMState(fsm_, SHIFTING, LEFT, &error_);
    }
    EXPECT_EQ(state_, MOVING);
    EXPECT_TRUE(fsm_->field->data[10]->data[3] == FIGURE_SYMBOL);

    for (size_t x = 0; x < 10; x++) {
      state_ = SetFSMState(fsm_, SHIFTING, RIGHT, &error_);
    }
    EXPECT_TRUE(fsm_->field->data[14]->data[FIELD_WIDTH - FIG_LEN] ==
                FIGURE_SYMBOL);

  } catch (...) {
    std::cout << "error in test\n";
  }
}

TEST_F(S21TetrisFSMTest1, RestShapes1) {
  try {
    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(RZSHAPE, 0, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    EXPECT_TRUE(fsm_->field->data[1]->data[0] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[1] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[0]->data[1] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[0]->data[1] == FIGURE_SYMBOL);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(RLSHAPE, 0, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    EXPECT_TRUE(fsm_->field->data[1]->data[0] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[1] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[2] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[0]->data[2] == FIGURE_SYMBOL);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(LLSHAPE, 0, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    EXPECT_TRUE(fsm_->field->data[0]->data[0] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[0] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[1] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[2] == FIGURE_SYMBOL);

    free(fsm_->next_figure);
    figure_next_ = InitNeedFigure(TSHAPE, 0, 0, &error_);
    fsm_->next_figure = figure_next_;

    state_ = SetFSMState(fsm_, SHIFTING, DOWN, &error_);
    EXPECT_EQ(state_, MOVING);

    EXPECT_TRUE(fsm_->field->data[1]->data[0] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[1] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[0]->data[1] == FIGURE_SYMBOL);
    EXPECT_TRUE(fsm_->field->data[1]->data[2] == FIGURE_SYMBOL);
  } catch (...) {
    std::cout << "error in test\n";
  }
}