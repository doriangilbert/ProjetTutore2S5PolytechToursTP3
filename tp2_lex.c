/**
 * \file tp2_lex.c
 * \brief analyseur lexical pour le langage JSON
 * \author GILBERT Dorian et DHONDT Matheo
 * \version 0.1
 * \date 04/01/2023
 *
 */

#include "tp2_lex.h"

/**
 * \fn int isSep(char _symb)
 * \brief fonction qui teste si un symbole fait partie des separateurs
 *
 * \param[in] _symb symbole a analyser
 * \return 1 (vrai) si _symb est un separateur, 0 (faux) sinon
 */
int isSep(const char _symb)
{
    switch (_symb)
    {
    case ' ': /* espace */
        return 1;
    case '\n': /* nouvelle ligne */
        return 1;
    case '\t': /* tabulation */
        return 1;
    case '\r': /* retour chariot */
        return 1;
    case ',':
        return 1;
    case '{':
        return 1;
    case '}':
        return 1;
    default:
        return 0;
    }
}

/**
 * \fn TLex * initLexData(char * _data)
 * \brief fonction qui reserve la memoire et initialise les
 * donnees pour l'analyseur lexical
 *
 * \param[in] _data chaine a analyser
 * \return pointeur sur la structure de donnees creee
 */
TLex *initLexData(char *_data)
{
    TLex *_lex = malloc(sizeof(TLex));
    _lex->tailleTableSymboles = 5;
    _lex->tableSymboles = malloc(sizeof(TSymbole) * _lex->tailleTableSymboles);
    for (int i = 0; i < _lex->tailleTableSymboles; i++)
    {
        _lex->tableSymboles[i].type = 0;
    }
    _lex->data = malloc(sizeof(char) * strlen(_data) + 1);
    strcpy(_lex->data, _data);
    _lex->startPos = _lex->data;
    _lex->nbLignes = 0;
    _lex->nbSymboles = 0;
    return _lex;
}

/**
 * \fn void deleteLexData(TLex ** _lexData)
 * \brief fonction qui supprime de la memoire les donnees pour
 * l'analyseur lexical
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \return neant
 */
void deleteLexData(TLex **_lexData)
{
    free((*_lexData)->data);
    for (int i = 0; i < (*_lexData)->tailleTableSymboles; i++)
    {
        if ((*_lexData)->tableSymboles[i].type == JSON_STRING)
        {
            free((*_lexData)->tableSymboles[i].val.chaine);
        }
    }
    free((*_lexData)->tableSymboles);
    free((*_lexData));
}

/**
 * \fn void printLexData(TLex * _lexData)
 * \brief fonction qui affiche les donnees pour
 * l'analyseur lexical
 *
 * \param[in] _lexData donnees de l'analyseur lexical
 * \return neant
 */
void printLexData(TLex *_lexData)
{
    printf("LexData:\n");
    printf("data : %s\n", _lexData->data);
    printf("startPos : %s\n", _lexData->startPos);
    printf("nbLigne : %d\n", _lexData->nbLignes);
    printf("nbSymboles : %d\n", _lexData->nbSymboles);
    printf("tableSymboles :\n");
    int i = 0;
    for (i = 0; i < _lexData->nbSymboles; i++)
    {
        if (_lexData->tableSymboles[i].type == JSON_STRING)
            printf("Chaine : %s\n", _lexData->tableSymboles[i].val.chaine);
        else if (_lexData->tableSymboles[i].type == JSON_INT_NUMBER)
            printf("Entier : %d\n", _lexData->tableSymboles[i].val.entier);
        else
            printf("Reel : %f\n", _lexData->tableSymboles[i].val.reel);
    }
}

/**
 * \fn void addIntSymbolToLexData(TLex * _lexData, const int _val)
 * \brief fonction qui ajoute un symbole entier a la table des symboles
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur entiere a ajouter
 * \return neant
 */
void addIntSymbolToLexData(TLex *_lexData, const int _val)
{
    int i = _lexData->nbSymboles;
    if (_lexData->nbSymboles == _lexData->tailleTableSymboles)
    {
        _lexData->tailleTableSymboles++;
        _lexData->tableSymboles=realloc(_lexData->tableSymboles, sizeof(TSymbole) * _lexData->tailleTableSymboles);
    }
    _lexData->tableSymboles[i].type = JSON_INT_NUMBER;
    _lexData->tableSymboles[i].val.entier = _val;
    _lexData->nbSymboles++;
}

/**
 * \fn void addRealSymbolToLexData(TLex * _lexData, const float _val)
 * \brief fonction qui ajoute un symbole reel a la table des symboles
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur reelle a ajouter
 */
void addRealSymbolToLexData(TLex *_lexData, const float _val)
{
    int i = _lexData->nbSymboles;
    if (_lexData->nbSymboles == _lexData->tailleTableSymboles)
    {
        _lexData->tailleTableSymboles++;
        _lexData->tableSymboles=realloc(_lexData->tableSymboles, sizeof(TSymbole) * _lexData->tailleTableSymboles);
    }
    _lexData->tableSymboles[i].type = JSON_REAL_NUMBER;
    _lexData->tableSymboles[i].val.reel = _val;
    _lexData->nbSymboles++;
}

