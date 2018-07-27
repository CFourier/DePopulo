/* fenetremenu.h :
 *  Fichier d'en-tête de la classe FenetreMenu, permettant la création d'une fenêtre destinée à l'affichage du menu principal.
 *  Créé le 13/05/2018.
 */

#ifndef FENETREMENU_H
#define FENETREMENU_H

#include "fenetreprincipale.h"
#include "layoutmenu.h"

class FenetreMenu : public FenetrePrincipale
{
    public :

    Q_OBJECT

    public :

    FenetreMenu();

    public slots :

    void afficherGenerer();

    protected :

    int layoutAffiche;
    LayoutMenu *layout;
};

#endif // FENETREMENU_H
