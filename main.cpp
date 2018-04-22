/*            De_populo
 * Projet de simulation de population
 *
 * Projet par : Virgile SOLT
 * Démarré le 22/04/2018
 * EDI : Qt Creator
 * Gestionnaire de versions : Git
 *
 * main.cpp :
 *  Fichier main
 *  Créé le 22/04/2018
 */

#include <QApplication>
#include <QtDebug>

#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
