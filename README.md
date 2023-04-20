# Travelling Salesman Problem
Travelling Salesman Problem solved using Genetic Algorithm.
## Main functions
The algorithm involves four main functions:
### Mutation
The function randomly chooses two places inside a single chromosome and interchanges them. The function requires the usage of the auxillary function "Tournament" in order to choose the chromosome to be mutated.
### Mutation inverse
The function randomly chooses an element in the range from the 2nd to the 6th inside the single chromosome and reverses the next five elements. Function requires the use of the auxillary function "Tournament" in order to choose the chromosome to be mutated.
### Crossover
The function interchanges the last five elements of the two chromosomes one by one. It also avoids repetition by comparing each individual element that ought to be replaced with the first five elements inside the target chromosome.
### Reproduction
The function copies the last 2 chromosomes untouched to the new generation in order to occasionally help avoid local minimum situations.

## Auxillary functions:
The algorithm involves two auxillary functions:
### Fitness
The function checks the overall distance of the given chromosome's route.
### Tournament
The function checks the fitness of randomly chosen chromosomes and returns the position of the winning chromosome in the "chromemx" array.
## Features
The program is fully functional for 10 cities as well as any amount up until 10 with slight code modifications. It also has the ability to randomly generate the symmetrical matrix of distances in a given range so that the user won't bother with inputting it themselves.
