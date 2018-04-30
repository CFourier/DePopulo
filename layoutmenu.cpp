/* layoutmenu.cpp :
 *  Fichier source de la classe LayoutMenu, permettant la création d'un layout destiné au menu principal ;
 *  Créé le 29/04/2018
 */

#include "fenetreprincipale.h"
#include "layoutmenu.h"

LayoutMenu::LayoutMenu()
{
    imageMenu = new QPixmap(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    QRgb couleur_rgb;
    couleur_rgb = qRgb(0, 60, 255);
    QColor couleur(couleur_rgb);
    imageMenu->fill(couleur);
    imageMenu_label = new QLabel;
    imageMenu_label->setPixmap(*imageMenu);

    boutonQuitter = new QPushButton("Quitter");
    boutonGenerer = new QPushButton("Créer une nouvelle population");
    boutonCharger = new QPushButton("Charger une population");
    boutonOptions = new QPushButton("Options");

    this->addWidget(imageMenu_label, 0, 0, 1, 2);
    this->addWidget(boutonGenerer, 1, 0, 1, 2);
    this->addWidget(boutonCharger, 2, 0, 1, 2);
    this->addWidget(boutonOptions, 3, 0);
    this->addWidget(boutonQuitter, 3, 1);
}
