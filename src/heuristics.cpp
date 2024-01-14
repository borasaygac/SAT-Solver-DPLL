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
    //std::cout << "CHOOSE_LIT:" << curVar << "\n";
    update(curVar);
    
}

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

void chooseMOM() {
    int max = 0;
    int index = 0;
    bool pol = false;

    while (!minClauses.empty()) {
        int minClause = minClauses.front();
        if (clauses[minClause].sat != 0) continue;
        minClauses.pop();
        for (auto literal : clauses[minClause].literals) {
            (literal > 0) ? vars[literal].posMOM++ : vars[-literal].negMOM++;
        }
    }

    for (int i = 1; i < numOfVars; i++) {
        if (vars[i].val != FREE || vars[i].posMOM + vars[i].negMOM == 0) continue;

        int MOMscore = (vars[i].posMOM + vars[i].negMOM) * pow(2, 2) + (vars[i].posMOM * vars[i].negMOM);

        if (MOMscore > max) {
            max = MOMscore;
            index = i;
            pol = (vars[i].posMOM >= vars[i].negMOM) ? true : false;
        }

        vars[i].posMOM = 0;
        vars[i].negMOM = 0;
    }

    vars[curVar].localMinClauses = minClauses;
    vars[curVar].localMinWidth = minWidth;
    curVar = index;
    vars[curVar].val = vars[curVar].posMOM ? TRUE : FALSE;
    vars[curVar].forced = false;
    // std::cout << "chosen var " << curVar << "and max score " << max <<"\n";
    assig.push(curVar);
    update(curVar);

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

void chooseJW() {
    double max = 0;
    int index = 0;
    bool pol = false;

    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].val != FREE) continue;
        double pos = 0;
        double neg = 0;
        for (int j = 0; j < vars[i].pos_occ.size(); j++) {
            pos += pow(2, -clauses[j].active);
        }
        for (int j = 0; j < vars[i].neg_occ.size(); j++) {
            neg += pow(2, -clauses[j].active);
        }
        double cur = (pos >= neg) ? pos : neg;

        if (cur > max) {
            max = cur;
            index = i;
            pol = (pos >= neg) ? true : false;
        }
    }

    curVar = index;
    vars[curVar].val = pol ? TRUE : FALSE;
    vars[curVar].forced = false;
    // std::cout << "chosen var " << curVar << "and max score " << max <<"\n";
    assig.push(curVar);
    update(curVar);
}