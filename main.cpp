/* De_populo
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

#include "citoyen.h"
#include "datenaissance.h"
#include "debat.h"
#include "fenetreprincipale.h"
#include "population.h"
#include "identite.h"
#include "opinion.h"
#include "solution.h"
#include "territoire.h"
#include "ville.h"

int main(int argc, char *argv[])
{
    qsrand(0);

    QApplication app(argc, argv);

    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
