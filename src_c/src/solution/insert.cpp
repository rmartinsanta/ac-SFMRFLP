#include "Solution.h"

//******************************************************************************
// Insert moves
//******************************************************************************

void Solution::Insert(int i, int j, int k, int l) {

    int f = rho[i][j];

    rho[i].erase (rho[i].begin()+j);
    rho[k].insert(rho[k].begin()+l,f);

}

int Solution::EvaluateSwap(int i, int j) {

    // Variables involved in the move
    int u    = rho[i][j];
    int v    = rho[i][j+1];
    int xu   = x[u];
    int xv   = x[v];
    int Lu   = data.L[u];
    int Lv   = data.L[v];
    int xup  = xu + Lv;
    int xvp  = xv - Lu;
    int Luv  = Lu - 2*xv;
    int Lvu  = Lv + 2*xu;

    // Delta_a: Evaluates the cost change of facilities u and v with all the facilities in zones 1-4
    int delta1 = 0, delta2 = 0, delta4 = 0, delta5 = 0, delta6 = 0;
    for(int s=0  ; s<j            ; s++) delta1 += data.W[u][rho[i][s]];
    for(int s=j+2; s<rho[i].size(); s++) delta1 -= data.W[u][rho[i][s]];
    for(int s=0  ; s<j            ; s++) delta2 += data.W[v][rho[i][s]];
    for(int s=j+2; s<rho[i].size(); s++) delta2 -= data.W[v][rho[i][s]];

    for(int r=0; r<data.nM; r++) {
        if(r==i) continue;
        for(int s=0; s<rho[r].size(); s++) {
            int f  = rho[r][s];
            int xf = x[f];
            if      (xf<xu ) delta4 += data.W[u][f];
            else if (xf<xup) delta6 += data.W[u][f]*(Lvu - 2*xf);
            else             delta4 -= data.W[u][f];
            if      (xf<xvp) delta5 += data.W[v][f];
            else if (xf<xv ) delta6 += data.W[v][f]*(Luv + 2*xf);
            else             delta5 -= data.W[v][f];
        }
    }

    return Lv*(delta1 + delta4) - Lu*(delta2 + delta5) + delta6;
}

int Solution::EvaluateDrop(int f) {

    int h = 0;

    // Evaluates the drop of f from the end of its row
    for(int r=0; r<data.nM; r++) for(int s=0; s<rho[r].size(); s++) h -= data.W[f][rho[r][s]]*abs(x[f]-x[rho[r][s]]);

    return h;
}

int Solution::EvaluateAdd(int f, int k) {

    int h = 0;

    // Evaluates the addition of f to the end of row k
    for(int r=0; r<data.nM; r++) {
        if(r!=k) for(int s=0; s<rho[r].size()  ; s++) h += data.W[f][rho[r][s]]*abs(x[f]-x[rho[r][s]]);
        else     for(int s=0; s<rho[k].size()-1; s++) h += data.W[f][rho[k][s]]*   (x[f]-x[rho[k][s]]);
    }

    return h;
}

