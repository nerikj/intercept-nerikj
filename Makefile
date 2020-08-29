all: intercept-t14s

intercept-t14s: t14s.o
	gcc -o intercept-t14s t14s.o

t14s.o:
	gcc -c t14s.c -o t14s.o
