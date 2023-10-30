/* 
 * File:   Source file for class VND
 * Author: A. Herrán
 */

#include "VND.h"

//------------------------
// Constructor/destructor
//------------------------
VND::VND(): Metaheuristic() {
 
 // Sequence of neighborhoods for different VND versions
    int nmax = static_cast<int>(data.B2*data.nN);
    Sn.emplace_back("bvswap"  );
    Sn.emplace_back("bvinsert");
    Sn.emplace_back("beswap"  );
    Sn.emplace_back("beinsert");
    //    switch(data.V2) {
//        case 0:     // Sequence of neighborhoods: VND0 (1O, 2E, 2O)
//            Sn.push_back({"2ExcBest","1"});
//            Sn.push_back({"2OptBest","1"});
//            break;
//        case 1:     // Sequence of neighborhoods: VND1 (1O, 2E1, 2O1, ..., 2Ek, 2Ok)
//            for(int i=1; i<=nmax; i++) {
//                Sn.push_back({"2ExcBest",to_string(i)});
//                Sn.push_back({"2OptBest",to_string(i)});
//            }      
//            break;
//        case 2:     // Sequence of neighborhoods: VND2 (1O, 2E1..k, 2O1..k)
//            for(int i=1; i<=nmax; i++) Sn.push_back({"2ExcBest",to_string(i)});
//            for(int i=1; i<=nmax; i++) Sn.push_back({"2OptBest",to_string(i)});
//            break;
//        case 3:     // Sequence of neighborhoods: VND3 (1O, 2Ek, 2Ok, ..., 2E1, 2O1)
//            for(int i=nmax; i>0; i--) {
//                Sn.push_back({"2ExcBest",to_string(i)});
//                Sn.push_back({"2OptBest",to_string(i)});
//            }
//            break;
//        case 4:     // Sequence of neighborhoods: VND4 (1O, 2Ek..1, 2Ok..1)
//            for(int i=nmax; i>0; i--) Sn.push_back({"2ExcBest",to_string(i)});
//            for(int i=nmax; i>0; i--) Sn.push_back({"2OptBest",to_string(i)});
//            break;
//        default:
//            cout << "\n Wrong VND version.";
//            cin.get();
//    }
    
}

VND::~VND() = default;

//---------------------------------------------
// Performs one iteration of the metaheuristic
//---------------------------------------------
bool VND::Iterate() {
  
    bool finish = false;
        
 // Explores the k-th neighborhood
//    if(solutiona.Explore(Sn[k][0],stoi(Sn[k][1]))) {
//        solutione = solutiona;
//        tabulist.Add(solutione.sol);
//        k = 0;
//    }
//    else k++;
    
    bool improved = false;
    while(solutiona.Explore(Sn[k])) improved = true;
    if(improved) {
        solutione = solutiona;
        //tabulist.Add(solutione.sol);
        k = 0;
    }
    else k++;
    
 // Saturation to kmax
    if(k==Sn.size()) k = 0;//finish = true;
    
    return finish;
}
