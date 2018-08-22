/* ecrireFichier.cpp :
 *  Fichier source de fonctions destinées à faciliter l'écriture d'une information dans un fichier ;
 *  Créé le 21/08/2018.
 */

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>

#include "ecrirefichier.h"

bool ecrireMentionPrincipale(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrecedente, const QString &mentionAjoutee)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadWrite | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lecture(&fichier);

        QString lignes = "";
        QString ligneCherchee(mentionPrecedente);
        lecture.seek(0);

        do
        {
            lignes = lecture.readLine();

            if (!lignes.startsWith(ligneCherchee) && lecture.atEnd())
                throw QString("Erreur 7 : impossible de trouver la mention \"" + mentionPrecedente + "\" dans le fichier \"" + cheminAbsolu + "\"");

        }while (!lignes.startsWith(ligneCherchee));

        int position = lecture.pos() - 1;
        QString aMettreApres = lecture.readAll(); //Pour ne pas perdre ce qui est écrit après, on lit le reste

        QTextStream ecriture(&fichier);
        ecriture.seek(position);
        ecriture << "\n\n" << mentionAjoutee << "\n" << aMettreApres; //On rajoute ce qui devrait être après

        fichier.close();

        return true;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);

        return false;
    }
}

bool ecrireMentionSubordonnee(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrecedente, const QString &mentionAjoutee)
{
    try
    {
        QFile fichier;
        fichier.setFileName(cheminAbsolu);
        if (!fichier.exists())
            throw QString("Erreur 8 : le fichier \"" + fichier.fileName() + "\" n'existe pas.");
        if (!fichier.open(QIODevice::ReadWrite | QIODevice::Text))
            throw QString("Erreur 9 : le fichier \"" + fichier.fileName() + "\" n'a pas pu être ouvert.");

        QTextStream lecture(&fichier);

        QString lignes = "";
        QString ligneCherchee(mentionPrecedente);
        lecture.seek(0);

        do
        {
            lignes = lecture.readLine();

            if (!lignes.startsWith(ligneCherchee) && lecture.atEnd())
                throw QString("Erreur 7 : impossible de trouver la mention \"" + mentionPrecedente + "\" dans le fichier \"" + cheminAbsolu + "\"");

        }while (!lignes.startsWith(ligneCherchee));

        do
        {
            lignes = lecture.readLine();

        }while (lignes.startsWith("*"));

        int position = lecture.pos() - 1;
        QString aMettreApres = lecture.readAll(); //Pour ne pas perdre ce qui est écrit après, on lit le reste

        QTextStream ecriture(&fichier);
        ecriture.seek(position);
        ecriture << mentionAjoutee << "\n\n" << aMettreApres; //On rajoute ce qui devrait être après

        fichier.close();

        return true;
    }
    catch (const QString &erreur)
    {
        QMessageBox::critical(fenetreParente, "Erreur", erreur);

        return false;
    }
}
