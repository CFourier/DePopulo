#include <QFileDialog>
#include <QtDebug>
#include <QCoreApplication>
#include <QMessageBox>

#include "dialoguegenerer.h"
#include "population.h"
#include "fenetreprincipale.h"

DialogueGenerer::DialogueGenerer(FenetrePrincipale *parent)
{
    fenetreParente = parent;

    setWindowTitle("Nouvelle population");

    nomPopulation = new QLineEdit;
    nomPopulation->setMaxLength(TAILLE_MAXIMALE_NOM_POPULATION);
    taillePopulation = new QSpinBox;
    taillePopulation->setMaximum(1000000000);
    taillePopulation->setSingleStep(1000000);
    populationSimulee = new QSpinBox;
    populationSimulee->setMinimum(0);
    populationSimulee->setMaximum(taillePopulation->value()); //Un slot qui fait changer le label ci-dessous lorsque la valeur de ce QSlider est modifiée
    labelPopulationSimulee = new QLabel();
    labelPopulationSimulee->setText("(0 %)");
    avertissementTaillePopulation1 = new QLabel;
    avertissementTaillePopulation2 = new QLabel;
    avertissementTaillePopulation3 = new QLabel;
    avertissementTaillePopulation4 = new QLabel;
    avertissementTaillePopulation1->setText("<b>Attention !</b>");
    avertissementTaillePopulation2->setText("Plus il y aura de citoyens simulés, plus cela nécessitera d'espace sur votre disque dur.");
    avertissementTaillePopulation3->setText("De plus, la création de la population ou une action de recensement massif de l'opinion des citoyens (e.g. élection) sera plus longue.");
    avertissementTaillePopulation4->setText("En contrepartie, la précision et le réalisme des chiffres se verront accrus.");
    avertissementTaillePopulation1->setAlignment(Qt::AlignHCenter);
    avertissementTaillePopulation2->setAlignment(Qt::AlignHCenter);
    avertissementTaillePopulation3->setAlignment(Qt::AlignHCenter);
    avertissementTaillePopulation4->setAlignment(Qt::AlignHCenter);
    paquetOpinions = new QPushButton("Paquet d'opinions de départ");
    paquetOpinionsChoisi = new QString("NULL");
    paquetProprietes = new QPushButton("Paquet de propriétés de départ");
    paquetProprietesChoisi = new QString("NULL");

    layoutFormulaire = new QFormLayout;
    layoutFormulaire->addRow("Nom de la population (ex. France, Allemagne ...) :", nomPopulation);
    layoutFormulaire->addRow("Nombre de citoyens :", taillePopulation);
    layoutFormulaire->addRow("Nombre de citoyens simulés :", populationSimulee);
    layoutFormulaire->addWidget(labelPopulationSimulee);

    emplacementFichiers = new QLabel("Emplacement des fichiers :");

    QDir dir(QCoreApplication::applicationDirPath() + "/Populations");
    if (!dir.exists())
    {
        QDir dirD(QCoreApplication::applicationDirPath());
        dirD.mkpath(QCoreApplication::applicationDirPath() + "/Populations");
    }

    cheminFichiersPopulation = new QLineEdit(QCoreApplication::applicationDirPath() + "/Populations");
    parcourirCheminFichiersPopulation = new QPushButton("Parcourir");
    emplacementFichiersChoisi = new QString("NULL");

    boutonOK = new QPushButton("OK");

    layoutCheminFichiers = new QHBoxLayout;
    layoutCheminFichiers->addWidget(emplacementFichiers);
    layoutCheminFichiers->addWidget(cheminFichiersPopulation);
    layoutCheminFichiers->addWidget(parcourirCheminFichiersPopulation);

    layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutFormulaire);
    layoutPrincipal->addWidget(avertissementTaillePopulation1);
    layoutPrincipal->addWidget(avertissementTaillePopulation2);
    layoutPrincipal->addWidget(avertissementTaillePopulation3);
    layoutPrincipal->addWidget(avertissementTaillePopulation4);
    layoutPrincipal->addWidget(paquetOpinions);
    layoutPrincipal->addWidget(paquetProprietes);
    layoutPrincipal->addLayout(layoutCheminFichiers);
    layoutPrincipal->addWidget(boutonOK);

    setLayout(layoutPrincipal);

    QObject::connect(paquetOpinions, SIGNAL(clicked()), this, SLOT(choisirPaquetOpinions()));
    QObject::connect(paquetProprietes, SIGNAL(clicked()), this, SLOT(choisirPaquetProprietes()));
    QObject::connect(parcourirCheminFichiersPopulation, SIGNAL(clicked()), this, SLOT(choisirEmplacementFichiers()));
    QObject::connect(boutonOK, SIGNAL(clicked()), this, SLOT(creerPopulation()));
    QObject::connect(populationSimulee, SIGNAL(valueChanged(int)), this, SLOT(synchroniserPopulationSimulee(int)));
    QObject::connect(taillePopulation, SIGNAL(valueChanged(int)), this, SLOT(synchroniserMaxSlider(int)));
}

