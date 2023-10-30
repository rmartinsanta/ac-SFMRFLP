#include "Solution.h"

//******************************************************************************
// Constructives
//******************************************************************************

// Fills each row with a random facility from FL: totally random or equilibrated (equal)
//--------------------------------------------------------------------------------------
void Solution::ConstructRandom(int c) {

    // Generates a random ordering of facilities (FL)
    vecInt FL;
    for(int u=0; u<data.nN; u++) FL.push_back(u);
    rndShuffle(FL);

    // Generates the size of each row
    vecInt rhosize(data.nM,3);
    int Nleft = data.nN - c*data.nM;
    while(Nleft>0) {
        rhosize[rndInt(0,data.nM-1)]++;
        Nleft--;
    }

    // Adds the rest of facilities to fill the rows
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rhosize[i]; j++) {
            rho[i].push_back(FL.back());
            FL.pop_back();
        }
    }

//    rho[0][0] = 0;
//    rho[0][1] = 5;
//    rho[0][2] = 4;
//    rho[1][0] = 2;
//    rho[1][1] = 1;
//    rho[1][2] = 3;

//    rho[0][0] = 0;
//    rho[0][1] = 5;
//    rho[0][2] = 4;
//    rho[0][3] = 2;
//    rho[0][4] = 1;
//    rho[0][5] = 3;
//
//    Evaluate();
//    cout << obj/2.0;
//
//    cin.get();


}

// Adds a facility (randomly selected from FL) to the end of the shortest row
//---------------------------------------------------------------------------
void Solution::ConstructBalanced() {

    // Generates a random ordering of facilities (FL)
    vecInt FL(data.nN,0);
    for(int u=0; u<FL.size(); u++) FL[u] = u;
    rndShuffle(FL);

    // Adds the rest of facilities selecting the shortest row at each iteration
    vecInt Lx(data.nM,0);
    while(!FL.empty()) {
        int u = FL.back();
        FL.pop_back();
        int i = distance(Lx.begin(),min_element(Lx.begin(),Lx.end()));
        rho[i].push_back(u);
        Lx[i] += data.L[u];
    }

}

// Adds a facility (selected from FL according to the Greedy function) to the end of the shortest row
//---------------------------------------------------------------------------------------------------
void Solution::ConstructGreedyA(int greedy, double alpha) {

    // Generates a random ordering of facilities (FL)
    vecInt FL(data.nN,0);
    for(int u=0; u<FL.size(); u++) FL[u] = u;
    rndShuffle(FL);

    // Adds one facility to each row at random
    for(int i=0; i<data.nM; i++) {
        int u = FL.back();
        FL.pop_back();
        rho[i].push_back(u);
    }

    // Adds facilities according to the Greedy function value
    int c;
    vecInt Lx(data.nM,0);
    while(!FL.empty()) {
        rndShuffle(FL);
        int i = distance(Lx.begin(),min_element(Lx.begin(),Lx.end()));
        if(alpha==0.0) alpha = rndDbl(0.0,1.0);
        if(greedy==1) c = getGreedyA1(FL, i, alpha); //G-R
        else          c = getGreedyA2(FL, i, alpha); //R-G
        int u = FL[c];
        FL.erase(FL.begin()+c);
        if(!rho[i].empty()) x[u] = x[rho[i].back()] + (data.L[rho[i].back()] + data.L[u])/2;
        else                x[u] = data.L[u]/2;
        Lx[i] += data.L[u];
        rho[i].push_back(u);
    }

}

int Solution::getGreedyA1(vecInt &FL, int i, double alpha) {

    int candidate;

    int gmin = std::numeric_limits<int>::max();
    int gmax = std::numeric_limits<int>::min();

    vecInt g = vecInt(FL.size(),0);
    for(int c=0; c<FL.size(); c++) {
        g[c] = EvaluateGreedy(FL[c],i);
        if(g[c]<gmin) gmin = g[c];
        if(g[c]>gmax) gmax = g[c];
    }
    double th = gmin + alpha*(gmax-gmin);
    for(int c=0; c<FL.size(); c++) if (g[c] >= th) { candidate = c; break; }

    return candidate;
}

int Solution::getGreedyA2(vecInt &FL, int i, double alpha){

    int candidate;

    int s    = (int)floor(alpha*FL.size()); if(s==0) s = 1;
    int gmax = std::numeric_limits<int>::min();

    for(int c=0; c<s; c++) {
        int g = EvaluateGreedy(FL[c],i);
        if(g>gmax) {
            gmax      = g;
            candidate = c;
        }
    }

    return candidate;

//    int candidate;
//
//    int s    = (int)floor(alpha*FL.size()); if(s==0) s = 1;
//    int gmin = std::numeric_limits<int>::max();
//
//    for(int c=0; c<s; c++) {
//        int g = EvaluateGreedy(FL[c],i);
//        if(g<gmin) {
//            gmin      = g;
//            candidate = c;
//        }
//    }
//
//    return candidate;

}

