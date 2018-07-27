/* territoire.h :
 *  Fichier d'en-tête de la classe Territoire, permettant la création de regroupements de citoyens dans un but statistique ou de découpage électoral ;
 *  Créé le 27/04/2018.
 */

#ifndef TERRITOIRE_H
#define TERRITOIRE_H

#include <QVector>

class Territoire
{
    public :

    Territoire();
    Territoire(const QString &p_nomTerritoire);
    void inclureTerritoire(const Territoire &territoire);
    void integrerAuTerritoire(Territoire &territoire);
    void integrerAuTerritoire(const QString &p_nomTerritoire, Territoire Etat);

    protected :

    QString *nomTerritoire;

    private :

    QVector<Territoire> *territoiresInclus;
};

#endif // TERRITOIRE_H
