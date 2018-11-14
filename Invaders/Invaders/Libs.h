//OS Included Libs
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
//Custom Libs
#include "functions.h"
#include "bullets.h"
#include "player.h"
//Definizioni
#define TIME_SECOND 1000000 //1 sec = 1mln ms
#define SLEEP_TIME 1*TIME_SECOND  //da cambiare in futuro
#define BULLETS_SPEED TIME_SECOND/8 //un ottavo di secondo = 125ms