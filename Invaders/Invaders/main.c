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
		}

		printPlayer(posX, posY);
	};
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
