/* chercherInfoFichier.cpp :
 *  Fichier source de fonctions destinées à faciliter la recherche d'une information dans un fichier ;
 *  Créé le 17/08/2018.
 */

#include "chercherinfofichier.h"

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>

QString chercherInfoStandard(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrefixe)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lecture(&fichier);

        QString lignes = "";
        QString ligneCherchee(mentionPrefixe);
        int i = 0;
        lecture.seek(0);

        do
        {
            lignes = lecture.readLine();
            i++;

            if (!lignes.startsWith(ligneCherchee) && lecture.atEnd())
                throw QString("Erreur 7 : impossible de trouver la mention \"" + mentionPrefixe + "\" dans le fichier \"" + cheminAbsolu + "\"");

        }while (!lignes.startsWith(ligneCherchee));

        lignes.remove(0, ligneCherchee.size());

        fichier.close();

        return lignes;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }

    return "@@@ERREUR@@@";
}

QString chercherNomPopulation(QWidget *fenetreParente, const QString &cheminAbsolu)
{
    //On recherche le nom de la population, en enlevant les astérisques

    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lectureFichier(&fichier);
        QString lignes = lectureFichier.readLine();
        lignes = lectureFichier.readLine();     //On part de la seconde ligne, car la première est normalement composée exclusivement d'astérisques

        bool asterisquesAbsents = false;
        int i = 0;
        while (asterisquesAbsents == false)
        {
            QChar asterisqueOuNon = lignes.at(i);

            if (asterisqueOuNon != "*")
                asterisquesAbsents = true;

            else
                i++;

            if (i == lignes.size())
                throw QString("Erreur 5 : le fichier \"" + fichier.fileName() + "\" est corrompu !");
        }

        lignes.remove(0, i+14); //i+14, car on enlève aussi la mention " Population : "

        asterisquesAbsents = false;
        i = lignes.size() - 1;
        while (asterisquesAbsents == false)
        {
            QChar asterisqueOuNon = lignes.at(i);

            if (asterisqueOuNon != "*")
                asterisquesAbsents = true;

            else
                i--;

            if (i == 0)
                throw QString("Erreur 6 : le fichier \"" + fichier.fileName() + "\" est corrompu !");
        }

        lignes.chop(lignes.size() - i);

        fichier.close();

        return lignes;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }

    return "@@@ERREUR@@@";
}

QString chercherInfoSubordonnee(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrincipale, const QString &mentionSubordonnee)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lecture(&fichier);

        QString lignes = "";
        QString ligneCherchee(mentionPrincipale);
        int i = 0;
        lecture.seek(0);

        do //On cherche la mention principale
        {
            lignes = lecture.readLine();
            i++;

            if (!lignes.startsWith(ligneCherchee) && lecture.atEnd())
                throw QString("Erreur 7 : impossible de trouver la mention \"" + mentionPrincipale + "\" dans le fichier \"" + cheminAbsolu + "\"");

        }while (!lignes.startsWith(ligneCherchee));

        lignes = "";
        ligneCherchee = mentionSubordonnee;
        i = 0;

        do //On cherche la mention subordonnée
        {
            lignes = lecture.readLine();
            i++;

            if (lignes.startsWith("\n"))
                throw QString("Erreur 10 : impossible de trouver la mention \"" + mentionSubordonnee + "\" subordonnée à la mention \"" + mentionPrincipale + "\" dans le fichier \"" + cheminAbsolu + "\"");

        }while(!lignes.startsWith(ligneCherchee) && lecture.atEnd());

        lignes.remove(0, ligneCherchee.size());

        fichier.close();

        return lignes;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }

    return "@@@ERREUR@@@";
}

QVector<QString> chercherInfoListe(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrefixe)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lecture(&fichier);

        QString lignes = "";
        QString ligneCherchee(mentionPrefixe);
        int i = 0;
        lecture.seek(0);

        do
        {
            lignes = lecture.readLine();
            i++;

            if (!lignes.startsWith(ligneCherchee) && lecture.atEnd())
                throw QString("Erreur 7 : impossible de trouver la mention \"" + mentionPrefixe + "\" dans le fichier \"" + cheminAbsolu + "\"");

        }while (!lignes.startsWith(ligneCherchee));

        QVector<QString> liste;

        while (!lignes.startsWith("\n") && !lecture.atEnd())
        {
            lignes = lecture.readLine();
            i++;

            liste.push_back(lignes);
        }

        fichier.close();

        for (i = 0; i < liste.size(); i++)
        {
            liste[i].remove("*");
        }

        return liste;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }

    QVector<QString> erreur;
    erreur.push_back("@@@ERREUR@@@");
    return erreur;
}

QVector<QString> lireFichier(QWidget *fenetreParente, const QString &cheminAbsolu)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lecture(&fichier);

        for (int i = 0; i < 10; i++) //On enlève l'en-tête
            lecture.readLine();

        QVector<QString> liste;
        QString lignes = "";

        while (!lecture.atEnd())
        {
            lignes = lecture.readLine();
            lignes.remove("*");
            liste.push_back(lignes);
        }

        return liste;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }

    QVector<QString> erreur;
    erreur.push_back("@@@ERREUR@@@");
    return erreur;
}
