#ifndef S21_BRICK_GAME_TETRIS_SUPPORT_H
#define S21_BRICK_GAME_TETRIS_SUPPORT_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "s21_tetris_field.h"

#define SCORE_DIR "/brick_game_logs"
#define SCORE_FILEPATH "/tetris_score.log"

bool CheckOrMakeDir(char** dir, size_t len);
char* GetHighscorePath(S21TetrisError* error);

#endif
