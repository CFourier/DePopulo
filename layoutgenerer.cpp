/* layoutgenerer.cpp :
 *  Fichier source de la classe LayoutGenerer, permettant la création d'un layout pré-défini pour la fenêtre principale ;
 *  Créé le 01/05/2018
 */

#include "layoutgenerer.h"

LayoutGenerer::LayoutGenerer()
{
    onglets = new QTabWidget;
    ongletEtat = new QWidget;
    ongletTerritoires = new QTabWidget;
    ongletsTerritoiresSubordonnes = new QVector<QWidget>;

    //Onglet État :

    layoutEtat = new QFormLayout;
    nomEtat = new QLineEdit;
    nomTerritoires = new QLineEdit;
    nombreTerritoires = new QSpinBox;
    nombreTerritoires->setMinimum(0);
    nombreTerritoires->setMaximum(25);
    nombreTerritoires->setValue(0);
    nombreTerritoires->setSuffix(nomTerritoires->text());

    layoutEtat->addRow("Nom du pays :", nomEtat);
    layoutEtat->addRow("Nom des territoires (régions, États, etc.) :", nomTerritoires);
    QString rowNombreTerritoires = "Nombre de " + nomTerritoires->text() + " :";
    layoutEtat->addRow(rowNombreTerritoires, nombreTerritoires);

    ongletEtat->setLayout(layoutEtat);

    //Onglet Territoires subordonnés :

    layoutTerritoires = new QFormLayout;
    nomTerritoire = new QLineEdit;

    QString rowNomTerritoire = "Nom du/de la " + nomTerritoire->text() + " :";
    layoutTerritoires->addRow(rowNomTerritoire, nomTerritoire);

    //---------------------

    onglets->addTab(ongletEtat, nomEtat->text());
    onglets->addTab(ongletTerritoires, nomTerritoires->text());
}

/*

void LayoutGenerer::genererOngletsSubordonnes()
{
    QWidget *ongletSubordonne;
    QString rowNomSubordonne = "Territoire subordonné";
    ongletTerritoires->addTab(ongletSubordonne, rowNomSubordonne);

    ongletsTerritoiresSubordonnes->push_back(*ongletSubordonne);
}

void LayoutGenerer::changerNombreTerritoires(int nombre)
{
    while (nombre > ongletsTerritoiresSubordonnes->size())
    {        
        genererOngletsSubordonnes();
    }

    while (nombre < ongletsTerritoiresSubordonnes->size())
    {
        ongletsTerritoiresSubordonnes->pop_back();
    }
}

*/

//À faire :
//- terminer les onglets ;
//- rendre le tout modifiable (création de slots tels que changerNomTerritoire(QString nom), etc.).
