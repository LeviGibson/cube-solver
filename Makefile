all:
	gcc cube.c main.c search.c easySolutions.c -O3 -o cube-solver
prof:
	gcc -pg cube.c main.c search.c easySolutions.c -O3 -o cube-solver-prof
gdb:
	gcc cube.c main.c search.c easySolutions.c -O3 -g
run:
	./cube-solver
