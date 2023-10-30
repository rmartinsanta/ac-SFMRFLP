/* 
 * File:   Source file for class GVNS
 * Author: A. Herrán
 */

#include "GVNS.h"

//------------------------
// Constructor/destructor
//------------------------
GVNS::GVNS(): Metaheuristic() { 
    
 // Sequence of neighborhoods for different VND versions
    switch(data.V2) {   
        case 1: Sn.emplace_back("exc_fi"); Sn.emplace_back("ins_hi"); break;
        case 2: Sn.emplace_back("ins_hi"); Sn.emplace_back("exc_fi"); break;
        default:
            cout << "\n Wrong VND version.";
            cin.get();
    }
    
 // Set lower and upper bounds of k for Shake procedure
    kmin = 1;
    kmax = static_cast<int>(ceil(data.B1*data.nN));

}

GVNS::~GVNS() = default;

//---------------------------------------------
// Performs one iteration of the metaheuristic
//---------------------------------------------
bool GVNS::Iterate() {
    
    bool finish = false;

 // Shake to a non-tabu neighbor
    do {
        solutiona = solutione;
        //solutiona.Shake(k);
    } while(tabulist.Check(solutiona.rho));

 // VND
    int kp = 0;
    while(kp<Sn.size()) {
        if(solutiona.Explore(Sn[kp])) kp = 0;
        //while(solutiona.Explore(Sn[kp])) kp = 0;
        kp++;
    }

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
