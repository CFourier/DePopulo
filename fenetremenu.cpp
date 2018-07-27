/* fenetremenu.cpp :
 *  Fichier source de la classe FenetreMenu, permettant la création d'une fenêtre destinée à l'affichage du menu principal.
 *  Créé le 13/05/2018.
 */

#include <QApplication>
#include <QtDebug>

#include "fenetremenu.h"
#include "fenetregenerer.h"
#include "layoutmenu.h"

FenetreMenu::FenetreMenu()
{
    layoutAffiche = MENU;
    layout = new LayoutMenu;

    setFixedSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    setWindowTitle("De populo");

    setLayout(layout);

    QObject::connect(layout->boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(layout->boutonGenerer, SIGNAL(clicked()), this, SLOT(afficherGenerer()));
}

void FenetreMenu::afficherGenerer()
{
    qDebug() << "1";

    FenetreGenerer fenetreGenerer;
    fenetreGenerer.show();
}
