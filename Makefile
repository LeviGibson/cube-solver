all:
	gcc cube.c cube.h main.c search.c search.h easySolutions.c easySolutions.h easyDominoes.c easyDominoes.h -Ofast -o cube-solver
run:
	./cubs-solver
