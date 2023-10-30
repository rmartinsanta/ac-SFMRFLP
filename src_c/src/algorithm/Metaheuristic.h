/* 
 * File:   Header file for class Metaheuristic
 * Author: A. Herrán
 */

#ifndef METAHEURISTIC_H
#define METAHEURISTIC_H

#include "solution/Solution.h"
#include "solution/TabuList.h"

class Metaheuristic {
    
    public:

     // Public attributes
        int      k = 0;
        Solution solutione;
        
     // Constructor/destructor   
        Metaheuristic();
        virtual ~Metaheuristic();
        
     // Public functions
        void         Construct();
        virtual bool Iterate() = 0;

    protected:
        
     // Protected attributes
        Solution solutiona;
        TabuList tabulist;
        
};

#endif /* METAHEURISTIC_H */
