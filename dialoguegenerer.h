#ifndef DIALOGUEGENERER_H
#define DIALOGUEGENERER_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

#include <fenetreprincipale.h>

class DialogueGenerer : public QWidget
{
    Q_OBJECT

    public :

    DialogueGenerer(FenetrePrincipale *parent);

    public slots :

    void choisirPaquetOpinions();
    void choisirPaquetProprietes();
    void choisirEmplacementFichiers();
    void creerPopulation();
    void synchroniserPopulationSimulee(int p_citoyensSimules);
    void synchroniserMaxSlider(int max);

    protected :

    FenetrePrincipale *fenetreParente;

    QFormLayout *layoutFormulaire;
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutCheminFichiers;

    QLineEdit *nomPopulation;
    QSpinBox *taillePopulation;
    QSlider *populationSimulee;
    QLabel *labelPopulationSimulee;
    QLabel *avertissementTaillePopulation1;
    QLabel *avertissementTaillePopulation2;
    QLabel *avertissementTaillePopulation3;
    QLabel *avertissementTaillePopulation4;
    QPushButton *paquetOpinions;
    QPushButton *paquetProprietes;
    QLineEdit *cheminFichiersPopulation;
    QPushButton *parcourirCheminFichiersPopulation;
    QLabel *emplacementFichiers;
    QPushButton *boutonOK;

    QString *paquetProprietesChoisi;
    QString *paquetOpinionsChoisi;
    QString *emplacementFichiersChoisi;
};

#endif // DIALOGUEGENERER_H
