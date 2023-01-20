/**
 * \file tp3_a.c
 * \brief Table LR
 * \author GILBERT Dorian et DHONDT Matheo
 * \version 0.1
 * \date 20/01/2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pile.h"
#include "tp2_lex.h"

int analyseurLR(){
   /* initialisation */
TIntPile *_pile=initIntPile();
TVoidPile *_pileJSon=initVoidPile();
empilerInt(_pile,0);
/* on recupère un symbole en appelant l'analyseur lexicale */
int lexeme = Lex();
/* boucle générale */
int fini = 0;
while (!fini){
    int action;
    action = TableAction[sommet(_pile)][lexeme]; /* Acc=0 ; Deplacement=1 ; Reduction=2*/
    if (action = 'a')
    {
        /*O = Depiler un objet JSon de la PileJSon /* l'arbre JSON est sur la pile *Fini = vrai
        Retourner (O)*/
        return 0;
    }
    else if (action ='d')
    {
        empilerInt(_pile,TableGoto[sommet(_pile)][lexeme]);
        lexeme = Lex();
    }
    else if (action ='e')
    {
        printf("ERREUR\n");
        fini=1;
    }
    else
    {
        int i=0;
        while (i<taillePartieDroiteRegle[action])
        {
            depilerInt(_pile);
            i++;
        }
        empilerInt(TableGoto[sommet(Pile)][ElementPartieGaucheRegle[action]]);
    }
}
}