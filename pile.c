/**
 * \file pile.c
 * \brief gestion d'une pile
 * \author NM
 * \version 0.2
 * \date 14/01/2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pile.h"


/** constante pour la taille par defaut d'une pile (utilise pour
 * la reservation memoire) */
#define _DEFAULT_PILE_SIZE 15



/** pile d'entier ----------------------------------------------------*/
/**
 * \fn TPile * initPile()
 * \brief fonction qui initialise une pile : reservation memoire+initialisation
 * des champs
 *
 * \return pointeur sur TIntPile cree en memoire
 */
TIntPile * initIntPile() {
/* A ECRIRE */
}


/**
 * \fn void deleteIntPile(TIntPile ** _pile)
 * \brief efface la memoire occupe par la pile
 *
 * \param[in/out] _pile : l'adresse du pointeur sur la pile
 * \return neant
 */
void deleteIntPile(TIntPile ** _pile) {
/* A ECRIRE */
}


/**
 * \fn void printIntPile(TIntPile * _pile)
 * \brief affichage du contenu d'une pile
 *
 * \param[in] _pile : la pile a afficher
 * \return neant
 */
void printIntPile(TIntPile * _pile) {
/* A ECRIRE */
}

/**
 * \fn void empilerInt(TIntPile * _pile, int _val)
 * \brief empiler un entier sur la pile, si la zone memoire reservee
 * n'est pas suffisante, celle-ci est etendue
 *
 * \param[in/out] _pile : la pile a utiliser
 * \param[in] _val : l'entier a empiler
 * \return neant
 */
void empilerInt(TIntPile * _pile, int _val) {
/* A ECRIRE */
}

/**
 * \fn int depilerInt(TIntPile * _pile)
 * \brief dépiler un entier
 *
 * \param[in] _pile : la pile a depiler
 * \return l'entier en sommet de pile (0 si la pile est vide)
 */
int depilerInt(TIntPile * _pile) {
/* A ECRIRE */
}

/**
 * \fn int sommetInt(TIntPile * _pile)
 * \brief renvoie la valeur du sommet (sans depiler)
 *
 * \param[in] _pile : la pile a utiliser
 * \return l'entier en sommet de pile (0 si la pile est vide)
 */
int sommetInt(TIntPile * _pile) {
/* A ECRIRE */
}


/** pile de void * ---------------------------------------------------*/

/**
 * \fn TVoidPile * initVoidPile()
 * \brief fonction qui initialise une pile de pointeur void *
 *
 * \return pointeur sur une pile TVoidPile
 */
TVoidPile * initVoidPile() {
/* A ECRIRE */
}


/**
 * \fn void deleteVoidPile(TVoidPile ** _pile)
 * \brief libere la memoire occupee par la pile
 *
 * \param[in] _pile : adresse du pointeur sur la pile a liberer
 * \return neant
 */
void deleteVoidPile(TVoidPile ** _pile) {
/* A ECRIRE */
}


/**
 * \fn void printVoidPile(TVoidPile * _pile)
 * \brief affichage de la pile (comme on ne connait pas
 * les type des elements empiles, on affiche les adresses
 * de tous les pointeurs empiles)
 *
 * \param[in] _pile : pile a afficher
 * \return neant
 */
void printVoidPile(TVoidPile * _pile) {
/* A ECRIRE */
}

/**
 * \fn  void empilerVoid(TVoidPile * _pile, void * _val)
 * \brief empile un void *
 *
 * \param[in/out] _pile : pile a utiliser pour empiler
 * \param[in] _val : element de type void * a empiler
 * \return neant
 */
void empilerVoid(TVoidPile * _pile, void * _val) {
/* A ECRIRE */
}

/**
 * \fn void * depilerVoid(TVoidPile * _pile)
 * \brief dépiler un élément de type void *
 *
 * \param[in] _pile : pile a utiliser
 * \return pointeur sur void (0 si la pile est vide)
 */
void * depilerVoid(TVoidPile * _pile) {
/* A ECRIRE */
}

/**
 * \fn void * sommetVoid(TVoidPile * _pile)
 * \brief obtenir la valeur du sommet de type void *
 *
 * \param[in] _pile : pile a utiliser pour lire le sommet
 * \return la valeur void * du sommet (0 si la pile est vide)
 */
void * sommetVoid(TVoidPile * _pile) {
/* A ECRIRE */
}


/** code pour tests (lors de la mise au point de la bibliotheque)
 * compiler avec l'option -D pour inclure la fonction main :
 * gcc pile.c -D TEST -o test_pile
 * 
 * ensuite la compilation n'integrera plus la fonction main :
 * gcc -c pile.c
 */
#ifdef TEST
/**
 * \fn int main(void)
 * \brief fonction principale utilisee uniquement en cas de tests
 *
 */
int main(void) {
    int i;
    {
		/* tests pour une pile d'entier */
		TIntPile * p = NULL;

		printf("----------------------------\ntest pour une pile d'entier\n");
		//empilerInt(p,99);
		printIntPile(p);
		p = initIntPile();
		printIntPile(p);
		for ( i=0;i<35;i++) {
			empilerInt(p,sommetInt(p)+i);
			printIntPile(p);
		}
		for ( i=0;i<40;i++) {
			int r = depilerInt(p);
			printf("r=%d\n",r);
			printIntPile(p);
		}
		deleteIntPile(&p);
    }
    /* tests pour un pile de void * */
    {
		TVoidPile * q = NULL;
		/* 2 exemples de différents type : entier et chaine */
		int a = 321;
		char * b = "azerty";

		printf("----------------------------\ntest pour une pile de void *\n");
		//empilerVoid(q,&a);
		printVoidPile(q);
		q = initVoidPile();
		printVoidPile(q);
		empilerVoid(q,&a);
		printVoidPile(q);
		empilerVoid(q,&b);
		printVoidPile(q);
		empilerVoid(q,&a);
		printVoidPile(q);
		empilerVoid(q,q);
		printVoidPile(q);
		printf("depiler : %p\n",depilerVoid(q));
		printVoidPile(q);

		printf("depiler : %p\n",depilerVoid(q));
		printVoidPile(q);

		printf("depiler : %p\n",depilerVoid(q));
		printVoidPile(q);

		printf("depiler : %p\n",depilerVoid(q));
		printVoidPile(q);

		printf("depiler : %p\n",depilerVoid(q));
		printVoidPile(q);

		deleteVoidPile(&q);

	}
}
#endif
