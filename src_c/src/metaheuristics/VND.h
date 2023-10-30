/* 
 * File:   Header file for class VND
 * Author: A. Herrán
 */

#ifndef VND_H
#define VND_H

#include "algorithm/Metaheuristic.h"

class VND: public Metaheuristic {
    
    public:
        
     // Constructor/destructor 
        VND();
        ~VND() override;
        
    private:
        
     // Private atributes
        vector<string> Sn;
                
     // Private functions
        bool Iterate() override;
        
};

#endif /* VND_H */

