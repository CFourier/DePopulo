/* layoutgenerer.h :
 *  Fichier d'en-tête de la classe LayoutGenerer, permettant la création d'un layout pré-défini pour la fenêtre principale ;
 *  Créé le 01/05/2018
 */

#ifndef LAYOUTGENERER_H
#define LAYOUTGENERER_H

#include <QGridLayout>
#include <QTabWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>

class LayoutGenerer : public QGridLayout
{
    public :

    LayoutGenerer();
    void genererOngletsSubordonnes();
    void changerNombreTerritoires(int nombre);

    public :

    QTabWidget *onglets;

    QWidget *ongletEtat;
    QFormLayout *layoutEtat;
    QLineEdit *nomEtat;
    QLineEdit *nomTerritoires;
    QSpinBox *nombreTerritoires;

    QTabWidget *ongletTerritoires;
    QFormLayout *layoutTerritoires;
    QLineEdit *nomTerritoire;

    QVector<QWidget> *ongletsTerritoiresSubordonnes;

    friend FenetreGenerer();
};

#endif // LAYOUTGENERER_H