bool Solution::ExploreInsert(int strategy) {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

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
        if(rho[i].size()>1) {
            for(auto &&posk: vecpos) {
                int k = posk.first;
                int l = posk.second;
                if( (i!=k) || ((i==k)&&(l<rho[i].size())) ) {
                    Insert(i, j, k, l);
                    int h = EvaluateMove();
                    Insert(k, l, i, j);
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
    }

    if(improved) {
        obj += hbest;
        Insert(ibest,jbest,kbest,lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreInsertInc(int strategy) {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    int hbest = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            // Backward Swaps
            int h = 0;
            for (int l = j; l > 0; l--) {
                h += EvaluateSwap(i, l - 1);
                if (h < hbest) {
                    ibest = i;
                    jbest = j;
                    kbest = i;
                    lbest = l - 1;
                    hbest = h;
                    improved = true;
                }
                x[rho[i][l - 1]] += data.L[rho[i][l]];
                x[rho[i][l]] -= data.L[rho[i][l - 1]];
                Exchange(i, l - 1, i, l);
            }
            // Restore solution
            if (j > 0) {
                Insert(i, 0, i, j);
                for (int s = 0; s <= j; s++) x[rho[i][s]] = xaux[rho[i][s]];
            }
            // Forward Swaps
            h = 0;
            for (int l = j; l < rho[i].size() - 1; l++) {
                h += EvaluateSwap(i, l);
                if (h < hbest) {
                    ibest = i;
                    jbest = j;
                    kbest = i;
                    lbest = l + 1;
                    hbest = h;
                    improved = true;
                }
                x[rho[i][l]] += data.L[rho[i][l + 1]];
                x[rho[i][l + 1]] -= data.L[rho[i][l]];
                Exchange(i, l, i, l + 1);
            }
            // Insert into a different row
            int f = rho[i].back();
            rho[i].pop_back();
            h += EvaluateDrop(f);
            for (int k = 0; k < data.nM; k++) {
                if (k != i) {
                    // Insert at the end of row k
                    x[f] = x[rho[k].back()] + (data.L[rho[k].back()] + data.L[f]) / 2;
                    rho[k].push_back(f);
                    int haux = h + EvaluateAdd(f, k);
                    if (haux < hbest) {
                        ibest = i;
                        jbest = j;
                        kbest = k;
                        lbest = static_cast<int>(rho[k].size() - 1);
                        hbest = haux;
                        improved = true;
                    }
                    //  Backward Swaps
                    for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                        haux += EvaluateSwap(k, l - 1);
                        if (haux < hbest) {
                            ibest = i;
                            jbest = j;
                            kbest = k;
                            lbest = l - 1;
                            hbest = haux;
                            improved = true;
                        }
                        x[rho[k][l - 1]] += data.L[rho[k][l]];
                        x[rho[k][l]] -= data.L[rho[k][l - 1]];
                        Exchange(k, l - 1, k, l);
                    }
                    // Restore partial solution
                    rho[k].erase(rho[k].begin());
                    for (int u: rho[k]) x[u] = xaux[u];
                }
            }
            // Restore solution
            rho[i].insert(rho[i].begin() + j, f);
            for (int s = j; s < rho[i].size(); s++) x[rho[i][s]] = xaux[rho[i][s]];
            if((strategy>0)&&(improved)) break;
        }
    }

    if(improved) {
        obj += hbest;
        Insert(ibest,jbest,kbest,lbest);
        CalculateCenters();
    }

    return improved;
}


bool Solution::ExploreInsertHorizontalBest() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                for (int l = j + 1; l < rho[i].size(); l++) {
                    Insert(i, j, i, l);
                    int h = EvaluateMove();
                    Insert(i, l, i, j);
                    if (h < hbest || ((h == hbest) && (h < 0) && (rndInt(0, 1)))) {
                        ibest = i;
                        jbest = j;
                        kbest = i;
                        lbest = l;
                        hbest = h;
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

bool Solution::ExploreInsertHorizontalBestInc() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    vecInt  xaux  = x;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                // Backward Swaps
                int h = 0;
                for (int l = j; l > 0; l--) {
                    h += EvaluateSwap(i, l - 1);
                    if (h < hbest || ((h == hbest) && (h < 0) && (rndInt(0, 1)))) {
                        ibest = i;
                        jbest = j;
                        kbest = i;
                        lbest = l - 1;
                        hbest = h;
                        improved = true;
                    }
                    x[rho[i][l - 1]] += data.L[rho[i][l]];
                    x[rho[i][l]] -= data.L[rho[i][l - 1]];
                    Exchange(i, l - 1, i, l);
                }
                // Restore solution
                if (j > 0) {
                    Insert(i, 0, i, j);
                    for (int s = 0; s <= j; s++) x[rho[i][s]] = xaux[rho[i][s]];
                }
                // Forward Swaps
                h = 0;
                for (int l = j; l < rho[i].size() - 1; l++) {
                    h += EvaluateSwap(i, l);
                    if (h < hbest || ((h == hbest) && (h < 0) && (rndInt(0, 1)))) {
                        ibest = i;
                        jbest = j;
                        kbest = i;
                        lbest = l + 1;
                        hbest = h;
                        improved = true;
                    }
                    x[rho[i][l]] += data.L[rho[i][l + 1]];
                    x[rho[i][l + 1]] -= data.L[rho[i][l]];
                    Exchange(i, l, i, l + 1);
                }
                // Restore solution
                if (j < rho[i].size() - 1) {
                    Insert(i, static_cast<int>(rho[i].size() - 1), i, j);
                    for (int s = j; s < rho[i].size(); s++) x[rho[i][s]] = xaux[rho[i][s]];
                }
            }
        }
    }

    if(improved) {
        obj += hbest;
        Insert(ibest,jbest,kbest,lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreInsertVerticalBest() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                for (int k = 0; k < data.nM; k++) {
                    if (k != i) {
                        for (int l = 0; l < rho[k].size() - 1; l++) {
                            Insert(i, j, k, l);
                            int h = EvaluateMove();
                            Insert(k, l, i, j);
                            if (h < hbest || ((h == hbest) && (h < 0) && (rndInt(0, 1)))) {
                                ibest = i;
                                jbest = j;
                                kbest = k;
                                lbest = l;
                                hbest = h;
                                improved = true;
                            }
                        }
                    }
                }
            }
        }
    }

    if(improved) {
        obj += hbest;
        Insert(ibest,jbest,kbest,lbest);
        CalculateCenters();
    }

    return improved;
}

