/* 
 * File:   Source file for class SA
 * Author: A. Herrán
 */

#include "SA.h"

//------------------------
// Constructor/destructor
//------------------------
SA::SA(): Metaheuristic() {
   
    Nk = data.nN*data.nN/100;
    Tn = Solution::getT0SA()/1.0;
    
}

SA::~SA() = default;

//---------------------------------------------
// Performs one iteration of the metaheuristic
//---------------------------------------------
bool SA::Iterate() {
    
    bool finish = false;
    
 // Execute a cycle composed by Nk iterations at temperature Tn
    solutiona.Cycle(Nk, Tn);
    
 // Update incumbent solution
    if(solutiona < solutione) solutione = solutiona;
 
 // Update the cooling schedule
    Nk = static_cast<int>(1.0*Nk);
    Tn = data.AL*Tn;
    
    return finish;
}
