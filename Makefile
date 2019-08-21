project:
	stty sane
	rm -f ./Invaders
	gcc -o Invaders  main.c functions.c -lncurses -lm
	clear
	./Invaders
	
	
build:
	gcc -o Invaders main.c functions.c -lncurses -lm
clean: Invaders
	rm Invaders
fix:
	stty sane
	clear
run:
	./Invaders
