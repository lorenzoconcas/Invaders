#include "libs.h"

//prototipi dei processi
void mainProcess(int);
void playerProcess(int pipe);
void directionGeneratorProcess(int pipe, int type);
int main() {
    int pIDS[PROCESS_N], p[2];
    srand((unsigned int) time(NULL));

    initScreen();

    pipe(p);


    mvprintw(S_HEIGHT/2, S_WIDTH/2 - 20, "Premi un tasto qualsiasi per iniziare...");
    getch();
    cbreak();

    /*
    * Generiamo i vari processi
    * Processo Principale = main (contenente il loop principale)
    * Processo player = acquisisce tutte le informazioni da tastiera e stabilisce comportamento player
    * Processo nemico1 = genera la direzione dei nemici di primo livello
    * Processo nemico2 = uguale ma per secondo livello
    * Processo bomba = gestisce la formazione delle bombe lanciate dai nemici
    */

    pIDS[0] = fork();
    if(!pIDS[0])
        playerProcess(p[1]);
    else {
        pIDS[1] = fork();
        if(!pIDS[1])
            directionGeneratorProcess(p[1], ENEMY); //pipe e tipo di entità generata
        else {
            pIDS[2] = fork();
            if(!pIDS[2])
                directionGeneratorProcess(p[1], BOMB);
            else {
                pIDS[3] = fork();
                if(!pIDS[3])
                    directionGeneratorProcess(p[1], ENEMY2);
                else
                    mainProcess(p[0]);
            }
        }
    }


    endwin();
    printf("\nPartita terminata\n");
    return 0;
}

