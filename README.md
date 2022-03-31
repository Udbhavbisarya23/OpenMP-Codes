# OpenMP Codes

## Description

Each of these folders represents the work done during a Parallel Computing Couse

1. **Lab1-Introduction** - Introduction to openmp and usage of parallel directive with different clauses such as if,private and num_threads

2. **Lab2-Array_Operations** - The array_addition program sums up two arrays and stores the output in a third array using the parallel and for directives with the shared clause. Similarly, using the for directive (in addition to critical), the largest number is calculated .

3. **Lab3-Collapse** - Learning the usage of different clauses along with the for directive. Parallelization of nested for loops

4. **Lab4-Matrix_Sums** - Involves the initialization of a matrix of a user defined size and calculation of row sum and column sum. 

5. **Lab5-Binary_Search** - Comparison of the time taken by the sequential and parallel executions of binary search.

6. **Lab6-RBG_Conversion** - Conversion of a RGB image to a Grayscale image using both parallel and sequential approach. Comparison of these approaches depending on how much time is taken

7. **Lab7-Clustering** - K-Means clustering using OpenMP. Evaluation of the time taken by the program. There are a 1000 nodes and each node has an x coordinate and y coordinate randomly assigned to it. The user inputs the number of clusters and the number of iterations and the results are recorded. 

## Usage
To run the files, open the terminal in the respective folder.

The files can be executed using the following commands  :-

``` bash
gcc -o prog -fopenmp [filename].c 
./prog
```

For example, to run rgb_conversion.c :- 

``` bash
cd Lab6-RGB_Conversion
gcc -o prog -fopenmp rgb_conversion.c 
./prog
```

