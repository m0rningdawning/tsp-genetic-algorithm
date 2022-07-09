#ifndef ALGORITHM_INITIALIZATION_H_
#define ALGORITHM_INITIALIZATION_H_

extern int CITIES;
extern int AMOUNT;

int initialize(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES], int nextGen[AMOUNT][CITIES], int overallBest[1][CITIES], int amountGiven, int min, int max);

#endif