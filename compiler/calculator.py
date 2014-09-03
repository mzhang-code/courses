#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import sys

def stream(s): 
    for c in s: 
        yield c
    yield '$'

def is_digit(c): 
    return ord('0') <= ord(c) <= ord('9')

class Calculator(object): 
    
    def __init__(self): 
        self.buf = ''
        self.lookahead = '' 

    def calc(self, s): 
        self.buf = stream(s)
        self.lookahead = self.buf.next() 
        return self.expr() 
    
    def match(self, c): 
        self.lookahead = self.buf.next() 


class SimpleDigitCalculator(Calculator): 
    ''' 
        LL(1) Grammar: 

            expr    : term rest 

            rest    : + term rest 
                    | - term rest
                    | ε

            term    | atom 
                    : - atom 

            atom    : (expr) 
                    | 0 
                    | 1  
                      ... 
                    | 9  

        e.g. 
            9-(5+2) -> 2 
            -1      -> -1 
            -1+-1+2 -> 0 
    '''
            
    def expr(self): 
        left_operand = self.term() 
        return self.rest(left_operand) 

    def rest(self, left_operand): 
        if self.lookahead == '+': 
            self.match('+')
            val = left_operand + self.term()
            return self.rest(val)

        elif self.lookahead == '-': 
            self.match('-')
            val = left_operand - self.term()
            return self.rest(val)

        else: 
            # epsilon production 
            return left_operand

    def term(self): 
        if self.lookahead == '-': 
            self.match('-') 
            return (-1) * self.atom()
        else: 
            return self.atom()

    def atom(self): 
        if is_digit(self.lookahead): 
            d = self.lookahead
            self.match(d)
            return ord(d) - ord('0') 
        elif self.lookahead == '(': 
            self.match('(') 
            val = self.expr() 
            self.match(')') 
            return val 
        else: 
            raise ValueError('digit or left parenthesis is expected') 

    
class DigitCalculator(Calculator): 
    ''' 
        LL(1) Grammar: 

            expr        : sub expr_rest 

            expr_rest   : + sub expr_rest 
                        | - sub expr_rest
                        | ε

            sub         : term sub_rest

            sub_rest    : * term sub_rest 
                        | / term sub_rest 
                        | ε

            term        : - atom 
                        | atom 

            atom        : (expr) 
                        | 0 
                        | 1  
                          ... 
                        | 9  

        e.g. 
            -(1+2)*3/(-3) -> 3 
    '''
     
    def expr(self): 
        left_operand = self.sub() 
        return self.expr_rest(left_operand) 

    def expr_rest(self, left_operand): 
        op = self.lookahead
        if op in '+-': 
            self.match(op) 
            if op == '+': 
                val = left_operand + self.sub()
            else: 
                val = left_operand - self.sub() 
            return self.expr_rest(val) 
        else: 
            return left_operand 

    def sub(self): 
        left_operand = self.term() 
        return self.sub_rest(left_operand) 

    def sub_rest(self, left_operand): 
        op = self.lookahead 
        if op in '*/': 
            self.match(op) 
            if op == '*': 
                val = left_operand * self.term() 
            else: 
                val = left_operand / self.term() 
            return self.sub_rest(val) 
        else: 
            return left_operand 

    def term(self): 
        if self.lookahead == '-': 
            self.match('-') 
            return (-1) * self.atom()
        else: 
            return self.atom()

    def atom(self): 
        if is_digit(self.lookahead): 
            d = self.lookahead
            self.match(d)
            return ord(d) - ord('0') 
        elif self.lookahead == '(': 
            self.match('(') 
            val = self.expr() 
            self.match(')') 
            return val 
        else: 
            raise ValueError('digit or left parenthesis is expected') 

if __name__ == '__main__': 
    string = sys.argv[1] 
    calculator = DigitCalculator() 
    print calculator.calc(string) 

