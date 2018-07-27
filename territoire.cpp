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
}

Territoire::Territoire(const QString &p_nomTerritoire)
{
    nomTerritoire = new QString(p_nomTerritoire);
    territoiresInclus = new QVector<Territoire>;

    //Préparer l'onglet/la fenêtre (en appelant un objet d'une classe à créer) qui permettra de déterminer les choix concernant chaque territoire subordonné
}

void Territoire::inclureTerritoire(const Territoire &territoire)
{
    territoiresInclus->push_back(territoire);
}

void Territoire::integrerAuTerritoire(Territoire &territoire)
{
    territoire.inclureTerritoire(*this);
}

void Territoire::integrerAuTerritoire(const QString &p_nomTerritoire, Territoire Etat)
{
    Territoire territoire(p_nomTerritoire);
    territoire.inclureTerritoire(*this);

    Etat.inclureTerritoire(territoire);
}
