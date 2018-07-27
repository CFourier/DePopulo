/* identite.cpp :
 *  Fichier source de la classe Identite, permettant l'indexation de toutes les particularités de l'identité d'un citoyen (nom, âge, sexe, etc.) en un seul objet ;
 *  Créé le 30/04/2018
 */

#include "identite.h"

Identite::Identite()
{
    dateNaissance = new DateNaissance();
    estMasculin = new bool(qrand() % (1));
}
