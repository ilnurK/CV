#include "config.h"

void ChooseInputMode();
void RandMapInit(char map[Y][X]);
void FileMapInit(char map[Y][X]);
void ChangeSpeed(char* key, int* delay);
void MapUpdate(char map[Y][X]);
void CopyArr(char map[Y][X], char map_copy[Y][X]);
int CheckNeighbours(int y, int x, char field[Y][X]);
void ShowMap(char map[Y][X], int delay);

int main() {
    char map[Y][X];
    int delay = 3;
    initscr();
    ChooseInputMode(map);
    char key = ' ';
    while (key != '\e') {
        clear();
        halfdelay(delay);
        MapUpdate(map);
        ShowMap(map, delay);
        refresh();
        // key = getch();
        ChangeSpeed(&key, &delay);

    }
    endwin();
    return 0;
}

void ChooseInputMode(char map[Y][X]) {
    halfdelay(50);
    printw(
        "Select input mode\nPress 1 for random map generate\nPress 2 for map "
        "from file\n");
    char inp = ' ';
    while (inp != '1' && inp != '2') {
        inp = getch();
        if (inp == '1') {
            RandMapInit(map);
        } else if (inp == '2') {
            FileMapInit(map);
        } else {
            clear();
            printw(
                "Please press 1 for random generate or press 2 for input from "
                "file\n");
        }
    }
}

void RandMapInit(char map[Y][X]) {
    srand(time(NULL));
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            int rand_val = rand() % 10;
            map[y][x] = (rand_val == 1) ? symbol_alive : symbol_empty;
        }
    }
}

void FileMapInit(char map[Y][X]) {
    clear();
    printw("Choose file number from 0 to 9\n");
    char inp = ' ';
    while (!(inp >= '0' && inp <= '9')) {
        inp = getch();
        clear();
        printw("Please choose file number from 0 to 9\n");
    }
    char file_name[6] = "0.txt";
    file_name[0] = inp;
    FILE* f = fopen(file_name, "r");
    int i = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++, i++) {
            fscanf(f, "%c", &map[y][x]);
        }
    }
    fclose(f);
}

void ChangeSpeed(char* key, int* delay) {
    *key = getch();
    if ((*key == key_speed_up || *key == key_speed_up_alt) && *delay > 0) {
        *delay -= 1;
    } else if ((*key == key_speed_down || *key == key_speed_down_alt) &&
               *delay < 50) {
        *delay += 1;
    }
}

void MapUpdate(char map[Y][X]) {
    char map_copy[Y][X];
    CopyArr(map, map_copy);
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            int neighbours = CheckNeighbours(y, x, map_copy);
            if (map_copy[y][x] == symbol_alive) {
                map[y][x] = (neighbours == 2 || neighbours == 3) ? symbol_alive
                                                                 : symbol_empty;
            } else if (map_copy[y][x] == symbol_empty) {
                map[y][x] = (neighbours == 3) ? symbol_alive : symbol_empty;
            }
        }
    }
}

void CopyArr(char map[Y][X], char map_copy[Y][X]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            map_copy[y][x] = map[y][x];
        }
    }
}

int CheckNeighbours(int y, int x, char field[Y][X]) {
    int neighbours = 0;
    int y_up = y - 1 < 0 ? Y - 1 : y - 1;
    int y_down = y + 1 > Y - 1 ? 0 : y + 1;
    int x_left = x - 1 < 0 ? X - 1 : x - 1;
    int x_right = x + 1 > X - 1 ? 0 : x + 1;
    neighbours += (field[y_up][x] == symbol_alive) ? 1 : 0;
    neighbours += (field[y_up][x_right] == symbol_alive) ? 1 : 0;
    neighbours += (field[y][x_right] == symbol_alive) ? 1 : 0;
    neighbours += (field[y_down][x_right] == symbol_alive) ? 1 : 0;
    neighbours += (field[y_down][x] == symbol_alive) ? 1 : 0;
    neighbours += (field[y_down][x_left] == symbol_alive) ? 1 : 0;
    neighbours += (field[y][x_left] == symbol_alive) ? 1 : 0;
    neighbours += (field[y_up][x_left] == symbol_alive) ? 1 : 0;
    return neighbours;
}

void ShowMap(char map[Y][X], int delay) {
    move(0, X / 2 - 6);
    printw("Game of Life\n");
    for (int y = 0; y < Y + 2; y++) {
        for (int x = 0; x < X + 2; x++) {
            if ((y == 0 || y == Y + 1) && (x == 0 || x == X + 1)) {
                printw("+");
            } else if (y == 0 || y == Y + 1) {
                printw("-");
            } else if (x == 0 || x == X + 1) {
                printw("|");
            } else {
                printw("%c", map[y - 1][x - 1]);
            }
        }
        printw("\n");
    }
    move(Y + 3, X / 2 - 7);
    printw("Game speed %d\n", delay);
}