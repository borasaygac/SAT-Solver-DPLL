#include "../include/cnf.hpp"

void printModel(int res) {
    if (res == 1) {
        printf("\nUNSAT: No model!\n");
    } else {
        std::cout << "SAT!"
                  << "\n";
        printf("Model: [");
    }

    for (int i = 1; i < numOfVars; i++) {
        int value;
        if (vars[i].val == FREE) value = 0;
        if (vars[i].val == TRUE) value = i;
        if (vars[i].val == FALSE) value = -i;

        printf("%i, ", value);
    }
    int value;
    if (vars[numOfVars].val == FREE) value = 0;
    if (vars[numOfVars].val == TRUE) value = numOfVars;
    if (vars[numOfVars].val == FALSE) value = -numOfVars;
    printf("%i", value);
    printf("]\n");
}