bool Solution::ExploreInsertVerticalBestInc() {

    bool improved = false;

    int  ibest, jbest;
    int  kbest, lbest;

    vecInt  xaux  = x;

    int hbest = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                // Insert f at the end of row i
                Insert(i, j, i, static_cast<int>(rho[i].size() - 1));
                int h = EvaluateMove();
                // Insert into a different row
                int f = rho[i].back();
                rho[i].pop_back();
                h += EvaluateDrop(f);
                for (int k = 0; k < data.nM; k++) {
                    if (k != i) {
                        // Insert at the end of row k
                        x[f] = x[rho[k].back()] + (data.L[rho[k].back()] + data.L[f]) / 2;
                        rho[k].push_back(f);
                        int haux = h + EvaluateAdd(f, k);
                        if (haux < hbest || ((haux == hbest) && (h < 0) && (rndInt(0, 1)))) {
                            ibest = i;
                            jbest = j;
                            kbest = k;
                            lbest = static_cast<int>(rho[k].size() - 1);
                            hbest = haux;
                            improved = true;
                        }
                        //  Backward Swaps
                        for (int l = static_cast<int>(rho[k].size()-1); l > 0; l--) {
                            haux += EvaluateSwap(k, l - 1);
                            if (haux < hbest || ((haux == hbest) && (h < 0) && (rndInt(0, 1)))) {
                                ibest = i;
                                jbest = j;
                                kbest = k;
                                lbest = l - 1;
                                hbest = haux;
                                improved = true;
                            }
                            x[rho[k][l - 1]] += data.L[rho[k][l]];
                            x[rho[k][l]] -= data.L[rho[k][l - 1]];
                            Exchange(k, l - 1, k, l);
                        }
                        // Restore partial solution
                        rho[k].erase(rho[k].begin());
                        for (int u: rho[k]) x[u] = xaux[u];
                    }
                }
                // Restore solution
                rho[i].insert(rho[i].begin() + j, f);
                for (int s = j; s < rho[i].size(); s++) x[rho[i][s]] = xaux[rho[i][s]];
            }
        }
    }

    if(improved) {
        obj += hbest;
        Insert(ibest,jbest,kbest,lbest);
        CalculateCenters();
    }

    return improved;
}
