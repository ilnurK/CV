#include "s21_brick_games_highscores.h"

const char *directory = "/brick_games/";
const char *race_log_file_name = "race_highscore";
const char *snake_log_file_name = "snake_highscore";
const char *tetris_log_file_name = "tetris_highscore";

size_t S21InitHighScore(const char *filename, bool *is_creating_error) {
  const char *home_path = getenv("HOME");
  size_t highscore = 0;
  struct stat statbuf;
  char *directory_path = S21GetConcatStr(home_path, directory);
  if (directory_path && stat(directory_path, &statbuf)) {
    *is_creating_error = S21InitDirectory(directory_path);
  }
  char *file_path = S21GetConcatStr(directory_path, filename);
  if (file_path) {
    S21IsHighScoreFile(file_path, &highscore);
    free(file_path);
  }
  free(directory_path);
  return highscore;
}

bool S21InitDirectory(const char *directory_path) {
  bool error = 0;
  if (mkdir(directory_path, 0755) == -1) {
    error = 1;
  }
  return error;
}

char *S21GetConcatStr(const char *s1, const char *s2) {
  char *concat_str = NULL;
  if (s1 && s2) {
    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);
    concat_str = (char *)calloc(s1_len + s2_len + 1, sizeof(char));
    if (concat_str) {
      memcpy(concat_str, s1, s1_len);
      memcpy(concat_str + s1_len, s2, s2_len + 1);
    }
  }
  return concat_str;
}

void S21IsHighScoreFile(const char *file_path, size_t *highscore) {
  FILE *f = fopen(file_path, "r");
  if (f) {
    int scanned_hscore = 0;
    if (fscanf(f, "%d", &scanned_hscore) == 1) {
      *highscore = scanned_hscore;
    }
    fclose(f);
  }
}

bool S21WriteHighScore(const char *filename, const size_t highscore) {
  bool is_writing_error = true;
  const char *home_path = getenv("HOME");
  char *directory_path = S21GetConcatStr(home_path, directory);
  char *file_path = NULL;
  if (directory_path) {
    file_path = S21GetConcatStr(directory_path, filename);
  }
  if (directory_path && file_path) {
    FILE *f = fopen(file_path, "w");
    if (f) {
      fprintf(f, "%lu", highscore);
      is_writing_error = false;
      fclose(f);
    }
    free(file_path);
  }
  free(directory_path);
  return is_writing_error;
}

char *S21GetLogFilePath(const char *file_name, bool *error) {
  const char *home_path = getenv("HOME");
  char *directory_path = S21GetConcatStr(home_path, directory);
  char *file_path = S21GetConcatStr(directory_path, file_name);
  if (directory_path == NULL || file_path == NULL) {
    *error = true;
  }
  free(directory_path);
  return file_path;
}

const char *S21GetRaceLogFileName() { return race_log_file_name; }
