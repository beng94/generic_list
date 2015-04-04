all:
	gcc -g -Wall -std=c11 -o ALL \
	main.c \
	glist.h glist.c \
	test.h test.c
