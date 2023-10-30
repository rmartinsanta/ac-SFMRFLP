/* 
 * File:   Source file for class BVNS
 * Author: A. Herrán
 */

#include "BVNS.h"

//------------------------
// Constructor/destructor
//------------------------
BVNS::BVNS(): Metaheuristic() {
       
 // Set lower and upper bounds of k for Shake procedure
    kmin = 1;
    kmax = static_cast<int>(ceil(data.B1*data.nN));
    
}

BVNS::~BVNS() = default;

//---------------------------------------------
// Performs one iteration of the metaheuristic
//---------------------------------------------
bool BVNS::Iterate() {
    
    bool finish = false;
        
 // Shake to a non-tabu neighbor
    do {
        solutiona = solutione;
        solutiona.Shake(k);
    } while(tabulist.Check(solutiona.rho));
    
 // Local Search
    while(solutiona.Explore(data.ME)) continue;
    
 // Neighborhood change
    if(solutiona<solutione) {
        solutione = solutiona;
        tabulist.Add(solutiona.rho);
        k = kmin;
    }
    else k++;   
        
    if(k>kmax) {
        k = kmin;
        finish = true;
    }
        
    return finish;
}
