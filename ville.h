/* ville.h :
 *  Fichier d'en-tête de la classe Ville, fille de Territoire, mais possédant une liste des citoyens qui la composent ;
 *  Créé le 01/05/2018.
 */

#ifndef VILLE_H
#define VILLE_H

#include "citoyen.h"
#include "territoire.h"

class Ville : public Territoire
{
    public :

    Ville(const QString &p_nomTerritoire, QVector<Citoyen> p_population);

    protected :

    QVector<Citoyen> population;
};

#endif // VILLE_H