/**
 * \fn void addStringSymbolToLexData(TLex * _lexData, char * _val)
 * \brief fonction qui ajoute une chaine de caracteres a la table des symboles
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \param[in] _val chaine a ajouter
 */
void addStringSymbolToLexData(TLex *_lexData, char *_val)
{
    if (_val != NULL)
    {
        int i = _lexData->nbSymboles;
        if (_lexData->nbSymboles == _lexData->tailleTableSymboles)
        {
            _lexData->tailleTableSymboles++;
            _lexData->tableSymboles=realloc(_lexData->tableSymboles, sizeof(TSymbole) * _lexData->tailleTableSymboles);
        }
        _lexData->tableSymboles[i].type = JSON_STRING;
        _lexData->tableSymboles[i].val.chaine = strdup(_val);
        _lexData->nbSymboles++;
    }
}

/**
 * \fn int lex(Lex * _lexData)
 * \brief fonction qui effectue l'analyse lexicale (contient le code l'automate fini)
 *
 * \param[inout] _lexData donnees de suivi de l'analyse lexicale
 * \return code d'identification de l'entite lexicale trouvee
 */
int lex(TLex *_lexData)
{
    int etat = 0;
    int fini = 0;
    int result = JSON_LEX_ERROR;
    char symbole = ' ';
    int nbCaractere = 0;
    char *PosDeb = _lexData->startPos;
    while (!fini)
    {
        symbole = *_lexData->startPos;
        while ((symbole == ' ' || symbole == '\n') && etat == 0)
        {
            if (symbole == '\n')
            {
                _lexData->nbLignes++;
            }
            _lexData->startPos++;
            PosDeb = _lexData->startPos;
            symbole = *_lexData->startPos;
        }
        switch (etat)
        {
        case 0:
            switch (symbole)
            {
            case 't':
                etat = 1;
                break;
            case '{':
                etat = 17;
                break;
            case '}':
                etat = 18;
                break;
            case '[':
                etat = 19;
                break;
            case ']':
                etat = 20;
                break;
            case ':':
                etat = 21;
                break;
            case ',':
                etat = 22;
                break;
            case 'f':
                etat = 6;
                break;
            case 'n':
                etat = 12;
                break;
            case '"':
                etat = 23;
                break;
            case '1' ... '9':
                etat = 29;
                break;
            case '-':
                etat = 27;
                break;
            case '0':
                etat = 28;
                break;
            default:
                fini = 1;
            }
            break;
        case 1:
            switch (symbole)
            {
            case 'r':
                etat = 2;
                break;
            default:
                fini = 1;
            }
            break;
        case 2:
            switch (symbole)
            {
            case 'u':
                etat = 3;
                break;
            default:
                fini = 1;
            }
            break;
        case 3:
            switch (symbole)
            {
            case 'e':
                etat = 4;
                break;
            default:
                fini = 1;
            }
            break;
        case 4:
            switch (symbole)
            {
            default:
                if (isSep(symbole) == 1)
                {
                    etat = 5;
                    fini = 3;
                    result = JSON_TRUE;
                }

                else
                    fini = 1;
            }
            break;
        case 5:
            fini = 3;
            result = JSON_TRUE;
            break;
        case 6:
            switch (symbole)
            {
            case 'a':
                etat = 7;
                break;
            default:
                fini = 1;
            }
            break;
        case 7:
            switch (symbole)
            {
            case 'l':
                etat = 8;
                break;
            default:
                fini = 1;
            }
            break;
        case 8:
            switch (symbole)
            {
            case 's':
                etat = 9;
                break;
            default:
                fini = 1;
            }
            break;
        case 9:
            switch (symbole)
            {
            case 'e':
                etat = 10;
                break;
            default:
                fini = 1;
            }
            break;
        case 10:
            if (isSep(symbole) == 1)
            {
                etat = 11;
                fini = 3;
                result = JSON_FALSE;
            }
            else
                fini = 1;
            break;
        case 11:
            fini = 3;
            result = JSON_FALSE;
            break;
        case 12:
            switch (symbole)
            {
            case 'u':
                etat = 13;
                break;
            default:
                fini = 1;
            }
            break;
        case 13:
            switch (symbole)
            {
            case 'l':
                etat = 14;
                break;
            default:
                fini = 1;
            }
            break;
        case 14:
            switch (symbole)
            {
            case 'l':
                etat = 15;
                break;
            default:
                fini = 1;
            }
            break;
        case 15:
            if (isSep(symbole) == 1)
            {
                etat = 16;
                fini = 3;
                result = JSON_NULL;
            }

            else
                fini = 1;
            break;
        case 16:
            fini = 3;
            result = JSON_NULL;
            break;
        case 17:
            fini = 3;
            result = JSON_LCB;
            break;
        case 18:
            fini = 3;
            result = JSON_RCB;
            break;
        case 19:
            fini = 3;
            result = JSON_LB;
            break;
        case 20:
            fini = 3;
            result = JSON_RB;
            break;
        case 21:
            fini = 3;
            result = JSON_COLON;
            break;
        case 22:
            fini = 3;
            result = JSON_COMMA;
            break;
        case 23:
            switch (symbole)
            {
            case '\\':
                etat = 25;
                break;
            case '"':
                etat = 26;
                break;
            case '\0':
                fini = 1;
                break;
            default:
                etat = 23;
            }
            break;
        case 24:
            switch (symbole)
            {
                /*Y'a pas de 24 ?-?*/
            }
            break;
        case 25:
            switch (symbole)
            {
            case '\0':
                fini = 1;
                break;
            default:
                etat = 23;
            }
            break;
        case 26:
            fini = 3;
            result = JSON_STRING;
            break;
        case 27:
            switch (symbole)
            {
            case '1' ... '9':
                etat = 29;
                break;
            case 0:
                etat = 28;
                break;
            default:
                fini = 1;
            }
            break;
        case 28:
            switch (symbole)
            {
            case '.':
                etat = 30;
                break;
            case 'e':
                etat = 32;
                break;
            case 'E':
                etat = 32;
                break;
            default:
                if (isSep(symbole) == 1)
                {
                    etat = 31;
                    fini = 3;
                    result = JSON_INT_NUMBER;
                }
                else
                    fini = 1;
            }
            break;
        case 29:
            switch (symbole)
            {
            case '0' ... '9':
                etat = 29;
                break;
            case '.':
                etat = 30;
                break;
            case 'e':
                etat = 32;
                break;
            case 'E':
                etat = 32;
                break;
            default:
                if (isSep(symbole) == 1)
                {
                    etat = 31;
                    fini = 3;
                    result = JSON_INT_NUMBER;
                }
                else
                    fini = 1;
            }
            break;
        case 30:
            switch (symbole)
            {
            case '0' ... '9':
                etat = 33;
                break;
            default:
                fini = 1;
            }
            break;
        case 31:
            fini = 3;
            result = JSON_INT_NUMBER;
            break;
        case 32:
            switch (symbole)
            {
            case '0' ... '9':
                etat = 35;
                break;
            case '+':
                etat = 35;
                break;
            case '-':
                etat = 35;
                break;
            default:
                fini = 1;
            }
            break;
        case 33:
            switch (symbole)
            {
            case '0' ... '9':
                etat = 33;
                break;
            case 'e':
                etat = 32;
                break;
            case 'E':
                etat = 32;
                break;
            default:
                if (isSep(symbole) == 1)
                {
                    etat = 34;
                    fini = 3;
                    result = JSON_REAL_NUMBER;
                }
                else
                    fini = 1;
            }
            break;
        case 34:
            fini = 3;
            result = JSON_REAL_NUMBER;
            break;
        case 35:
            switch (symbole)
            {
            case '0' ... '9':
                etat = 35;
                break;
            default:
                if (isSep(symbole) == 1)
                {
                    etat = 36;
                    fini = 3;
                    result = JSON_REAL_NUMBER;
                }

                else
                    fini = 1;
            }
            break;
        case 36:
            fini = 3;
            result = JSON_REAL_NUMBER;
            break;
        default:
            fini = 2; /* erreur */
        }
        if (fini == 0)
        {
            _lexData->startPos++;
            nbCaractere++;
        }
    }
    /* gestion de la sortie */
    switch (fini)
    {
    case 1:
        if (symbole != '\0')
        {
            fprintf(stderr, "Erreur : caractere %c inconnu (etat %d)\n", symbole, etat);
        }
        return JSON_LEX_ERROR;
    case 2:
        fprintf(stderr, "Erreur : etat %d inconnu\n", etat);
        return JSON_LEX_ERROR;
    default:
        if (result >= JSON_STRING && result <= JSON_REAL_NUMBER)
        {
            char *truc = malloc(sizeof(char) * nbCaractere + 1);
            strncpy(truc, PosDeb, nbCaractere);
            truc[nbCaractere] = '\0';
            if (result == JSON_STRING)
            {
                addStringSymbolToLexData(_lexData, truc);
            }
            else if (result == JSON_INT_NUMBER)
            {
                int val = atoi(truc);
                addIntSymbolToLexData(_lexData, val);
            }
            else
            {
                float val = atof(truc);
                addRealSymbolToLexData(_lexData, val);
            }
            free(truc);
        }
        return result;
    }
}

/**
 * \fn int main()
 * \brief fonction principale
 */
#ifdef TEST

int main()
{
    char *test = " ";
    int i = 0;
    TLex *lex_data;

    test = strdup("{\"obj1\": [ {\"obj2\": 12, \"obj3\":\"text1 \\\"and\\\" text2\"},\n {\"obj4\":314.32} ], \"obj5\": true }");

    printf("%s", test);
    printf("\n");

    lex_data = initLexData(test);
    i = lex(lex_data);
    while (i != JSON_LEX_ERROR)
    {
        printf("lex()=%d\n", i);
        i = lex(lex_data);
    }
    printLexData(lex_data);
    deleteLexData(&lex_data);
    free(test);
    return 0;
}
#endif