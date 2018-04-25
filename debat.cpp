/* debat.cpp :
 *  Fichier source de la classe Debat, permettant la détermination des problèmes et des solutions populaires possibles, des opinions des mouvements et des citoyens ;
 *  Créé le 23/04/2018.
 */

#include "debat.h"
#include "solution.h"

Debat::Debat(const QString &p_nomDebat)
{
    nomDebat = new QString(p_nomDebat);
}

void Debat::ajouterSolution(const QString &p_nomSolution)
{
    solutions.push_back(Solution(p_nomSolution));
}

void Debat::retirerSolution(const QString &p_nomSolution)
{
    for (QVector<Solution>::iterator it = solutions.begin(); it != solutions.end(); it++)
    {
        if (it->getNomSolution() == p_nomSolution)
            solutions.erase(it);
    }
}

QVector<QString> Debat::getListeSolutions()
{
    QVector<QString> listeSolutions;

    for (QVector<Solution>::iterator it = solutions.begin(); it != solutions.end(); it++)
    {
        listeSolutions.push_back(it->getNomSolution());
    }

    return listeSolutions;
}
