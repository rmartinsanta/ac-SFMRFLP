/* 
 * File:   Header file for class BVNS
 * Author: A. Herrán
 */

#ifndef BVNS_H
#define BVNS_H

#include "algorithm/Metaheuristic.h"

class BVNS: public Metaheuristic {
    
    public:

     // Constructor/destructor 
        BVNS();
        ~BVNS() override;
    
    private:
        
     // Private atributes
        int kmin;
        int kmax;
        
     // Private functions
        bool Iterate() override;

};

#endif /* BVNS_H */

