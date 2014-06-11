;; ch02 

(ns ch02)

;; Exercise 2.36 accumulate-n 

(defn reduce-n 
  [op init seqs] 
  (if (nil? (ffirst seqs)) 
    nil
    (cons (reduce op init (map first seqs)) 
          (reduce-n op init (map rest seqs))))) 

;; Exercise 2.37 matrix multiplication 

(defn dot-product 
  [v w] 
  (reduce + (map * v w))) 

(defn matrix-*-vector 
  [m v] 
  (map (fn [r] (dot-product r v)) m)) 

(defn append 
  "append element to list, which simulates 'cons' in scheme. "
  [l x] 
  (concat l (list x)))

(defn transpose 
  [mat] 
  (reduce-n append '() mat))

(defn matrix-*-matrix 
  [m n] 
  (let
    [cols (transpose n)] 
    (map (fn [r] (matrix-*-vector cols r)) m))) 

