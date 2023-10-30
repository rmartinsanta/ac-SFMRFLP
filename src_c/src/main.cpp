/* 
 * File:   Algorithm.cpp
 * Author: A. Herrán
 */

#include <iostream>
#include "algorithm/Algorithm.h"

// Global data and random engines
bool            parallel_enabled = true;
Data            data;
vector<Tengine> vengine;

void LoadProperties(const string& pathProperties);
void LoadInstance  (const string& pathInstance);
   
int main(int argc, const char *argv[]) {  

 // Console inputs
    LoadInstance(argv[1]);
    data.nM = stoi(argv[2]);
    int ne  = stoi(argv[3]);
    data.TC = stod(argv[4]);
    data.S  = stoi(argv[5]);
    if(data.S==0) data.S = numeric_limits<int>::max();
    if(argc==7) LoadProperties(argv[6]);
            
 // Seed for random number generation
    random_device rd;
    for(int p=0; p<omp_get_max_threads(); p++) {
        vengine.emplace_back(rd());
        if(ne!=0) vengine[p].seed((p+1)*ne);
        else      vengine[p].seed(random_device{}());
    }
    
 // Stopping condition
    int    i     = 0;
    //int    imax  = static_cast<int>(data.TC)/(data.NI*data.NM);
    int    imax  = static_cast<int>(data.TC);
    auto   start = clk::now();
    double tcpu  = 0.0;
    
 // Algorithm
    Algorithm algorithm(argv[1],ne); 
    //algorithm.Construct();
    while(i<imax) {
    //while(tcpu<data.TC) {

     // Algorithm iteration
        //Tengine &engine = vengine[omp_get_thread_num()];
        //engine.seed(1234*i);
//        algorithm.Construct();
//        auto start = clk::now();
//        bool iteration = algorithm.Iterate();
//        tcpu += (double)(duration_cast<microseconds>(clk::now()-start)).count()/1e6;

     // Algorithm iteration
        bool iteration = algorithm.Iterate();
        tcpu = (double)(duration_cast<microseconds>(clk::now()-start)).count()/1e6;
        
     // Logs and communication at every R iterations
        if(iteration) {
            i++;
            algorithm.EvolutionConsole(false,i);
            algorithm.EvolutionArchive(false,i,tcpu);
            if(i%data.R==0) algorithm.Migrate();
            //if(imax<data.R) algorithm.Migrate();
            //else {
            //    if(i%(imax/data.R)==0) algorithm.Migrate();
            //}
            //if((i%(imax/(data.NI*data.NM)))==0) algorithm.Migrate();
            //if((i%(imax/data.R))==0) algorithm.Construct();
        }
        
        //if(tcpu>600.0) break;
    }
    algorithm.EvolutionConsole(true,i);
    algorithm.EvolutionArchive(true,i,tcpu);
    
 // Saves results to a file
    algorithm.SaveCost();
    algorithm.SaveSolution();
    
 // End message
    cout << "\n Optimization completed in " << tcpu << " seconds.\n\n";

//    algorithm.GetBest().Evaluate();
//    cout << algorithm.GetBest().obj;

    return 0;
}

void LoadProperties(const string& pathProperties) {
   
    ifstream file;
    string   line;
    
    file.open(pathProperties);
    if(!file) {
        cout << "\n The properties file can not be opened.";
        exit(1);
    }
       
    while(getline(file,line)) { 
        if(line[0]=='#' || line.size()==1) continue;
        vector<string> tokens = Algorithm::split(line," ");
        if     (tokens[0]=="NI") data.NI = stoi(tokens[2]);
        else if(tokens[0]=="NM") data.NM = stoi(tokens[2]);
        else if(tokens[0]=="MM") data.MM =      tokens[2];
        else if(tokens[0]=="R" ) data.R  = stoi(tokens[2]);
        else if(tokens[0]=="T" ) data.TC = stod(tokens[2]);
        else if(tokens[0]=="MC") data.MC =      tokens[2];
        else if(tokens[0]=="AG") data.AG = stod(tokens[2]);
        else if(tokens[0]=="ME") data.ME =      tokens[2];
        else if(tokens[0]=="MS") data.MS =      tokens[2];
        else if(tokens[0]=="V0") data.V0 = stoi(tokens[2]);
        else if(tokens[0]=="V1") data.V1 = stoi(tokens[2]);
        else if(tokens[0]=="V2") data.V2 = stoi(tokens[2]);
        else if(tokens[0]=="NT") data.NT = stoi(tokens[2]);
        else if(tokens[0]=="KW") data.KW = stoi(tokens[2]);
        else if(tokens[0]=="Q" ) data.Q  = stoi(tokens[2]);
        else if(tokens[0]=="B1") data.B1 = stod(tokens[2]);
        else if(tokens[0]=="B2") data.B2 = stod(tokens[2]);
        else if(tokens[0]=="NL") data.NL = stoi(tokens[2]);
        else if(tokens[0]=="AL") data.AL = stod(tokens[2]);
        else {
            cout << "\n Parameter " << tokens[0] << " does not exists.";
            exit(1);
        }  
    }
    
    file.close();
    
}

void LoadInstance(const string& pathInstance) {
    
 // Opens the instance file 
    ifstream file;
    file.open(pathInstance);
    if(!file) {
        cout << "\n The instance file can not be opened.";
        cin.get();
    }

 // Loads the Problem dimensions    
    file >> data.nN;

 // Includes fake facilities
    int F = 1;
    data.nN += F;

 // Loads the Length vector
    data.L = vecInt(data.nN,0);
    for(int j=0; j< data.nN - F; j++) {
        file >> data.L[j];
        data.L[j] = 4*data.L[j];
    }
    for(int j= data.nN - F; j < data.nN; j++) data.L[j] = 2;

 // Loads the Costs matrix
    data.W = matInt(data.nN,vecInt(data.nN,0));
    for(int u=0; u< data.nN - F; u++) {
        for(int v=0; v< data.nN - F; v++) {
            file >> data.W[u][v];
            if(v<u) data.W[u][v] = data.W[v][u];
        }
    }
    
 // Closes the instance file 
    file.close();   
    
}
