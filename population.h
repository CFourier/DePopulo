/* population.h :
 *  Fichier d'en-tête de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#ifndef POPULATION_H
#define POPULATION_H

#define LARGEUR_EN_TETE_FICHIER 47
#define TAILLE_MAXIMALE_NOM_POPULATION LARGEUR_EN_TETE_FICHIER - 15

#include <QFile>

#include "territoire.h"

class Population
{
    public :

    Population();
    Population(QWidget *fenetreParente, QString *p_fichierPopulo); //Pour charger une population
    Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers, const QString &paquetOpinions = "%%NULL%%", const QString &paquetProprietes = "%%NULL%%", const int p_taillePopulation = 0, const int p_taillePopulationSimulee = 0); //Pour créer une population
    ~Population();

    protected :

    Territoire *Etat;
    QString *nomPopulation;
    QString *emplacementFichiers;
    int *taillePopulationSimulee;
    double *ratioPopulationSurSimules;

    QFile *fichierPopulation;
    QFile *fichierOpinions;
    QFile *fichierProprietes;
};

#endif // POPULATION_H
