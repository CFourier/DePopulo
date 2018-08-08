/* population.cpp :
 *  Fichier source de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#include <QDir>
#include <QMessageBox>
#include <QtDebug>

#include "fenetreprincipale.h"
#include "population.h"

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
