;; CH01 

(ns ch01)

(defn abs 
  [x] 
  (if (< x 0) 
    (- x) 
    x)) 

(defn square 
  [x] 
  (* x x)) 

(defn cube 
  [x] 
  (* x x x)) 

(defn sum-of-square-of-larger-two
  "Exercise 1.3. Taking three numbers as arguments and 
  returns the sum of the squares of the two larger numbers."
  [x y z]
  (- (+ (square x) (square y) (square z)) (square (min x y z)))) 

(defn good-enough? 
  [guess x] 
  (< (abs (- (cube guess) x)) 0.001)) 

(defn improve-root 
  [guess x] 
  (/ (+ (/ x (square guess)) (* 2 guess)) 3))

(defn cube-root-newton-iter 
  [guess x] 
  (if (good-enough? guess x)
    guess 
    (cube-root-newton-iter (improve-root guess x) x)))

(defn cube-root-newton 
  "Exercise 1.8. Calculating cube root using Newton's method." 
  [x] 
  (cube-root-newton-iter 1.0 x)) 

(defn pascal-trianle-element-rec 
  "Execrcise 1.12. 
  Compute elements of Pascal's triangle by means of a recursive process" 
  [row col] 
  (cond 
    (> col row) "Out Of Border"
    (or (= col 1) (= col row)) 1 
    :else (+ (pascal-trianle-element-rec (- row 1) (- col 1)) 
       (pascal-trianle-element-rec (- row 1) col)))) 

