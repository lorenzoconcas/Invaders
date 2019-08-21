#include "libs.h"

bool range(int min, int max, int value) {
    return (min <= value && value <= max);
}
void initScreen(){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    start_color();
    defineColors();
}

//Funzioni utili al debug
/*void logNumber(char * fName, int i) {
    FILE * fp = NULL;
    fp = fopen(fName, "a");
    fprintf(fp, "%d", i);
    fprintf(fp, "\n");
    fclose(fp);
}
void logEntity(char * fName, entity_s t) {
    FILE * fp = NULL;
    fp = fopen(fName, "a");
    fprintf(fp, "POS X : %d, Y : %d, health %d, char %c type %s", t.pos.x, t.pos.y, t.health, t.extra, entity_name[t.type]);
    fprintf(fp, "\n");
    fclose(fp);
}

void logChar(char * fName, char t) {
    FILE * fp = NULL;
    fp = fopen(fName, "a");
    fprintf(fp, "%c", t);
    fprintf(fp, "\n");
    fclose(fp);
}
void logString(char * fName, char * string) {
    FILE * fp = NULL;
    fp = fopen(fName, "a");
    fprintf(fp, "%s", string);
    fprintf(fp, "\n");
    fclose(fp);
}
*/
entity_s initEntity(int type, char extra, int x, int y, int health) {
    entity_s temp;
    temp.health = health;
    temp.extra = extra;
    temp.pos.x = x;
    temp.pos.y = y;
    temp.type = type;
    return temp;
}

void clearZone(int endX, int endY) {
    for (int y = 0; y < endY; y++) {
        for (int x = 0; x < endX; x++) {
            mvaddch(y, x, ' ');
        }
    }
}
void printEnd(char * msg) {
    flash();
    flash();
    flash();

    int msgSize = strlen(msg);

    mvprintw(S_HEIGHT / 2, S_WIDTH / 2 - msgSize / 2, msg);
    mvprintw(S_HEIGHT / 2 + 1, S_WIDTH / 2 - 12, "Premi \"ENTER\" per uscire");
    //  refresh();
    char c;
    do {
        c = getch();
        cbreak();
    } while (c != '\n');
}
void initEnemies(entity_s * enemies) {

    int screenWidth = getmaxx(stdscr);
    //3 è la larghezza di un nemico
    int space_occupied = 3 * ENEMY_N + 2 * (ENEMY_N - 1) + 2;
    int border = (screenWidth - space_occupied) / 2;

    for (int i = 0; i < ENEMY_N; i++) {
        /*
         * questo perchè la vita viene ridotta sempre di un terzo
         * quando vengono colpiti, un punto non fa differenza
         */
        enemies[i].health = 99;
        enemies[i].pos.x = border; //distanza dal bordo
        if (i > 0) //se è il secondo nemico o successivo allora aggiungiamo gli spazi relativi
            enemies[i].pos.x += 5 * i;
        enemies[i].pos.y = 2;
        enemies[i].type = ENEMY;
    }
}
void initEnemy2(entity_s * enemies, entity_s origin) {
    //i nemici di secondo livello sono 4 e sono centrati rispetto al nemico-padre
    int originX = origin.pos.x;
    int originY = origin.pos.y;

    enemies[0] = initEntity(ENEMY2, 'a', originX - 2, originY - 1, 99); //sx, alto
    enemies[1] = initEntity(ENEMY2, 'a', originX + 2, originY - 1, 99); //dx, alto
    enemies[2] = initEntity(ENEMY2, 'a', originX - 2, originY + 2, 99); //sx, basso
    enemies[3] = initEntity(ENEMY2, 'a', originX + 2, originY + 2, 99); //dx, basso


}

