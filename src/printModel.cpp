#include "../include/cnf.hpp"

void printModel(int res) {
    if (res == 1) {
        printf("\nUNSAT: No model!\n");
    } else {
        std::cout << "All clauses satisfied!"
                  << "\n";
        printf("Model: ");
    }

    printf("[");
    for (int i = 1; i < numOfVars; i++) {
        int val;
        if (vars[i].val == FREE) val = 0;
        if (vars[i].val == TRUE) val = i;
        if (vars[i].val == FALSE) val = -i;

        printf("%i, ", val);
    }
    int val;
    if (vars[numOfVars].val == FREE) val = 0;
    if (vars[numOfVars].val == TRUE) val = numOfVars;
    if (vars[numOfVars].val == FALSE) val = -numOfVars;
    printf("%i", val);
    printf("]\n");
}