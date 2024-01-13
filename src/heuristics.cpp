#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "../include/cnf.hpp"

void chooseINC() {
    int i = 0;
    while (vars[curVar].val != FREE) {
        curVar++;
        // std::cout << "Curvar value " << curVar << "\n";
    }

    vars[curVar].val = TRUE;
    vars[curVar].forced = false;
    assig.push(curVar);
    // std::cout << "CHOOSE_LIT:" << curVar << "\n";
}
/*--------------------END FOR CHOOSE INC-----------------------*/

// Custom utility function that helps keep the DLISOccurance set ordered
void chooseDLIS() {
    int max = 0;
    int index = 0;
    bool pol = false;

    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].val != FREE) continue;

        int indPosSum = vars[i].pos_occ.size();
        int indNegSum = vars[i].neg_occ.size();

        max = (indPosSum > indNegSum) ? indPosSum : indNegSum;
        index = i;
        pol = (indPosSum > indNegSum);
    }

    curVar = index;
    vars[curVar].val = (pol) ? TRUE : FALSE;
    vars[curVar].forced = false;
    assig.push(curVar);
}

void chooseDLCS() {
    int max = 0;
    int index = 0;

    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].val != FREE) continue;
        
        int totalOcc = vars[i].neg_occ.size() + vars[i].pos_occ.size();
        if (totalOcc > max) {
            max = totalOcc;
            index = i;
        }
    }

    curVar = index;
    if (vars[curVar].pos_occ.size() > vars[curVar].neg_occ.size()) {
        vars[curVar].val = TRUE;
    } else {
        vars[curVar].val = FALSE;
    }
    //std::cout << "CHOOSE_LIT:" << curVar << "\n";
    vars[curVar].forced = false;
    assig.push(curVar);
}
/*---------------------------------END OF DLCS-------------------------------*/
void chooseMOM() {
    std::vector<double> MOMScore (numOfClauses, 0.0);
    int param;

     for (const auto clause : minimalClauses) {
        for (int i = 0; i < cnf[clause].literals.size(); i++) {
            
        }
     }
} 

void MOMUpdate() {

}

void chooseJW() {}