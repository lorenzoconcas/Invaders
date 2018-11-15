#include "Libs.h"

void initGraphics() {
	initscr();   /* Inizializza schermo di output */
	noecho();	/* Imposta modalità della tastiera */
	curs_set(0); /* Nasconde il cursore */
	keypad(stdscr, true);
	
}
void checkEnvironment() {
	if (getmaxx(stdscr) < MIN_WIDTH) {
		endwin();
		system("clear");
		printf("E' richiesto un terminale da almeno %d caratteri, ingrandisci la finestra\n", MIN_WIDTH);
		refresh();

		exit(-1);

	}
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
}


void printEnemy(int startX, int startY) {
	mvaddch(startY, startX, '#');
	mvaddch(startY, startX+2, '#');
	mvaddch(startY+1, startX, '#');
	mvaddch(startY + 1, startX+1, '#');
	mvaddch(startY + 1, startX+2, '#');
	mvaddch(startY + 2, startX+1, '#');
	refresh();
}


void closeAllThreads(int* threadList) {
	for (int i = 0; i < THREADS_NUMBER; i++) {
		kill(threadList[i], 0);
	}
}