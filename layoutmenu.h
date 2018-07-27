/* layoutmenu.h :
 *  Fichier d'en-tête de la classe LayoutMenu, permettant la création d'un layout destiné au menu principal ;
 *  Créé le 29/04/2018
 */

#ifndef LAYOUTMENU_H
#define LAYOUTMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QImage>

class LayoutMenu : public QGridLayout
{
    public :

    LayoutMenu();

    QPushButton *boutonQuitter;
    QPushButton *boutonGenerer;
    QPushButton *boutonCharger;
    QPushButton *boutonOptions;
    QPixmap *imageMenu;
    QLabel *imageMenu_label;

    friend FenetreMenu();
};

#endif // LAYOUTMENU_H
