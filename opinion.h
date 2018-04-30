/* opinion.h :
 *  Fichier d'en-tête de la classe Opinion, fournissant un objet facile à manipuler pour connaître l'avis des citoyens ;
 *  Créé le 30/04/2018
 */

#ifndef OPINION_H
#define OPINION_H

#define CONVICTION_MAXIMALE 1000 //Valeur maximale de convictionValeur

#include "debat.h"
#include "solution.h"

class Opinion
{
    public :

    Opinion();
    Opinion(const Debat &p_debat);
    Opinion(const Debat &p_debat, Solution &p_conviction, int &p_convictionValeur);
    void changerAvis(Solution &solutionGagnant, const int gainConviction);

    protected :

    const Debat *debat; //Le débat auquel l'opinion se rapporte
    Solution *conviction; //La solution préconisée par le citoyen
    int *convictionValeur; //La valeur de la conviction, c'est-à-dire à quel point le citoyen est convaincu que sa solution est la bonne
};

#endif // OPINION_H
