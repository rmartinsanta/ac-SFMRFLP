#include "Solution.h"

//******************************************************************************
// Exchange moves
//******************************************************************************

void Solution::Exchange(int i, int j, int k, int l)  {

//    int temp  = rho[i][j];
//    rho[i][j] = rho[k][l];
//    rho[k][l] = temp;

    rho[i][j] ^= rho[k][l];
    rho[k][l] ^= rho[i][j];
    rho[i][j] ^= rho[k][l];

}

int Solution::DeltaExchange(int f, int g, int xfp, int xgp) {

    return data.W[f][g]*(abs(xfp-xgp)-abs(x[f]-x[g]));

}

int Solution::EvaluateExchangeSame(int i, int j, int l) {

    int h = 0;

 // Variables involved in the move
    int u    = rho[i][j];
    int v    = rho[i][l];
    int Laux = data.L[u] - data.L[v];
    int xup  = x[v] - Laux/2;
    int xvp  = x[u] - Laux/2;

 // Delta_a: Evaluates the cost change of facilities u and v with all the facilities in zones 1-4
    for(int s=0  ; s<j            ; s++)                             h += DeltaExchange(u, rho[i][s], xup, x[rho[i][s]]     ) + DeltaExchange(v, rho[i][s], xvp, x[rho[i][s]]     );
    for(int s=j+1; s<l            ; s++)                             h += DeltaExchange(u, rho[i][s], xup, x[rho[i][s]]-Laux) + DeltaExchange(v, rho[i][s], xvp, x[rho[i][s]]-Laux);
    for(int s=l+1; s<rho[i].size(); s++)                             h += DeltaExchange(u, rho[i][s], xup, x[rho[i][s]]     ) + DeltaExchange(v, rho[i][s], xvp, x[rho[i][s]]     );
    for(int r=0  ; r<data.nM      ; r++) if(r!=i) for(int f: rho[r]) h += DeltaExchange(u, f        , xup, x[f]             ) + DeltaExchange(v, f        , xvp, x[f]             );

 // Delta_b: Evaluates the cost change of facilities in zone 2 with all the facilities in zones 1, 3 and 4
    if(data.L[u]!=data.L[v]) { // Otherwise, facilities in zone 2 does not change its position
        for(int t=j+1; t<l; t++) {
            int f   = rho[i][t];
            int xfp = x[f] - Laux;
            for(int s=0  ; s<j            ; s++)                             h += DeltaExchange(f, rho[i][s], xfp, x[rho[i][s]]);
            for(int s=l+1; s<rho[i].size(); s++)                             h += DeltaExchange(f, rho[i][s], xfp, x[rho[i][s]]);
            for(int r=0  ; r<data.nM      ; r++) if(r!=i) for(int g: rho[r]) h += DeltaExchange(f, g        , xfp, x[g]        );
        }
    }

    return h;
}

