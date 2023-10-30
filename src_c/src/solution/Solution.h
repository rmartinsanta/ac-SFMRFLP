/* 
 * File:   Header file for class Solution
 * Author: A. Herrán
 */

#ifndef SOLUTION_H
#define	SOLUTION_H

#include "includes.h"

class Solution {
        
    public:
                
     // Public atributes
        matInt  rho;    // Facility assignment
        int     obj;    // Objective function value
        vecInt  x;      // Facility centers
        
     // Constructor/destructor
        Solution();
        //Solution(const Solution &orig);
        virtual ~Solution();
        
     // Operators redefinition
        bool operator<(const Solution &solution) const { return obj<solution.obj; }
        bool operator>(const Solution &solution) const { return obj>solution.obj; }
        
     // Public functions
        void    Construct   (); 
        void    Evaluate    ();       
        bool    Explore     (const string& ME);
        void    Shake       (int ks);
        //void    Perturbation(int &ps, int &js, int &pl, int &jl);
        void    Cycle       (int Nk, double Tn);
        static double  getT0SA();
        
    private: 

     // Random numbers
        template <class T>
        void rndShuffle(T &vec) {
            Tengine &engine = vengine[omp_get_thread_num()];
            shuffle(vec.begin(),vec.end(),engine);
        }

        int rndInt(int from, int upto) {
            Tengine &engine = vengine[omp_get_thread_num()];
            uniform_int_distribution<int> rndDist(from,upto);
            return rndDist(engine);
        }

        double rndDbl(double from, double upto) {
            Tengine &engine = vengine[omp_get_thread_num()];
            uniform_real_distribution<double> rndDist(from,upto);
            return rndDist(engine);
        }
        
     // Construction methods
        void    ConstructRandom(int c);
        void    ConstructBalanced();
        void    ConstructGreedyA(int greedy, double alpha);
        int     getGreedyA1(vecInt &FL, int i, double alpha);
        int     getGreedyA2(vecInt &FL, int i, double alpha);
        void    ConstructGreedyB(int greedy, double alpha);
        pairGre getGreedyB1(vecInt &CL, double alpha);
        pairGre getGreedyB2(const vecInt &CL, double alpha);
        void    ConstructGreedyC(int greedy, double alpha);
        pairPos getGreedyC1(vecGre &CL, int u, double alpha);
        pairPos getGreedyC2(vecGre &CL, int u, double alpha);
        int     EvaluateGreedy(int f, int i);
        
     // Evaluation of a move
        int     EvaluateMove();
        void    CalculateCenters();
       
     // Exchange moves
        void    Exchange            (int i, int j, int k, int l);
        int     EvaluateExchangeSame(int i, int j, int l);
        int     EvaluateExchangeDiff(int i, int j, int k, int l);
        int     DeltaExchange       (int f, int g, int xfp, int xgp);
        bool    ExploreExchange     (int strategy);
        bool    ExploreExchangeInc  (int strategy);
        bool    ExploreExchangeHorizontalBest();
        bool    ExploreExchangeHorizontalBestInc();
        bool    ExploreExchangeVerticalBest();
        bool    ExploreExchangeVerticalBestInc();
        //bool    ExploreExchangeVerticalRedu();
        
     // Insert moves        
        void    Insert          (int i, int j, int k, int l);
        int     EvaluateSwap    (int i, int j);
        int     EvaluateDrop    (int f);
        int     EvaluateAdd     (int f, int k);
        bool    ExploreInsert   (int strategy);
        bool    ExploreInsertInc(int strategy);
        bool    ExploreInsertHorizontalBest();
        bool    ExploreInsertHorizontalBestInc();
        bool    ExploreInsertVerticalBest();
        bool    ExploreInsertVerticalBestInc();
        
     // Extended neighborhoods
        bool    ExploreExtendedBest();

        bool    ExploreExtendedBestBestInc();
        bool    ExploreExtendedBestHybridInc();
        bool    ExploreExtendedBestFirstInc();

        bool    ExploreExtendedHybridBestInc();
        bool    ExploreExtendedHybridHybridInc();
        bool    ExploreExtendedHybridFirstInc();

        bool    ExploreExtendedFirstBestInc();
        bool    ExploreExtendedFirstHybridInc();
        bool    ExploreExtendedFirstFirstInc();

     // Shake procedures for VNS
        void    Shake1(int ks, int move);
        void    Shake2(int ks, int move);
        void    Shake3(int ks, int move);
        void    Shake4(int ks, int move);
        void    Shake5(int ks, int move);
        
     // Perturbation procedures for ILS
//        void    Perturbation1(int &ps, int &js, int &pl, int &jl);
//        void    Perturbation2(int &ps, int &js, int &pl, int &jl);
        
};

#endif	/* SOLUTION_H */
