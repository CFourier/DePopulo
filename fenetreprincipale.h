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
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QImage>

#include "debat.h"

class FenetrePrincipale : public QWidget
{
    private :

    Q_OBJECT

    public :

    FenetrePrincipale();

    public slots :


    protected :

    QGridLayout *layoutPrincipal;
    QPushButton *boutonQuitter;
    QPushButton *boutonGenerer;
    QPushButton *boutonCharger;
    QPushButton *boutonOptions;
    QPixmap *imageMenu;
    QLabel *imageMenu_label;
};

#endif // FENETREPRINCIPALE_H
