#include "Libs.h"
void playerThread() {
	int posX = (getmaxx(stdscr) / 2 - 2), posY = getmaxy(stdscr) - 8;
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
		case ' ': {
			animateFire(posX, posY);
			break;
		}
		}

		printPlayer(posX, posY);
	};
}
void animateFire(int x, int y) {
	int xLeft = x-1;
	int xRight = x + 5;
	y--;


	for (; xLeft > 0, y > 0, xRight < getmaxx(stdscr); xLeft--, y--, xRight++) {
		mvaddch(y, xLeft, '$');
		mvaddch(y + 1, xLeft + 1, ' ');
		mvaddch(y, xRight, '$');
		mvaddch(y + 1, xRight - 1, ' ');
		//mvprintw(1, 1, "%d %d", x, y);
		usleep(BULLETS_SPEED);
		refresh();
	}
	mvprintw(0, 0, "ho finito");
}

int main()
{
	//variabili
	int points = 0;
	int processesIDS[4];
	int p[4];

	//inizializzazioni
	srand((unsigned int) time(NULL));//inizializziamo il seed random
	pipe(p);
	initGraphics(); //setta varie opzioni grafiche
	
	processesIDS[0] = fork(); //clono il primo thread
	if (processesIDS[0] == 0) {
		playerThread();
	}
	else {
		while (true); //vado in loop 
	}
	
	endwin();

	
    return 0;
}
