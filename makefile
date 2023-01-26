tp3_a:pile.c tp2_lex.c tp3_a.c
	gcc -g pile.c tp2_lex.c tp3_a.c -o tp3_a -Wall

pile.o : pile.c
	gcc -c pile.c

tp2_lex.o : tp2_lex.c
	gcc -c tp2_lex.c

tp3_a.o : tp3_a.c
	gcc -c tp3_a.c

build: pile.o tp2_lex.o tp3_a.o
	gcc pile.o tp2_lex.o tp3_a.o -o tp3_a

ifneq ($(fichier),)
test:pile.c tp2_lex.c tp3_a.c
	gcc -g pile.c tp2_lex.c tp3_a.c -o tp3_a
	valgrind ./tp3_a $(fichier) --leak-check=full 
else
test:pile.c tp2_lex.c tp3_a.c
	echo ERREUR : Chemin du fichier manquant : Ajouter "fichier=chemin_du_fichier" en fin de commande
endif