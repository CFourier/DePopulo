/* ecrireFichier.h :
 *  Fichier d'en-tête de fonctions destinées à faciliter l'écriture d'une information dans un fichier ;
 *  Créé le 21/08/2018.
 */

#ifndef ECRIREFICHIER_H
#define ECRIREFICHIER_H

#include <QString>
#include <QWidget>

bool ecrireMentionPrincipale(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrecedente, const QString &mentionAjoutee);
bool ecrireMentionSubordonnee(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrecedente, const QString &mentionAjoutee);

#endif // ECRIREFICHIER_H
