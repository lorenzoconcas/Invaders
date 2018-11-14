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
			if(t == 0)
				animateFire(posX, posY);
			break;
		}
		}
		printPlayer(posX, posY);
	};
}