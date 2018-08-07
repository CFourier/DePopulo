#include <QFileDialog>
#include <QtDebug>
#include <QCoreApplication>

#include "dialoguegenerer.h"

DialogueGenerer::DialogueGenerer(QWidget *parent)
{
    setWindowTitle("Nouvelle population");

    nomPopulation = new QLineEdit;
    paquetOpinions = new QPushButton("Paquet d'opinions de départ");
    paquetOpinionsChoisi = new QString("NULL");

    layoutFormulaire = new QFormLayout;
    layoutFormulaire->addRow("Nom de la population (ex. France, Allemagne ...) :", nomPopulation);

    emplacementFichiers = new QLabel("Emplacement des fichiers :");
    cheminFichiersPopulation = new QLineEdit(QCoreApplication::applicationDirPath());
    parcourirCheminFichiersPopulation = new QPushButton("Parcourir");
    emplacementFichiersChoisi = new QString("NULL");

    layoutCheminFichiers = new QHBoxLayout;
    layoutCheminFichiers->addWidget(emplacementFichiers);
    layoutCheminFichiers->addWidget(cheminFichiersPopulation);
    layoutCheminFichiers->addWidget(parcourirCheminFichiersPopulation);

    layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutFormulaire);
    layoutPrincipal->addWidget(paquetOpinions);
    layoutPrincipal->addLayout(layoutCheminFichiers);

    setLayout(layoutPrincipal);

    QObject::connect(paquetOpinions, SIGNAL(clicked()), this, SLOT(choisirPaquetOpinions()));
    QObject::connect(parcourirCheminFichiersPopulation, SIGNAL(clicked()), this, SLOT(choisirEmplacementFichiers()));
}

void DialogueGenerer::choisirPaquetOpinions()
{
    *paquetOpinionsChoisi = QFileDialog::getOpenFileName(this, "Ouvrir", QString(), "Paquet d'opinions (*.populopack)");

    if (*paquetOpinionsChoisi != "" && *paquetOpinionsChoisi != "NULL")
        paquetOpinions->setText("Paquet d'opinions de départ : " + *paquetOpinionsChoisi);
}

void DialogueGenerer::choisirEmplacementFichiers()
{
    *emplacementFichiersChoisi = QFileDialog::getExistingDirectory(this, "Choisir un emplacement pour les fichiers", cheminFichiersPopulation->text(), QFileDialog::ShowDirsOnly);

    if (*emplacementFichiersChoisi != "" && *emplacementFichiersChoisi != "NULL")
        cheminFichiersPopulation->setText(*emplacementFichiersChoisi);
}
