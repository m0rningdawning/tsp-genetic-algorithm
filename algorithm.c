#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "algorithm.h"
#include "algorithm_initialization.h"

// Traveling Salesman Problem

extern int nextFree;

int fitness(int distmx[CITIES][CITIES], int ch[]){
    int distance = 0;
    for(int i = 0; i < CITIES - 1; i++){
        distance += distmx[ch[i]-1][ch[i+1]-1];
    }
    return distance;
}

void createDistmxRand(int distmx[CITIES][CITIES], int min, int max){
	srand(time(NULL));
	for(int i = 0; i < AMOUNT; i++)
		for(int j = i; j < CITIES; j++){
			if(i == j)
				distmx[i][j] = 0;
			else{
				distmx[i][j] = rand() % max + min;
				distmx[j][i] = distmx[i][j];
			}
		}
}

void createChromosomes(int chromemx[AMOUNT][CITIES]){
    srand(time(NULL));
    int temp, counter;
    for(int i = 0; i < AMOUNT; i++)
        for(int j = 0; j < CITIES; j++){
            chromemx[i][j] = j + 1;
        }
    for(int i = 0; i < AMOUNT; i++)
        for(int j = 0; j < CITIES; j++){
            counter = (rand() % CITIES - 1) + 1;
            temp = chromemx[i][j];
            chromemx[i][j] = chromemx[i][counter];
            chromemx[i][counter] = temp;
        }
}

void createChromosomesNg(int nextGen[AMOUNT][CITIES]){
    for(int i = 0; i < AMOUNT; i++)
        for(int j = 0; j < CITIES; j++){
            nextGen[i][j] = j + 1;
        }
}

void printChromosomes(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES]){
  for(int i = 0; i < AMOUNT; i++){
        for(int j = 0; j < CITIES; j++)
            printf("%d  ",chromemx[i][j]);
        printf("Distance: %d ", fitness(distmx, chromemx[i]));
        puts("");
    }
}

int tournament(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES], int numofTour){
    int tmp[numofTour];
    int bestPos;
    int bestValue;

    for(int i = 0; i < numofTour; i++)
        tmp[i] = rand() % AMOUNT;

    bestPos = tmp[0];
    bestValue = fitness(distmx, chromemx[tmp[0]]);

    for(int i = 0; i < numofTour; i++){
        if(fitness(distmx, chromemx[tmp[i]]) < bestValue){
            bestPos = tmp[i];
            bestValue = fitness(distmx, chromemx[bestPos]);
        }
    }
    return bestPos;
}


void copyChrome(int distmx[CITIES][CITIES], int destination[AMOUNT][CITIES], int source[AMOUNT][CITIES], int from){
    if (fitness(distmx, destination[nextFree]) > fitness(distmx, source[from])){
        for (int i = 0; i < CITIES; i++)
            destination[nextFree][i] = source[from][i];
        nextFree++;
    }
    else
        nextFree++;
}

void copyMx(int chromemx[AMOUNT][CITIES], int nextGen[AMOUNT][CITIES]){
    for (int i = 0; i < AMOUNT; i++){
        for (int j = 0; j < CITIES; j++)
            chromemx[i][j] = nextGen[i][j];
    }
    nextFree = 0;
}

void mutation(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]){ 
    int pos = tournament(distmx,chromemx, 3);
    int counter1 = rand() % CITIES;
    int counter2 = rand() % CITIES;
    if (counter1 != counter2){
        int temp = chromemx[pos][counter1];
        chromemx[pos][counter1] = chromemx[pos][counter2];
        chromemx[pos][counter2] = temp;
        copyChrome(distmx, nextGen, chromemx, pos);
    }
    else{
        counter2 = rand() % CITIES;
        mutation(distmx, chromemx, nextGen);
    }
}

void crossover(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]){
    int pos1 = tournament(distmx, chromemx, 3);
    int pos2 = tournament(distmx, chromemx, 3);
    int firstCopy[CITIES];
    if (pos1 != pos2){
        int i = 5;
        int j = 0;
        int i2 = i;
        int j2 = j;
        for (int n = 0; n < CITIES; n++)
            firstCopy[n] = chromemx[pos1][n];
        while(i < CITIES){
            while(j < CITIES){
                int k = 0;
                while(k < CITIES / 2) {
                    if(chromemx[pos1][k] == chromemx[pos2][(j + 5) % CITIES]){
                        j++;
                        break;
                    }
                    else if ((chromemx[pos1][k] != chromemx[pos2][(j + 5) % CITIES]) && (k != 4)){
                        k++;
                    }
                    else if ((chromemx[pos1][k] != chromemx[pos2][(j + 5) % CITIES]) && (k == 4)){
                        chromemx[pos1][i] = chromemx[pos2][((j + 5) % 10)];
                        i++;
                        j++;
                        break;
                    }
                }
            }
        }
        while(i2 < CITIES){
            while(j2 < CITIES){
                int k2 = 0;
                while(k2 < CITIES / 2) {
                    if(chromemx[pos2][k2] == firstCopy[(j2 + 5) % CITIES]){
                        j2++;
                        break;
                    }
                    else if ((chromemx[pos2][k2] != firstCopy[(j2 + 5) % CITIES]) && (k2 != 4)){
                        k2++;
                    }
                    else if ((chromemx[pos2][k2] != firstCopy[(j2 + 5) % CITIES]) && (k2 == 4)){
                        chromemx[pos2][i2] = firstCopy[(j2 + 5) % CITIES];
                        i2++;
                        j2++;
                        break;
                    }
                }
            }
        }

        copyChrome(distmx, nextGen, chromemx, pos1);
        copyChrome(distmx, nextGen, chromemx, pos2);
    }
    else{
        pos2 = tournament(distmx, chromemx, 3);
        crossover(distmx, chromemx, nextGen);
    }
}

void mutationInv(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]){
    int pos = tournament(distmx,chromemx, 3);
    int tmp = rand() % CITIES / 2;
    int counter1 = tmp + 1;
    int counter2 = counter1 + 4;
    while(counter1 != counter2){
        int temp = chromemx[pos][counter1];
        chromemx[pos][counter1] = chromemx[pos][counter2];
        chromemx[pos][counter2] = temp;
        counter1++;
        counter2--;
    }
    copyChrome(distmx, nextGen, chromemx, pos);
}

void reproduction(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES]){
    int pos = nextFree;
    copyChrome(distmx, nextGen, chromemx, pos);
}

void pickBest(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES], int overallBest[1][CITIES]){
    int pos = tournament(distmx, chromemx, 100);
    int bestValueCh = fitness(distmx, chromemx[pos]); 
    int bestValueOv = fitness(distmx, overallBest[0]);
    if (bestValueOv > bestValueCh){
        for(int i = 0; i < CITIES; i++)
            overallBest[0][i] = chromemx[pos][i];
    }
}
/*
int get_ascii(char character) {
    void* result;
    result = character;
    return (int)character;
}
*/