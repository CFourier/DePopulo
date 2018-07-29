/* datenaissance.h :
 *  Fichier d'en-tête de la classe DateNaissance, permettant la création de date de naissance afin de calculer les âges plus efficacement (pour permettre l'évolution de l'âge au fil des ans) ;
 *  Créé le 30/04/2018.
 */

#ifndef DATENAISSANCE_H
#define DATENAISSANCE_H

#include <QDate>

class DateNaissance : public QDate
{
    public :

    DateNaissance();
    DateNaissance(const int &p_annee, const int &p_mois, const int &p_jour);

    protected :

    int *annee;
    int *mois;
    int *jour;
};

#endif // DATENAISSANCE_H
