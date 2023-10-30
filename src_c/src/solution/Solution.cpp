/* 
 * File:   Source file for class Solution
 * Author: A. Herrán
 */

#include "Solution.h"

//------------------------
// Constructor/destructor
//------------------------
Solution::Solution() {

    vecInt row;
    rho = matInt(data.nM,row);
    x   = vecInt(data.nN,0);
    obj = 0;

}

//Solution::Solution(const Solution &orig) {
//
//    rho = orig.rho;
//    obj = orig.obj;
//    x   = orig.x;
//
//}

Solution::~Solution() = default;


//******************************************************************************
// Construct Operators: Random, GreedyRandom, RandomGreedy
//******************************************************************************
void Solution::Construct() {
   
 // Clear the solution
    vecInt row;
    rho.clear();
    rho = matInt(data.nM,row);
    x   = vecInt(data.nN,0);
    obj = 0;
    
 // Constructs a new solution
    if     (data.MC=="random"  ) ConstructRandom(1);
    else if(data.MC=="equal"   ) ConstructRandom(data.nN/data.nM);
    else if(data.MC=="balanced") ConstructBalanced();
    else if(data.MC=="greedyA1") ConstructGreedyA(1,data.AG);
    else if(data.MC=="greedyA2") ConstructGreedyA(2,data.AG);
    else if(data.MC=="greedyB1") ConstructGreedyB(1,data.AG);
    else if(data.MC=="greedyB2") ConstructGreedyB(2,data.AG);
    else if(data.MC=="greedyC1") ConstructGreedyC(1,data.AG);
    else if(data.MC=="greedyC2") ConstructGreedyC(2,data.AG);
    else {
        cout << "\n Wrong construction method (x).";
        cin.get();
    }
    
 // Evaluates de solution
    Evaluate();
    
}

//******************************************************************************
// Eval Operators: Full solution and full generic move
//******************************************************************************

void Solution::Evaluate() {
        
 // Calculate the centers of all the facilities
    CalculateCenters();
    
 // Evaluates de solution
    obj = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            int u = rho[i][j];
            for(int l=j+1; l<rho[i].size(); l++) {
                int v = rho[i][l];
                obj += data.W[u][v]*(x[v] - x[u]);
            }
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    int v = rho[k][l];
                    obj += data.W[u][v]*abs(x[v] - x[u]);
                }
            }
        }
    }
    
}

int Solution::EvaluateMove() {
   
    int h = 0;
    
 // Calculate the centers of all the facilities
    CalculateCenters();
       
 // Evaluates de solution
    int objaux = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            int u = rho[i][j];
            for(int l=j+1; l<rho[i].size(); l++) {
                int v = rho[i][l];
                objaux += data.W[u][v]*(x[v] - x[u]);
            }
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    int v = rho[k][l];
                    objaux += data.W[u][v]*abs(x[v] - x[u]);
                }
            }
        }
    }
    
 // Calculates cost difference
    h = objaux - obj;
            
    return h;
}

void Solution::CalculateCenters() {

    for(int i=0; i<data.nM; i++) {
        int xaux = 0;
        for(int u: rho[i]) {
            xaux += data.L[u]/2;
            x[u] = xaux;
            xaux += data.L[u]/2;
        }
    }

}

//******************************************************************************
// Neighborhood exploration strategies
//******************************************************************************

