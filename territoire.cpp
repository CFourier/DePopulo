/* territoire.cpp :
 *  Fichier source de la classe Territoire, permettant la création de regroupements de citoyens dans un but statistique ou de découpage électoral ;
 *  Créé le 27/04/2018.
 */

#include "population.h"
#include "territoire.h"

Territoire::Territoire()
{
    nomTerritoire = new QString("Territoire par défaut");
    territoiresInclus = new QVector<Territoire>;
    taillePopulation = new int(0);
}

Territoire::Territoire(const QString &p_nomTerritoire)
{
    nomTerritoire = new QString(p_nomTerritoire);
    territoiresInclus = new QVector<Territoire>;
    taillePopulation = new int(0);

    //Préparer l'onglet/la fenêtre (en appelant un objet d'une classe à créer) qui permettra de déterminer les choix concernant chaque territoire subordonné
}

Territoire::Territoire(const QString &p_nomTerritoire, const int &p_taillePopulation)
{
    nomTerritoire = new QString(p_nomTerritoire);
    territoiresInclus = new QVector<Territoire>;
    taillePopulation = new int(p_taillePopulation);

    //Préparer l'onglet/la fenêtre (en appelant un objet d'une classe à créer) qui permettra de déterminer les choix concernant chaque territoire subordonné
}

void Territoire::inclureTerritoire(Territoire &territoire)
{
    territoiresInclus->push_back(territoire);
}

QString Territoire::getNomTerritoire()
{
    return *nomTerritoire;
}

QVector<Territoire> Territoire::getTerritoiresSubordonnes()
{
    return *territoiresInclus;
}
