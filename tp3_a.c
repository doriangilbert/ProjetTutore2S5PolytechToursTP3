/**
 * \file tp3_a.c
 * \brief Analyseur syntaxique LR
 * \author GILBERT Dorian et DHONDT Matheo
 * \version 0.1
 * \date 20/01/2023
 *
 */

#include "tp3_a.h"

/**
 * \fn int analyseurLR()
 * \brief fonction qui fait l'analyse LR
 *
 * \param[in] _data chaine à analyser
 * \param[out] _valide boolen indiquant la validité de la chaine passé en paramètre vis a vis de la grammaire JSON, 1 si valide, 0 sinon
 */
int analyseurLR(char *_chaine) {
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
        else if (lexeme==1) lexeme=8;
        else if (lexeme==2) lexeme=9;
        else if (lexeme==3) lexeme=10;
        else if (lexeme==4) lexeme=0;
        else if (lexeme==5) lexeme=1;
        else if (lexeme==6) lexeme=2;
        else if (lexeme==7) lexeme=3;
        else if (lexeme==8) lexeme=4;
        else if (lexeme==9) lexeme=5;
        else if (lexeme==10) lexeme=6;
        else lexeme=7;


        action = TableAction[sommetInt(_pile)][lexeme]; /* Acc='a' ; Deplacement='d' ; Reduction='r' ; Erreur='e' */
        if (action == 'a')
        {
            /*O = Depiler un objet JSon de la PileJSon */ 
            /* l'arbre JSON est sur la pile *Fini = vrai
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
            lexeme = lex(lex_data_analyseur);
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
    return 0;
}

/* pour compiler c'est gcc pile.c tp2_lex.c tp3_a.c -o tp3_a*/
int main(int argc, char *argv[]) {
    if (argc<2)
    {
        printf("Erreur argument manquant\n");
        return 1;
    }
    else 
    {
        printf("%d %s %s %s\n", argc, argv[0], argv[1], argv[2]);
        FILE* fichier=NULL;
        fichier=fopen(argv[1],"r");
        char *texte;
        if (fichier==NULL)
        {
            printf("Erreur d'ouverture du fichier\n");
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
    return 0;
}