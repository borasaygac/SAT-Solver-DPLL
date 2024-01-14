#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "../include/cnf.hpp"

void chooseINC() {
    while (vars[curVar].val != FREE) {
        curVar++;
        // std::cout << "Curvar value " << curVar << "\n";
    }

    vars[curVar].val = TRUE;
    vars[curVar].forced = false;
    assig.push(curVar);
    update(curVar);
    // std::cout << "CHOOSE_LIT:" << curVar << "\n";
}
/*--------------------END FOR CHOOSE INC-----------------------*/

// Custom utility function that helps keep the DLISOccurance set ordered
void chooseDLIS() {
    int max = 0;
    int index = 0;

    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].val != FREE) continue;

        int cur = std::max(vars[i].pos_occ.size(), vars[i].neg_occ.size());
        if (cur > max) {
            max = cur;
            index = i;
        }
    }

    curVar = index;
    vars[curVar].val = vars[curVar].pos_occ.size() > vars[curVar].neg_occ.size() ? TRUE : FALSE;
    vars[curVar].forced = false;
    assig.push(curVar);
    update(curVar);
}

void chooseDLCS() {
    int max = 0;
    int index = 0;

    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].val != FREE) continue;

        int combinedSum = vars[i].neg_occ.size() + vars[i].pos_occ.size();
        if (combinedSum > max) {
            max = combinedSum;
            index = i;
        }
    }

    curVar = index;
    vars[curVar].val = vars[curVar].pos_occ.size() > vars[curVar].neg_occ.size() ? TRUE : FALSE;
    vars[curVar].forced = false;
    assig.push(curVar);
    update(curVar);
}
/*---------------------------------END OF DLCS-------------------------------*/

void chooseMOM() {
    lastValidWidth = minWidth;
    chooseINC();
    // std::vector<double> MOMScore(numOfClauses, 0.0);
    // int param;

    // for (const auto clause : minimalClauses) {
    //     for (int i = 0; i < cnf[clause].literals.size(); i++) {
    //         auto it = maxHeap.find(std::abs(cnf[clause].literals[i]));
    //         (cnf[clause].literals[i] > 0) ? vars[*it].posCount++ : vars[*it].negCount++;
    //         if (it != maxHeap.end()) maxHeap.erase(std::abs(cnf[clause].literals[i]));
    //         maxHeap.insert(std::abs(cnf[clause].literals[i]));
    //     }
    // }

    // curVar = *(maxHeap.begin());
    // vars[curVar].posCount > vars[curVar].negCount ? vars[curVar].val = TRUE : vars[curVar].val = FALSE;
    // vars[curVar].forced = false;
    // assig.push(curVar);
}

void chooseJW() { printf("HI %i", 4); }