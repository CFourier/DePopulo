/* fenetreprincipale.h :
 *  Fichier d'en-tête de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme.
 *
 * Créé le 22/04/2018
 */

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class FenetrePrincipale : public QWidget
{
    public :

    FenetrePrincipale();

    protected :

    QVBoxLayout *layoutPrincipal;
    QPushButton *boutonQuitter;
};

#endif // FENETREPRINCIPALE_H