entity_s initPlayer();
void playerP(int pipe);
void clearPlayer(entity_s player) {
    int startX = player.pos.x, startY = player.pos.y;

    mvaddch(startY, startX + 2, ' ');
    for (int i = 0; i < 5; i++) {
        mvaddch(startY + 1, startX + i, ' ');
    }
    mvaddch(startY + 2, startX, ' ');
    mvaddch(startY + 2, startX + 2, ' ');
    mvaddch(startY + 2, startX + 4, ' ');
    refresh();
}
void printPlayer(entity_s player) {

    /*
    *Aspetto del player :

    	  #
    	#####
    	# # #

    */
    int startX = player.pos.x, startY = player.pos.y;

    // attron(A_BOLD);
    mvaddch(startY, startX + 2, '#');
    for (int i = 0; i < 5; i++) {
        mvaddch(startY + 1, startX + i, '#');
    }
    mvaddch(startY + 2, startX, '#');
    mvaddch(startY + 2, startX + 2, '#');
    mvaddch(startY + 2, startX + 4, '#');
    refresh();
}
void printEnemy(entity_s enemy) {

    int startX = enemy.pos.x, startY = enemy.pos.y;

    attron(COLOR_PAIR(2));

    if (enemy.health > 0) {
        mvaddch(startY, startX, '#');
        mvaddch(startY, startX + 2, '#');
    }
    if (enemy.health > 40) {
        mvaddch(startY + 1, startX, '#');
        mvaddch(startY + 1, startX + 1, '#');
    }
    if (enemy.health > 70) {
        mvaddch(startY + 1, startX + 2, '#');
        mvaddch(startY + 2, startX + 1, '#');
    }
    attroff(COLOR_PAIR(2));
    refresh();
}

void printEnemy2(entity_s enemies[]) {
    /*
     * c'è rischio che anche non essendo inizializzati 
     * i nemici possano avere lo stesso il valore "extra" impostato su 'a'
     * ne prendiamo atto e andiamo avanti
     */

    attron(COLOR_PAIR(2));

    for (int i = 0; i < 4; i++) {
        entity_s enemy = enemies[i];
        if (enemy.extra == 'a') {
            int startX = enemy.pos.x, startY = enemy.pos.y;
            if (enemy.health > 0) {
                mvaddch(startY, startX, '#');
                mvaddch(startY, startX + 2, '#');
            }

            if (enemy.health > 50) {
                mvaddch(startY + 1, startX + 1, '#');
            }
        }
    }
    attroff(COLOR_PAIR(2));
    refresh();
}

entity_s bullet(char direction, position_s position) {
    entity_s temp;
    temp.pos = position;
    temp.health = 100;
    if (direction == '<')
        temp.pos.x -= 1;
    else
        temp.pos.x += 5;

    temp.extra = direction;

    return temp;
}

bool checkInvasion(entity_s enemies[], entity_s enemies2[][4], int y) {
    for (int i = 0; i < ENEMY_N; i++)
        if (enemies[i].type == ENEMY && enemies[i].health > 0 && enemies[i].pos.y + 3 >= y)
            return true;
        else if (enemies[i].extra == 'd') {
        for (int j = 0; j < 4; j++) {
            if (enemies2[i][j].health > 0 && enemies2[i][j].pos.y + 3 >= y)
                return true;
        }
    }
    return false;
}

int enemiesAlive(entity_s enemies[]) {
    int count = 0;
    for (int i = 0; i < ENEMY_N; i++)
        if (enemies[i].health > 0)
            count++;
    return count;
}
int enemiesAlive2(entity_s enemies[][4]) {
    int count = 0;
    for (int i = 0; i < ENEMY_N; i++)
        for (int j = 0; j < 4; j++)
            if (enemies[i][j].health > 0)
                count++;
    return count;
}

bool checkNearby(bool right, entity_s current, entity_s enemies[], entity_s enemies2[][4]) {
    //direction == true = dx, else sx
    int whereCheck = 0;
    int i = 0;

    if (right)
        if (current.type == ENEMY2)
            whereCheck = 7;
        else
            whereCheck = 3;
    else
        whereCheck = -3;

    //navi di primo tipo contro navi di primo tipo
    for (i = 0; i < ENEMY_N; i++)
        if (enemies[i].pos.x == current.pos.x + whereCheck)
            return true;

    //primo vs secondo
    for (i = 0; i < ENEMY_N; i++)
        for (int j = 0; j < 4; j++)
            if (enemies2[i][j].pos.x == current.pos.x + whereCheck)
                return true;

    return false;
}

