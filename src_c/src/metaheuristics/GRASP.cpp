/* 
 * File:   Source file for class GRASP
 * Author: A. Herrán
 */

#include "../metaheuristics/GRASP.h"

//------------------------
// Constructor/destructor
//------------------------
GRASP::GRASP(): Metaheuristic() { }

GRASP::~GRASP() = default;

//---------------------------------------------
// Performs one iteration of the metaheuristic
//---------------------------------------------
bool GRASP::Iterate() {
    
    bool finish = true;
    
//    Tengine &engine = vengine[omp_get_thread_num()];
//    engine.seed(1234*k);
    
 // Constructive procedure
    Solution solution;
    solution.Construct();
    solutiona = solution;
    for(int i=0; i<data.NC-1; i++) {
        solution.Construct();
        if(solution<solutiona) solutiona = solution;
    }

 // Local Search procedures
    while(solutiona.Explore(data.ME)) continue;

 // Update incumbent solution
    if(solutiona<solutione) solutione = solutiona;
    //solutione = solutiona;
    
    k++;
            
    return finish;
}
