/* population.cpp :
 *  Fichier source de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#include <QDir>
#include <QMessageBox>
#include <QtDebug>

#include "chercherinfofichier.h"
#include "ecrirefichier.h"
#include "fenetreprincipale.h"
#include "population.h"

Population::Population()
{
    Etat = new Territoire;
    nomPopulation = new QString("Population");
    emplacementFichiers = new QString;
    *emplacementFichiers = QDir::currentPath();

    fichierPopulation = new QFile("population.populo");
    fichierOpinions = new QFile("population.populopack");
}

Population::Population(QWidget *fenetreParente, QString *p_fichierPopulo)
{
    try
    {
        fichierPopulation = new QFile(*p_fichierPopulo);

        //On recherche le nom de la population

        nomPopulation = new QString;
        *nomPopulation = chercherNomPopulation(fenetreParente, fichierPopulation->fileName());
        if (*nomPopulation  == "@@@ERREUR@@@")
            throw bool(true);

        //On recherche le paquet d'opinions

        QString cherche = chercherInfoStandard(fenetreParente, fichierPopulation->fileName(), "*Paquet d'opinions : ");
        if (cherche == "@@@ERREUR@@@")
            throw bool(true);
        fichierOpinions = new QFile(cherche);

        //On recherche la taille de la population totale et simulée

        cherche = chercherInfoStandard(fenetreParente, fichierPopulation->fileName(), "*Citoyens simulés : ");
        if (cherche == "@@@ERREUR@@@")
            throw bool(true);
        taillePopulationSimulee = new int;
        *taillePopulationSimulee = cherche.toInt();

        cherche = chercherInfoStandard(fenetreParente, fichierPopulation->fileName(), "*Citoyens : ");
        if (cherche == "@@@ERREUR@@@")
            throw bool(true);
        ratioPopulationSurSimules = new double;
        *ratioPopulationSurSimules = cherche.toInt() / *taillePopulationSimulee;

        Etat = new Territoire(*nomPopulation, *taillePopulationSimulee);
        emplacementFichiers = new QString;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }
    catch (const bool &erreur)
    {

    }
}

Population::Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers)
{
    Etat = new Territoire("Etat");
    nomPopulation = new QString(p_nomPopulation);
    emplacementFichiers = new QString(p_emplacementFichiers);
    QString *nomDossier;
    nomDossier = new QString("DePopulo - " + *nomPopulation);

    fichierPopulation = new QFile;

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

        //On crée le dossier dans lequel seront contenus les fichiers relatifs à la population.

        bool emplacementEstCree = QDir(*emplacementFichiers).mkpath(*nomDossier);

        *emplacementFichiers += "/" + *nomDossier;

        if (emplacementEstCree == false)
            throw QString("Erreur 2 : le dossier " + *nomDossier + " n'a pas pu être créé.");

        //Dans ce dossier, on crée le fichier principal "nomPopulation.populo"

      /*  fichierPopulation->setFileName(*nomDossier + "/" + *nomPopulation + ".populo"); //Ne fonctionne pas
        if (!fichierPopulation->open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("Impossible d'ouvrir le fichier " + fichierPopulation->fileName()); */

        /* On crée ces fichiers (remplacer "population" par le nom de la population) :
         * Un fichier "population.populo" recensant les caractéristiques de l'État : nom, population totale, territoires subordonnés, etc. ainsi que le fichier .populopack correspondant à la population ;
         * Un fichier "population.populopack", paquet d'opinions, c'est-à-dire référençant les opinions et les solutions relatives à la population (législation sur telle ou telle chose ---> Autorisation/Interdiction/Tolérance à la consommation, etc., ou encore système politique ---> démocratique/monarchique/totalitaire, etc.) ;
         * Un fichier "territoire.subpopulo" (remplacer "territoire" par le nom du territoire), du même type que le fichier .populo, mais à plus petite échelle, à chaque territoire subordonné ;
         * Un fichier "population_citoyen.populocitoyen" (remplacer "citoyen" par un numéro d'identification quelconque) pour chaque citoyen, renseignant sur l'ensemble de ses caractéristiques (âge, genre, solutions préconisées sur toutes les opinions, etc.) ;
         * Un fichier "propriété.populopropri" (remplacer "propriété" par la propriété en question) pour chaque propriété des citoyens : âge, genre, activité, etc., contenant l'ensemble des solutions qu'il peut y avoir (1 an, 2 ans, 3 ans ... 150 ans ; femme, homme ; agriculteur, infirmier, demandeur d'emploi, retraité, étudiant, etc.).
         */
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
