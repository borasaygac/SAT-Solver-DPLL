#include "../include/cnf.hpp"

void chooseINC() {
    while (vars[curVar].val != FREE) curVar++;
    vars[curVar].val = TRUE;
    vars[curVar].forced = false;
    assig.push(curVar);
    // std::cout << "CHOOSE_LIT:" << curVar << "\n";
}

void chooseDLIS(){}

void chooseDLCS(){}

void chooseMOM(){}

void chooseJW(){}