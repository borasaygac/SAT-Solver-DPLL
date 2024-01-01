#include "../include/cnf.hpp"

void chooseINC() {
    while (vars[curVar].getValue() != FREE) curVar++;
    vars[curVar].setValue(TRUE);
    vars[curVar].forced = false;
    assig.push(curVar);
}

void chooseDLIS(){}

void chooseDLCS(){}

void chooseMOM(){}

void chooseJW(){}