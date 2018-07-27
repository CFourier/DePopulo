/* ville.cpp :
 *  Fichier source de la classe Ville, fille de Territoire, mais possédant une liste des citoyens qui la composent ;
 *  Créé le 01/05/2018.
 */

#include "ville.h"

Ville::Ville(const QString &p_nomTerritoire, QVector<Citoyen> p_population)
{
    nomTerritoire = new QString(p_nomTerritoire);
    population = p_population;
}
