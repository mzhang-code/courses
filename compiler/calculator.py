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

            term    : 0  
                    | 1  
                      ... 
                    | 9  

        e.g. 
            9-5+2 -> 6
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
            r = self.rest(val)
            if r: 
                return r
            else: 
                return val

        elif self.lookahead == '-': 
            self.match('-')
            val = left_oprand - self.term()
            r = self.rest(val)
            if r: 
                return r
            else: 
                return val 

        else: 
            # reaching '$'
            return '' 

    def term(self): 
        if is_digit(self.lookahead): 
            d = self.lookahead
            self.match(d)
            return ord(d) - ord('0') 
        else: 
            raise ValueError('digit expected') 

    def match(self, c): 
        self.lookahead = self.buf.next() 

if __name__ == '__main__': 
    string = sys.argv[1] 
    calculator = SimpleDigitCalculator() 
    print calculator.calc(string) 

