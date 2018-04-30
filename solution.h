/* solution.h :
 *  Fichier d'en-tête de la classe Solution, permettant la création d'une solution à un débat ;
 *  Créé le 23/04/2018.
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "QString"

class Solution
{
    public :

    Solution();
    Solution(const QString &p_nomSolution);
    QString getNomSolution();

    protected :

    QString *nomSolution;
};

bool operator==(Solution solution1, Solution solution2);
bool operator!=(Solution solution1, Solution solution2);

#endif // SOLUTION_H
