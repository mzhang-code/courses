Homework 4
Graphs/Multicore
MPCS 51100
due: 12/10/2014

Compile
=======

```
$ sh compile.sh
```

Executables `p1_a`, `p1_b`, `p2` will be generated. 

1. 
==

The format of input test file has been modified, where the comments have been removed, and an extra line is added to indicate node number and edge number. 

a) p1_a.cc

b) p1_b.cc

Your strategy will be straightforward -- simply assign a different
source vertex to each core. Assume n > p, where p is the number of
processors (i.e.  cores) on a multicore machine. What is the
complexity of the parallel algorithm in terms of n and p? Compare the
performance of the serial and parallel approach using the provided
sample graph. Comment briefly on the observed timings.

2. Next, consider how you might use a shared memory parallel processor
to accelerate Dijskstra *within* a single source computation? There
are several possible approaches, and developing a reasonable approach
yourself (doesn't have to be optimal) is part of the exercise. In this
case, to guide your thinking you may assume that n is much larger than
p -- i.e there are many more vertices than cores. Consider ways to
partition the graph among processors to minmize contention and load
balance -- ie to keep all cores busy but require minimum
synchronization.

a) write pseudocode to describe your approach
b) implement the psuedocode in C/OpenMP

Note that you get 50% credit for just the psuedo-code -- ie a
non-trivial part of the exercise involves developing a reasonable
approach.
