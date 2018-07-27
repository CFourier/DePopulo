/* datenaissance.cpp :
 *  Fichier source de la classe DateNaissance, permettant la création de date de naissance afin de calculer les âges plus efficacement (pour permettre l'évolution de l'âge au fil des ans) ;
 *  Créé le 30/04/2018.
 */

#include <QtGlobal>

#include "datenaissance.h"

DateNaissance::DateNaissance()
{
    int min = 1920, max = 2018;

    *annee = (qrand() % (max - min + 1)) + min; //Génération d'une année aléatoire

    min = 1, max = 12;

    *mois = (qrand() % (max - min + 1)) + min; //Génération d'un mois aléatoire

    min = 1;

    if (*mois == 1 || *mois == 3 || *mois == 5 || *mois == 7 || *mois == 8 || *mois == 10 || *mois == 12) //On détermine le jour maximum, selon le mois.
    {
        max = 31;
    }

    else if (*mois == 2)
    {
        if (*annee % 4 == 0) //Si l'année est un nombre divisible par 4 ; autrement dit, s'il s'agit d'une année bissextile.
            *jour = 29;

        else
            *jour = 28;
    }

    else
    {
        max = 30;
    }

    *jour = (qrand() % (max - min + 1)) + min;
}

DateNaissance::DateNaissance(const int &p_annee, const int &p_mois, const int &p_jour)
{
    if (*mois > 12)
        *mois = 12;

    else if (*mois < 1)
        *mois = 1;

    if (*jour < 1)
        *jour = 1;

    else if (*jour > 28)
    {
        if (*mois == 1 || *mois == 3 || *mois == 5 || *mois == 7 || *mois == 8 || *mois == 10 || *mois == 12)
        {
            if (*jour > 31)
                *jour = 31;
        }

        else if (*mois == 2)
        {
            if (*annee % 4 == 0)
                *jour = 29;

            else
                *jour = 28;
        }

        else
        {
            if (*jour > 30)
                *jour = 30;
        }
    }

    *annee = p_annee;
    *mois = p_mois;
    *jour = p_jour;
}
