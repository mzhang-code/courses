Homework 4
Graphs/Multicore

Mengyu Zhang

mengyuzhang@uchicago.edu

1. 
==

The format of input test file has been modified, where the comments have been removed, and an extra line is added to indicate node number and edge number. 

Compile
-------

```
$ sh compile.sh
```

Executables `p1_a`, `p1_b` will be generated. 

a)
--

p1_a.cc

Run 

```
$ cat text_graph_small.txt | ./p1_a 
```

b)
--

p1_b.cc

Run 

```
$ cat text_graph_small.txt | ./p1_b
```

Complexity is O(V^2/P). 

2. 
==

Inside the loop of Dijkstra algorithm, the major operations are extract unmarked vertex with minimum distance and update distances when new vertex is added. 

Thus, the parallel algorithm will explore the concurrency in EXTRACT-MIN procedure and RELAX procedure. For edges relaxation, there's no dependency at all, which can be speedup using openmp directly. For the part of EXTRACT-MIN, a map-reduce like idea is adopted, which every thread keeps a local minimum vertex, and finally reduce these local values together and return the vertex with global minimum distance. 

a) pseudocode
-------------

EXTRACT-MIN(D) 
    T = number of threads
    n = number of vertices 

    local_min_vals = Array[n] 
    local_min_idx = Array[n] 

    PARALLEL BEGIN    
        tid = id of thread 

        start = start point for thread tid 
        end = end point for thread tid 

        for i = start to end
            if D[i] > local_min_vals[i]
                local_min_vals[i] = D[i]
                local_min_idx[i] = i
    PARALLEL END

    return select_min_from(local_min_vals)    

RELAX(u, D) 
    PARALLEL FOR LOOP 
    for v in G.Adj[u]
        if D[v] > D[u] + weight(u, v) 
            D[v] = D[u] + weight(u, v)

b) implement the psuedocode in C/OpenMP

