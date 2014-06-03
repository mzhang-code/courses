
;; CH01 

(ns ch01)

(defn square 
  [x] 
  (* x x)) 

(defn sum-of-square-of-larger-two
  "Exercise 1.3. Taking three numbers as arguments and 
  returns the sum of the squares of the two larger numbers."
  [x y z]
  (- (+ (square x) (square y) (square z)) (square (min x y z)))) 

