/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "parser.h"

namespace Doppio
{

Parser::Parser(const char *input, size_t length) :
        Scanner(input, length)
{
}

Parser::~Parser()
{
}

void Parser::expect(Token::Type expectedToken)
{
    if (next() != expectedToken)
    {
        unexpectedToken();
    }
}

void Parser::unexpectedToken()
{
    // TODO переделать
    printf("unexpected token: %s", Token::Name(current()));
    exit(0);
}

void Parser::error(const char *msg)
{
    // TODO переделать
    printf(msg);
    exit(0);
}

Expression* Parser::parseExpression()
{
    /*
     * expression:   additive_expression;
     */
    return parseAdditiveExpression();
}

Expression* Parser::parseBinaryExpression(int prec)
{
    /*
     * additive_expression:
     *      (multiplicative_expression) ('+' multiplicative_expression | '-' multiplicative_expression)*
     *
     * multiplicative_expression:
     *      (postfix_expression) ('*' postfix_expression | '/' postfix_expression | '%' postfix_expression | '^' postfix_expression)*
     */
    ASSERT(prec >= 4);
    Expression* result = parsePostfixExpression();
    for (int prec1 = Token::Precedence(peek()); prec1 >= prec; prec1--)
    {
        while (Token::Precedence(peek()) == prec1)
        {
            Token::Type operation = next();
            Expression* right = parseBinaryExpression(prec1 + 1);
            if (result && result->isConstant() && right && right->isConstant())
            {
                Number* x = (Number *) result;
                Number* y = (Number *) right;
                switch (operation)
                {
                case Token::ADD:
                    result = *x + *y;
                    break;
                case Token::SUB:
                    result = *x - *y;
                    break;
                case Token::MUL:
                    result = *x * *y;
                    break;
                case Token::DIV:
                    result = *x / *y;
                    break;
                case Token::MOD:
                    result = *x % *y;
                    break;
                case Token::POW:
                    result = *x ^ *y;
                    break;
                default:
                    break;
                }
                delete x;
                delete y;
            }
            else
            {
                result = new BinaryOperationExpression(operation, result,
                        right);
            }
        }
    }
    return result;
}

Expression* Parser::parsePostfixExpression()
{
    /* postfix_expression:
     *      primary_expression ( arguments_expression | '!' )*;
     */
    Expression* result = parsePrimaryExpression();
    while (true)
    {
        switch (peek())
        {
        case Token::LPAREN:
            result = new FunctionExpression(result, parseArgumentsExpression());
            break;
        case Token::FACTORIAL:
            if (result->isConstant())
            {
                // TODO проверить что константа или переменная - это целое число
                if (current() == Token::NUMBER_INTEGER)
                {
                    // TODO реализовать быстрые алгоритмы вычисления факториала целых и дробных чисел
                    long val = 1;
                    for (int i = 2; i <= ((Number *)result)->integer(); i++)
                    {
                        val *= i;
                    }
                    delete result;
                    result = new Number(val);
                }
                else
                {
                    error("Factorial can be calculated only for integers");
                }
            }
            else
            {
                result = new UnaryOperationExpression(Token::FACTORIAL, result);
            }
            next();
            break;
        default:
            return result;
        }
    }
    return NULL; // make compiler happy
}

Expression* Parser::parsePrimaryExpression()
{
    /*
     * primary_expression: IDENTIFIER | INT | FLOAT | '(' expression ')'
     */
    next();
    Token token = currentToken();
    switch (token.type)
    {
    case Token::IDENTIFIER:
        return new Identifier(std::string(_beg + token.start, _beg + token.end));
    case Token::NUMBER_FLOAT:
        return new Number(strtod(_beg + token.start, NULL));
    case Token::NUMBER_INTEGER:
        return new Number(strtol(_beg + token.start, NULL, 10));
    case Token::LPAREN:
        return parseExpression();
    default:
        unexpectedToken();
        break;
    }
    return NULL; // make compiler happy
}

std::vector<Expression*> Parser::parseArgumentsExpression()
{
    /*
     * arguments_expression:  '(' additive_expression (',' additive_expression)* ')' | '(' ')';
     */
    std::vector<Expression*> args;
    bool done = (peek() == Token::RPAREN);
    expect(Token::LPAREN);
    while (!done)
    {
        Expression* argument = parseAdditiveExpression();
        args.push_back(argument);
        done = (peek() == Token::RPAREN);
        // TODO check if too many arguments
        if (!done)
        {
            expect(Token::COMMA);
        }
    }
    expect(Token::RPAREN);
    return args;
}

} /* Doppio namespace */
