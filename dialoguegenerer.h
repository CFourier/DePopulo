#ifndef DIALOGUEGENERER_H
#define DIALOGUEGENERER_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class DialogueGenerer : public QWidget
{
    Q_OBJECT

    public :

    DialogueGenerer(QWidget *parent = 0);

    public slots :

    void choisirPaquetOpinions();
    void choisirEmplacementFichiers();

    protected :

    QFormLayout *layoutFormulaire;
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutCheminFichiers;

    QLineEdit *nomPopulation;
    QPushButton *paquetOpinions;
    QLineEdit *cheminFichiersPopulation;
    QPushButton *parcourirCheminFichiersPopulation;
    QLabel *emplacementFichiers;

    QString *paquetOpinionsChoisi;
    QString *emplacementFichiersChoisi;
};

#endif // DIALOGUEGENERER_H