bool checkCollision(entity_s bullet, entity_s enemies[], int damage) {
    //se il proiettile è "morto" non può esserci collisione
    if (!bullet.health)
        return false;

    /*
     * controlliamo per ogni nemico vivo se è avvenuta una collisione
     * il proiettile può collidere solo con un nemico alla volta
     * variabili.. "varie", l'intero contatore, le coordinate del proiettile e la dimensione dei nemici
     */
    int i = 0;
    int x = bullet.pos.x;
    int y = bullet.pos.y;
    int enemySize = 0;

    for (i = 0; i < ENEMY_N; i++) {
        entity_s enemy = enemies[i];
        //dobbiamo controllare se il proiettile è compreso negli estremi delle coordinate
        //solo se il nemico è vivo
        if (enemy.health > 0) {
            position_s ePos = enemy.pos;
            //controlliamo che il proiettile colpisca solo ciò che è rimasto della nave
            // cambiando il range dove viene controllata la posizione
            if (enemy.health > 0) enemySize = 1;
            else if (enemy.health > 40) enemySize = 2;
            else if (enemy.health > 70) enemySize = 3;
            //il controllo della collisione vero e proprio
            if (range(ePos.x, ePos.x + enemySize, x) && range(ePos.y, ePos.y + enemySize, y)) {
                enemies[i].health -= damage;
                return true;
            }
        }
    }
    return false; //-1;}
}
bool checkCollision2(entity_s bullet, entity_s enemies[][4], int damage) {
    //se il proiettile è "morto" non può esserci collisione
    if (!bullet.health)
        return false;

    /*
     * controlliamo per ogni nemico vivo se è avvenuta una collisione
     * il proiettile può collidere solo con un nemico alla volta
     * variabili.. "varie", l'intero contatore, le coordinate del proiettile e la dimensione dei nemici
     */
    int i = 0, j = 0;
    int x = bullet.pos.x;
    int y = bullet.pos.y;
    int enemySize = 0;

    for (i = 0; i < ENEMY_N; i++) {
        for (j = 0; j < 4; j++) {
            entity_s enemy = enemies[i][j];
            //dobbiamo controllare se il proiettile è compreso negli estremi delle coordinate
            //solo se il nemico è vivo
            if (enemy.health > 0) {
                position_s ePos = enemy.pos;
                //controlliamo che il proiettile colpisca solo ciò che è rimasto della nave
                // cambiando il range dove viene controllata la posizione
                if (enemy.health > 0) enemySize = 1;
                else if (enemy.health > 50) enemySize = 3;
                //il controllo della collisione vero e proprio
                if (range(ePos.x, ePos.x + enemySize, x) && range(ePos.y, ePos.y + enemySize, y)) {
                    enemies[i][j].health -= damage;
                    return true;
                }
            }
        }
    }
    return false; //-1;
}
void drawScene(int points, entity_s player, entity_s enemies[], entity_s enemies2[][4], entity_s * bullets, int bulletCount, entity_s * bomb, int bombCount) {
    clearZone(S_WIDTH - 1, S_HEIGHT - 1);
    //stampo il giocatore
    printPlayer(player);

    //i nemici
    for (int i = 0; i < ENEMY_N; i++) {
        printEnemy(enemies[i]);
    }
    //i nemici di secondo livello
    for (int i = 0; i < ENEMY_N; i++) {
        printEnemy2(enemies2[i]);
    }
    //i proiettili, per il colore fare riferimento alla funzione defineColors()
    attron(COLOR_PAIR(3));
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i].health > 0)
            mvaddch(bullets[i].pos.y, bullets[i].pos.x, '$');
        refresh();
    }
    attroff(COLOR_PAIR(3));

    //le bombe
    for (int i = 0; i < bombCount; i++) {
        if (bomb[i].health > 0 && bomb[i].type == BOMB) {
            mvaddch(bomb[i].pos.y, bomb[i].pos.x, '%');
            refresh();
        }
    }

    //e il punteggio
    attron(COLOR_PAIR(1));
    //l''intera parte bassa dello schermo è una linea bianca
    for (int i = 0; i < S_WIDTH; i++)
        mvprintw(S_HEIGHT - 1, i, " ");
    //il punteggio
    mvprintw(S_HEIGHT - 1, 0, "Punteggio : %d", points);
    attroff(COLOR_PAIR(1));
    //aggiorno il tutto
    refresh();
}



int rnd(int MAX, int MIN) {
    return MIN + rand() % (MAX - MIN + 1);
}

void defineColors() {
    //definisce le coppie di colori
    if (has_colors()) {
        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        /*init_pair(4, COLOR_BLACK, COLOR_WHITE);
        init_pair(5, COLOR_BLACK, COLOR_WHITE);*/
    }
}