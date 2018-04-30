/* fenetreprincipale.cpp :
 *  Fichier source de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme.
 *
 * Créé le 22/04/2018
 */

#include <QApplication>
#include <QWidget>

#include "fenetreprincipale.h"
#include "layoutmenu.h"

FenetrePrincipale::FenetrePrincipale()
{
    layoutMenu = new LayoutMenu;

    chargerMenu();
}

void FenetrePrincipale::chargerMenu()
{
    setFixedSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    setWindowTitle("De populo");
    setLayout(layoutMenu);

    QObject::connect(layoutMenu->boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}
