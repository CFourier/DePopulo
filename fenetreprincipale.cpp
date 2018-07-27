/* fenetreprincipale.cpp :
 *  Fichier source de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme ;
 *  Créé le 22/04/2018.
 *  Modifié le 13/05/2018 :
 *  Il est désormais la classe-mère des différents types de fenêtres à afficher.
 */

#include <QApplication>
#include <QWidget>

#include "fenetreprincipale.h"
#include "layoutmenu.h"
#include "population.h"

FenetrePrincipale::FenetrePrincipale()
{

}

int FenetrePrincipale::getLayoutAffiche()
{
    return layoutAffiche;
}
