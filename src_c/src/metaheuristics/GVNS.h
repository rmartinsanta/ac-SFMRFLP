/* 
 * File:   Header file for class GVNS
 * Author: A. Herrán
 */

#ifndef GVNS_H
#define GVNS_H

#include "algorithm/Metaheuristic.h"

class GVNS: public Metaheuristic {
    
    public:
       
     // Constructor/destructor 
        GVNS();
        ~GVNS() override;
        
    private:
        
     // Private atributes      
        int kmin;
        int kmax;
        vector<string> Sn;
            
     // Private functions
        bool Iterate() override;
        
};

#endif /* GVNS_H */

