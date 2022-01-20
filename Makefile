all:
	gcc cube.c main.c search.c easySolutions.c easyDominoes.c -O3 -o cube-solver
gdb:
	gcc cube.c main.c search.c easySolutions.c easyDominoes.c -O3 -g cube-solver
run:
	./cube-solver
