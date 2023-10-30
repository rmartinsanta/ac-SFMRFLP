/* 
 * File:   Source file for class Metaheuristic
 * Author: A. Herrán
 */

#include "Metaheuristic.h"

//------------------------
// Constructor/destructor
//------------------------
Metaheuristic::Metaheuristic()  { 

 // Constructs the initial solution
    Construct();
    
 // Selects the initial solution as the current best one
    solutione = solutiona;
    
 // Adds the initial solution to the Tabu list
    tabulist.Add(solutiona.rho);
    
    
}
Metaheuristic::~Metaheuristic() = default;

//----------------------------------------------------------------------------
// Constructs n solutions and initializes the metaheuristic with the best one
//----------------------------------------------------------------------------
void Metaheuristic::Construct() {
     
    Solution solution;
    solution.Construct();
    solutiona = solution;
    for(int i=0; i<data.NC-1; i++) {
        solution.Construct();
        if(solution<solutiona) solutiona = solution;
    }

}
