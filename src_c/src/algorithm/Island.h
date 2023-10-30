/* 
 * File:   Header file for class Island
 * Author: A. Herrán
 */

#ifndef ISLAND_H
#define ISLAND_H

#include "metaheuristics/GRASP.h"
#include "metaheuristics/ILS.h"
#include "metaheuristics/VND.h"
#include "metaheuristics/BVNS.h"
#include "metaheuristics/GVNS.h"
#include "metaheuristics/SA.h"

class Island {
    
    public:
        
     // Constructor/destructor   
        Island();
        //Island(const Island &orig);
        virtual ~Island();
        
     // Public functions
        void     Construct();
        bool     Iterate();
        void     Add(Solution &solution);
        Solution GetBest();
    
    private:
       
     // Private attributes
        Metaheuristic **metaheuristics;
        //vector<Metaheuristic*> metaheuristics;
        
};

#endif /* ISLAND_H */
