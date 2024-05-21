#ifndef S21_BRICK_GAME_TETRIS_FSM_H
#define S21_BRICK_GAME_TETRIS_FSM_H

#include <stdio.h>
#include <string.h>

#include "s21_tetris_figures.h"

#define MAX_SHIFTS 4
#define LEVEL_COEF 600
#define MAX_LEVEL 10

typedef enum {
  START = 1,
  SPAWN = 2,
  MOVING = 3,
  SHIFTING = 4,
  ATTACHING = 5,
  GAME_OVER = 6
} S21TetrisStates;

typedef struct S21TetrisFSM {
  S21Field* field;
  S21Figure* cur_figure;
  S21Figure* next_figure;
  size_t score;
  size_t highscore;
  size_t level;
  size_t shifts_counter;
} S21TetrisFSM;

S21TetrisStates SetFSMState(S21TetrisFSM* fsm, const S21TetrisStates state,
                            const S21Dirs dir, S21TetrisError* error);
S21TetrisStates StableFSM(S21TetrisFSM* fsm, const S21TetrisStates state,
                          const S21Dirs dir, S21TetrisError* error);
bool FSM(S21TetrisFSM* fsm, S21TetrisStates* cur_state, const S21Dirs dir,
         S21TetrisError* error);
bool Moving(S21TetrisFSM* fsm, S21TetrisStates* cur_state);
bool ShiftingHandler(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
                     const S21Dirs dir);
bool IsAttachY(S21TetrisFSM* fsm);
bool Shifting(S21TetrisFSM* fsm, S21TetrisStates* cur_state, const S21Dirs dir);
bool IsBorders(S21TetrisFSM* fsm, const S21Dirs dir);
bool Falling(S21TetrisFSM* fsm, S21TetrisStates* cur_state);
bool Rotating(S21TetrisFSM* fsm, S21TetrisStates* cur_state);
bool TryRotate(S21TetrisFSM* fsm);
bool Spawn(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
           S21TetrisError* error);
bool Attaching(S21TetrisFSM* fsm, S21TetrisStates* cur_state);
size_t CheckLines(S21TetrisFSM* fsm);
bool CheckLine(S21TetrisFSM* fsm, const size_t y);
void DeleteLine(S21TetrisFSM* fsm, const size_t y);
bool Start(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
           S21TetrisError* error);
size_t InitTetrisHighScore(S21TetrisError* error);
void WriteHighScore(S21TetrisFSM* fsm, S21TetrisError* error);
void DeleteFSM(S21TetrisFSM* fsm);

#endif
