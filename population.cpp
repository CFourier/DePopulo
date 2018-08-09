/* population.cpp :
 *  Fichier source de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#include <QDir>
#include <QMessageBox>
#include <QtDebug>

#include "fenetreprincipale.h"
#include "population.h"

Population::Population()
{

}

Population::Population(QString *fichierPopulo)
{

}

Population::Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers)
{
    Etat = new Territoire("Etat");
    nomPopulation = new QString(p_nomPopulation);
    emplacementFichiers = new QString(p_emplacementFichiers);
    QString *nomDossier;
    nomDossier = new QString("DePopulo - " + *nomPopulation);
    *emplacementFichiers += "/" + *nomDossier;

    try
    {
        //On vérifie si le dossier à créer (dans lequel seront contenus les fichiers relatifs à la population) existe déjà (ainsi que des variantes du type "nomPopulation (1)", "nomPopulation (2)", etc. Sinon, on continue.

        bool emplacementExisteDeja;
        QString emplacementTest = *emplacementFichiers;

        for (int i = 0; emplacementExisteDeja == true; i++)
        {
            emplacementExisteDeja = QDir(emplacementTest).exists();

            emplacementTest = *nomDossier + "(" + i + ")";

            if (emplacementExisteDeja == true && i != 0)
                *nomDossier = "DePopulo - " + *nomPopulation + " (" + i + ")" + "/";

            if (i >= 1000 && emplacementExisteDeja == false)
                throw QString ("Erreur 1 : le dossier " + *nomDossier + " existe déjà. Veuillez le renommer, le déplacer ou le supprimer avant de réessayer.");
        }

        //On crée le dossier dans lequel seront contenus les fichiers relatifs à la population

        bool emplacementEstCree = QDir(*emplacementFichiers).mkpath(*nomDossier);

        if (emplacementEstCree == false)
            throw QString("Erreur 2 : le dossier " + *nomDossier + " n'a pas pu être créé.");

    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }
}

Population::Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers, const QString &paquetOpinions)
{
    Etat = new Territoire("Etat");
    nomPopulation = new QString(p_nomPopulation);
    emplacementFichiers = new QString(p_emplacementFichiers);
}

void Population::ajouterTerritoireEtat(const Territoire &territoire)
{
    Etat->inclureTerritoire(territoire);
}

Population::~Population()
{
    delete Etat;
    delete nomPopulation;
    delete emplacementFichiers;
}