void mainProcess(int pipe) {

    /*
    * Struttura del programma :
    * Il processo principale (questo) legge dal buffer il dato di tipo entità
    * a seconda del tipo viene fatto un controllo differente
    * Le informazioni della tastiera vengono messe nel dato di tipo player
    */



    //variabile generiche
    int random;
    char *endGame = ""; //il messaggio stampato a fine partita
    bool cycle = true; //usata per capire se rimanere nel loop
    int points = 0; //punteggio del giocatore


    //dati
    entity_s enemies[ENEMY_N]; //nemici
    initEnemies(enemies); //inizializzazione lista nemici (primo livello)

    //nemici di secondo livello
    entity_s enemies2[ENEMY_N][4];
    /*
    * non inizializziamo i valori perchè sapremo la posizione solo una volta che il nemico corrispettivo di 1o livello non è morto
    * Perchè x4? la navicella morente si suddivide in 4 sottonavicelle
    */
    entity_s player = initEntity(PLAYER, -1,S_WIDTH/2-2, S_HEIGHT-BOTTOM_PADDING, 100); //giocatore (e inizializzazione)

    entity_s *bullets =  NULL; //array dinamico contenente i proiettili sparati dal player
    int bulletCount = 0;

    entity_s *bombs = (entity_s*)malloc(sizeof(entity_s));
    bombs[0] = initEmpty();
    int bombCount = 1;



    //ciclo principale
    do {

        entity_s entity = initEmpty(); //la variabile dove vengono salvati i dati letti dal buffer, viene pulita a ogni ciclo

        read(pipe, &entity, sizeof(entity_s)); //lettura dei dati


        /*
        * A seconda del tipo di entità letto aggiorno la posizione di conseguenza
        * controllando che la nuova posizione sia valida
        * in caso sia il player analizziamo l'informazione extra che contiene
        * il tasto premuto dalla tastiera
        */
        switch(entity.type) {
        case PLAYER: {
            //posizione
            if(entity.type == PLAYER) {
                if((player.pos.x >= 0 && entity.pos.x == 1) || (player.pos.x < S_WIDTH && entity.pos.x == -1))
                    player.pos.x += entity.pos.x;
            }
            //gestione tastiera
            switch(entity.extra) {
            //creo due proiettili divergenti
            case ' ': {
                if(bullets == NULL)
                    bullets = (entity_s*)malloc(sizeof(entity_s));

                bulletCount+=2;
                //faccio spazio per due nuovi proiettili
                bullets = (entity_s*)realloc(bullets, bulletCount*sizeof(entity_s));
                bullets[bulletCount-2] = bullet('<', player.pos);
                bullets[bulletCount-1] = bullet('>', player.pos);

                break;
            }
            case '': //ESC
            case 'q': {

                //se il giocatore vuole smettere di giocare
                cycle = false;
                endGame = "Hai abbandonato il campo di battaglia";
                break;
            }
            default: {
                break;
            }
            }

            break;
        }
        //  questo caso è stato messo per via del controllo fatto poco sotto,
        //  in ogni caso, il concetto è identico a quello dei nemici di primo livello
        case ENEMY2: {
            //questo controllo potrebbe influenzare le dinamiche del gioco?
            //se non ci sono ancora nemici di secondo grado "promuoviamo" il dato a nemico di primo livello
            if(enemiesAlive(enemies) == ENEMY_N)
                entity.type = ENEMY;
            else {
                //scegliamo un nemico morto (e non un vivo come nel caso ENEMY)
                do {
                    random = rnd(ENEMY_N-1, 0);
                } while(enemies[random].health > 0);
                //controllo che la posizione sia valida
                int enemyPos = enemies2[random][0].pos.x + 7;
                int nextPos = enemyPos + entity.pos.x;
                if(nextPos> 0 && nextPos < S_WIDTH) { //7 è al dimensione del "blocco" di navicelle
                    for(int i = 0; i<4; i++) {
                        enemies2[random][i].pos.x += entity.pos.x;
                        enemies2[random][i].pos.y += entity.pos.y;
                    }
                }

                while(checkNearby(true, enemies2[random][0],enemies, enemies2) )
                    for(int i = 0; i<4; i++)
                        enemies2[random][i].pos.x -= 1;

                while(checkNearby(false, enemies2[random][0],enemies, enemies2))
                    for(int i = 0; i<4; i++)
                        enemies2[random][i].pos.x += 1;

                break;

            }
        }
        case ENEMY: {
            //se è un nemico
            //scegliamo un nemico a caso a cui dare la nuova direzione
            do {
                random = rnd(ENEMY_N-1, 0);
            } while(enemies[random].health == 0);

            int posX = enemies[random].pos.x; //la posizione attuale del nemico, in una variabile per comodità

            //controllo che la posizione del nemico sia valida
            if(posX + entity.pos.x > 0 && posX + entity.pos.x < S_WIDTH) {
                enemies[random].pos.x += entity.pos.x;
                enemies[random].pos.y += entity.pos.y;
            }

            while(checkNearby(true, enemies[random],enemies, enemies2))
                enemies[random].pos.x -= 1;
            while(checkNearby(false, enemies[random],enemies, enemies2))
                enemies[random].pos.x += 1;

            break;
        }
        case BOMB: {
            //scegliamo un nemico a caso a cui dare la bomba
            random = rnd(ENEMY_N-1, 0);
            entity_s target = initEmpty();
            bombs[bombCount-1] = entity;

            if(enemies[random].health == 0 && enemies[random].extra == 'd')
                target = enemies2[random][rnd(3, 0)];
            else
                target = enemies[random];


            bombs[bombCount-1].pos.x += target.pos.x;
            bombs[bombCount-1].pos.y += target.pos.y+3;

            bombCount++;
            bombs = (entity_s*)realloc(bombs, bombCount*sizeof(entity_s));


            break;
        }
        }

        /*
        * Aggiornamento della posizione dei proiettili
        * e controllo delle collisioni nemico-proiettile.
        * In assenza di una funzione tipo "trim" per rimuovere
        * i proiettili "morti" dalla lista riduciamo la loro vita a 0 e non verrano più considerati
        */

        if(bullets != NULL) {
            //per ogni proiettile in lista
            for(int i = 0; i<bulletCount; i++) {
                int y = bullets[i].pos.y;
                int x = bullets[i].pos.x;
                //se il proiettile è fuori dallo schermo la vita va 0
                if( y < 0  || x < 0 || x > S_WIDTH)
                    bullets[i].health = 0;
                //altrimenti
                else {
                    //aggiorno la posizione
                    //decido la nuova coordinata x a seconda della direzione indicata nell'informazione extra
                    if(bullets[i].extra == '<')
                        bullets[i].pos.x--;
                    else
                        bullets[i].pos.x++;
                    //in entrambi i casi il proiettile sale verso l'alto
                    bullets[i].pos.y--;
                    /*
                    * controllo se ha colpito qualche nemico,
                    * in caso il proiettile esaurisce la sua vita e viene tolta salute al nemico
                    * vengono attivate i nemici di secondo livello
                    * perchè due funzioni simili ma differenti?
                    * i nemici di secondo livello sono array bidimensionali
                    * per pulizia del codice meglio fare due funzioni separate
                    */


                    if(checkCollision(bullets[i], enemies, 33) || checkCollision2(bullets[i], enemies2, 50)) {
                        points+=10; //punteggio del giocatore
                        bullets[i].health = 0;
                    }

                }

            }
        }


        //gestione delle bombe
        if(bombs != NULL) {
            for(int i = 0; i < bombCount; i++) {
                //"uccido" tutte le bombe fuori dallo schermo
                if(bombs[i].pos.y >= S_HEIGHT)
                    bombs[i].health = 0;
                //collisione
                //commenta questo blocco per debuggare, rendendo invincibile il player


                if(range(player.pos.x, player.pos.x+PLAYER_WIDTH, bombs[i].pos.x) &&
                        range(player.pos.y, player.pos.y+PLAYER_WIDTH, bombs[i].pos.y)) {
                    player.health = 0;
                    bombs[i].health = 0;
                }
                bombs[i].pos.y++;
            }
        }

        //controllo lo spawn di nemici di secondo livello
        for(int i = 0; i < ENEMY_N; i++) {
            if(enemies[i].health == 0 && enemies[i].extra != 'd') {
                enemies[i].extra = 'd';
                initEnemy2(enemies2[i], enemies[i]);
            }
        }

        //disegno la scena
        drawScene(points, player, enemies, enemies2, bullets, bulletCount, bombs, bombCount);


        /*
        * Controlliamo le seguenti condizioni :
        * se i nemici sono ad altezza player
        * se ci sono nemici vivi
        * se il player si scontra coi nemici
        */

        if(checkInvasion(enemies,enemies2, player.pos.y)) {
            endGame = "I mostri hanno invaso la terra";
            break; //esco dal ciclo
        }
        if(player.health < 1) {
            endGame = "Sei stato fatto fuori dagli invasori";
            break;
        }
        if(enemiesAlive2(enemies2) < 1) {
            endGame = "Minaccia sventata! Hai vinto";
            break;
        }


    } while(cycle);

    printEnd(endGame);
    return;
}
void playerProcess(int pipe) {

    entity_s player;

    while(true) {
        player.pos.x = 0;
        player.pos.y = 0;
        player.type = PLAYER;
        player.extra = -1;
        char c = getch();
        cbreak();

        switch(c) {
        //movimento a sinistra

        case KEY_LEFT&A_CHARTEXT:
        case 'a':
        case 'A': {
            player.pos.x = -1;
            break;
        }
        //movimento a destra
        case KEY_RIGHT&A_CHARTEXT:
        case 'd':
        case 'D': {
            player.pos.x = +1;
            break;
        }
        default: {
            player.extra = c;
        }

        };

        write(pipe, &player, sizeof(entity_s));

        usleep(DELAY);
    };
}
void directionGeneratorProcess(int pipe, int type) {
    while (true) {
        entity_s enemy;
        enemy.pos.x = 0;
        enemy.pos.y = 0;
        enemy.type = type;
        enemy.health = 100;
        enemy.extra = -1;

        //se vengono chieste le coordinate di una bomba
        if (type == BOMB) {
            enemy.pos.x = rnd(0, 2);
            usleep(BOMB_DELAY);
        } else {
            enemy.pos.x = rnd(1, -1);
            enemy.pos.y = rnd(1, 0);
            usleep(ENEMY_DELAY);
        }

        write(pipe, & enemy, sizeof(entity_s));
    }
}
