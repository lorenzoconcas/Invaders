project:
	rm -f test
	gcc -o test main.c functions.c player.c bullets.c UI.c -lncurses -lm
	clear
	./test
build:
	gcc -o test main.c functions.c player.c bullets.c UI.c -lncurses -lm
clean: test
	rm test

run: test
	./test