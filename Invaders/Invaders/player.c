#include "Libs.h"

void playerThread() {
	int posX = (getmaxx(stdscr) / 2 - 2), posY = getmaxy(stdscr) - 8;
	int t;
	//prima posizione	
	printPlayer(posX, posY);
	while (true) {

		switch (getch()) {

		case 'a':
		case 'A': {
			clearPlayer(posX, posY);
			posX--;
			break;
		}
		case 'd':
		case 'D': {
			clearPlayer(posX, posY);
			posX++;
			break;
		}
				  //questo andrà spostato
		case ' ': {
			t = fork();
			if (t == 0) {
				animateFire(posX, posY);
				exit(0);
			}
			break;
		}
		}
		printPlayer(posX, posY);
	};
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
		mvaddch(startY + 1, startX + i, '#');
	}
	mvaddch(startY + 2, startX, '#');
	mvaddch(startY + 2, startX + 2, '#');
	mvaddch(startY + 2, startX + 4, '#');
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