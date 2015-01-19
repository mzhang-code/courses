
Mengyu Zhang
mengyuzhang@uchicago.edu

Env
===

Compile
-------

```
$ make 
```

And the elf file `mat_mul` will be produced. 

Run
---

There's a script to run multiple experiments automatically.

```
$ sh stats.sh
```

Stats
=====

The running time counts in seconds. 

|	    	| 	n = 256	  |   n = 512 	|   n = 1024  |   n = 2048  | 
|	naive	|   0.11	  |	  1.07		|   13.12	  |   172.41	| 
|   recur	|   0.23	  |   1.93      | 	15.38	  |   122.17	| 
|   blk/32	|   0.17      |	  1.37		|   10.95	  |   88.76		|
|	blk/64	|   0.17	  |   1.36		|	11.06	  |   87.09		|
|	blk/128	|	0.17	  |   1.38		|   11.33	  |   89.31		|

From the table we can see that, when the matrices can completely fit into cache the naive method has the great performance, however recursive method has the worst. This is mainly because the simplicity of naive procedure while recursive method introduces recursion overhead. 

When the size of matrix grows to 2048, the locality advantage brought by recursion and block method appears to be dominant. In addition, the results show that there's little difference among the experiments with different block size. 


