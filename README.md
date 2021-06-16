# Randomized Shear Sort

The Randomized shear sort algorithm is a randomized version of the shear sort which is described as follows.

Considering n rows and m columns meth and sorting numbers in a major-row snake-like order.

1. Shuffle each row randomly.
1. Sort each column from top to bottom.
1. Shear each row (from left to right for odd row, and right to left for even row).
   Check if sorted is done. If yes, halt.
1. Sort each column from top to bottom and returns to step 1.

|  1  |  2  |  3  |  
| --  |  --  |  --  |  
|  6  |  5  |  4  |  
|  7  |  8  |  9  |  

Sorting by this algorithm is expected to be finished within O(log log n) iterations.

## Build

```
$ mkdir build; cd build;
$ cmake ..
$ make
```

## Run

```
$ ./RandomizedShearSort
options:
  -n, --number     mesh size (int [=5])
  -v, --verbose    display results
      --help       print help
output:
  row  : mesh row num
  col  : mesh column num
  itrs.: number of iterations
```
## Example

- Default
```
$ ./RandomizedShearSort 
## row  col  itrs.
5 5 2
```


- with verbose
```
$ ./RandomizedShearSort -v
[org]
 22 15 14  8  5
 16  9 12  7 19
 10 18  4  0 24
  3 17 20  1 21
 11 13  6  2 23

[Itr : 1]
[r step]
  5 14  8 15 22
  9 12 16  7 19
  4 24 10 18  0
 21 20  3 17  1
  6 11 13  2 23
[c sort]
  4 11  3  2  0
  5 12  8  7  1
  6 14 10 15 19
  9 20 13 17 22
 21 24 16 18 23
[shear step]
  0  2  3  4 11
 12  8  7  5  1
  6 10 14 15 19
 22 20 17 13  9
 16 18 21 23 24
[c sort]
  0  2  3  4  1
  6  8  7  5  9
 12 10 14 13 11
 16 18 17 15 19
 22 20 21 23 24

[Itr : 2]
[r step]
  3  2  1  4  0
  8  5  7  6  9
 14 10 12 11 13
 18 17 19 16 15
 23 22 20 21 24
[c sort]
  3  2  1  4  0
  8  5  7  6  9
 14 10 12 11 13
 18 17 19 16 15
 23 22 20 21 24
[shear step]
  0  1  2  3  4
  9  8  7  6  5
 10 11 12 13 14
 19 18 17 16 15
 20 21 22 23 24
 
## row  col  itrs.
5 5 2
```