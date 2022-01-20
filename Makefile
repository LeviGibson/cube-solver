all:
	gcc cube.c cube.h main.c search.c search.h easySolutions.c easySolutions.h easyDominoes.c easyDominoes.h -O3 -o cube-solver
gdb:
	gcc cube.c cube.h main.c search.c search.h easySolutions.c easySolutions.h easyDominoes.c easyDominoes.h -O3 -g cube-solver
run:
	./cubs-solver
