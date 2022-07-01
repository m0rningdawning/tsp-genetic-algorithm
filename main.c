#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Amount of chromosomes
#define AMOUNT 10
//Max number of cities
#define CITIES 10

// Traveling Salesman Problem

int extern fitness(int distmx[AMOUNT][CITIES], int ch[]);

int nextFree;

void createChromosomes(int chromemx[AMOUNT][CITIES])
{
    srand(time(NULL));
    int temp, counter;
    for(int i = 0; i < AMOUNT; i++)
        for(int j = 0; j < CITIES; j++)
        {
            chromemx[i][j] = j + 1;
        }
    for(int i = 0; i < AMOUNT; i++)
        for(int j = 0; j < CITIES; j++)
        {
            counter = (rand() % CITIES - 1) + 1;
            temp = chromemx[i][j];
            chromemx[i][j] = chromemx[i][counter];
            chromemx[i][counter] = temp;
        }
}

void createChromosomesNg(int nextGen[AMOUNT][CITIES])
{
    for(int i = 0; i < AMOUNT; i++)
        for(int j = 0; j < CITIES; j++)
        {
            nextGen[i][j] = j + 1;
        }
}

void printChromosomes(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES])
{
  for(int i = 0; i < AMOUNT; i++)
    {
        for(int j = 0; j < CITIES; j++)
        {
            printf("%d  ",chromemx[i][j]);
        }
        printf("Distance: %d ", fitness(distmx, chromemx[i]));
        puts("");
    }
}

int tournament(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES], int numofTour)
{
    int tmp[numofTour];
    int bestPos;
    int bestValue;

    for(int i = 0; i < numofTour; i++)
        tmp[i] = rand() % AMOUNT;

    bestPos = tmp[0];
    bestValue = fitness(distmx, chromemx[tmp[0]]);

    for(int i = 0; i < numofTour; i++)
    {
        if(fitness(distmx, chromemx[tmp[i]]) < bestValue)
        {
            bestPos = tmp[i];
            bestValue = fitness(distmx, chromemx[bestPos]);
        }
    }
    return bestPos;
}

int fitness(int distmx[AMOUNT][CITIES], int ch[])
{
    int distance = 0;
    for(int i = 0; i < CITIES - 1; i++)
    {
        distance += distmx[ch[i]-1][ch[i+1]-1];
    }
    return distance;
}

void copyChrome(int distmx[AMOUNT][CITIES], int destination[AMOUNT][CITIES], int source[AMOUNT][CITIES], int from)
{
    if (fitness(distmx, destination[nextFree]) > fitness(distmx, source[from]))
    {
        for (int i = 0; i < CITIES; i++)
            destination[nextFree][i] = source[from][i];
        nextFree++;
    }
    else
        nextFree++;
}

void copyMx(int chromemx[AMOUNT][CITIES], int nextGen[AMOUNT][CITIES])
{
    for (int i = 0; i < AMOUNT; i++)
    {
        for (int j = 0; j < CITIES; j++)
            chromemx[i][j] = nextGen[i][j];
    }
    nextFree = 0;
}

void mutation(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES])
{ 
    int pos = tournament(distmx,chromemx, 3);
    int counter1 = rand() % CITIES;
    int counter2 = rand() % CITIES;
    if (counter1 != counter2)
    {
        int temp = chromemx[pos][counter1];
        chromemx[pos][counter1] = chromemx[pos][counter2];
        chromemx[pos][counter2] = temp;
        copyChrome(distmx, nextGen, chromemx, pos);
    }
    else
    {
        counter2 = rand() % CITIES;
        mutation(distmx, chromemx, nextGen);
    }
}

void crossover(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES])
{
    int pos1 = tournament(distmx, chromemx, 3);
    int pos2 = tournament(distmx, chromemx, 3);
    int firstCopy[CITIES];

    // Code to test the correctness of the function(pt1)
    /*
            puts(" \n1st: ");
    for(int i = 0; i < 10; i++)
        {
            printf(" %d", chromemx[pos1][i]);
        }

            puts(" \n2nd: ");
    for(int i = 0; i < 10; i++)
        {
            printf(" %d", chromemx[pos2][i]);
        }
    */
    if (pos1 != pos2)
    {
        int i = 5;
        int j = 0;
        int i2 = i;
        int j2 = j;
        for (int n = 0; n < CITIES; n++)
            firstCopy[n] = chromemx[pos1][n];
        while(i < CITIES)
        {
            while(j < CITIES)
            {
                int k = 0;
                while(k < CITIES / 2) 
                {
                    if(chromemx[pos1][k] == chromemx[pos2][(j + 5) % CITIES])
                    {
                        j++;
                        break;
                    }
                    else if ((chromemx[pos1][k] != chromemx[pos2][(j + 5) % CITIES]) && (k != 4))
                    {
                        k++;
                    }
                    else if ((chromemx[pos1][k] != chromemx[pos2][(j + 5) % CITIES]) && (k == 4))
                    {
                        chromemx[pos1][i] = chromemx[pos2][((j + 5) % 10)];
                        i++;
                        j++;
                        break;
                    }
                }
            }
        }
        while(i2 < CITIES)
        {
            while(j2 < CITIES)
            {
                int k2 = 0;
                while(k2 < CITIES / 2) 
                {
                    if(chromemx[pos2][k2] == firstCopy[(j2 + 5) % CITIES])
                    {
                        j2++;
                        break;
                    }
                    else if ((chromemx[pos2][k2] != firstCopy[(j2 + 5) % CITIES]) && (k2 != 4))
                    {
                        k2++;
                    }
                    else if ((chromemx[pos2][k2] != firstCopy[(j2 + 5) % CITIES]) && (k2 == 4))
                    {
                        chromemx[pos2][i2] = firstCopy[(j2 + 5) % CITIES];
                        i2++;
                        j2++;
                        break;
                    }
                }
            }
        }

        // Code to test the correctness of the function(pt1)

        /*
            puts(" \n1sta: ");
        for(int i = 0; i < 10; i++)
        {
            printf(" %d", chromemx[pos1][i]);
        }

            puts(" \n2nda: ");
        for(int i = 0; i < 10; i++)
        {
            printf(" %d", chromemx[pos2][i]);
        }
        */
        copyChrome(distmx, nextGen, chromemx, pos1);
        copyChrome(distmx, nextGen, chromemx, pos2);
    }
    else
    {
        pos2 = tournament(distmx, chromemx, 3);
        crossover(distmx, chromemx, nextGen);
    }
}

