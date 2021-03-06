/* territoire.h :
 *  Fichier d'en-tête de la classe Territoire, permettant la création de regroupements de citoyens dans un but statistique ou de découpage électoral ;
 *  Créé le 27/04/2018.
 */

#ifndef TERRITOIRE_H
#define TERRITOIRE_H

#include <QVector>
#include <QDir>

class Territoire
{
    public :

    Territoire();
    Territoire(const QString &p_nomTerritoire);
    Territoire(const QString &p_nomTerritoire, const int &p_taillePopulation);
    void inclureTerritoire(Territoire &territoire);
    QString getNomTerritoire();
    QVector<Territoire> getTerritoiresSubordonnes();

    protected :

    QString *nomTerritoire;
    QVector<Territoire> *territoiresInclus;
    int *taillePopulation;
};

#endif // TERRITOIRE_H
