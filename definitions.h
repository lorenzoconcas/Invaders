#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#define BOTTOM_PADDING 8
#define DELAY 100000
#define ENEMY_DELAY DELAY*2

#define BOMB_DELAY DELAY*3
#define PROCESS_N 5
#define ENEMY_N 10
#define initEmpty() initEntity(-1, -1, 0, 0, 100)
#define S_WIDTH getmaxx(stdscr)
#define S_HEIGHT getmaxy(stdscr)
#define PLAYER_WIDTH 5
//#define size(x)  (sizeof(x) / sizeof((x)[0]))

//char  entity_name[5][7] = {"PLAYER", "ENEMY", "ENEMY2", "BULLET", "BOMB"};


#endif // DEFINITIONS_H_INCLUDED
