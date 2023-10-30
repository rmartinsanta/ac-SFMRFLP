#include "Solution.h"

//******************************************************************************
// Shakes
//******************************************************************************

//----------------------------------------
// Shake 1: Move
//----------------------------------------
void Solution::Shake1(int ks, int move) {

    int i, j, k, l;

    if(move==1) {
        for (int iks=0; iks<ks; iks++) {
            i = rndInt(0, data.nM - 1);
            j = rndInt(0, static_cast<int>(rho[i].size() - 1));
            do { k = rndInt(0, data.nM - 1); } while ((k == i) && (rho[i].size() == 1));
            if (i == k) do { l = rndInt(0, static_cast<int>(rho[i].size() - 1)); } while (l == j);
            else l = rndInt(0, static_cast<int>(rho[k].size() - 1));
            Exchange(i, j, k, l);
        }
    }
    else {
        for (int iks = 0; iks < ks; iks++) {
            do { i = rndInt(0, data.nM - 1); } while (rho[i].size() == 1);
            j = rndInt(0, static_cast<int>(rho[i].size() - 1));
            do { k = rndInt(0, data.nM - 1); } while ((k == i) && (rho[i].size() == 1));
            if (i == k) do { l = rndInt(0, static_cast<int>(rho[i].size() - 1)); } while (l == j);
            else l = rndInt(0, rho[k].size());
            Insert(i, j, k, l);
        }
    }

}


//----------------------------------------
// Shake 2: Horizontal move
//----------------------------------------
void Solution::Shake2(int ks, int move) {

    int i, j, l;

    if(data.nN>data.nM) {
        for (int iks = 0; iks < ks; iks++) {
            do { i = rndInt(0, data.nM - 1); } while (rho[i].size() < 2);
            j = rndInt(0, static_cast<int>(rho[i].size() - 1));
            do { l = rndInt(0, static_cast<int>(rho[i].size() - 1)); } while (l == j);
            if (move == 1) Exchange(i, j, i, l);
            else Insert(i, j, i, l);
        }
    }

}

//----------------------------------------
// Shake 3: Vertical-j move
//----------------------------------------
void Solution::Shake3(int ks, int move) {

    int i, k, j;

    for (int iks = 0; iks < ks; iks++) {
        if (move == 1) i = rndInt(0, data.nM - 1);
        else do { i = rndInt(0, data.nM - 1); } while (rho[i].size() < 2);
        do { k = rndInt(0, data.nM - 1); } while (k == i);
        if (rho[i].size() > rho[k].size()) j = rndInt(0, static_cast<int>(rho[k].size() - 1));
        else j = rndInt(0, static_cast<int>(rho[i].size() - 1));
        if (move == 1) Exchange(i, j, k, j);
        else Insert(i, j, k, j);
    }

}

//----------------------------------------
// Shake 4: Vertical-aligned move
//----------------------------------------
//void Solution::Shake4(int ks,int move) {
//
//    int i, j, k, l;
//
//    for(int ik=0; ik<ks; ik++) {
//        if (move == 1) i = rndInt(0, data.nM - 1);
//        else do { i = rndInt(0, data.nM - 1); } while (rho[i].size() < 2);
//        j = rndInt(0, static_cast<int>(rho[i].size() - 1));
//        int xij = x[rho[i][j]];
//        do { k = rndInt(0, data.nM - 1); } while (k == i);
//        l = 0;
//        int dprev = x[rho[k][l]] - xij;
//        while (dprev < 0) {
//            l++;
//            if (l > rho[k].size() - 1) {
//                l--;
//                break;
//            } else {
//                int dnext = x[rho[k][l]] - xij;
//                if (dnext >= 0) {
//                    if (abs(dprev) < dnext) l--;
//                    break;
//                } else dprev = dnext;
//            }
//        }
//        if (move == 1) Exchange(i, j, k, l);
//        else Insert(i, j, k, l);
//        CalculateCenters();
//    }
//
//}
void Solution::Shake4(int ks,int move) {

    int i, j, k, l;

    pairPos         pos;
    vector<pairPos> vecPos;

    for(int ik=0; ik<ks; ik++) {
        if (move == 1) i = rndInt(0, data.nM - 1);
        else do { i = rndInt(0, data.nM - 1); } while (rho[i].size() < 2);
        j = rndInt(0, static_cast<int>(rho[i].size() - 1));
        int xij = x[rho[i][j]];
        vecPos.clear();
        for(k=0; k<data.nM; k++) {
            if (k != i) {
                l = 0;
                int dprev = x[rho[k][l]] - xij;
                while (dprev < 0) {
                    l++;
                    if (l > rho[k].size() - 1) {
                        l--;
                        break;
                    } else {
                        int dnext = x[rho[k][l]] - xij;
                        if (dnext >= 0) {
                            if (abs(dprev) < dnext) l--;
                            break;
                        } else dprev = dnext;
                    }
                }
                pos.first  = k;
                pos.second = l;
                vecPos.push_back(pos);
            }
        }
        pos = vecPos[rndInt(0, data.nM - 2)];
        k = pos.first;
        l = pos.second;
        if (move == 1) Exchange(i, j, k, l);
        else Insert(i, j, k, l);
        CalculateCenters();
    }

}

//----------------------------------------
// Shake 5: Vertical-contact move
//----------------------------------------
void Solution::Shake5(int ks, int move) {

    int i, j, k, l;

    vecInt vecf;
    for(int iks=0; iks<ks; iks++) {
        if (move == 1) i = rndInt(0, data.nM - 1);
        else do { i = rndInt(0, data.nM - 1); } while (rho[i].size() < 2);
        j = rndInt(0, static_cast<int>(rho[i].size() - 1));
        int u = rho[i][j];
        int Lbu = x[u] - data.L[u] / 2;
        int Ubu = x[u] + data.L[u] / 2;
        do { k = rndInt(0, data.nM - 1); } while (k == i);
        vecf.clear();
        l = 0;
        int v = rho[k][l];
        while ((x[v] - data.L[v] / 2) < Ubu) {
            if ((x[v] + data.L[v] / 2) > Lbu) vecf.push_back(l);
            if (l < rho[k].size() - 1) {
                l++;
                v = rho[k][l];
            } else break;
        }
        if (vecf.empty()) l = static_cast<int>(rho[k].size() - 1);
        else l = vecf[rndInt(0, static_cast<int>(vecf.size() - 1))];
        if (move == 1) Exchange(i, j, k, l);
        else Insert(i, j, k, l);
        CalculateCenters();
    }

}
