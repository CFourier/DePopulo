/* identite.h :
 *  Fichier d'en-tête de la classe Identite, permettant l'indexation de toutes les particularités de l'identité d'un citoyen (nom, âge, genre, etc.) en un seul objet ;
 *  Créé le 30/04/2018
 */

#ifndef IDENTITE_H
#define IDENTITE_H

#include <QString>

#include "datenaissance.h"
#include "territoire.h"

class Identite
{
    public :

    Identite();

    protected :

    const DateNaissance *dateNaissance;
    Territoire *domicile;
    const bool *estMasculin;
};

#endif // IDENTITE_H
