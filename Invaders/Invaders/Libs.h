//OS Included Libs
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
//Custom Libs
#include "functions.h"
#include "bullets.h"
#include "player.h"
#include "UI.h"
//Definizioni
#define TIME_SECOND 1000000 //1 sec = 1mln ms
#define SLEEP_TIME 1*TIME_SECOND  //da cambiare in futuro
#define BULLETS_SPEED TIME_SECOND/8 //un ottavo di secondo = 125ms
#define THREADS_NUMBER 4
#define MIN_WIDTH 98
//Strutture
typedef struct position_struct{
	int x;
	int y;
}position_s;

typedef enum ANCHOR_E_X {
	LEFT, CENTER_X, RIGHT
}ANCHOR_X;
typedef enum ANCHOR_E_Y {
	TOP, CENTER_Y, BOTTOM
}ANCHOR_Y;
