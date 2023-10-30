/* 
 * File:   Header file for class GRASP
 * Author: A. Herrán
 */

#ifndef GRASP_H
#define GRASP_H

#include "algorithm/Metaheuristic.h"

class GRASP: public Metaheuristic {
    
    public:
        
     // Constructor/destructor    
        GRASP();
        ~GRASP() override;
        
    private:
        
     // Private atributes
        //vecDbl vP;
        
     // Private functions
        bool Iterate() override;
        
};

#endif /* GRASP_H */
