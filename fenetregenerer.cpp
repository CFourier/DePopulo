/* fenetregenerer.cpp :
 *  Fichier source de la classe FenetreGenerer, permettant la création d'une fenêtre destinée à générer une population.
 *  Créé le 13/05/2018.
 */

#include "fenetregenerer.h"
#include "layoutgenerer.h"

FenetreGenerer::FenetreGenerer()
{
    layoutAffiche = GENERER;
    layout = new LayoutGenerer;

    setFixedSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    setWindowTitle("De populo");

    setLayout(layout);

    Population population;

    QObject::connect(layout->nombreTerritoires, SIGNAL(valueChanged(int)), this, SLOT(changerNombreTerritoires(int)));
}

void FenetreGenerer::changerNombreTerritoires(int nombre)
{
    // layoutGenerer->changerNombreTerritoires(nombre);
}
