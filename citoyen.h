/* citoyen.h :
 *  Fichier d'en-tête de la classe Citoyen, permettant la création d'individus capables d'être intégrés à un échantillon statistique ou électoral ;
 *  Créé le 27/04/2018.
 */

#ifndef CITOYEN_H
#define CITOYEN_H

#include "debat.h"
#include "identite.h"
#include "opinion.h"
#include "solution.h"

class Citoyen
{
    public :

    Citoyen();
    void creerOpinion(const Debat &debat, const Solution &solution, const int convictionValeur);

    protected :

    QVector<Opinion> *opinions;
    Identite *identite;
};

#endif // CITOYEN_H
