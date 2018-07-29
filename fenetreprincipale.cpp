/* fenetreprincipale.cpp :
 *  Fichier source de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme ;
 *  Créé le 22/04/2018.
 *  Modifié le 13/05/2018 :
 *  Il est désormais la classe-mère des différents types de fenêtres à afficher.
 */

#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QLabel>

#include "dialoguegenerer.h"
#include "fenetreprincipale.h"
#include "population.h"

FenetrePrincipale::FenetrePrincipale()
{
    setWindowTitle("De populo");
    setFixedSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);

    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    QMenu *menuFichier = menuBar()->addMenu("Fichier");
    QAction *actionNouvellePopulation = menuFichier->addAction("Nouvelle population");
    QAction *actionChargerPopulation = menuFichier->addAction("Charger une population");
    QAction *actionEnregistrer = menuFichier->addAction("Enregistrer");
    QAction *actionEnregistrerSous = menuFichier->addAction("Enregistrer sous");
    QAction *actionQuitter = menuFichier->addAction("Quitter");

    QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QToolBar *barreDOutils = addToolBar("Gestion de population");
    barreDOutils->addAction(actionEnregistrer);
    barreDOutils->addSeparator();
    QAction *actionOpinions = barreDOutils->addAction("Opinions");
    QAction *actionPartis = barreDOutils->addAction("Partis");
    QAction *actionElections = barreDOutils->addAction("Élections");

    layoutOpinions = new QVBoxLayout;
    layoutPartis = new QVBoxLayout;
    layoutElections = new QVBoxLayout;

    onglets = new QStackedWidget;
    ongletOpinions = new QWidget;
    ongletPartis = new QWidget;
    ongletElections = new QWidget;
    ongletOpinions->setLayout(layoutOpinions);
    ongletPartis->setLayout(layoutPartis);
    ongletElections->setLayout(layoutElections);
    onglets->addWidget(ongletOpinions);
    onglets->addWidget(ongletPartis);
    onglets->addWidget(ongletElections);

    layoutCentral = new QVBoxLayout;
    layoutCentral->addWidget(onglets);
    zoneCentrale->setLayout(layoutCentral);

    tableauOpinions = new QTableWidget;
    tableauOpinions->setRowCount(2);
    tableauOpinions->setColumnCount(2);
    layoutOpinions->addWidget(tableauOpinions);

    QObject::connect(actionOpinions, SIGNAL(triggered()), this, SLOT(afficherOpinions()));
    QObject::connect(actionPartis, SIGNAL(triggered()), this, SLOT(afficherPartis()));
    QObject::connect(actionElections, SIGNAL(triggered()), this, SLOT(afficherElections()));
    QObject::connect(actionNouvellePopulation, SIGNAL(triggered()), this, SLOT(creerNouvellePopulation()));
    QObject::connect(actionChargerPopulation, SIGNAL(triggered()), this, SLOT(chargerPopulation()));
    QObject::connect(actionEnregistrer, SIGNAL(triggered()), this, SLOT(enregistrer()));
    QObject::connect(actionEnregistrerSous, SIGNAL(triggered()), this, SLOT(enregistrerSous()));
}

void FenetrePrincipale::afficherOpinions()
{
    onglets->setCurrentWidget(ongletOpinions);
}

void FenetrePrincipale::afficherPartis()
{
    onglets->setCurrentWidget(ongletPartis);
}

void FenetrePrincipale::afficherElections()
{
    onglets->setCurrentWidget(ongletElections);
}

void FenetrePrincipale::creerNouvellePopulation()
{

}

void FenetrePrincipale::chargerPopulation()
{

}

void FenetrePrincipale::enregistrer()
{

}

void FenetrePrincipale::enregistrerSous()
{

}
