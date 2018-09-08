/* chercherInfoFichier.h :
 *  Fichier d'en-tête de fonctions destinées à faciliter la recherche d'une information dans un fichier ;
 *  Créé le 17/08/2018.
 */

#ifndef CHERCHERINFOFICHIER_H
#define CHERCHERINFOFICHIER_H

#include <QString>
#include <QWidget>

QString chercherInfoStandard(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrefixe);
QString chercherNomPopulation(QWidget *fenetreParente, const QString &cheminAbsolu);
QString chercherInfoSubordonnee(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrincipale, const QString &mentionSubordonnee);
QVector<QString> chercherInfoListe(QWidget *fenetreParente, const QString &cheminAbsolu, const QString &mentionPrefixe);
QVector<QString> lireFichier(QWidget *fenetreParente, const QString &cheminAbsolu);

#endif // CHERCHERINFOFICHIER_H