// Adds a facility (selected from FL according to the Greedy function) to its best position in the layout
//-------------------------------------------------------------------------------------------------------
void Solution::ConstructGreedyB(int greedy, double alpha) {

    // Generates a random ordering of facilities (Candidate List of facilities, FL)
    vecInt FL(data.nN,0);
    for(int u=0; u<FL.size(); u++) FL[u] = u;
    rndShuffle(FL);

// // Adds a random facility to a random row
//    int u = FL.back();
//    FL.pop_back();
//    rho[rndInt(0,data.nM-1)].push_back(u);

    // Adds one facility to each row at random
    int u;
    for(int i=0; i<data.nM; i++) {
        u = FL.back();
        FL.pop_back();
        rho[i].push_back(u);
    }

    // Adds facilities according to the Greedy function value
    pairGre gre;
    while(!FL.empty()) {
        CalculateCenters();
        rndShuffle(FL);
        if(alpha==0.0) alpha = rndDbl(0.0,1.0);
        if(greedy==1) gre = getGreedyB1(FL, alpha); //G-R
        else          gre = getGreedyB2(FL, alpha); //R-G
        int c = gre.first;
        int i = gre.second.first;
        int j = gre.second.second;
        u = FL[c];
        FL.erase(FL.begin()+c);
        rho[i].insert(rho[i].begin()+j,u);
    }

}

pairGre Solution::getGreedyB1(vecInt &CL, double alpha) {

    int gmin = std::numeric_limits<int>::max();
    int gmax = std::numeric_limits<int>::min();

    vecGre  g;
    pairGre gre;
    for(int &c: CL) {
        gre.first = std::numeric_limits<int>::max();
        for(int i=0; i<data.nM; i++) {
            for(int j=0; j<rho[i].size()+1; j++) {
                rho[i].insert(rho[i].begin()+j, c);
                int h = EvaluateMove();
                rho[i].erase(rho[i].begin()+j);
                if(h<gre.first) {
                    gre.first         = h;
                    gre.second.first  = i;
                    gre.second.second = j;
                }
                else if(h==gre.first) {
                    if(i==gre.second.first && rndInt(0,1)) {
                        gre.first         = h;
                        gre.second.first  = i;
                        gre.second.second = j;
                    }
                    else {
                        int ui, uib, Li, Lib;
                        if(rho[i].empty()) Li = 0;
                        else {
                            ui = rho[i].back();
                            Li = x[ui] + data.L[ui] / 2;
                        }
                        if(rho[gre.second.first].empty()) Lib = 0;
                        else {
                            uib = rho[gre.second.first].back();
                            Lib = x[uib] + data.L[uib] / 2;
                        }
                        if (Li < Lib || (Li == Lib && rndInt(0, 1))) {
                            gre.first         = h;
                            gre.second.first  = i;
                            gre.second.second = j;
                        }
                    }
                }
            }
        }
        if(gre.first<gmin) gmin = gre.first;
        if(gre.first>gmax) gmax = gre.first;
        g.push_back(gre);
    }

    vecInt RCL;
    double th = gmax - alpha*(gmax-gmin);
    for(int c=0; c<CL.size(); c++) if(g[c].first<=th) RCL.push_back(c);
    int candidate = RCL[rndInt(0,static_cast<int>(RCL.size()-1))];
    gre.first  = candidate;
    gre.second = g[candidate].second;

//    int candidate;
//    int th = gmax - alpha*(gmax-gmin);
//    for(int c=0; c < CL.size(); c++) if(g[c].first<=th) { candidate = c; break; }
//    gre.first  = candidate;
//    gre.second = g[candidate].second;

    return gre;
}

