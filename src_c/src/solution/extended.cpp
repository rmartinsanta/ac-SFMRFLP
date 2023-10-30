#include "Solution.h"

//******************************************************************************
// Extended neighborhoods: exchange & insert
//******************************************************************************

bool Solution::ExploreExtendedBest() {

    bool improved = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    int hbest_exc = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            for(int l=j+1; l<rho[i].size(); l++) {
                Exchange(i, j, i, l);
                int h = EvaluateMove();
                Exchange(i, l, i, j);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = i;
                    lbest_exc = l;
                    hbest_exc = h;
                }
            }
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    Exchange(i, j, k, l);
                    int h = EvaluateMove();
                    Exchange(k, l, i, j);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                    }
                }
            }
        }
    }

    int hbest_ins = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                // Backward Swaps
                for (int l = j; l > 0; l--) {
                    Insert(i, j, i, l - 1);
                    int h = EvaluateMove();
                    Insert(i, l - 1, i, j);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l - 1;
                        hbest_ins = h;
                    }
                }
                // Forward Swaps
                for (int l = j; l < rho[i].size() - 1; l++) {
                    Insert(i, j, i, l + 1);
                    int h = EvaluateMove();
                    Insert(i, l + 1, i, j);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l + 1;
                        hbest_ins = h;
                    }
                }
                // Insert into a different row
                for (int k = 0; k < data.nM; k++) {
                    if (k != i) {
                        for (int l = rho[k].size(); l >= 0; l--) {
                            Insert(i, j, k, l);
                            int h = EvaluateMove();
                            Insert(k, l, i, j);
                            if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                                ibest_ins = i;
                                jbest_ins = j;
                                kbest_ins = k;
                                lbest_ins = l;
                                hbest_ins = h;
                            }
                        }
                    }
                }
            }
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedBestBestInc() {

    bool improved = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    int hbest_exc = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            for(int l=j+1; l<rho[i].size(); l++) {
                int h = EvaluateExchangeSame(i, j, l);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = i;
                    lbest_exc = l;
                    hbest_exc = h;
                }
            }
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                    }
                }
            }
        }
    }

    int hbest_ins = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                // Backward Swaps
                int h = 0;
                for (int l = j; l > 0; l--) {
                    h += EvaluateSwap(i, l - 1);
                    //h += EvaluateExchangeSame(i,l-1,l);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l - 1;
                        hbest_ins = h;
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
                    //h += EvaluateExchangeSame(i,l,l+1);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l + 1;
                        hbest_ins = h;
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
                        if (!rho[k].empty()) x[f] = x[rho[k].back()] + (data.L[rho[k].back()] + data.L[f]) / 2;
                        else x[f] = data.L[f] / 2;
                        rho[k].push_back(f);
                        int haux = h + EvaluateAdd(f, k);
                        if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                            ibest_ins = i;
                            jbest_ins = j;
                            kbest_ins = k;
                            lbest_ins = static_cast<int>(rho[k].size() - 1);
                            hbest_ins = haux;
                        }
                        //  Backward Swaps
                        for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                            haux += EvaluateSwap(k, l - 1);
                            //haux += EvaluateExchangeSame(k,l-1,l);
                            if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                                ibest_ins = i;
                                jbest_ins = j;
                                kbest_ins = k;
                                lbest_ins = l - 1;
                                hbest_ins = haux;
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

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedBestHybridInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    int hbest_exc = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            for(int l=j+1; l<rho[i].size(); l++) {
                int h = EvaluateExchangeSame(i, j, l);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = i;
                    lbest_exc = l;
                    hbest_exc = h;
                }
            }
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                    }
                }
            }
        }
    }

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    improved = false;
    int hbest_ins = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            // Backward Swaps
            int h = 0;
            for (int l = j; l > 0; l--) {
                h += EvaluateSwap(i, l - 1);
                if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                    ibest_ins = i;
                    jbest_ins = j;
                    kbest_ins = i;
                    lbest_ins = l - 1;
                    hbest_ins = h;
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
                if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                    ibest_ins = i;
                    jbest_ins = j;
                    kbest_ins = i;
                    lbest_ins = l + 1;
                    hbest_ins = h;
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
                    if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = k;
                        lbest_ins = static_cast<int>(rho[k].size() - 1);
                        hbest_ins = haux;
                        improved = true;
                    }
                    //  Backward Swaps
                    for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                        haux += EvaluateSwap(k, l - 1);
                        if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                            ibest_ins = i;
                            jbest_ins = j;
                            kbest_ins = k;
                            lbest_ins = l - 1;
                            hbest_ins = haux;
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
            if (improved) break;
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedBestFirstInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    int hbest_exc = 0;
    for(int i=0; i<data.nM; i++) {
        for(int j=0; j<rho[i].size(); j++) {
            for(int l=j+1; l<rho[i].size(); l++) {
                int h = EvaluateExchangeSame(i, j, l);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = i;
                    lbest_exc = l;
                    hbest_exc = h;
                }
            }
            for(int k=i+1; k<data.nM; k++) {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                    }
                }
            }
        }
    }

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    vector<pairPos> vecposk;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size()+1; pos.second++) {
            vecposk.push_back(pos);
        }
    }
    rndShuffle(vecposk);

    improved  = false;
    int hbest_ins = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            for(auto &&posk: vecposk) {
                int k = posk.first;
                int l = posk.second;
                if( (i!=k) || ((i==k)&&(l<rho[i].size())) ) {
                    Insert(i, j, k, l);
                    int h = EvaluateMove();
                    Insert(k, l, i, j);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = k;
                        lbest_ins = l;
                        hbest_ins = h;
                        improved = true;
                    }
                }
                if (improved) break;
            }
            if (improved) break;
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedHybridBestInc() {

    bool improved =false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    int hbest_exc = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        for(int k=0; k<data.nM; k++) {
            if(k==i) {
                for(int l=0; l<rho[i].size(); l++) {
                    if(l!=j) {
                        int h = 0;
                        if(l<j) h = EvaluateExchangeSame(i, l, j);
                        else    h = EvaluateExchangeSame(i, j, l);
                        if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                            ibest_exc = i;
                            jbest_exc = j;
                            kbest_exc = i;
                            lbest_exc = l;
                            hbest_exc = h;
                            improved  = true;
                        }
                    }
                }
            }
            else {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                        improved  = true;
                    }
                }
            }
        }
        if(improved) break;
    }

    int hbest_ins = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                // Backward Swaps
                int h = 0;
                for (int l = j; l > 0; l--) {
                    h += EvaluateSwap(i, l - 1);
                    //h += EvaluateExchangeSame(i,l-1,l);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l - 1;
                        hbest_ins = h;
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
                    //h += EvaluateExchangeSame(i,l,l+1);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l + 1;
                        hbest_ins = h;
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
                        if (!rho[k].empty()) x[f] = x[rho[k].back()] + (data.L[rho[k].back()] + data.L[f]) / 2;
                        else x[f] = data.L[f] / 2;
                        rho[k].push_back(f);
                        int haux = h + EvaluateAdd(f, k);
                        if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                            ibest_ins = i;
                            jbest_ins = j;
                            kbest_ins = k;
                            lbest_ins = static_cast<int>(rho[k].size() - 1);
                            hbest_ins = haux;
                        }
                        //  Backward Swaps
                        for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                            haux += EvaluateSwap(k, l - 1);
                            //haux += EvaluateExchangeSame(k,l-1,l);
                            if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                                ibest_ins = i;
                                jbest_ins = j;
                                kbest_ins = k;
                                lbest_ins = l - 1;
                                hbest_ins = haux;
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

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedHybridHybridInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    int hbest_exc = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        for(int k=0; k<data.nM; k++) {
            if(k==i) {
                for(int l=0; l<rho[i].size(); l++) {
                    if(l!=j) {
                        int h = 0;
                        if(l<j) h = EvaluateExchangeSame(i, l, j);
                        else    h = EvaluateExchangeSame(i, j, l);
                        if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                            ibest_exc = i;
                            jbest_exc = j;
                            kbest_exc = i;
                            lbest_exc = l;
                            hbest_exc = h;
                            improved  = true;
                        }
                    }
                }
            }
            else {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                        improved  = true;
                    }
                }
            }
        }
        if(improved) break;
    }

    improved = false;
    int hbest_ins = 0;
    rndShuffle(vecposi);
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            // Backward Swaps
            int h = 0;
            for (int l = j; l > 0; l--) {
                h += EvaluateSwap(i, l - 1);
                if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                    ibest_ins = i;
                    jbest_ins = j;
                    kbest_ins = i;
                    lbest_ins = l - 1;
                    hbest_ins = h;
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
                if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                    ibest_ins = i;
                    jbest_ins = j;
                    kbest_ins = i;
                    lbest_ins = l + 1;
                    hbest_ins = h;
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
                    if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = k;
                        lbest_ins = static_cast<int>(rho[k].size() - 1);
                        hbest_ins = haux;
                        improved = true;
                    }
                    //  Backward Swaps
                    for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                        haux += EvaluateSwap(k, l - 1);
                        if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                            ibest_ins = i;
                            jbest_ins = j;
                            kbest_ins = k;
                            lbest_ins = l - 1;
                            hbest_ins = haux;
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
            if (improved) break;
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedHybridFirstInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    int hbest_exc = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        for(int k=0; k<data.nM; k++) {
            if(k==i) {
                for(int l=0; l<rho[i].size(); l++) {
                    if(l!=j) {
                        int h = 0;
                        if(l<j) h = EvaluateExchangeSame(i, l, j);
                        else    h = EvaluateExchangeSame(i, j, l);
                        if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                            ibest_exc = i;
                            jbest_exc = j;
                            kbest_exc = i;
                            lbest_exc = l;
                            hbest_exc = h;
                            improved  = true;
                        }
                    }
                }
            }
            else {
                for(int l=0; l<rho[k].size(); l++) {
                    int h = EvaluateExchangeDiff(i, j, k, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = k;
                        lbest_exc = l;
                        hbest_exc = h;
                        improved  = true;
                    }
                }
            }
        }
        if(improved) break;
    }

    rndShuffle(vecposi);

    vector<pairPos> vecposk;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size()+1; pos.second++) {
            vecposk.push_back(pos);
        }
    }
    rndShuffle(vecposk);

    improved  = false;
    int hbest_ins = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            for(auto &&posk: vecposk) {
                int k = posk.first;
                int l = posk.second;
                if( (i!=k) || ((i==k)&&(l<rho[i].size())) ) {
                    Insert(i, j, k, l);
                    int h = EvaluateMove();
                    Insert(k, l, i, j);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = k;
                        lbest_ins = l;
                        hbest_ins = h;
                        improved = true;
                    }
                }
                if (improved) break;
            }
            if (improved) break;
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedFirstBestInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    vector<pairPos> vecposk;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposk.push_back(pos);
        }
    }
    rndShuffle(vecposk);

    int  hbest_exc = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        for(auto &&posk: vecposk) {
            int k = posk.first;
            int l = posk.second;
            if(k==i) {
                if(l!=j) {
                    int h = 0;
                    if(l<j) h = EvaluateExchangeSame(i, l, j);
                    else    h = EvaluateExchangeSame(i, j, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = i;
                        lbest_exc = l;
                        hbest_exc = h;
                        improved  = true;
                    }
                }
            }
            else {
                int h = EvaluateExchangeDiff(i, j, k, l);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = k;
                    lbest_exc = l;
                    hbest_exc = h;
                    improved  = true;
                }
            }
            if(improved) break;
        }
        if(improved) break;
    }

    int hbest_ins = 0;
    for(int i=0; i<data.nM; i++) {
        if(rho[i].size()>1) {
            for (int j = 0; j < rho[i].size(); j++) {
                // Backward Swaps
                int h = 0;
                for (int l = j; l > 0; l--) {
                    h += EvaluateSwap(i, l - 1);
                    //h += EvaluateExchangeSame(i,l-1,l);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l - 1;
                        hbest_ins = h;
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
                    //h += EvaluateExchangeSame(i,l,l+1);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = i;
                        lbest_ins = l + 1;
                        hbest_ins = h;
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
                        if (!rho[k].empty()) x[f] = x[rho[k].back()] + (data.L[rho[k].back()] + data.L[f]) / 2;
                        else x[f] = data.L[f] / 2;
                        rho[k].push_back(f);
                        int haux = h + EvaluateAdd(f, k);
                        if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                            ibest_ins = i;
                            jbest_ins = j;
                            kbest_ins = k;
                            lbest_ins = static_cast<int>(rho[k].size() - 1);
                            hbest_ins = haux;
                        }
                        //  Backward Swaps
                        for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                            haux += EvaluateSwap(k, l - 1);
                            //haux += EvaluateExchangeSame(k,l-1,l);
                            if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                                ibest_ins = i;
                                jbest_ins = j;
                                kbest_ins = k;
                                lbest_ins = l - 1;
                                hbest_ins = haux;
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

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedFirstHybridInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    vector<pairPos> vecposk;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposk.push_back(pos);
        }
    }
    rndShuffle(vecposk);

    int  hbest_exc = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        for(auto &&posk: vecposk) {
            int k = posk.first;
            int l = posk.second;
            if(k==i) {
                if(l!=j) {
                    int h = 0;
                    if(l<j) h = EvaluateExchangeSame(i, l, j);
                    else    h = EvaluateExchangeSame(i, j, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = i;
                        lbest_exc = l;
                        hbest_exc = h;
                        improved  = true;
                    }
                }
            }
            else {
                int h = EvaluateExchangeDiff(i, j, k, l);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = k;
                    lbest_exc = l;
                    hbest_exc = h;
                    improved  = true;
                }
            }
            if(improved) break;
        }
        if(improved) break;
    }

    rndShuffle(vecposi);

    improved = false;
    int hbest_ins = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            // Backward Swaps
            int h = 0;
            for (int l = j; l > 0; l--) {
                h += EvaluateSwap(i, l - 1);
                if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                    ibest_ins = i;
                    jbest_ins = j;
                    kbest_ins = i;
                    lbest_ins = l - 1;
                    hbest_ins = h;
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
                if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                    ibest_ins = i;
                    jbest_ins = j;
                    kbest_ins = i;
                    lbest_ins = l + 1;
                    hbest_ins = h;
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
                    if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = k;
                        lbest_ins = static_cast<int>(rho[k].size() - 1);
                        hbest_ins = haux;
                        improved = true;
                    }
                    //  Backward Swaps
                    for (int l = static_cast<int>(rho[k].size() - 1); l > 0; l--) {
                        haux += EvaluateSwap(k, l - 1);
                        if (haux < hbest_ins || ((haux == hbest_ins) && (haux < 0) && (rndInt(0, 1)))) {
                            ibest_ins = i;
                            jbest_ins = j;
                            kbest_ins = k;
                            lbest_ins = l - 1;
                            hbest_ins = haux;
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
            if (improved) break;
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}

bool Solution::ExploreExtendedFirstFirstInc() {

    bool improved  = false;

    int  ibest_exc, jbest_exc;
    int  kbest_exc, lbest_exc;

    int  ibest_ins, jbest_ins;
    int  kbest_ins, lbest_ins;

    vecInt xaux = x;

    pairPos pos;
    vector<pairPos> vecposi;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposi.push_back(pos);
        }
    }
    rndShuffle(vecposi);

    vector<pairPos> vecposk;
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size(); pos.second++) {
            vecposk.push_back(pos);
        }
    }
    rndShuffle(vecposk);

    int hbest_exc = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        for(auto &&posk: vecposk) {
            int k = posk.first;
            int l = posk.second;
            if(k==i) {
                if(l!=j) {
                    int h = 0;
                    if(l<j) h = EvaluateExchangeSame(i, l, j);
                    else    h = EvaluateExchangeSame(i, j, l);
                    if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                        ibest_exc = i;
                        jbest_exc = j;
                        kbest_exc = i;
                        lbest_exc = l;
                        hbest_exc = h;
                        improved  = true;
                    }
                }
            }
            else {
                int h = EvaluateExchangeDiff(i, j, k, l);
                if(h<hbest_exc || ((h==hbest_exc)&&(h<0)&&(rndInt(0,1)))) {
                    ibest_exc = i;
                    jbest_exc = j;
                    kbest_exc = k;
                    lbest_exc = l;
                    hbest_exc = h;
                    improved  = true;
                }
            }
            if(improved) break;
        }
        if(improved) break;
    }

    rndShuffle(vecposi);

    vecposk.clear();
    for(pos.first=0; pos.first<data.nM; pos.first++) {
        for(pos.second=0; pos.second < rho[pos.first].size()+1; pos.second++) {
            vecposk.push_back(pos);
        }
    }
    rndShuffle(vecposk);

    improved = false;
    int hbest_ins = 0;
    for(auto &&posi: vecposi) {
        int i = posi.first;
        int j = posi.second;
        if(rho[i].size()>1) {
            for(auto &&posk: vecposk) {
                int k = posk.first;
                int l = posk.second;
                if( (i!=k) || ((i==k)&&(l<rho[i].size())) ) {
                    Insert(i, j, k, l);
                    int h = EvaluateMove();
                    Insert(k, l, i, j);
                    if (h < hbest_ins || ((h == hbest_ins) && (h < 0) && (rndInt(0, 1)))) {
                        ibest_ins = i;
                        jbest_ins = j;
                        kbest_ins = k;
                        lbest_ins = l;
                        hbest_ins = h;
                        improved = true;
                    }
                }
                if (improved) break;
            }
            if (improved) break;
        }
    }

    // Checks the extended move
    int hbest = 0;
    int move  = 0;
    if     (hbest_exc<hbest_ins) move = 1;
    else if(hbest_ins<hbest_exc) move = 2;
    else {
        if(rndDbl(0.0,1.0)<0.5) move = 1;
        else                    move = 2;
    }
    improved = false;
    switch(move) {
        case 1:
            if(hbest_exc<0) {
                improved = true;
                obj += hbest_exc;
                Exchange(ibest_exc, jbest_exc, kbest_exc, lbest_exc);
                CalculateCenters();
            }
            else improved = false;
            break;
        case 2:
            if(hbest_ins<0) {
                improved = true;
                obj += hbest_ins;
                Insert(ibest_ins, jbest_ins, kbest_ins, lbest_ins);
                CalculateCenters();
            }
            else improved = false;
            break;
        default:
            improved = false;
    }

    return improved;
}