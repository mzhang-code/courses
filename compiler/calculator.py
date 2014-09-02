#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import sys

def stream(s): 
    for c in s: 
        yield c
    yield '$'

def is_digit(c): 
    return ord('0') <= ord(c) <= ord('9')

class SimpleDigitCalculator(object): 
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
    def __init__(self): 
        self.buf = ''
        self.lookahead = '' 

    def calc(self, s): 
        self.buf = stream(s)
        self.lookahead = self.buf.next() 
        return self.expr() 
        
    def expr(self): 
        left_oprand = self.term() 
        return self.rest(left_oprand) 

    def rest(self, left_oprand): 
        if self.lookahead == '+': 
            self.match('+')
            val = left_oprand + self.term()
            return self.rest(val)

        elif self.lookahead == '-': 
            self.match('-')
            val = left_oprand - self.term()
            return self.rest(val)

        else: 
            return left_oprand

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

    def match(self, c): 
        self.lookahead = self.buf.next() 

class DigitCalculator(object): 
    ''' 
        LL(1) Grammar: 

            expr        : term expr_rest 

            expr_rest   : + term expr_rest 
                        | - term expr_rest
                        | ε

            term        : atom term_rest

            term_rest   : * atom term_rest 
                        | / atom term_rest 
                        | ε

            atom        : (expr) 
                        | 0 
                        | 1  
                          ... 
                        | 9  

        e.g. 
            9-(5*2) -> 2 
    '''
    pass 


if __name__ == '__main__': 
    string = sys.argv[1] 
    calculator = SimpleDigitCalculator() 
    print calculator.calc(string) 

