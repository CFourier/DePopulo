/* chercherInfoFichier.cpp :
 *  Fichier source de fonctions destinées à faciliter la recherche d'une information dans un fichier ;
 *  Créé le 17/08/2018.
 */

#include "chercherinfofichier.h"

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

QString chercherInfoStandard(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrefixe)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
        {
            QMessageBox::critical(fenetreParente, "Erreur", "Erreur 8 : le fichier " + fichier.fileName() + " n'existe pas.");
            return "";
        }
        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw QString("Erreur 9 : le fichier " + fichier.fileName() + " n'a pas pu être ouvert.");
            return "";
        }

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
                throw QString("Erreur 7 : impossible de trouver la mention " + mentionPrefixe + " dans le fichier " + cheminAbsolu);

        }while (!lignes.startsWith(ligneCherchee));

        lignes.remove(0, ligneCherchee.size());

        fichier.close();

        return lignes;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }
}

QString chercherNomPopulation(QWidget *fenetreParente, const QString &cheminAbsolu)
{
    //On recherche le nom de la population, en enlevant les astérisques

    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier " + fichier.fileName() + " n'existe pas.");
        if (!fichier.open(QIODevice::ReadWrite | QIODevice::Text))
            throw QString("Erreur 9 : le fichier " + fichier.fileName() + " n'a pas pu être ouvert.");

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
                throw QString("Erreur 5 : le fichier " + fichier.fileName() + " est corrompu !");
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
                throw QString("Erreur 6 : le fichier " + fichier.fileName() + " est corrompu !");
        }

        lignes.chop(lignes.size() - i);

        fichier.close();

        return lignes;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);
    }
}
