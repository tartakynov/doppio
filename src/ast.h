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

#ifndef DOPPIO_AST_H_
#define DOPPIO_AST_H_

#include <vector>
#include <string>
#include <cmath>
#include "token.h"

class AstNode
{
public:
    virtual ~AstNode()
    {
        printf(")");
    }

protected:
    AstNode()
    {
        printf("(");
    }
};

/* E x p r e s s i o n s */
class Expression: public AstNode
{
public:
    Expression()
    {
    }

    virtual bool isConstant() const
    {
        return false;
    }
};

class AssignmentExpression: public Expression
{
private:
    Token::Type _operation;
    Expression* _target;
    Expression* _value;

public:
    AssignmentExpression(Token::Type operation, Expression* target,
            Expression* value) :
            _operation(operation), _target(target), _value(value)
    {
    }

    Expression* target() const
    {
        return _target;
    }
    Expression* value() const
    {
        return _value;
    }
};

class UnaryOperationExpression: public Expression
{
private:
    Token::Type _operation;
    Expression* _expression;

public:
    UnaryOperationExpression(Token::Type operation, Expression* expression) :
            _operation(operation), _expression(expression)
    {
    }

    Token::Type operation() const
    {
        return _operation;
    }
    Expression* expression() const
    {
        return _expression;
    }
};

class BinaryOperationExpression: public Expression
{
private:
    Token::Type _operation;
    Expression* _left;
    Expression* _right;

public:
    BinaryOperationExpression(Token::Type operation, Expression* left,
            Expression* right) :
            _operation(operation), _left(left), _right(right)
    {
    }

    Token::Type operation() const
    {
        return _operation;
    }
    Expression* left() const
    {
        return _left;
    }
    Expression* right() const
    {
        return _right;
    }
};

class FunctionExpression: public Expression
{
private:
    Expression* _identifier;
    std::vector<Expression*> _arguments;

public:
    FunctionExpression(Expression* identifier,
            std::vector<Expression*> arguments) :
            _identifier(identifier), _arguments(arguments)
    {
    }
};

class Identifier: public Expression
{
private:
    std::string _value;

public:
    Identifier(std::string value) :
            _value(value)
    {
    }
};

class Number: public Expression
{
private:
    Token::Type _type;
    union
    {
        double _real;
        long _integer;
    };

public:
    Number(double value) :
            _type(Token::NUMBER_FLOAT), _real(value)
    {
    }

    Number(long value) :
            _type(Token::NUMBER_INTEGER), _integer(value)
    {
    }

    Token::Type type() const
    {
        return _type;
    }

    bool isConstant() const
    {
        return true;
    }

    double real() const
    {
        return _type == Token::NUMBER_FLOAT ? _real : (double) _integer;
    }

    long integer() const
    {
        return _type == Token::NUMBER_INTEGER ? _integer : (long) _real;
    }

    friend Number* operator+(const Number &c1, const Number &c2)
    {
        if (c1.type() == Token::NUMBER_INTEGER
                && c2.type() == Token::NUMBER_INTEGER)
        {
            return new Number(c1.integer() + c2.integer());
        }
        return new Number(c1.real() + c2.real());
    }

    friend Number* operator-(const Number &c1, const Number &c2)
    {
        if (c1.type() == Token::NUMBER_INTEGER
                && c2.type() == Token::NUMBER_INTEGER)
        {
            return new Number(c1.integer() - c2.integer());
        }
        return new Number(c1.real() - c2.real());
    }

    friend Number* operator*(const Number &c1, const Number &c2)
    {
        if (c1.type() == Token::NUMBER_INTEGER
                && c2.type() == Token::NUMBER_INTEGER)
        {
            return new Number(c1.integer() * c2.integer());
        }
        return new Number(c1.real() * c2.real());
    }

    friend Number* operator/(const Number &c1, const Number &c2)
    {
        return new Number(c1.real() / c2.real());
    }

    friend Number* operator%(const Number &c1, const Number &c2)
    {
        if (c1.type() == Token::NUMBER_INTEGER
                && c2.type() == Token::NUMBER_INTEGER)
        {
            return new Number(c1.integer() % c2.integer());
        }
        double x = c1.real();
        double n = c2.real();
        return new Number(x - n * floor(x / n));
    }

    friend Number* operator^(const Number &c1, const Number &c2)
    {
        return new Number(pow(c1.real(), c2.real()));
    }
};

/* S t a t e m e n t s */
class Statement: public AstNode
{
public:
    virtual bool IsEmpty() const
    {
        return false;
    }
};

class ExpressionStatement: public Statement
{
private:
    Expression *_expression;

public:
    Expression* expression() const
    {
        return _expression;
    }
};

#endif /* DOPPIO_AST_H_ */