pairGre Solution::getGreedyB2(const vecInt &CL, double alpha){

    int s    = (int)floor(alpha * CL.size()); if(s == 0) s = 1;
    int gmin = std::numeric_limits<int>::max();

    pairGre gre, gremin;
    for(int c=0; c<s; c++) {
        gre.first = std::numeric_limits<int>::max();
        for(int i=0; i<data.nM; i++) {
            for(int j=0; j<rho[i].size()+1; j++) {
                rho[i].insert(rho[i].begin()+j, CL[c]);
                int h = EvaluateMove();
                rho[i].erase(rho[i].begin()+j);
                if(h<gre.first) {
                    gre.first         = h;
                    gre.second.first  = i;
                    gre.second.second = j;
                }
                else if(h==gre.first) {
                    if(i==gre.second.first && rndInt(0,1)) {
                        gre.first         = h;
                        gre.second.first  = i;
                        gre.second.second = j;
                    }
                    else {
                        int ui, uib, Li, Lib;
                        if(rho[i].empty()) Li = 0;
                        else {
                            ui = rho[i].back();
                            Li = x[ui] + data.L[ui] / 2;
                        }
                        if(rho[gre.second.first].empty()) Lib = 0;
                        else {
                            uib = rho[gre.second.first].back();
                            Lib = x[uib] + data.L[uib] / 2;
                        }
                        if (Li < Lib || (Li == Lib && rndInt(0, 1))) {
                            gre.first         = h;
                            gre.second.first  = i;
                            gre.second.second = j;
                        }
                    }
                }
            }
        }
        if(gre.first<gmin || (gre.first==gmin && rndInt(0,1))) {
            gmin         = gre.first;
            gremin       = gre;
            gremin.first = c;
        }
    }

    return gremin;
}

// Adds a facility (randomly selected from FL) at a position of the layout selected according to the Greedy function
void Solution::ConstructGreedyC(int greedy, double alpha) {

    // Generates a random ordering of facilities
    vecInt FL(data.nN,0);
    for(int u=0; u<FL.size(); u++) FL[u] = u;
    rndShuffle(FL);

    // Adds one facility to each row at random
    for(int i=0; i<data.nM; i++) {
        int u = FL.back();
        FL.pop_back();
        rho[i].push_back(u);
    }

    // Generates the Candidate List of positions (PL)
    vecGre  PL;
    pairPos pos;
    pairGre gre;
    for(int i=0; i<data.nM; i++) {
        pos.first  = i;
        for(int j=0; j<rho[i].size()+1; j++) {
            pos.second = j;
            gre.first  = 0;
            gre.second = pos;
            PL.push_back(gre);
        }
    }

    // Adds facilities according to the Greedy function value
    while(!FL.empty()) {
        rndShuffle(PL);
        int u = FL.back();
        FL.pop_back();
        if(alpha==0.0) alpha = rndDbl(0.0,1.0);
        if(greedy==1) pos = getGreedyC1(PL, u, alpha); //G-R
        else          pos = getGreedyC2(PL, u, alpha); //R-G
        int i = pos.first;
        int j = pos.second;
        rho[i].insert(rho[i].begin()+j,u);
        pos.second = rho[i].size();
        gre.first  = 0;
        gre.second = pos;
        PL.push_back(gre);
    }

}

pairPos Solution::getGreedyC1(vecGre &CL, int u, double alpha) {

    int gmin = std::numeric_limits<int>::max();
    int gmax = std::numeric_limits<int>::min();

    for(auto &c : CL) {
        int i = c.second.first;
        int j = c.second.second;
        rho[i].insert(rho[i].begin()+j,u);
        c.first = EvaluateMove();
        rho[i].erase(rho[i].begin()+j);
        if(c.first<gmin) gmin = c.first;
        if(c.first>gmax) gmax = c.first;
    }

    vecInt RCL;
    double th = gmax - alpha*(gmax-gmin);
    for(int c=0; c < CL.size(); c++) if(CL[c].first<=th) RCL.push_back(c);
    int candidate = RCL[rndInt(0,static_cast<int>(RCL.size()-1))];

//    int candidate;
//    int th = gmax - alpha*(gmax-gmin);
//    for(int c=0; c<CL.size(); c++) if(CL[c].first<=th) { candidate = c; break; };

    return CL[candidate].second;
}

pairPos Solution::getGreedyC2(vecGre &CL, int u, double alpha){

    int s    = (int)floor(alpha * CL.size()); if(s == 0) s = 1;
    int gmin = std::numeric_limits<int>::max();

    int candidate;
    for(int c=0; c<s; c++) {
        int i = CL[c].second.first;
        int j = CL[c].second.second;
        rho[i].insert(rho[i].begin()+j,u);
        CL[c].first = EvaluateMove();
        rho[i].erase(rho[i].begin()+j);
        if(CL[c].first<gmin || (CL[c].first==gmin && rndInt(0,1))) {
            gmin      = CL[c].first;
            candidate = c;
        }
    }

    return CL[candidate].second;
}

int Solution::EvaluateGreedy(int u, int i) {

    int g = 0;

    int xu;
    if(!rho[i].empty()) xu = x[rho[i].back()] + (data.L[rho[i].back()] + data.L[u])/2;
    else                xu = data.L[xu]/2;
    for(int k=0; k<data.nM; k++) {
        for(int l=0; l<rho[k].size(); l++) {
            int rhokl = rho[k][l];
            g += data.W[u][rhokl]*abs(xu - x[rhokl]);
        }
    }

    return g;
}
