//
//  Scanner.cpp
//  Interpreter
//
//  Created by Juan Trejo on 10/8/17.
//  Copyright © 2017 PocketMatlab. All rights reserved.
//

#include "Scanner.hpp"

Scanner::Scanner(std::string input) {
    _in = std::stringstream(input);
}

Token Scanner::getNextToken() {
    
    while(_in.peek() != std::char_traits<char>::eof()) {
        
        if(_in.peek() == ' ') {
            skipWhitespace();
            if (_in.peek() == std::char_traits<char>::eof()) break;
        }
        
        if(isdigit(_in.peek())) {
            return Token(Integer, getIntegerStr());
        }
        
        if(_in.peek() == '+') {
            return Token(Plus, std::string(1, _in.get()));
        }
        
        if(_in.peek() == '-') {
            return Token(Minus, std::string(1, _in.get()));
        }
        
        if(_in.peek() == '*') {
            return Token(Mul, std::string(1, _in.get()));
        }
        
        if(_in.peek() == '/') {
            return Token(Div, std::string(1, _in.get()));
        }
        
        if(_in.peek() == '(') {
            return Token(LParen, std::string(1, _in.get()));
        }
        
        if(_in.peek() == ')') {
            return Token(RParen, std::string(1, _in.get()));
        }
        
        throwError();
    }
    return Token(eof, "None");
}

void Scanner::skipWhitespace() {
    while(_in.peek() == ' '){
        _in.ignore();
    }
}

std::string Scanner::getIntegerStr() {
    std::string res = "";
    while(!_in.eof() && isdigit(_in.peek())) {
        res += _in.get();
    }
    return res;
}

void Scanner::throwError() {
    throw std::invalid_argument("Invalid character");
}
