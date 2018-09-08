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

Population::Population(QWidget *fenetreParente, const QString &p_nomPopulation, const QString &p_emplacementFichiers, const QString &paquetOpinions, const QString &paquetProprietes, const int p_taillePopulation, const int p_taillePopulationSimulee)
{
    Etat = new Territoire("Etat");
    nomPopulation = new QString(p_nomPopulation);
    emplacementFichiers = new QString(p_emplacementFichiers);
    taillePopulationSimulee = new int;
    *taillePopulationSimulee = p_taillePopulationSimulee;
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

        //On crée tous les dossiers nécessaires

        QDir dossier;
        dossier.setPath(*emplacementFichiers);
        dossier.mkdir("Citoyens");
        dossier.mkdir("Territoires");
        dossier.mkdir("Opinions");
        dossier.mkdir("Propriétés");

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

        fluxEcriture << "\n****************** De populo ******************\n";
        for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
            fluxEcriture << "*";

        fluxEcriture << "\n******* NE PAS TOUCHER, SAUF INDICATION *******\n******** CONTRAIRE DE L'ADMINISTRATEUR ********\n***************** DE DE POPULO ****************\n***********************************************\n***********************************************\n";
        fluxEcriture << "\n*Créée le " + QDate::currentDate().toString("dd/MM/yyyy") + " à " + QTime::currentTime().toString("HH:mm");

        //On crée le paquet d'opinions

        if (paquetOpinions != "%%NULL%%")
        {
            QFile paqOpinions;
            paqOpinions.setFileName(paquetOpinions);
            if (!paqOpinions.open(QIODevice::WriteOnly | QIODevice::Text))
                throw QString("Impossible d'ouvrir le fichier " + paqOpinions.fileName());

            paqOpinions.copy(*emplacementFichiers + "/" + *nomPopulation + ".populopack");
        }

        else
        {
            QFile paqOpinions;
            paqOpinions.setFileName(*emplacementFichiers + "/" + *nomPopulation + ".populopack");
            if (!paqOpinions.open(QIODevice::WriteOnly | QIODevice::Text))
                throw QString("Impossible d'ouvrir le fichier " + paqOpinions.fileName());

            QTextStream fluxEcriturePPack;
            fluxEcriturePPack.setDevice(&paqOpinions);

            for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
                fluxEcriturePPack << "*";

            fluxEcriturePPack << "\n************** Paquet d'opinions **************";
            fluxEcriturePPack << "\n****************** De populo ******************\n";

            for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
                fluxEcriturePPack << "*";

            fluxEcriturePPack << "\n******* NE PAS TOUCHER, SAUF INDICATION *******\n******** CONTRAIRE DE L'ADMINISTRATEUR ********\n***************** DE DE POPULO ****************\n***********************************************\n***********************************************\n";

            paqOpinions.close();
        }

        fichierOpinions = new QFile();
        fichierOpinions->setFileName(*emplacementFichiers + "/" + *nomPopulation + ".populopack");

        fluxEcriture << "\n*Paquet d'opinions : " + fichierOpinions->fileName();

        //On crée le paquet de propriétés

        if (paquetProprietes != "%%NULL%%")
        {
            QFile paqProprietes;
            paqProprietes.setFileName(paquetOpinions);
            if (!paqProprietes.open(QIODevice::WriteOnly | QIODevice::Text))
                throw QString("Impossible d'ouvrir le fichier " + paqProprietes.fileName());

            paqProprietes.copy(*emplacementFichiers + "/" + *nomPopulation + ".populopropripack");
        }

        else
        {
            QFile paqProprietes;
            paqProprietes.setFileName(*emplacementFichiers + "/" + *nomPopulation + ".populopropripack");
            if (!paqProprietes.open(QIODevice::WriteOnly | QIODevice::Text))
                throw QString("Impossible d'ouvrir le fichier " + paqProprietes.fileName());

            QTextStream fluxEcriturePPack;
            fluxEcriturePPack.setDevice(&paqProprietes);

            for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
                fluxEcriturePPack << "*";

            fluxEcriturePPack << "\n************ Paquet de propriétés *************";
            fluxEcriturePPack << "\n****************** De populo ******************\n";

            for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
                fluxEcriturePPack << "*";

            fluxEcriturePPack << "\n******* NE PAS TOUCHER, SAUF INDICATION *******\n******** CONTRAIRE DE L'ADMINISTRATEUR ********\n***************** DE DE POPULO ****************\n***********************************************\n***********************************************\n";

            paqProprietes.close();
        }

        fichierProprietes = new QFile();
        fichierProprietes->setFileName(*emplacementFichiers + "/" + *nomPopulation + ".populopropripack");

        fluxEcriture << "\n*Paquet de propriétés : " + fichierProprietes->fileName();
        fluxEcriture << "\n\n*Citoyens : " << p_taillePopulation;
        fluxEcriture << QString("\n*Citoyens simulés : ") << p_taillePopulationSimulee;
        fluxEcriture << QString("\n\n*Territoires subordonnés : ");

        if (paquetOpinions != "%%NULL%%") //En plus de copier le paquet, on copie toutes les opinions
        {
            QFileInfo fichierOpinionsBase(paquetOpinions);
            QDir dossierOpinionsBase = fichierOpinionsBase.dir();
            QString emplacementOpinionsBase = dossierOpinionsBase.absolutePath();

            QVector<QString> opinions = lireFichier(fenetreParente, fichierOpinionsBase.fileName());

            for (int i = 0; i < opinions.size(); i++)
            {
                QFile fichierOpinionACopier;
                fichierOpinionACopier.setFileName(emplacementOpinionsBase + "/" + opinions[i].toLower() + ".populopinion");
                if (!fichierOpinionACopier.open(QIODevice::WriteOnly | QIODevice::Text))
                    throw QString("Impossible d'ouvrir le fichier " + fichierOpinionACopier.fileName());

                fichierOpinionACopier.copy(*emplacementFichiers + "/" + *nomPopulation + "/Opinions/" + opinions[i].toLower() + ".populopinion");
            }
        }

        if (paquetProprietes != "%%NULL%%") //En plus de copier le paquet, on copie toutes les propriétés
        {
            QFileInfo fichierProprietesBase(paquetProprietes);
            QDir dossierProprietesBase = fichierProprietesBase.dir();
            QString emplacementProprietesBase = dossierProprietesBase.absolutePath();

            QVector<QString> proprietes = lireFichier(fenetreParente, fichierProprietesBase.fileName());

            for (int i = 0; i < proprietes.size(); i++)
            {
                QFile fichierProprieteACopier;
                fichierProprieteACopier.setFileName(emplacementProprietesBase + "/" + proprietes[i].toLower() + ".populopropri");
                if (!fichierProprieteACopier.open(QIODevice::WriteOnly | QIODevice::Text))
                    throw QString("Impossible d'ouvrir le fichier " + fichierProprieteACopier.fileName());

                fichierProprieteACopier.copy(*emplacementFichiers + "/" + *nomPopulation + "/Propriétés/" + proprietes[i].toLower() + ".populopropri");
            }
        }


        for (int i = 0; i < *taillePopulationSimulee; i++)
        {
            QFile fichierCitoyen;
            fichierCitoyen.setFileName(*emplacementFichiers + "/Citoyens/citoyen" + QVariant(i).toString() + ".populocitoyen"); //QVariant(i).toString : on crée un objet qui contient un int ; on applique ensuite la méthode toString() sur l'objet et on obtient l'équivalent de l'entier en QString.
            if (!fichierCitoyen.open(QIODevice::WriteOnly | QIODevice::Text))
                throw QString("Impossible d'ouvrir le fichier " + fichierCitoyen.fileName());

            QTextStream fluxEcritureCitoyen;
            fluxEcritureCitoyen.setDevice(&fichierCitoyen);

            for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
                fluxEcritureCitoyen << "*";

            int nombreAsterisquesAvant = (TAILLE_MAXIMALE_NOM_POPULATION - nomPopulation->size()) / 2;
            int nombreAsterisquesApres = nombreAsterisquesAvant + (TAILLE_MAXIMALE_NOM_POPULATION - nomPopulation->size()) % 2;

            fluxEcritureCitoyen << "\n";
            for (int i = 0; i < nombreAsterisquesAvant; i++)
                fluxEcritureCitoyen << "*";

            fluxEcritureCitoyen << " Population : " + *nomPopulation + " ";

            for (int i = 0; i < nombreAsterisquesApres; i++)
                fluxEcritureCitoyen << "*";

            fluxEcritureCitoyen << "\n****************** De populo ******************\n";
            for (int i = 0; i < LARGEUR_EN_TETE_FICHIER; i++)
                fluxEcritureCitoyen << "*";

            fluxEcritureCitoyen << "\n******* NE PAS TOUCHER, SAUF INDICATION *******\n******** CONTRAIRE DE L'ADMINISTRATEUR ********\n***************** DE DE POPULO ****************\n***********************************************\n***********************************************\n";
        }

        fichierPopulation->close();

        /* On crée ces fichiers (remplacer "population" par le nom de la population) :
         * [FAIT] Un fichier "population.populo" recensant les caractéristiques de l'État : nom, population totale, territoires subordonnés, etc. ainsi que le fichier .populopack correspondant à la population ;
         * [FAIT] Un fichier "population.populopack", paquet d'opinions, c'est-à-dire référençant les opinions relatives à la population (législation sur telle ou telle chose ---> Autorisation/Interdiction/Tolérance à la consommation, etc., ou encore système politique ---> démocratique/monarchique/totalitaire, etc.) ;
         * [FAIT] Un fichier "opinion.populopinion" (remplacer "opinion" par le nom de l'opinion) par opinion, référençant les différentes solutions possibles qui s'y rapportent ;
         * Un fichier "territoire.subpopulo" (remplacer "territoire" par le nom du territoire), du même type que le fichier .populo, mais à plus petite échelle, pour chaque territoire subordonné ;
         * [FAIT] Un fichier "citoyenX.populocitoyen" (remplacer "X" par un numéro d'identification quelconque) pour chaque citoyen, renseignant sur l'ensemble de ses caractéristiques (âge, genre, solutions préconisées sur toutes les opinions, etc.) ;
         * [FAIT] Un fichier "population.populopropripack", recensant toutes les propriétés des individus
         * [FAIT] Un fichier "propriété.populopropri" (remplacer "propriété" par la propriété en question) pour chaque propriété des citoyens : âge, genre, activité, etc., contenant l'ensemble des solutions qu'il peut y avoir (1 an, 2 ans, 3 ans ... 150 ans ; femme, homme ; agriculteur, infirmier, demandeur d'emploi, retraité, étudiant, etc.).
         *
         * Remplacer les "throw bool"/"throw QString" par quelque chose d'un peu plus ... utile, rigoureux et facile à consulter
         * Ajouter une barre de progression lors de la création d'une population (QProgressBar/QProgressDialog)
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