bool Solution::Explore(const string& ME) {

    bool improved;

    if     (ME=="exc_b"  ) improved = ExploreExchange(0);
    else if(ME=="exc_h"  ) improved = ExploreExchange(1);
    else if(ME=="exc_f"  ) improved = ExploreExchange(2);
    else if(ME=="exc_bi" ) improved = ExploreExchangeInc(0);
    else if(ME=="exc_hi" ) improved = ExploreExchangeInc(1);
    else if(ME=="exc_fi" ) improved = ExploreExchangeInc(2);
    
    else if(ME=="exc_Hb" ) improved = ExploreExchangeHorizontalBest();
    else if(ME=="exc_Hbi") improved = ExploreExchangeHorizontalBestInc();
    else if(ME=="exc_Vb" ) improved = ExploreExchangeVerticalBest();
    else if(ME=="exc_Vbi") improved = ExploreExchangeVerticalBestInc();

    else if(ME=="ins_b"  ) improved = ExploreInsert(0);
    else if(ME=="ins_h"  ) improved = ExploreInsert(1);
    else if(ME=="ins_f"  ) improved = ExploreInsert(2);
    else if(ME=="ins_bi" ) improved = ExploreInsertInc(0);
    else if(ME=="ins_hi" ) improved = ExploreInsertInc(1);

    else if(ME=="ins_Hb" ) improved = ExploreInsertHorizontalBest();
    else if(ME=="ins_Hbi") improved = ExploreInsertHorizontalBestInc();
    else if(ME=="ins_Vb" ) improved = ExploreInsertVerticalBest();
    else if(ME=="ins_Vbi") improved = ExploreInsertVerticalBestInc();

    else if(ME=="ext_b"  ) improved = ExploreExtendedBest();

    else if(ME=="ext_bbi") improved = ExploreExtendedBestBestInc();
    else if(ME=="ext_bhi") improved = ExploreExtendedBestHybridInc();
    else if(ME=="ext_bfi") improved = ExploreExtendedBestFirstInc();

    else if(ME=="ext_hbi") improved = ExploreExtendedHybridBestInc();
    else if(ME=="ext_hhi") improved = ExploreExtendedHybridHybridInc();
    else if(ME=="ext_hfi") improved = ExploreExtendedHybridFirstInc();

    else if(ME=="ext_fbi") improved = ExploreExtendedFirstBestInc();
    else if(ME=="ext_fhi") improved = ExploreExtendedFirstHybridInc();
    else if(ME=="ext_ffi") improved = ExploreExtendedFirstFirstInc();

    else {
        cout << "\n Wrong neighborhood exploration method.";
        cin.get();
    }
    
    return improved;
}

//******************************************************************************
// Shake Operators for VNS (Basic or General): Shake 1, 2, 3, 4, 5, 6
//******************************************************************************

void Solution::Shake(int ks) {

    if     (data.V1== 1) Shake1(ks,1); //                  Exchange
    else if(data.V1== 2) Shake2(ks,1); // Horizontal       Exchange
    else if(data.V1== 3) Shake3(ks,1); // Vertical-j       Exchange
    else if(data.V1== 4) Shake4(ks,1); // Vertical-aligned Exchange
    else if(data.V1== 5) Shake5(ks,1); // Vertical-contact Exchange
    else if(data.V1== 6) Shake1(ks,2); //                  Insert
    else if(data.V1== 7) Shake2(ks,2); // Horizontal       Insert
    else if(data.V1== 8) Shake3(ks,2); // Vertical-j       Insert
    else if(data.V1== 9) Shake4(ks,2); // Vertical-aligned Insert
    else if(data.V1==10) Shake5(ks,2); // Vertical-contact Insert
    else {
        cout << "\n Wrong Shake method.";
        cin.get();
    }
    Evaluate();
    
}

//-------------------------
// Perturbation for ILS
//-------------------------
//void Solution::Perturbation(int &ps, int &js, int &pl, int &jl) {
//
//    if     (data.V0==1) Perturbation1(ps,js,pl,jl);
//    else if(data.V0==2) Perturbation2(ps,js,pl,jl);
//    else {
//        cout << "\n Wrong Perturbation method.";
//        cin.get();
//    }
//
//}
//
//void Solution::Perturbation1(int &ps, int &pl, int &js, int &jl) {
//
//    int fs = rho[ps][js];
//    int fl = rho[pl][jl];
//    if(x[fs]+data.L[fs]/2 > x[fl]+data.L[fl]/2) {
//        int temp = jl;
//        jl = js;
//        js = temp;
//        temp = pl;
//        pl = ps;
//        ps = temp;
//    }
//    Exchange(ps, js, pl, jl);
//    Evaluate();
//
//}
//
//void Solution::Perturbation2(int &ps, int &pl, int &js, int &jl) {
//
////    int fs = sol[ps][js];
////    int d  = Cx[fs] - Cx[sol[pl][jl]];
////    while(d<0) {
////        d =
////        jl++;
////        if(Cx[fl] >= Cx[fs]) {
////            if(j==0) break;
////        }
////    }
////    Swap(ps,js,pl,jl);
////    Evaluate();
//
//}

//******************************************************************************
// Functions for SA algorithm
//******************************************************************************
double Solution::getT0SA() {

    return 1.0;

}

//-----------------------
// Cycle of SA algorithm
//-----------------------
void Solution::Cycle(int Nk, double Tn) {

}
