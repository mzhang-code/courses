
Mengyu Zhang
mengyuzhang@uchicago.edu

HW 05
=====

Compile
-------

```
$ make 
```

Outputs

`simpson_omp`
`mc_omp`
`simpson_cu`
`mc_cu`


Peformance
----------

Had some trouble when running cuda programs on Midway. I once ran both mc and simpson successfully, however later the patch job kept resubmitting and overwriting the .out and .err files. 

Simpson OMP 
===========

n = 5
1800000 clocks (0.113750 seconds)
integral is: 0.232324

n = 8
14860000 clocks (1.736347 seconds)
integral is: 0.232323

n = 10
51670000 clocks (5.387846 seconds)
integral is: 0.232323

n = 15 
391410000 clocks (29.501478 seconds)
integral is: 0.232323

MC OMP 
======

n = 100000
2400000 clocks (0.153879 seconds)
integral is: 0.232628

n = 1000000
24880000 clocks (1.590012 seconds)
integral is: 0.232342

n = 10000000
235870000 clocks (15.098052 seconds)
integral is: 0.232248

