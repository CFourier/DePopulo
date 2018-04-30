/* territoire.h :
 *  Fichier d'en-tête de la classe Territoire, permettant la création de regroupements de citoyens dans un but statistique ou de découpage électoral ;
 *  Créé le 27/04/2018.
 */

#ifndef ETAT_H
#define ETAT_H

#include <QVector>

#include "citoyen.h"

class Territoire
{
    public :

    Territoire();

    protected :

    QString *nomTerritoire;
    QVector<Territoire> territoiresInclus;
    QVector<Citoyen> population;
};

#endif // ETAT_H
