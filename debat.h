/* debat.h :
 *  Fichier d'en-tête de la classe Debat, permettant la détermination des problèmes et des solutions populaires possibles, des opinions des mouvements et des citoyens ;
 *  Créé le 23/04/2018.
 */

#ifndef DEBAT_H
#define DEBAT_H

#include <QString>
#include <QVector>

#include "solution.h"

class Debat
{
    public :

    Debat(const QString &p_nomDebat);
    void ajouterSolution(const QString &p_nomSolution);
    void retirerSolution(const QString &p_nomSolution);
    QVector<QString> getListeSolutions();

    protected :

    QString *nomDebat;
    QVector<Solution> solutions;
};

#endif // DEBAT_H
