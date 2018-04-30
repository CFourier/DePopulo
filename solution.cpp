/* solution.cpp :
 *  Fichier source de la classe Solution, permettant la création d'une solution à un débat ;
 *  Créé le 23/04/2018.
 */

#include "solution.h"

bool operator==(Solution solution1, Solution solution2)
{
    return(solution1.getNomSolution() == solution2.getNomSolution());
}

bool operator!=(Solution solution1, Solution solution2)
{
    return(solution1.getNomSolution() != solution2.getNomSolution());
}

Solution::Solution()
{
    nomSolution = new QString("Solution par défaut");
}

Solution::Solution(const QString &p_nomSolution)
{
    nomSolution = new QString(p_nomSolution);
}

QString Solution::getNomSolution()
{
    return *nomSolution;
}
