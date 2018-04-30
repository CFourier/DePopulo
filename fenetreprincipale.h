/* fenetreprincipale.h :
 *  Fichier d'en-tête de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme.
 *
 * Créé le 22/04/2018
 */

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 500

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QImage>

#include "layoutmenu.h"

class FenetrePrincipale : public QWidget
{
    public :

    FenetrePrincipale();
    void chargerMenu();

    protected :

    LayoutMenu *layoutMenu;
};

#endif // FENETREPRINCIPALE_H
