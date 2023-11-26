#ifndef PONG_CONFIG
#define PONG_CONFIG

// field
#define Y 25
#define X 80
#define BORDER_HORIZONTAL '-'
#define BORDER_VERTICAL '|'
#define BORDER_CORNER '+'
#define SYMBOL_NET '\''
#define FIELD_CELL ' '
#define SYMBOL_BALL 'o'
#define LEFT_RACKET '{'
#define RIGHT_RACKET '}'

#define KEY_LEFT_RACKET_UP 'a'
#define KEY_LEFT_RACKET_UP_ALT 'A'
#define KEY_LEFT_RACKET_DOWN 'z'
#define KEY_LEFT_RACKET_DOWN_ALT 'z'
#define KEY_RIGHT_RACKET_UP 'k'
#define KEY_RIGHT_RACKET_UP_ALT 'K'
#define KEY_RIGHT_RACKET_DOWN 'm'
#define KEY_RIGHT_RACKET_DOWN_ALT 'M'

#define KEY_PAUSE 'p'
#define KEY_PAUSE_ALT 'q'
#define KEY_GAME_SPEED_INC '='
#define KEY_GAME_SPEED_DEC '-'
#define KEY_GAME_SPEED_STD '0'

// game statuses
#define GAME_END -1
#define GAME_PAUSE 0
#define GAME_START 1
#define GAME_PLAY 2
#define RIGHT 1
#define LEFT -1
#define UP -1
#define DOWN 1

typedef struct {
  char symbol;
  char key_up, key_down;
  char key_up_alt, key_down_alt;
  int size;
  int thin;
  int y, x;
} TRacket;

typedef struct {
  char symbol;
  int x;
  int y;
  int speed;
  int direction_x;
  int direction_y;
} TBall;

typedef struct {
  int x;
  int y;
  int val;
} TScore;

#endif