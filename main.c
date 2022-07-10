#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "algorithm_initialization.h"

//Amount of chromosomes
int AMOUNT = 10;
//Max number of cities
int CITIES = 10;
//Indicator of the next free place in array
int nextFree;

int main(void){
    int distmx[CITIES][CITIES];
    int chromemx[AMOUNT][CITIES];
    int nextGen[AMOUNT][CITIES];
    int overallBest[1][CITIES];
    int amountGiven, min, max;
    initialize(distmx, chromemx, nextGen, overallBest, amountGiven, min, max);
    return 0;
}
