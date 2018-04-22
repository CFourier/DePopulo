/* fenetreprincipale.cpp :
 *  Fichier source de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme.
 *
 * Créé le 22/04/2018
 */

#include <QApplication>
#include <QWidget>

#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
    boutonQuitter = new QPushButton("Quitter");
    layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(boutonQuitter);

    setFixedSize(800, 600);
    setWindowTitle("De populo");
    setLayout(layoutPrincipal);

    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}
