# Travelling Salesman Problem 
Travelling Salesman Problem solved using Genetic Algorithm.
## Main functions
Algorithm involves 4 main functions:
### Mutation
The function randomly chooses 2 places inside the single chromosome and interchanges them. Function requires the use of auxillary function "Tournament" in order to choose the chromosome to be mutated.
### Mutation inverse
The function randomly chooses an element in range from the 2nd to 6th inside the single chromosome and reverses the next 5 elements. Function requires the use of auxillary function "Tournament" in order to choose the chromosome to be mutated. 
### Crossover
The function interchanges last 5 elements of 2 chromosomes one by one. It also avoids repetition by comparing each individual element that ought to be replaced with the first 5 elements inside the target chromosome.
### Reproduction
The function copies last 2 chromosomes to the new generation untouched in order to occasionally help avoiding local minimum situations.

## Auxillary functions:
Algorithm involves 2 auxillary functions:
### Fitness
The function checks the overall distance of the given chromosome(route).
### Tournament
The function checks the fitness of randomly chosen chromosomes and returns the position of the winning chromosome in the "chromemx" array.
## Features
The program is fully functional for 10 cities as well as with any amount up untill 10 with slight code modifications. It also has the ability to randomly generate the distances in given range so that user won't bother with inputting it themselves.