int Solution::EvaluateExchangeDiff(int i, int j, int k, int l) {

    int h = 0;

 // Variables involved in the move
    int u    = rho[i][j];
    int v    = rho[k][l];
    int Laux = data.L[u] - data.L[v];
    int xup  = x[v] + Laux/2;
    int xvp  = x[u] - Laux/2;

 // Evaluates the cost change between facilities u and v
    h += DeltaExchange(u, v, xup, xvp);

 // Delta_c: Evaluates the cost change of facilities u and v with all the facilities in zones 1-5
    for(int s=0  ; s<j            ; s++)                                       h += DeltaExchange(u, rho[i][s], xup, x[rho[i][s]]     ) + DeltaExchange(v, rho[i][s], xvp, x[rho[i][s]]     );
    for(int s=j+1; s<rho[i].size(); s++)                                       h += DeltaExchange(u, rho[i][s], xup, x[rho[i][s]]-Laux) + DeltaExchange(v, rho[i][s], xvp, x[rho[i][s]]-Laux);
    for(int s=0  ; s<l            ; s++)                                       h += DeltaExchange(u, rho[k][s], xup, x[rho[k][s]]     ) + DeltaExchange(v, rho[k][s], xvp, x[rho[k][s]]     );
    for(int s=l+1; s<rho[k].size(); s++)                                       h += DeltaExchange(u, rho[k][s], xup, x[rho[k][s]]+Laux) + DeltaExchange(v, rho[k][s], xvp, x[rho[k][s]]+Laux);
    for(int r=0  ; r<data.nM      ; r++) if((r!=i)&&(r!=k)) for(int f: rho[r]) h += DeltaExchange(u, f        , xup, x[f]             ) + DeltaExchange(v, f        , xvp, x[f]             );

 // Delta_d: Evaluates the cost change of facilities in zone 2 and 4 with all the facilities in zones 1, 3 and 5
    if(data.L[u]!=data.L[v]) { // Otherwise, facilities in zone 2 does not change its position
        for(int t=j+1; t<rho[i].size(); t++) { // Zone 2 with zones 1, 3 and 5
            int f   = rho[i][t];
            int xfp = x[f] - Laux;
            for(int s=0  ; s<j            ; s++)                                       h += DeltaExchange(f, rho[i][s], xfp, x[rho[i][s]]);
            for(int s=0  ; s<l            ; s++)                                       h += DeltaExchange(f, rho[k][s], xfp, x[rho[k][s]]);
            for(int r=0  ; r<data.nM      ; r++) if((r!=i)&&(r!=k)) for(int g: rho[r]) h += DeltaExchange(f, g        , xfp, x[g]        );
        }
        for(int t=l+1; t<rho[k].size(); t++) { // Zone 4 with zones 1, 3 and 5
            int f   = rho[k][t];
            int xfp = x[f] + Laux;
            for(int s=0  ; s<j            ; s++)                                       h += DeltaExchange(f, rho[i][s], xfp, x[rho[i][s]]);
            for(int s=0  ; s<l            ; s++)                                       h += DeltaExchange(f, rho[k][s], xfp, x[rho[k][s]]);
            for(int r=0  ; r<data.nM      ; r++) if((r!=i)&&(r!=k)) for(int g: rho[r]) h += DeltaExchange(f, g        , xfp, x[g]        );
        }
        for(int t=j+1; t<rho[i].size(); t++) { // Zone 2 with zone 4
            int f   = rho[i][t];
            int xfp = x[f] - Laux;
            for(int s=l+1; s<rho[k].size(); s++) h += DeltaExchange(f, rho[k][s], xfp, x[rho[k][s]] + Laux);
        }
    }

    return h;
}

