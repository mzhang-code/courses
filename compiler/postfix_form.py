#!/usr/bin/env python 
# -*- coding: utf-8 -*-

''' Execrcise of dragon book 2ed. 
    Chapter 2.5 "Translator for Simple Expression". 
''' 
import sys

def stream(s): 
    for c in s: 
        yield c
    yield '$'

def is_digit(c): 
    return ord('0') <= ord(c) <= ord('9')

class PostfixTranslator(object): 
    ''' The translator that parse infix expression and print postfix form. 
        LL(1) Grammar: 

            E       : term rest 

            rest    : + term { print '+' } rest 
                    | - term { print '-' } rest
                    | ε

            term    : 0 { print '0' } 
                    | 1 { print '1' } 
                      ... 
                    | 9 { print '9' } 

        e.g. 
            9-5+2 -> 95-2+
    '''
    def __init__(self): 
        self.buf = ''
        self.lookahead = '' 

    def translate(self, s): 
        self.buf = stream(s)
        self.lookahead = self.buf.next() 
        self.expr() 
        
    def expr(self): 
        self.term() 
        self.rest() 

    def rest(self): 
        if self.lookahead in '-+': 
            op = self.lookahead 
            self.match(op)
            self.term() 
            sys.stdout.write(op)
            self.rest() 
        else: 
            # reaching '$'
            pass 

    def term(self): 
        if is_digit(self.lookahead): 
            d = self.lookahead
            self.match(d)
            sys.stdout.write(d) 

    def match(self, c): 
        self.lookahead = self.buf.next() 

if __name__ == '__main__': 
    string = sys.argv[1] 
    translator = PostfixTranslator() 
    translator.translate(string) 

