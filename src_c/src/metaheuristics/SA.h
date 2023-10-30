/* 
 * File:   Header file for class SA
 * Author: A. Herrán
 */

#ifndef SA_H
#define SA_H

#include "algorithm/Metaheuristic.h"

class SA: public Metaheuristic {
    
    public:
        
     // Constructor/destructor 
        SA();
        ~SA() override;
        
    private:
        
     // Private atributes
        int    Nk;
        double Tn;
                
     // Private functions
        bool Iterate() override;
        
};

#endif /* SA_H */

