/* population.cpp :
 *  Fichier source de la classe Population, recensant une population et la créant ;
 *  Créé le 01/05/2018.
 */

#include <QDir>
#include <QMessageBox>
#include <QtDebug>
#include <QCoreApplication>
#include <QDate>
#include <QTime>

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

        //On cherche l'emplacement du dossier de la population, pour faciliter les recherches postérieures

        emplacementFichiers = new QString;
        *emplacementFichiers = QCoreApplication::applicationDirPath() + "/Populations/DePopulo - " + *nomPopulation;

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

        //On va créer tous les Territoires et les inclure chacun dans l'autre, grâce à la lecture des fichiers

        bool tousTerritoiresIntegres = false;
        QMap<QString, QString> territoiresAIntegrer; //L'indice est le nom du territoire, la valeur est le territoire auquel on l'inclut
        QMap<QString, Territoire> territoiresTraites; //Les territoires déjà intégrés. Le but, c'est que tous les Territoires passent de territoiresAIntegrer à territoiresTraites ; alors, on peut continuer
        territoiresTraites["Etat"] = *Etat;

        QVector<QString> territoiresATraiter = chercherInfoListe(fenetreParente, fichierPopulation->fileName(), "*Territoires subordonnés : "); //On cherche les territoires subordonnés
        if (territoiresATraiter.size() != 0 && territoiresATraiter[0] == "@@@ERREUR@@@") //En cas d'erreur
            throw bool(true);

        if (territoiresATraiter.size() > 0)
        {
            for (int i = 0; i < territoiresATraiter.size(); i++) //On intègre ces territoires dans la liste des territoires à traiter, avec le nom du territoire auquel on doit les inclure (présent normalement dans la QMap territoiresTraites)
                territoiresAIntegrer[territoiresATraiter[i]] = "Etat";
        }

        if (territoiresATraiter.size() != 0)
        {
            QVector<QString> clesASupprimer;

            while (tousTerritoiresIntegres == false) //On procède par étapes : d'abord, on crée l'État, puis les territoires en-dessous, puis ceux encore en-dessous, etc.
            {
                QMap<QString, QString> territoiresLus = territoiresAIntegrer; //Les territoires de l'étape, à intégrer et dont les territoires subordonnés devront être lus
                QMap<QString, QString>::iterator iterateur;
                for (iterateur = territoiresLus.begin(); iterateur != territoiresLus.end(); iterateur++)
                {
                    //On traite le territoire

                    Territoire *territoire; //On crée le territoire ...
                    territoire = new Territoire(iterateur.key()); //... avec pour nom la clé utilisée dans le QMap des territoires à intégrer

                    if (territoiresTraites.contains(iterateur.value())) //On vérifie que le territoire dans lequel inclure le nouveau existe bel et bien
                    {
                        QMap<QString, Territoire>::iterator iterateurDansLequelInclure = territoiresTraites.find(iterateur.value());
                        iterateurDansLequelInclure.value().inclureTerritoire(*territoire); //Si oui, on inclut le nouveau dedans
                    }

                    else
                        throw QString("Erreur 11 : Le territoire " + iterateur.value() + " qui inclut le territoire " + iterateur.key() + " n'existe pas !");

                    //On rajoute les territoires subordonnés à ce territoire

                    territoiresATraiter.clear();
                    territoiresATraiter = chercherInfoListe(fenetreParente, *emplacementFichiers + "/Territoires/" + iterateur.key().toLower() + ".subpopulo", "*Territoires subordonnés : "); //On cherche les territoires subordonnés
                    if (territoiresATraiter.size() != 0 && territoiresATraiter[0] == "@@@ERREUR@@@") //En cas d'erreur
                        throw bool(true);

                    if (territoiresATraiter.size() > 0)
                    {
                        for (int i = 0; i < territoiresATraiter.size(); i++) //On intègre ces territoires dans la liste des territoires à traiter, avec le nom du territoire auquel on doit les inclure (présent normalement dans la QMap territoiresTraites)
                            territoiresAIntegrer[territoiresATraiter[i]] = iterateur.key();
                    }

                    territoiresTraites[iterateur.key()] = *territoire; //On rajoute le territoire dans le tableau des territoires traités
                    clesASupprimer.push_back(iterateur.key());
                }

                for (int i = 0; i < clesASupprimer.size(); i++)
                {
                    QMap<QString, QString>::iterator iterateurSupprimer = territoiresAIntegrer.find(clesASupprimer[i]); //On cherche les clés des territoires que l'on a traités ...
                    territoiresAIntegrer.erase(iterateurSupprimer); //... et on les enlève du tableau des territoires qui sont à traiter (puisqu'ils ont été traités)
                    clesASupprimer.clear();
                }

                if (territoiresAIntegrer.isEmpty())
                    tousTerritoiresIntegres = true;
            }
        }
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }
    catch (const bool &erreur)
    {

    }
}

Population::Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers, const QString &paquetOpinions)
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

        QTextStream fluxEcriture;

        fichierPopulation = new QFile();
        fichierPopulation->setFileName(*emplacementFichiers + "/" + *nomPopulation + ".populo"); //Ne fonctionne pas
        if (!fichierPopulation->open(QIODevice::WriteOnly | QIODevice::Text))
            throw QString("Impossible d'ouvrir le fichier " + fichierPopulation->fileName());

        fluxEcriture.setDevice(fichierPopulation);

        for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
            fluxEcriture << "*";

        int nombreAsterisquesAvant = (TAILLE_MAXIMALE_NOM_POPULATION - nomPopulation->size()) / 2;
        int nombreAsterisquesApres = nombreAsterisquesAvant + (TAILLE_MAXIMALE_NOM_POPULATION - nomPopulation->size()) % 2;

        fluxEcriture << "\n";
        for (int i = 0; i < nombreAsterisquesAvant; i++)
            fluxEcriture << "*";

        fluxEcriture << " Population : " + *nomPopulation + " ";

        for (int i = 0; i < nombreAsterisquesApres; i++)
            fluxEcriture << "*";

        fluxEcriture << "\n";
        for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
            fluxEcriture << "*";

        fluxEcriture << "\n******* NE PAS TOUCHER, SAUF INDICATION *******\n******** CONTRAIRE DE L'ADMINISTRATEUR ********\n***************** DE DE POPULO ****************\n***********************************************\n***********************************************\n";
        fluxEcriture << "\n*Créée le " + QDate::currentDate().toString("dd/MM/yyyy") + " à " + QTime::currentTime().toString("HH:mm");

        fichierOpinions = new QFile();
        fichierOpinions->setFileName(*emplacementFichiers + "/" + *nomPopulation + ".populopack");
        fluxEcriture << "\n*Paquet d'opinions : " + fichierOpinions->fileName();



        fichierPopulation->close();

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

Population::~Population()
{
    delete Etat;
    delete nomPopulation;
    delete emplacementFichiers;
}
