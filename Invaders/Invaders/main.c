#include "Libs.h"

int main()
{
	//variabili
	int points = 0;
	int processesIDS[THREADS_NUMBER];
	int p[THREADS_NUMBER];

	//inizializzazioni
	srand((unsigned int) time(NULL));//inizializziamo il seed random
	pipe(p);
	initGraphics(); //setta varie opzioni grafiche
	checkEnvironment();
	start_color();
	
	
	processesIDS[0] = fork(); //clono il primo thread
	if (processesIDS[0] == 0) {

		playerThread();
	}
	else {
		while (!(getch() == 'q')); //vado in loop e aspetto
		//chiudo tutti i thread
		closeAllThreads(processesIDS);
	}
	
	endwin();
	printf("\nEsecuzione terminata ;)\n");
	
    return 0;
}
