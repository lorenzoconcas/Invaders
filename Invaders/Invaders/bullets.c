#include "Libs.h"

void animateFire(int x, int y) {
	int xLeft = x - 1;
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
	return;
}
 
//dovrebbe prendere la pipe come parametro in ingresso
void BulletThread() {

}