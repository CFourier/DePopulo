/* population.h :
 *  Fichier d'en-tête de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#ifndef POPULATION_H
#define POPULATION_H

#include <QDir>

#include "territoire.h"

class Population
{
    public :

    Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers);
    Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers, const QString &paquetOpinions);
    void ajouterTerritoireEtat(const Territoire &territoire);

    protected :

    Territoire *Etat;
    QString *nomPopulation;
    QString *emplacementFichiers;
};

#endif // POPULATION_H
