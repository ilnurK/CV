#include "s21_tetris_support.h"

bool CheckOrMakeDir(char** dir, size_t len) {
  bool result = true;
  char* home_dir = getenv("HOME");
  if (home_dir && sizeof(home_dir) < len) {
    strcat(*dir, home_dir);
    if (sizeof(SCORE_DIR) < len) {
      strcat(*dir, SCORE_DIR);
    }
  }
  int out = mkdir(*dir, S_IRWXU);
  if (out != 0 && errno != EEXIST) {
    result = false;
  }
  return result;
}

char* GetHighscorePath(S21TetrisError* error) {
  const size_t len = 256;
  char* path = calloc(len, sizeof(char));
  if (path) {
    if (!CheckOrMakeDir(&path, len)) {
      *error = PATH_ERROR;
    }
  } else {
    *error = BAD_ALLOC;
  }
  if (path && sizeof(SCORE_FILEPATH) < len) {
    strcat(path, SCORE_FILEPATH);
  }
  return path;
}
