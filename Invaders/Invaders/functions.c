#include "Libs.h"

void initGraphics() {
	initscr();   /* Inizializza schermo di output */
	noecho();	/* Imposta modalità della tastiera */
	curs_set(0); /* Nasconde il cursore */
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
void checkWindow(int max_x, int max_y) {
	if (max_x < 90) {
		endwin();
		system("clear");
		mvprintw(0, max_x / 2, "E' richiesto un terminale da almeno 90 caratteri, ingrandisci la finestra\n");
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