void DialogueGenerer::choisirPaquetOpinions()
{
    *paquetOpinionsChoisi = QFileDialog::getOpenFileName(this, "Ouvrir", QString(), "Paquet d'opinions (*.populopack)");

    if (*paquetOpinionsChoisi != "" && *paquetOpinionsChoisi != "NULL")
    {
        QFileInfo opin(*paquetOpinionsChoisi);
        paquetOpinions->setText("Paquet d'opinions de départ : " + opin.fileName());
    }
}

void DialogueGenerer::choisirPaquetProprietes()
{
    *paquetProprietesChoisi = QFileDialog::getOpenFileName(this, "Ouvrir", QString(), "Paquet de propriétés (*.populopropripack)");

    if (*paquetProprietesChoisi != "" && *paquetProprietesChoisi != "NULL")
    {
        QFileInfo prop(*paquetProprietesChoisi);
        paquetProprietes->setText("Paquet de propriétés de départ : " + prop.fileName());
    }
}


void DialogueGenerer::choisirEmplacementFichiers()
{
    *emplacementFichiersChoisi = QFileDialog::getExistingDirectory(this, "Choisir un emplacement pour les fichiers", cheminFichiersPopulation->text(), QFileDialog::ShowDirsOnly);

    if (*emplacementFichiersChoisi != "" && *emplacementFichiersChoisi != "NULL")
        cheminFichiersPopulation->setText(*emplacementFichiersChoisi);
}

void DialogueGenerer::creerPopulation()
{
    if (nomPopulation->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous n'avez pas précisé de nom pour la population");
    }

    else if (taillePopulation->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous n'avez pas précisé de taille pour la population");
    }

    else if (populationSimulee->value() == 0)
    {
        QMessageBox::critical(this, "Erreur", "Le nombre de citoyens à simuler ne peut être nul !");
    }

    else
    {
        Population *population;

        if ((*paquetOpinionsChoisi == "" || *paquetOpinionsChoisi == "NULL") && (*paquetProprietesChoisi == "" || *paquetProprietesChoisi == "NULL"))
            population = new Population(fenetreParente, nomPopulation->text(), cheminFichiersPopulation->text(), "%%NULL%%", "%%NULL%%", taillePopulation->value(), populationSimulee->value());

        else if (*paquetOpinionsChoisi != "" && *paquetOpinionsChoisi != "NULL" && (*paquetProprietesChoisi == "" || *paquetProprietesChoisi == "NULL"))
            population = new Population(fenetreParente, nomPopulation->text(), cheminFichiersPopulation->text(), *paquetOpinionsChoisi, "%%NULL%%", taillePopulation->value(), populationSimulee->value());

        else if ((*paquetOpinionsChoisi == "" || *paquetOpinionsChoisi == "NULL") && *paquetProprietesChoisi != "" && *paquetProprietesChoisi != "NULL")
            population = new Population(fenetreParente, nomPopulation->text(), cheminFichiersPopulation->text(), "%%NULL%%", *paquetProprietesChoisi, taillePopulation->value(), populationSimulee->value());

        else if (*paquetOpinionsChoisi != "" && *paquetOpinionsChoisi != "NULL" && *paquetProprietesChoisi != "" && *paquetProprietesChoisi != "NULL")
            population = new Population(fenetreParente, nomPopulation->text(), cheminFichiersPopulation->text(), *paquetOpinionsChoisi, *paquetProprietesChoisi, taillePopulation->value(), populationSimulee->value());

        fenetreParente->setPopulation(*population);

        this->close();
    }
}

void DialogueGenerer::synchroniserPopulationSimulee(int p_citoyensSimules)
{
    double pourcentsDouble = (double)p_citoyensSimules / taillePopulation->value();
    int pourcentMille = pourcentsDouble * 100000;

    QString texte = "(";
    texte += QVariant(pourcentMille).toString();
    texte += " simulés pour 100 000 citoyens)";
    labelPopulationSimulee->setText(texte);
}

void DialogueGenerer::synchroniserMaxSlider(int max)
{
    if (populationSimulee->maximum() != 0)
    {
        double pourcentageDuTotal = populationSimulee->value()/populationSimulee->maximum();
        populationSimulee->setValue(pourcentageDuTotal * max);
    }

    populationSimulee->setMaximum(max);

    synchroniserPopulationSimulee(populationSimulee->value());
}
