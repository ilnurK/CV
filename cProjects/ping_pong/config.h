#ifndef PONG_CONFIG
#define PONG_CONFIG

// field
#define Y 25
#define X 80
#define border_horizontal '-'
#define border_vertical '|'
#define border_corner '+'
#define symbol_net '\''
#define field_cell ' '

// game statuses
#define flag_game_end -1
#define flag_game_pause 0
#define flag_game_start 1
#define flag_game_play 2
#define right 1
#define left -1
#define up -1
#define down 1


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
    int value;
} TScore;

#endif