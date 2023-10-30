/* 
 * File:   Header file for class Algorithm
 * Author: A. Herrán
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Island.h"

class Algorithm {
    
    public:       
        
     // Constructor/destructor
        Algorithm(const string& pathInstance, int ne);
        //Algorithm(const Algorithm &orig);
        virtual ~Algorithm();
        
     // Public functions
        void     Construct();
        bool     Iterate();
        void     Migrate();
        Solution GetBest(int i);
        Solution GetBest();
        
        void EvolutionConsole(bool force, int it);
        void EvolutionArchive(bool force, int it, double tcpu);
        void SaveCost    ();
        void SaveSolution();
        
        static vector<string> split(string line, const string& separator);
                
    private:
        
     // Private attributes
        Island **islands;

        ofstream fileEvol;
        ofstream fileCost;
        ofstream fileSolu;
        
     // Private functions
        void Ring  ();
        void Fully (); 
        void Master(); 
        
};

#endif /* ALGORITHM_H */

