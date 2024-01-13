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

    for (int i = 1; i <= numOfVars; i++){
        int totalOcc = vars[i].neg_occ.size() + vars[i].pos_occ.size();
        if (totalOcc > max && vars[i].val == FREE) {
            max = totalOcc;
            index = i;
        } 
    }

    curVar = index;
    vars[curVar].val = TRUE;
    vars[curVar].forced = false;
    assig.push(curVar);
}

void chooseDLCS() {}

void chooseMOM() {}

void chooseJW() {}