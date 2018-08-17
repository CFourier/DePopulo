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

#endif // CHERCHERINFOFICHIER_H
