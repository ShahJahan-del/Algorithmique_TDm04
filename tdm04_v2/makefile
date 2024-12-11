CC= gcc
CFLAGS= -Wall -pedantic


main : main.o tests.o liste_double.o tableau_double.o liste_tableau_double.o util.o chrono.o

main.o: main.c util.h chrono.h tests.h
tests.o: tests.c tests.h util.h tableau_double.h liste_double.h liste_tableau_double.h
liste_double.o: liste_double.c liste_double.h
tableau_double.o: tableau_double.c tableau_double.h
liste_tableau_double.o: liste_tableau_double.c liste_tableau_double.h
util.o: util.c util.h
chrono.o: chrono.c chrono.h

.PHONY : clean solution
solution: main.o tests.o liste_double_sol.o tableau_double_sol.o liste_tableau_double_sol.o util.o chrono.o liste2_double_sol.o
	$(CC) $(CFLAGS) $^ -o main
clean :
	-rm *.o main