void mutationInv(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES])
{
    int pos = tournament(distmx,chromemx, 3);
    int tmp = rand() % CITIES / 2;
    int counter1 = tmp + 1;
    int counter2 = counter1 + 4;
    while(counter1 != counter2)
    {
        int temp = chromemx[pos][counter1];
        chromemx[pos][counter1] = chromemx[pos][counter2];
        chromemx[pos][counter2] = temp;
        counter1++;
        counter2--;
    }
    copyChrome(distmx, nextGen, chromemx, pos);
}

void reproduction(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES],int nextGen[AMOUNT][CITIES])
{
    int pos = nextFree;
    copyChrome(distmx, nextGen, chromemx, pos);
}

void pickBest(int distmx[AMOUNT][CITIES], int chromemx[AMOUNT][CITIES], int overallBest[1][CITIES])
{
    int pos = tournament(distmx, chromemx, 100);
    int bestValueCh = fitness(distmx, chromemx[pos]); 
    int bestValueOv = fitness(distmx, overallBest[0]);
    if (bestValueOv > bestValueCh)
    {
        for(int i = 0; i < CITIES; i++)
            overallBest[0][i] = chromemx[pos][i];
    }
}

int main (void)
{
    int distmx[AMOUNT][CITIES] = {{0,3,6,7,2,9,34,22,12,15},
                                  {3,0,4,5,12,11,17,16,19,20},
                                  {6,4,0,13,21,44,41,26,28,30},
                                  {7,5,13,0,18,37,28,19,33,51},
                                  {2,12,21,18,0,21,29,36,42,43},
                                  {9,11,44,37,21,0,2,1,14,10},
                                  {34,17,41,28,29,2,0,27,21,31},
                                  {22,16,26,19,36,1,27,0,46,47},
                                  {12,19,28,33,42,14,21,46,0,50},
                                  {15,20,30,51,43,10,31,47,50,0}};
    int chromemx[AMOUNT][CITIES];
    int nextGen[AMOUNT][CITIES];
    int overallBest[1][CITIES];
    int amountGiven;
    for(int i = 0; i < CITIES; i++)
        overallBest[0][i] = i + 1;
    printf("Insert the amount of additional generations you want to be created(in range between 0 - 100): ");
    scanf("%d", &amountGiven);
    createChromosomes(chromemx);
    createChromosomesNg(nextGen);
    if (amountGiven > 0 && amountGiven <= 100)
    {  
        puts("--------------------------------------------");
        puts("Initial population is: ");
        puts("--------------------------------------------");
        printChromosomes(distmx, chromemx);
        puts("--------------------------------------------");

        // Main part: 2 mutations, 2 reversed mutations, 4 crossovered chromosomes, 2 copied chromosomes with no changes.
        for(int i = 1; i <= amountGiven; i++)
        {
            for(int j = 0; j < CITIES / 2 - 3; j++)
            {
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
    else if(amountGiven == 0)
    {  
        puts("\nWarning, \"0\" has been selected! The shortest route will be picked from the initial population.\n");
        puts("--------------------------------------------");
        puts("Initial population is: ");
        puts("--------------------------------------------");
        printChromosomes(distmx, chromemx);
        puts("--------------------------------------------");
        puts("The best route is: ");
        puts("--------------------------------------------");
        pickBest(distmx, chromemx, overallBest);
        for(int i = 0; i < CITIES; i++)
            printf("%d  ", overallBest[0][i]);
        printf("Distance: %d\n",fitness(distmx, overallBest[0]));
        puts("--------------------------------------------");
    }
    else
    {
        puts("\nInserted number of generations is incorrect, please provide acceptable number.");
        return -1;
    }
    return 0; 
}
