/* fenetregenerer.h :
 *  Fichier d'en-tête de la classe FenetreGenerer, permettant la création d'une fenêtre destinée à générer une population.
 *  Créé le 13/05/2018.
 */

#ifndef FENETREGENERER_H
#define FENETREGENERER_H

#include "fenetreprincipale.h"
#include "layoutgenerer.h"

class FenetreGenerer : public FenetrePrincipale
{
    public :

    Q_OBJECT

    public :

    FenetreGenerer();

    public slots :

    void changerNombreTerritoires(int nombre);

    protected :

    int layoutAffiche;
    LayoutGenerer *layout;
};

#endif // FENETREGENERER_H
