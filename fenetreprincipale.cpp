/* fenetreprincipale.cpp :
 *  Fichier source de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme.
 *
 * Créé le 22/04/2018
 */

#include <QApplication>
#include <QWidget>

#include "debat.h"
#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
    debat = new Debat("Debat par défaut");

    listeSolutions = new QLabel("Liste des solutions");
    solution = new QLineEdit;
    boutonSolution = new QPushButton("Ajouter solution");
    boutonQuitter = new QPushButton("Quitter");
    layoutPrincipal = new QVBoxLayout;

    layoutPrincipal->addWidget(listeSolutions);
    layoutPrincipal->addWidget(solution);
    layoutPrincipal->addWidget(boutonSolution);
    layoutPrincipal->addWidget(boutonQuitter);

    setFixedSize(400, 300);
    setWindowTitle("De populo");
    setLayout(layoutPrincipal);

    QObject::connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(boutonSolution, SIGNAL(clicked()), this, SLOT(insereSolution()));
    QObject::connect(boutonSolution, SIGNAL(clicked()), this, SLOT(afficheListeSolutions()));
}

void FenetrePrincipale::insereSolution()
{
    debat->ajouterSolution(solution->text());
}

void FenetrePrincipale::afficheListeSolutions()
{
    QVector<QString> qVectorSolutions = debat->getListeSolutions();

    QString qStringSolutions;

    for (QVector<QString>::iterator it = qVectorSolutions.begin(); it != qVectorSolutions.end(); it++)
    {
        qStringSolutions += it;
        qStringSolutions += "\n";
    }

    listeSolutions->setText(qStringSolutions);
}
