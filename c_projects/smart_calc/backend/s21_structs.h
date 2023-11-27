#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum {
  OPEN_PAR = 0,
  CLOSE_PAR = 1,
  POWER = 2,
  DIV = 3,
  MUL = 4,
  MOD = 5,
  MINUS = 6,
  PLUS = 7,
  VAR_X = 8,
  SIN = 9,
  COS = 10,
  TAN = 11,
  ACOS = 12,
  ASIN = 13,
  ATAN = 14,
  SQRT = 15,
  LN = 16,
  LOG = 17,
  NUM = 18
} lexs_enum;

typedef struct lexems_t {
  int type;
  double num;
  struct lexems_t* next;
  struct lexems_t* prev;
} lexems_t;

typedef struct {
  int w;
  int h;
  double wmin;
  double wmax;
  double hmin;
  double hmax;
  double x1;
  double x2;
  double y1;
  double y2;
  double xstep;
  double ystep;
  int xaccuracy;
  int yaccuracy;
} area_t;

typedef struct {
  double xsize;
  double ysize;
  double x0;
  double y0;
  double oX_y;
  double oY_x;
  int on_x;
  int on_y;
} cell_t;

typedef struct {
  double start;
  double end;
} cycle_t;

#endif