#include <climits>
/*
 * File:   Source file for class Algorithm TabuList
 * Author: A. Herrán
 */

#include "TabuList.h"

//------------------------
// Constructor/destructor
//------------------------
TabuList::TabuList() {

    tabulist.clear();
    
}

__unused TabuList::TabuList(const TabuList& orig) { }
TabuList::~TabuList() = default;

//----------------------------------
// Adds a solution to the tabu list
//----------------------------------
void TabuList::Add(matInt &rho) {
  
    if(data.NT>0) {
        string strSol = ToString(rho);
        tabulist.push_back(strSol);
        if(tabulist.size()>data.NT) tabulist.pop_back();
    }
    
}

//------------------------------------------
// Checks if a solution is in the tabu list
//------------------------------------------
bool TabuList::Check(matInt &rho) {
    
    bool isTabu = false;
    
    if(data.NT>0) { 
        string strSol = ToString(rho);
        for(auto &s: tabulist) {
            if(strSol==s) {
                isTabu = true;
                break;
            }
        }
    }

    return isTabu;    
}

//----------------------------------------------
// Gets the string representation of a solution
//----------------------------------------------
string TabuList::ToString(matInt &rho) {
    
    string strSol;
    for(auto &rhoi: rho) {
        for(int u: rhoi) strSol += to_string(u) + "-";
        strSol += "*";
    }
    
    return strSol;
}
