//
//  TestInterpreter.cpp
//  Interpreter
//
//  Created by Juan Trejo on 10/1/17.
//  Copyright © 2017 PocketMatlab. All rights reserved.
//

#include <cstdio>
#include "gtest/gtest.h"
#include "Token.hpp"
#include "Interpreter.hpp"

/////////////////////////
// MARK: Token
/////////////////////////

TEST(test_token, token_construct_0) {
    Token myToken = Token();
    ASSERT_EQ(myToken.toString(), "Token(EOF, None)");
}

TEST(test_token, token_construct_1) {
    Token myToken(Integer, "10");
    ASSERT_EQ(myToken.toString(), "Token(INTEGER, 10)");
}

TEST(test_token, token_construct_2) {
    Token myToken(Plus, "+");
    ASSERT_EQ(myToken.toString(), "Token(BINARY_OP, +)");
}

TEST(test_token, token_construct_3) {
    Token myToken(Minus, "-");
    ASSERT_EQ(myToken.toString(), "Token(BINARY_OP, -)");
}

TEST(test_token, token_construct_4) {
    Token myToken(eof, "EOF");
    ASSERT_EQ(myToken.toString(), "Token(EOF, None)");
}


///////////////////////////////
// MARK: Scanner
///////////////////////////////

TEST(test_scanner, scanner_next_token_1) {
    Scanner* scanner = new Scanner("2");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(INTEGER, 2)");
}

TEST(test_scanner, scanner_next_token_2) {
    Scanner* scanner = new Scanner("23424");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(INTEGER, 23424)");
}

TEST(test_scanner, scanner_next_token_3) {
    Scanner* scanner = new Scanner("    424+");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(INTEGER, 424)");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(BINARY_OP, +)");
}

TEST(test_scanner, scanner_next_token_4) {
    Scanner* scanner = new Scanner("    424 +  239  ");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(INTEGER, 424)");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(BINARY_OP, +)");
    ASSERT_EQ(scanner->getNextToken().toString(), "Token(INTEGER, 239)");
}

///////////////////////////////
// MARK: Parser
///////////////////////////////

TEST(test_parser, parser_parse_1) {
    Scanner* s = new Scanner("2");
    Parser* parser = new Parser(s);
    Node* tree = parser->parse();
    printTree(tree, 3);
}

TEST(test_parser, parser_parse_2) {
    Scanner* s = new Scanner("2+2");
    Parser* parser = new Parser(s);
    Node* tree = parser->parse();
    printTree(tree, 3);
}

TEST(test_parser, parser_parse_3) {
    Scanner* s = new Scanner("2 + 2 ");
    Parser* parser = new Parser(s);
    Node* tree = parser->parse();
    printTree(tree, 3);
}

TEST(test_parser, parser_parse_4) {
    Scanner* s = new Scanner(" 2 * 7 + 3 ");
    Parser* parser = new Parser(s);
    Node* tree = parser->parse();
    printTree(tree, 3);
}

TEST(test_parser, parser_parse_5) {
    Scanner* s = new Scanner("7 + 3 * (10 / (12 / (3 + 1) - 1))");
    Parser* parser = new Parser(s);
    Node* tree = parser->parse();
    printTree(tree, 3);
}

//////////////////////////////
// MARK: Interpreter
//////////////////////////////

TEST(test_interp, interp_express_sum_1) {
    Scanner* s = new Scanner("1 + 1");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 2);
}

TEST(test_interp, interp_express_sum_2) {
    Scanner* s = new Scanner("9 + 19");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 28);
}

TEST(test_interp, interp_express_sum_3) {
    Scanner* s = new Scanner("0  +  0");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 0);
}

TEST(test_interp, interp_express_sub_1) {
    Scanner* s = new Scanner(" 2 - 1  ");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 1);
}

TEST(test_interp, interp_express_sub_2) {
    Scanner* s = new Scanner("15  -  5");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 10);
}

TEST(test_interp, interp_express_mult_1) {
    Scanner* s = new Scanner("2 * 14");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 28);
}

TEST(test_interp, interp_express_mult_2) {
    Scanner* s = new Scanner("15 * 5");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 75);
}

TEST(test_interp, interp_express_div_1) {
    Scanner* s = new Scanner(" 28 /  14");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 2);
}

TEST(test_interp, interp_express_div_2) {
    Scanner* s = new Scanner("15 / 5");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 3);
}

//////////////////////////////
// MARK: Interpreter_OperationStr
//////////////////////////////

TEST(test_interp, interp_express_short_1) {
    Scanner* s = new Scanner("3");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 3);
}

TEST(test_interp, interp_express_long_1) {
    Scanner* s = new Scanner("15 + 5 - 6 + 11 - 13 - 2");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 10);
}

TEST(test_interp, interp_express_long_2) {
    Scanner* s = new Scanner("10 * 4  * 2 * 3 / 8");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 30);
}

TEST(test_interp, interp_express_mix_1) {
    Scanner* s = new Scanner("14 + 2 * 3 - 6 / 2");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 17);
}

TEST(test_interp, interp_express_paren_1) {
    Scanner* s = new Scanner("(1 + 1)");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 2);
}

TEST(test_interp, interp_express_paren_2) {
    Scanner* s = new Scanner("7 + 3 * (10 / (12 / (3 + 1) - 1))");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 22);
}

TEST(test_interp, interp_express_paren_3) {
    Scanner* s = new Scanner("7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 10);
}

TEST(test_interp, interp_express_paren_4) {
    Scanner* s = new Scanner("7 + (((3 + 2)))");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_EQ(myInterp.interpret(), 12);
}

TEST(test_interp, interp_express_exept_4) {
    Scanner* s = new Scanner("++0");
    Parser*  p = new Parser(s);
    Interpreter myInterp(p);
    ASSERT_THROW(myInterp.interpret(), std::invalid_argument);
}

