/* opinion.cpp :
 *  Fichier source de la classe Opinion, fournissant un objet facile à manipuler pour connaître l'avis des citoyens ;
 *  Créé le 30/04/2018
 */

#include "opinion.h"

Opinion::Opinion()
{
    debat = NULL;
    conviction = NULL;
    convictionValeur = 0;
}

Opinion::Opinion(const Debat &p_debat)
{
    debat = &p_debat;
    conviction = NULL;
    convictionValeur = 0;
}

Opinion::Opinion(const Debat &p_debat, Solution &p_conviction, int &p_convictionValeur)
{
    debat = &p_debat;
    conviction = &p_conviction;
    convictionValeur = &p_convictionValeur;
}

void Opinion::changerAvis(Solution &solutionGagnant, const int gainConviction)
{
    if (debat != NULL && conviction != NULL)
    {

        if (*conviction == solutionGagnant)
        {
            convictionValeur += gainConviction;
        }

        else
        {
            convictionValeur -= gainConviction;

            if (*convictionValeur == 0)
            {
                conviction = NULL;
            }

            else if (*convictionValeur < 0)
            {
                conviction = &solutionGagnant;
                *convictionValeur = 0 - *convictionValeur;
            }
        }

        if (*convictionValeur > CONVICTION_MAXIMALE)
            *convictionValeur = CONVICTION_MAXIMALE;

    }

    else if (debat != NULL && conviction == NULL)
    {
        conviction = &solutionGagnant;
        *convictionValeur = gainConviction;
    }
}
