#ifndef PONG_H
#define PONG_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

void DrawStaticObj(char field[Y][X]);
void StartGame(TRacket *, TRacket *, TBall *);
char CheckInput(int *, TBall *);
void RacketMove(char, TRacket *);
int BallMove(int *, TBall *);
void BallAutoMove(TBall *ball);
void HoldMoment(char field[Y][X]);
void AfterGoalMove(int, TRacket, TRacket, TBall *);
void CheckChangeDirection(TBall *, TRacket, TRacket);
void CheckTouchRacket(TBall *, TRacket);
void CheckTouchBorder(TBall *);
void DrawDynamicObj(char field[Y][X], TBall, TRacket, TRacket, TScore, TScore);
void DrawScore(char field[Y][X], int, int, TScore);
void FieldPrint(char field[Y][X]);
void CheckScore(int *, TScore, TScore);
void WinnerPrint(char field[Y][X], TScore, TScore);
void PrintAtExit(char field[Y][X]);
void PrintText(char field[Y][X], char *, int, int);

#endif