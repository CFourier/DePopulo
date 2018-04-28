/* fenetreprincipale.cpp :
 *  Fichier source de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme.
 *
 * Créé le 22/04/2018
 */

#include <QApplication>
#include <QWidget>
#include <QImage>

#include "debat.h"
#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
    imageMenu = new QPixmap(800, 300);
    QRgb couleur_rgb;
    couleur_rgb = qRgb(0, 60, 255);
    QColor couleur(couleur_rgb);
    imageMenu->fill(couleur);
    imageMenu_label = new QLabel;
    imageMenu_label->setPixmap(*imageMenu);

    boutonQuitter = new QPushButton("Quitter");
    boutonGenerer = new QPushButton("Générer une nouvelle population");
    boutonCharger = new QPushButton("Charger une population");
    boutonOptions = new QPushButton("Options");

    layoutPrincipal = new QGridLayout;

    layoutPrincipal->addWidget(imageMenu_label, 0, 0, 1, 2);
    layoutPrincipal->addWidget(boutonGenerer, 1, 0, 1, 2);
    layoutPrincipal->addWidget(boutonCharger, 2, 0, 1, 2);
    layoutPrincipal->addWidget(boutonOptions, 3, 0);
    layoutPrincipal->addWidget(boutonQuitter, 3, 1);

    setFixedSize(800, 500);
    setWindowTitle("De populo");
    setLayout(layoutPrincipal);

    QObject::connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}
