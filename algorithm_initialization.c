#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "algorithm.h"
#include "algorithm_initialization.h"

// TSP Initialization

extern int nextFree;

int initialize(int distmx[CITIES][CITIES], int chromemx[AMOUNT][CITIES], int nextGen[AMOUNT][CITIES], int overallBest[1][CITIES], int amountGiven, int min, int max) { 
    int chCheck;

    printf("Insert the amount of additional generations you want to be created(in range between 0 - 10000): ");
    
    if (scanf("%d", &chCheck) == 0)
        getchar();
    else
        amountGiven = chCheck;
    
    puts("--------------------------------------------");
    
    if (amountGiven > 0 && amountGiven <= 10000) {    
        printf("Insert the range of distances to be generated. Only positive integer values from minimum to maximum or vice versa should be entered: ");
       
        if (scanf("%d", &chCheck) == 0)
            getchar();
        else
            min = chCheck;

        if (scanf("%d", &chCheck) == 0)
            getchar();
        else
            max = chCheck;
        
        puts("--------------------------------------------");
        
        while(true) {
            if(min <= 0 || max <= 0) {
        
            printf("Enerted values are incorrect! Provide acceptable numbers: "); 
        
            if (scanf("%d", &chCheck) == 0)
                getchar();
            else
                min = chCheck;

            if (scanf("%d", &chCheck) == 0)
                getchar();
            else
                max = chCheck;
        
            puts("--------------------------------------------");
            }
            else
                break;
        }

        if(min > max) {
            int tmp;
            tmp = min;
            min = max;
            max = tmp;
        }

        createDistmxRand(distmx, min, max);
        createChromosomes(chromemx);
        createChromosomesNg(nextGen);

        puts("--------------------------------------------");
        puts("Initial population is: ");
        puts("--------------------------------------------");
        printChromosomes(distmx, chromemx);
        puts("--------------------------------------------");

        for(int i = 0; i < CITIES; i++)
            overallBest[0][i] = chromemx[0][i];

        // Main part: 2 mutations, 2 reversed mutations, 4 crossovered chromosomes, 2 copied chromosomes with no changes.
        
        for(int i = 1; i <= amountGiven; i++) {
            for(int j = 0; j < CITIES / 2 - 3; j++) {
                mutation(distmx, chromemx, nextGen);
                mutationInv(distmx, chromemx, nextGen);
            }
            
            for (int k = 0;  k < CITIES / 2 - 3; k++)
                crossover(distmx, chromemx, nextGen);
            
            while(nextFree < AMOUNT) 
                reproduction(distmx, chromemx, nextGen); 
            
            printf("Generation №[%d]: \n", i);
            puts("--------------------------------------------");
            printChromosomes(distmx, nextGen);
            puts("--------------------------------------------"); 
            copyMx(chromemx, nextGen);
            pickBest(distmx, chromemx, overallBest);
        }

        puts("The best route from all generations is: ");
        puts("--------------------------------------------");
        
        for(int i = 0; i < CITIES; i++)
            printf("%d  ", overallBest[0][i]);
        
        printf("Distance: %d\n",fitness(distmx, overallBest[0]));
        puts("--------------------------------------------");
    }
    else { 
        puts("Warning, unacceptable value or \"0\" has been selected! The shortest route will be picked from the initial population, after the selection of the range of distances.");
        puts("--------------------------------------------");
        printf("Insert the range of distances to be generated. Only positive integer values from minimum to maximum or vice versa should be entered: ");
        
        if (scanf("%d", &chCheck) == 0)
            getchar();
        else
            min = chCheck;

        if (scanf("%d", &chCheck) == 0)
            getchar();
        else
            max = chCheck;
        
        while(true) {
            if(min <= 0 || max <= 0) {
                puts("--------------------------------------------");
            
            printf("Enerted values are incorrect! Provide acceptable numbers: "); 
            
            if (scanf("%d", &chCheck) == 0)
                getchar();
            else
                min = chCheck;

            if (scanf("%d", &chCheck) == 0)
                getchar();
            else
                max = chCheck;
            } 
        else
            break;
        }
        
        if(min > max) {
            int tmp;
            tmp = min;
            min = max;
            max = tmp;
        }
        
        createDistmxRand(distmx, min, max);
        createChromosomes(chromemx);
        
        puts("Initial population is: ");
        puts("--------------------------------------------");
        
        printChromosomes(distmx, chromemx);
        
        puts("--------------------------------------------");
        puts("The best route is: ");
        puts("--------------------------------------------");
        
        for(int i = 0; i < CITIES; i++)
            overallBest[0][i] = chromemx[0][i];
        
        pickBest(distmx, chromemx, overallBest);
        
        for(int i = 0; i < CITIES; i++)
            printf("%d  ", overallBest[0][i]);
        
        printf("Distance: %d\n", fitness(distmx, overallBest[0]));
        puts("--------------------------------------------");
    }
    return 0;
}