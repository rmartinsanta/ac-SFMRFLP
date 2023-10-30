/* 
 * File:   Source file for class ILS
 * Author: A. Herrán
 */

#include "ILS.h"

//------------------------
// Constructor/destructor
//------------------------
ILS::ILS(): Metaheuristic() {
    
 // Set the initial value of k      
    ps = 0;
    pl = 0;
    js = 0;
    jl = 0;
    
}

ILS::~ILS() = default;

//---------------------------------------------
// Performs one iteration of the metaheuristic
//---------------------------------------------
bool ILS::Iterate() {
 
    bool finish = false;
    
//    if(js==0) {
//        jl = 0;
//        int f1 = solutione.sol[0][js];
//        int f2 = solutione.sol[1][jl];
//        if     (L[f1]<L[f2]) ps = 0;
//        else if(L[f2]<L[f1]) ps = 1;
//        else                 ps = rand()%1;
//        if(ps==0) pl = 1;
//        else      pl = 0;
//    }
//    
// // Shake to a non-tabu neighbor
//    //do {
//        solutiona = solutione;
//        solutiona.Perturbation(data.V0, ps,pl,js,jl);    
//    //} while(tabulist.Check(solutiona.sol));
//    
// // Local Search
//    while(solutiona.Explore(data.ME,1)) continue;
//    
// // Neighborhood change
//    if(solutiona < solutione) {
//        solutione = solutiona;
//        //tabulist.Add(solutione.sol);
//        js = 0;
//    }
//    else js++;
//    
// // Saturation to kmax
//    if(js==solutiona.sol[ps].size()-1)js = 0;

    return finish;
}
