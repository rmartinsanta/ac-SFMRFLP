/* 
 * File:   Source file for class Island
 * Author: A. Herrán
 */

#include "Island.h"

//------------------------
// Constructor/destructor
//------------------------
Island::Island() {

    metaheuristics = new Metaheuristic *[data.NM];
    for(int m=0; m<data.NM; m++) {
        if      (data.MS=="grasp") metaheuristics[m] = new GRASP();
        else if (data.MS=="ils"  ) metaheuristics[m] = new ILS();
        else if (data.MS=="vnd"  ) metaheuristics[m] = new VND();
        else if (data.MS=="bvns" ) metaheuristics[m] = new BVNS();
        else if (data.MS=="gvns" ) metaheuristics[m] = new GVNS();
        else if (data.MS=="sa"   ) metaheuristics[m] = new SA();
        else {
            cout << "\n Wrong metaheuristic selected.";
            cin.get();
        }
    }
    
}

//Island::Island(const Island &orig) { }

Island::~Island() { 
    
    for(int m=0; m<data.NM; m++) delete metaheuristics[m];
    delete[] metaheuristics;
}

//---------------------------------------------------------
// Performs one iteration of each one of the metaheuristic
//---------------------------------------------------------
bool Island::Iterate() {

    bool finish = false;
    
    //#pragma omp parallel for if(parallel_enabled)
    for(int m=0; m<data.NM; m++) if(metaheuristics[m]->Iterate()) finish = true;
 
    return finish;
}

void Island::Construct() {

    //#pragma omp parallel for if(parallel_enabled)
    for(int m=0; m<data.NM; m++) metaheuristics[m]->Construct();
 
}

//----------------------------------------------------------------------------
// Adds the incoming front to the worst front among all the NM metaheuristics
//----------------------------------------------------------------------------
void Island::Add(Solution &solution) {
       
 // Get the worst solutions among the NM metaheuristics
    int iworst = 0;
    for(int m=1; m<data.NM; m++)
        if(metaheuristics[m]->solutione > metaheuristics[iworst]->solutione) iworst = m;

 // Replace the worst front with the incoming one
    metaheuristics[iworst]->solutione = solution;
    metaheuristics[iworst]->k = 1;
    
}

//----------------------------------------------------
// Gets the best solution among the NM metaheuristics
//----------------------------------------------------
Solution Island::GetBest() {
    
    int ibest = 0;
    
    for(int m=1; m<data.NM; m++)
        if(metaheuristics[m]->solutione < metaheuristics[ibest]->solutione) ibest = m;
    
    return metaheuristics[ibest]->solutione;
    
}
