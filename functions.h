#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED



/*

void logNumber(char * fName, int i);
void logEntity(char *fName, entity_s t);
void logChar(char *fName, char t);
void logString(char *fName, char * string);

*/


//B
entity_s bullet(char direction, position_s position);
//C
bool checkInvasion(entity_s enemies[], entity_s enemies2[][4], int y);
void clearZone(int endX, int endY);
bool checkNearby(bool right, entity_s current, entity_s enemies[], entity_s enemies2[][4]);
bool checkCollision(entity_s bullet, entity_s enemies[], int damage);
bool checkCollision2(entity_s bullet, entity_s enemies[][4], int damage);
//D
void drawScene(int points, entity_s player, entity_s enemies[], entity_s enemies2[][4],entity_s * bullets, int bulletCount, entity_s *bomb, int bombCount);
void defineColors();
//E
int enemiesAlive(entity_s enemies[]);
int enemiesAlive2(entity_s enemies[][4]);
//I
void initScreen();
void initEnemies(entity_s * enemies);
void initEnemy2(entity_s *enemies, entity_s origin);
entity_s initEntity(int type, char extra, int x, int y, int health);
//P
void printEnd(char *msg);
void printEnemy(entity_s enemy);
void printEnemy2(entity_s enemies[]) ;
void printPlayer(entity_s player);
//R
bool range(int min, int max, int value);
int rnd(int MAX, int MIN);

#endif