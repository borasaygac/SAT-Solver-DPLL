#include "../include/cnf.hpp"

void chooseINC() {
    int i = 0;
    while (vars[curVar].val != FREE){
        curVar++;
        //std::cout << "Curvar value " << curVar << "\n";
    } 

    vars[curVar].val = TRUE;
    vars[curVar].forced = false;
    assig.push(curVar);
    // std::cout << "CHOOSE_LIT:" << curVar << "\n";
}

void chooseDLIS(){}

void chooseDLCS(){}

void chooseMOM(){}

void chooseJW(){}