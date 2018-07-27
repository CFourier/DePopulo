/* citoyen.cpp :
 *  Fichier source de la classe Citoyen, permettant la création d'individus capables d'être intégrés à un échantillon statistique ou électoral ;
 *  Créé le 27/04/2018.
 */

#include "citoyen.h"

Citoyen::Citoyen()
{

}

void Citoyen::creerOpinion(const Debat &debat, const Solution &solution, const int convictionValeur)
{
    opinions->push_back(Opinion(debat, solution, convictionValeur));
}
