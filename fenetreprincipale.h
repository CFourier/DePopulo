/* fenetreprincipale.h :
 *  Fichier d'en-tête de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme ;
 *  Créé le 22/04/2018.
 *  Modifié le 13/05/2018 :
 *  Il est désormais la classe-mère des différents types de fenêtres à afficher.
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

#include "layoutgenerer.h"
#include "layoutmenu.h"
#include "population.h"

enum
{
    MENU, GENERER, CHARGER, OPTIONS
};

class FenetrePrincipale : public QWidget
{
    public :

    FenetrePrincipale();
    int getLayoutAffiche();

    protected :

    int layoutAffiche;
};

#endif // FENETREPRINCIPALE_H
