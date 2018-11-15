#include "Libs.h"

void printIntro() {

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
void printStringA(char * string, ANCHOR_X anchorX, ANCHOR_Y anchorY) {
	int x = 0, y = 0;
	switch (anchorX) {
	case CENTER_X: {
		x = getmaxx(stdscr) / 2;
		break;
	}
	case RIGHT:{
		x = getmaxx(stdscr) - 1;
		break;
	}	
	}
	switch (anchorY) {
	case CENTER: {
		x = getmaxy(stdscr) / 2;
		break;
	}
	case BOTTOM: {
		x = getmaxy(stdscr) - 1;
		break;
	}
	}
	printString(string, x, y);
}
void printUI() {
	/*for (int i = 0; i < getmaxx(stdscr); i++) {
		printStringC(" ", i, 0, COLOR_WHITE, COLOR_WHITE);
		printStringC(" ", i, getmaxx(stdscr) -1, COLOR_WHITE, COLOR_WHITE);
	}
	for (int i = 0; i < getmaxy(stdscr)-1; i++) {
		printStringC(" ", 0, i, COLOR_WHITE, COLOR_WHITE);
		printStringC(" ", getmaxx(stdscr) - 1, i, COLOR_WHITE, COLOR_WHITE);
	}
	//printString("Premi ESC per uscire", 0, 0);*/
}
void printStringC(char * string, int x, int y, int backgroundColor, int foregroundColor) {
	init_pair(1, foregroundColor, backgroundColor);
	attron(COLOR_PAIR(1));
	printString(string, x, y);
	attroff(COLOR_PAIR(1));
	refresh();
}
void printStringC_A(char * string, ANCHOR_X anchorX, ANCHOR_Y anchorY, int backgroundColor, int foregroundColor) {
	int x = 0, y = 0;
	switch (anchorX) {
	case CENTER_Y: {
		x = getmaxx(stdscr) / 2;
		break;
	}
	case RIGHT: {
		x = getmaxx(stdscr) - 1;
		break;
	}
	}
	switch (anchorY) {
	case CENTER: {
		x = getmaxy(stdscr) / 2;
		break;
	}
	case BOTTOM: {
		x = getmaxy(stdscr) - 1;
		break;
	}
	}
	printStringC(string, x, y, backgroundColor, foregroundColor);
}