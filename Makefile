all:
	gcc cube.c cube.h main.c search.c search.h -Ofast -o CFOPsolver
run:
	./CFOPsolver
