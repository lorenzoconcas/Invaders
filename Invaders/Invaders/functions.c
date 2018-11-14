#include "Libs.h"

void initGraphics() {
	initscr();   /* Inizializza schermo di output */
	noecho();	/* Imposta modalità della tastiera */
	curs_set(0); /* Nasconde il cursore */
	keypad(stdscr, true);
}
void printPoints(int points) {
	int lastLine;
	int idontcare;

	getmaxyx(stdscr, lastLine, idontcare);
	lastLine--;// iniziamo a contare da 0 perciò riduciamo di uno
	mvprintw(lastLine, 0, "Punteggio : %d", points);
	refresh();
}
void printString(char * string, int x, int y) {
	mvprintw(y, x, string);
	refresh();
}
void checkWindow() {
	if (getmaxx(stdscr) < MIN_WIDTH) {
		endwin();
		system("clear");
		printf("E' richiesto un terminale da almeno %d caratteri, ingrandisci la finestra\n", MIN_WIDTH);
		refresh();

		exit(-1);

	}
}

void printPlayer(int startX, int startY) {
	//start X e Y indicano le posizioni da dove iniziare a disegnare il player
	
	/*
	*Aspetto del player :
	
		  #
		#####
	    # # #

	*/
	

	mvaddch(startY, startX + 2, '#');
	for (int i = 0; i < 5; i++) {
		mvaddch(startY + 1, startX+i, '#');
	}
	mvaddch(startY + 2, startX, '#');
	mvaddch(startY + 2, startX+2, '#');
	mvaddch(startY + 2, startX+4, '#');
	refresh();
}
void clearPlayer(int startX, int startY) {
	mvaddch(startY, startX + 2, ' ');
	for (int i = 0; i < 5; i++) {
		mvaddch(startY + 1, startX + i, ' ');
	}
	mvaddch(startY + 2, startX, ' ');
	mvaddch(startY + 2, startX + 2, ' ');
	mvaddch(startY + 2, startX + 4, ' ');
	refresh();
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


void printUI() {
	printString("Premi ESC per uscire", 0, 0);
}
void closeAllThreads(int* threadList) {
	for (int i = 0; i < THREADS_NUMBER; i++) {
		kill(threadList[i], 0);
	}
}