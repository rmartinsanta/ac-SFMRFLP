/* 
 * File:   includes.h
 * Author: A. Herrán
 */

#ifndef INCLUDES_H
#define INCLUDES_H

 // Libraries
    #include <iostream>     // cin()/cout()
    #include <fstream>      // file streams
    #include <iomanip>      // io manipulators
    #include <stdio.h>      // printf(), fprintf(), fopen()
    #include <math.h>       // exp(), pow(), sqrt()
    #include <vector>       // vector class
    #include <limits>       // std::numeric_limits<double>::infinity()
    #include <algorithm>    // sort(), random_shuffle()
    #include <omp.h>        // oparallel execution
    #include <random>       // engines for random number generation
    #include <chrono>       // timer

    //#include <bits/stdc++.h> // All

 // Type definitions
    using namespace std;
    using namespace std::chrono;
    
    //using Tengine = default_random_engine;
    //using Tengine = minstd_rand0;
    //using Tengine = minstd_rand;
    using Tengine = mt19937;
    //using Tengine = mt19937_64;
    //using Tengine = ranlux24_base;
    //using Tengine = ranlux48_base;
    //using Tengine = ranlux24;
    //using Tengine = ranlux48;
    //using Tengine = knuth_b;
    
    using clk     = std::chrono::high_resolution_clock;
    
    using vecInt  = vector<int>;
    using matInt  = vector<vecInt>;
    using vecDbl  = vector<double>;
    //using matDbl  = vector<vecDbl> ;
    
    using pairPos = pair<int,int>;
    using pairGre = pair<int,pairPos>;
    using vecGre  = vector<pairGre>;
            
    typedef struct {
     // Problem parameters
        int     nN;
        int     nM;
        vecInt  L;
        matInt  W;
     // Algorithm parameters
        int     NI = 4;             // Number of Islands
        int     NM = 1;             // 1 o 5?? Number of Algorithms in each Island
        string  MM = "master";      // Migration Strategy: none, ring, fully, master
        int     R  = 20;            // Best solutions migrates at every N·R iterations
        int     S  = 1;             // Logs are saved at every S iterations
        double  TC = 2000;          // Termination Criteria
     // Metaheuristic parameters
        int     NC = 1;             // Number of constructions
        string  MC = "greedyB2";    // Construction: random, equal, balanced, greedyA1, greedyA2, greedyB1, greedyB2
        double  AG = 0.50;          // Alpha coefficient controlling the greediness: 0-purely random, 1-purely greedy
        string  ME = "ext_fhi";     // Exploration: vinser, vinter, einser, einter, extended
        string  MS = "bvns";       // Search: grasp, ils, vnd, bvns, gvns, sa
        int     V0 = 1;             // UNUSED, only for ILS: Perturbation procedure for ILS
        int     V1 = 2;             // Shake procedure for VNS (Basic or General)
        int     V2 = 1;             // UNUSED, only for GVNS: Exploration sequence of LS's in VND
     // Tabu List specific parameters
        int     NT = 0;             // Maximum number of elements in the Tabu list
     // GRASP specific parameters
        int     KW = 20;            // Number of iterations of the warming phase
        int     Q  = 2;             // Maximum number of dev away from the best
     // VNS specific parameters
        double  B1 = 0.1;           // Beta coefficient for VNS (Basic or General)
        double  B2 = 0.1;           // Beta coefficient for VND
     // SA specific parameters
        int     NL = 100;           // Number of iterations in each cycle
        double  AL = 0.99;          // Cooling speed
    } Data;
    
 // Problem data (global variables)
    extern bool            parallel_enabled;
    extern vector<Tengine> vengine;
    extern Data            data;

#endif /* INCLUDES_H */
