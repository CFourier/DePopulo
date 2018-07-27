/* population.cpp :
 *  Fichier source de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#include "fenetreprincipale.h"
#include "population.h"

Population::Population()
{
    Etat = new Territoire("Etat");
}

void Population::ajouterTerritoireEtat(const Territoire &territoire)
{
    Etat->inclureTerritoire(territoire);
}
