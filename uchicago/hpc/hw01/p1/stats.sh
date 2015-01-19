
EXEC=./mat_mul

for t in 0 2; do 
	for n in 256 512 1024 2048; do 
		$EXEC -t $t -n $n -b 0
	done 
done

for n in 256 512 1024 2048; do 
	for b in 32 64 128; do
		$EXEC -t 1 -n $n -b $b
	done 
done
