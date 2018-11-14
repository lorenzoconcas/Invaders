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

	mvprintw(lastLine, 0, "Punteggio : %d", points);
	refresh();
}
void printString(char * string, int x, int y) {

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
