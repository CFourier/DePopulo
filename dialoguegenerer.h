#ifndef DIALOGUEGENERER_H
#define DIALOGUEGENERER_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <fenetreprincipale.h>

class DialogueGenerer : public QWidget
{
    Q_OBJECT

    public :

    DialogueGenerer(FenetrePrincipale *parent);

    public slots :

    void choisirPaquetOpinions();
    void choisirEmplacementFichiers();
    void creerPopulation();

    protected :

    FenetrePrincipale *fenetreParente;

    QFormLayout *layoutFormulaire;
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutCheminFichiers;

    QLineEdit *nomPopulation;
    QPushButton *paquetOpinions;
    QLineEdit *cheminFichiersPopulation;
    QPushButton *parcourirCheminFichiersPopulation;
    QLabel *emplacementFichiers;
    QPushButton *boutonOK;

    QString *paquetOpinionsChoisi;
    QString *emplacementFichiersChoisi;
};

#endif // DIALOGUEGENERER_H
