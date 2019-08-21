#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct position_struct {
    int x;
    int y;
} position_s;

typedef enum entity_enum { PLAYER  = 0, ENEMY = 1, ENEMY2 = 2, BULLET = 3, BOMB = 4} entity_type;

typedef struct entity_struct {
    char extra;
    int type;
    int health;
    position_s pos;
} entity_s;



#endif // STRUCT_H_INCLUDED
