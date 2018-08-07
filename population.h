/* population.h :
 *  Fichier d'en-tête de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#ifndef POPULATION_H
#define POPULATION_H

#include "territoire.h"

class Population
{
    public :

    Population(QString &p_nomPopulation);
    Population(QString &p_nomPopulation, QString &paquetsOpinions);
    void ajouterTerritoireEtat(const Territoire &territoire);

    protected :

    Territoire *Etat;
};

#endif // POPULATION_H
