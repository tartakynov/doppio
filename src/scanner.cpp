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

#include "scanner.h"

Scanner::Scanner(const char* input, size_t length)
{
    _beg = input;
    _cur = input;
    _end = input + length;
    _c0 = *input;
    scan();
}

Scanner::~Scanner()
{
}

Token::Type Scanner::next()
{
    _current = _next;
    scan();
    return _current.type;
}

Token::Type Scanner::peek() const
{
    return _next.type;
}

Token::Type Scanner::current() const
{
    return _current.type;
}

Token Scanner::currentToken() const
{
    return _current;
}

void Scanner::scan()
{
    while (isspace(_c0) && _cur < _end)
    {
        advance();
    }

    Token::Type tokenType;
    _next.start = _cur - _beg;
    if (_cur >= _end)
    {
        tokenType = select(Token::EOS);
    }
    else
    {
        switch (_c0)
        {
        case '=':
            tokenType = select(Token::ASSIGN);
            break;

        case '!':
            tokenType = select(Token::FACTORIAL);
            break;

        case '+':
            tokenType = select(Token::ADD);
            break;

        case '-':
            tokenType = select(Token::SUB);
            break;

        case '*':
            tokenType = select(Token::MUL);
            break;

        case '%':
            tokenType = select(Token::MOD);
            break;

        case '/':
            tokenType = select(Token::DIV);
            break;

        case '^':
            tokenType = select(Token::POW);
            break;

        case ';':
            tokenType = select(Token::SEMICOLON);
            break;

        case ',':
            tokenType = select(Token::COMMA);
            break;

        case '(':
            tokenType = select(Token::LPAREN);
            break;

        case ')':
            tokenType = select(Token::RPAREN);
            break;

        default:
            if (isalpha(_c0) || _c0 == '_')
            {
                tokenType = scanIdentifierOrKeyword();
            }
            else if (isdigit(_c0) || _c0 == '.')
            {
                tokenType = scanNumber();
            }
            else
            {
                tokenType = select(Token::ILLEGAL);
            }
            break;
        }
    }
    _next.end = _cur - _beg;
    _next.type = tokenType;
}

Token::Type Scanner::scanIdentifierOrKeyword()
{
    ASSERT(_cur < _end);
    const char *input = _cur;
    while (isalpha(_c0) || isdigit(_c0) || _c0 == '_')
    {
        advance();
    }

    Token::Type tokenType = Token::IDENTIFIER;
    size_t inputLength = _cur - input;
#define T(a, b, c)
#define K(name, keyword, precedence)                                        \
    {                                                                       \
        size_t keywordLength = sizeof(keyword) - 1;                         \
        if (inputLength == keywordLength && input[1] == keyword[1]          \
                && (keywordLength <= 2 || input[2] == keyword[2])           \
                && (keywordLength <= 3 || input[3] == keyword[3])           \
                && (keywordLength <= 4 || input[4] == keyword[4])           \
                && (keywordLength <= 5 || input[5] == keyword[5])           \
                && (keywordLength <= 6 || input[6] == keyword[6])           \
                && (keywordLength <= 7 || input[7] == keyword[7])           \
                && (keywordLength <= 8 || input[8] == keyword[8])           \
                && (keywordLength <= 9 || input[9] == keyword[9]))          \
        {                                                                   \
            tokenType = Token::name;                                        \
        }                                                                   \
    }
    TOKEN_LIST(T, K)
#undef T
#undef K

    return tokenType;
}

Token::Type Scanner::scanNumber()
{
    Token::Type tokenType = Token::NUMBER_INTEGER;

    // read digits
    while (isdigit(_c0) && _cur < _end)
    {
        advance();
    }

    // read fraction
    if (_cur < _end && _c0 == '.')
    {
        tokenType = Token::NUMBER_FLOAT;
        advance();
        while (isdigit(_c0) && _cur < _end)
        {
            advance();
        }
    }

    // read exponent, if any
    if (_c0 == 'e' || _c0 == 'E')
    {
        advance();
        if (_c0 == '+' || _c0 == '-')
        {
            advance();
        }
        if (isdigit(_c0))
        {
            while (isdigit(_c0) && _cur < _end)
            {
                advance();
            }
        }
        else
        {
            // we must have at least one decimal digit after 'e'/'E'
            tokenType = Token::ILLEGAL;
        }
    }

    return tokenType;
}

Token::Type Scanner::select(Token::Type type)
{
    advance();
    return type;
}

void Scanner::advance()
{
    _c0 = *(++_cur);
}
