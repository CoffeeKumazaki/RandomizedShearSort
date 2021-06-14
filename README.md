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

## build

```
$ mkdir build; cd build;
$ cmake ..
$ make
```
