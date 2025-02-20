#ifndef S21_BRICK_GAMES_HIGHSCORES_H
#define S21_BRICK_GAMES_HIGHSCORES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const char *race_log_file_name;
extern const char *snake_log_file_name;
extern const char *tetris_log_file_name;
size_t S21InitHighScore(const char *filename, bool *is_creating_error);
bool S21InitDirectory(const char *directory_path);
char *S21GetConcatStr(const char *s1, const char *s2);
void S21IsHighScoreFile(const char *file_path, size_t *highscore);
const char *S21GetRaceLogFileName();
char *S21GetLogFilePath(const char *file_name, bool *error);

bool S21WriteHighScore(const char *filename, const size_t highscore);

#ifdef __cplusplus
}
#endif

#endif
