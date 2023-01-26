/**
 * \file tp3_a.c
 * \brief Analyseur syntaxique LR
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

/* Table contenant les actions à effectuer (Acc='a' ; Deplacement='d' ; Reduction=<un numéro de règle> ; Erreur='e') */
int TableAction[26][18] =
/*{    }    [    ]    ,    :    s    n    t    f    u    #    O    M    P    A    E    V*/
{
{'d', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //0
{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'a', 'e', 'e', 'e', 'e', 'e', 'e'}, //1
{'e', 'd', 'e', 'e', 'e', 'e', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //2
{'e', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //3
{'e',  3 , 'e', 'e', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //4
{'e',  1 , 'e',  1 ,  1 , 'e', 'e', 'e', 'e', 'e', 'e',  1 , 'e', 'e', 'e', 'e', 'e', 'e'}, //5
{'e', 'e', 'e', 'e', 'e', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //6
{'e',  2 , 'e',  2 ,  2 , 'e', 'e', 'e', 'e', 'e', 'e',  2 , 'e', 'e', 'e', 'e', 'e', 'e'}, //7
{'e', 'e', 'e', 'e', 'e', 'e', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //8
{'d', 'e', 'd', 'e', 'e', 'e', 'd', 'd', 'd', 'd', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //9
{'e',  4 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //10
{'e', 12 , 'e', 12 , 12 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //11
{'e', 13 , 'e', 13 , 13 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //12
{'e',  5 , 'e', 'e',  5 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //13
{'d', 'e', 'd', 'd', 'e', 'e', 'd', 'd', 'd', 'd', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //14
{'e', 10 , 'e', 10 , 10 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //15
{'e', 11 , 'e', 11 , 11 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //16
{'e', 14 , 'e', 14 , 14 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //17
{'e', 15 , 'e', 15 , 15 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //18
{'e', 16 , 'e', 16 , 16 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //19
{'e', 'e', 'e', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //20
{'e', 'e', 'e', 8  , 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //21
{'e',  6 , 'e', 6  ,  6 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //22
{'e',  7 , 'e', 7  ,  7 , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //23
{'d', 'e', 'd', 'e', 'e', 'e', 'd', 'd', 'd', 'd', 'd', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}, //24
{'e', 'e', 'e', 9  , 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}};//25

/* Table contenant les états vers lesquels naviguer (Erreur/Pas d'état=-1) */
int TableGoto[26][18] =
/*{  }  [  ]  ,  :  s  n  t  f  u  #  O  M  P  A  E  V*/
{
{ 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1}, //0
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1,-1}, //1
{-1, 5,-1,-1,-1,-1, 6,-1,-1,-1,-1,-1,-1, 3, 4,-1,-1,-1}, //2
{-1, 7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //3
{-1,-1,-1,-1, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //4
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //5
{-1,-1,-1,-1,-1, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //6
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //7
{-1,-1,-1,-1,-1,-1, 6,-1,-1,-1,-1,-1,-1,10, 4,-1,-1,-1}, //8
{ 2,-1,14,-1,-1,-1,15,16,17,18,19,-1,11,-1,-1,12,-1,13}, //9
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //10
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //11
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //12
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //13
{ 2,-1,14,22,-1,-1,15,16,17,18,19,-1,11,-1,-1,12,20,21}, //14
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //15
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //16
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //17
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //18
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //19
{-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //20
{-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //21
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //22
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //23
{ 2,-1,14,-1,-1,-1,15,16,17,18,19,-1,11,-1,-1,12,25,21}, //24
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};//25

/* Table contenant la taille de la partie droite de chaque règle*/
int taillePartieDroiteRegle[16] = {2,3,1,3,3,2,3,1,3,1,1,1,1,1,1,1};

/* Table contenant l'élément en partie gauche de chaque règle*/
int elementPartieGaucheRegle[16] = {13,13,14,14,15,16,16,17,17,18,18,18,18,18,18,18};

/**
 * \fn int analyseurLR()
 * \brief fonction qui fait l'analyse LR
 *
 * \param[in] _data chaine à analyser
 * \param[out] _valide boolen indiquant la validité de la chaine passé en paramètre vis a vis de la grammaire JSON, 1 si valide, 0 sinon
 */
int analyseurLR(char *_chaine){
/* initialisation */
TIntPile *_pile=initIntPile();
TVoidPile *_pileJSon=initVoidPile();
empilerInt(_pile,0);
/* on recupère un symbole en appelant l'analyseur lexicale */
TLex *lex_data_analyseur = NULL;
lex_data_analyseur = initLexData(_chaine); //NE PAS OUBLIER DE FAIRE deleteLexData(lex_data_analyseur) à la fin
int lexeme = lex(lex_data_analyseur);
/* boucle générale */
int fini = 0;
while (!fini){
    int action;
    if (_pile->indexSommet==-1)
    {
        lexeme=12;
    }
    else if (lexeme=1) lexeme=8;
    else if (lexeme=2) lexeme=9;
    else if (lexeme=3) lexeme=10;
    else if (lexeme=4) lexeme=0;
    else if (lexeme=5) lexeme=1;
    else if (lexeme=6) lexeme=2;
    else if (lexeme=7) lexeme=3;
    else if (lexeme=8) lexeme=4;
    else if (lexeme=9) lexeme=5;
    else if (lexeme=10) lexeme=6;
    else lexeme=7;


    action = TableAction[sommetInt(_pile)][lexeme]; /* Acc='a' ; Deplacement='d' ; Reduction='r' ; Erreur='e' */
    if (action == 'a')
    {
        /*O = Depiler un objet JSon de la PileJSon /* l'arbre JSON est sur la pile *Fini = vrai
        Retourner (O)*/
        deleteIntPile(&_pile);
        deleteLexData(&lex_data_analyseur);
        deleteVoidPile(&_pileJSon);
        printf("Le Json est bon");
        return 0;
    }
    else if (action == 'd')
    {
        empilerInt(_pile,TableGoto[sommetInt(_pile)][lexeme]);
        int lexeme = lex(lex_data_analyseur);
    }
    else if (action == 'e')
    {
        printf("ERREUR\n");
        deleteIntPile(&_pile);
        deleteLexData(&lex_data_analyseur);
        deleteVoidPile(&_pileJSon);
        return 1;
    }
    else
    {
        action++;
        int i=0;
        while (i<taillePartieDroiteRegle[action])
        {
            depilerInt(_pile);
            i++;
        }
        empilerInt(_pile,TableGoto[sommetInt(_pile)][elementPartieGaucheRegle[action]]);
    }
}
}

/* pour compiler c'est gcc pile.c tp2_lex.c tp3_a.c -o tp3_a*/
void main(int argc, char *argv[]) {
    //A COMPLETER avec la lecture de fichier, l'appel à l'analyseur LR et la libération des ressources
    FILE* fichier=NULL;
    fichier=fopen("json_test_files/test.json","r");
    char *texte;
    if (fichier==NULL)
    {
        printf("erreur d'ouverture du fichier\n");
    }
    else
    {
        texte=malloc(sizeof(char)*1);
        char charactere=fgetc(fichier);
        texte[0]=charactere;
        size_t i=1;
        charactere=fgetc(fichier);
        while(!feof(fichier))
        {
            texte=realloc(texte,sizeof(char)*(i+1));
            texte[i]=charactere;
            i++;
            charactere=fgetc(fichier);
        }
        printf("%s\n",texte);
        analyseurLR(texte);
    }
}