bool Solution::ExploreExchange(int strategy) {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    vector<vector<bool>> mat = vector<vector<bool>>(data.nN,vector<bool>(data.nN,false));
    for(int i=0; i<data.nN; i++) mat[i][i] = true;

    pairPos pos;
    vector<pairPos> vecpos;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecpos.push_back(pos);
        }
    }
    rndShuffle(vecpos);

    int hbest = 0;
    for(auto &&posi: vecpos) {
        int i = posi.first;
        int j = posi.second;
        int u = rho[i][j];
        for(auto &&posk: vecpos) {
            int k = posk.first;
            int l = posk.second;
            int v = rho[k][l];
            if(!mat[u][v]) {
                mat[u][v] = true;
                mat[v][u] = true;
                Exchange(i, j, k, l);
                int h = EvaluateMove();
                Exchange(k, l, i, j);
                if(h<hbest) {
                    ibest = i;
                    jbest = j;
                    kbest = k;
                    lbest = l;
                    hbest = h;
                    improved = true;
                }
            }
            if((strategy>1)&&(improved)) break;
        }
        if((strategy>0)&&(improved)) break;
    }

    if(improved) {
        obj += hbest;
        Exchange(ibest, jbest, kbest, lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreExchangeInc(int strategy) {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    vector<vector<bool>> mat = vector<vector<bool>>(data.nN,vector<bool>(data.nN,false));
    for(int i=0; i<data.nN; i++) mat[i][i] = true;

    pairPos pos;
    vector<pairPos> vecpos;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecpos.push_back(pos);
        }
    }
    rndShuffle(vecpos);

    int hbest = 0;
    for(auto &&posi: vecpos) {
        int i = posi.first;
        int j = posi.second;
        int u = rho[i][j];
        for(auto &&posk: vecpos) {
            int k = posk.first;
            int l = posk.second;
            int v = rho[k][l];
            if(!mat[u][v]) {
                mat[u][v] = true;
                mat[v][u] = true;
                int h = 0;
                if (k == i) {
                    if(l<j) h = EvaluateExchangeSame(i, l, j);
                    else    h = EvaluateExchangeSame(i, j, l);
                } else      h = EvaluateExchangeDiff(i, j, k, l);
                if(h<hbest) {
                    ibest = i;
                    jbest = j;
                    kbest = k;
                    lbest = l;
                    hbest = h;
                    improved = true;
                }
            }
            if((strategy>1)&&(improved)) break;
        }
        if((strategy>0)&&(improved)) break;
    }

    if(improved) {
        obj += hbest;
        Exchange(ibest, jbest, kbest, lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreExchangeHorizontalBest() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size()-1; j++) {
            for(int l=j+1; l<rho[i].size(); l++) {
                Exchange(i, j, i, l);
                int h = EvaluateMove();
                Exchange(i, l, i, j);
                if(h<hbest || ((h==hbest)&&(h<0)&&(rndInt(0,1)))) {
                    ibest    = i;
                    jbest    = j;
                    kbest    = i;
                    lbest    = l;
                    hbest    = h;
                    improved = true;
                }
            }
        }
    }

    if(improved) {
        obj += hbest;
        Exchange(ibest, jbest, kbest, lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreExchangeHorizontalBestInc() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size()-1; j++) {
            for(int l=j+1; l<rho[i].size(); l++) {
                int h = EvaluateExchangeSame(i, j, l);
                if(h<hbest || ((h==hbest)&&(h<0)&&(rndInt(0,1)))) {
                    ibest    = i;
                    jbest    = j;
                    kbest    = i;
                    lbest    = l;
                    hbest    = h;
                    improved = true;
                }
            }
        }
    }

    if(improved) {
        obj += hbest;
        Exchange(ibest, jbest, kbest, lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreExchangeVerticalBest() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    Exchange(i, j, k, l);
                    int h = EvaluateMove();
                    Exchange(k, l, i, j);
                    if(h<hbest || ((h==hbest)&&(h<0)&&(rndInt(0,1)))) {
                        ibest    = i;
                        jbest    = j;
                        kbest    = k;
                        lbest    = l;
                        hbest    = h;
                        improved = true;
                    }
                }
            }
        }
    }

    if(improved) {
        obj += hbest;
        Exchange(ibest, jbest, kbest, lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreExchangeVerticalBestInc() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest || ((h==hbest)&&(h<0)&&(rndInt(0,1)))) {
                        ibest    = i;
                        jbest    = j;
                        kbest    = k;
                        lbest    = l;
                        hbest    = h;
                        improved = true;
                    }
                }
            }
        }
    }

    if(improved) {
        obj += hbest;
        Exchange(ibest, jbest, kbest, lbest);
        CalculateCenters();
    }

    return improved;
}

//bool Solution::ExploreInterchangeVerticalRedu() {
//
//    bool improved = false;
//
//    int  ibest, jbest;
//    int  kbest, lbest;
//
//    vecInt vj;
//
//    int hbest = 0;
//    for(int i=0; i<data.nM; i++) {
//        for(int j=0; j<rho[i].size(); j++) {
//            for(int k=i+1; k<data.nM; k++) {
//                int f1   = rho[i][j];
//                int Lbf1 = x[f1] - data.L[f1]/2;
//                int Ubf1 = x[f1] + data.L[f1]/2;
//                vj.clear();
//                int jp = 0;
//                int f  = rho[k][jp];
//                while((x[f]-data.L[f]/2)<Ubf1) {
//                    if((x[f]+data.L[f]/2)>Lbf1) vj.push_back(jp);
//                    if(jp<rho[k].size()-1) jp++;
//                    else break;
//                    f = rho[k][jp];
//                }
//                for(int l=0; l<vj.size(); l++) {
//                    Exchange(i,j,k,l);
//                    int h = EvaluateMove();
//                    Exchange(k,l,i,j);
//                    if(h<hbest || ((h==hbest)&&(h<0)&&(rndInt(0,1)))) {
//                        ibest   = i;
//                        jbest   = j;
//                        kbest   = k;
//                        lbest   = l;
//                        hbest    = h;
//                        improved = true;
//                    }
//                }
//            }
//        }
//    }
//
//    if(improved) {
//        obj += hbest;
//        Exchange(ibest,jbest,kbest,lbest);
//        CalculateCenters();
//    }
//
//    return improved;
//}
