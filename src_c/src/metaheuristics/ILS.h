/* 
 * File:   Header file for class ILS
 * Author: A. Herrán
 */

#ifndef ILS_H
#define ILS_H

#include "algorithm/Metaheuristic.h"

class ILS: public Metaheuristic {
    
    public:
        
     // Constructor/destructor 
        ILS();
        ~ILS() override;
    
    private:
        
     // Private atributes
        int ps, pl, js, jl;
        
     // Private functions
        bool Iterate() override;

};

#endif /* ILS_H */

