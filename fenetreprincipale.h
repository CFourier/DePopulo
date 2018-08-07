/* fenetreprincipale.h :
 *  Fichier d'en-tête de la classe FenetrePrincipale, déterminant les caractéristiques de la fenêtre principale créée par le programme ;
 *  Créé le 22/04/2018.
 *  Modifié le 13/05/2018 :
 *  Il est désormais la classe-mère des différents types de fenêtres à afficher.
 *  Retour à sa fonction de départ le 27/07/2018.
 */

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 500

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QImage>
#include <QWidget>
#include <QMenu>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlTableModel>

#include "population.h"

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

    public :

    FenetrePrincipale();

    public slots :

    void afficherOpinions();
    void afficherPartis();
    void afficherElections();
    void creerNouvellePopulation();
    void chargerPopulation();
    void enregistrer();
    void enregistrerSous();

    protected :

    QString *fichier;

    QWidget *zoneCentrale;
    QVBoxLayout *layoutCentral;
    QVBoxLayout *layoutOpinions;
    QVBoxLayout *layoutPartis;
    QVBoxLayout *layoutElections;
    QStackedWidget *onglets;
    QWidget *ongletOpinions;
    QWidget *ongletPartis;
    QWidget *ongletElections;

    QTableView *tableauOpinions;
    QSqlTableModel *modeleTableauOpinions;
};

#endif // FENETREPRINCIPALE_H
