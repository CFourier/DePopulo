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
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

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

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
