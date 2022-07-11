#ifndef ALGORITHM_H_
#define ALGORITHM_H_

extern int CITIES;
extern int AMOUNT;

void createDistmxRand(int distmx[CITIES][CITIES], int min, int max);
void createChromosomes(int chromemx[AMOUNT][CITIES]);
void createChromosomesNg(int nextGen[AMOUNT][CITIES]);
void printChromosomes(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES]);
int tournament(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES], int numofTour);
int fitness(int distmx[CITIES][CITIES], int ch[]);
void copyChrome(int distmx[CITIES][CITIES], int destination[AMOUNT][CITIES], int source[AMOUNT][CITIES], int from);
void copyMx(int chromemx[AMOUNT][CITIES], int nextGen[AMOUNT][CITIES]);
void mutation(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]);
void crossover(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]);
void mutationInv(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]);
void reproduction(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]);
void pickBest(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES], int overallBest[1][CITIES]);

#endif