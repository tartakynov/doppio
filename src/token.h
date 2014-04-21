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

#ifndef DOPPIO_TOKEN_H_
#define DOPPIO_TOKEN_H_

#include "asserts.h"

namespace Doppio
{

#define TOKEN_LIST(T, K)                                                  \
    /* End of source indicator. */                                        \
    T(EOS, "EOS", 0)                                                      \
                                                                          \
    /* Punctuators. */                                                    \
    T(LPAREN, "(", 0)                                                     \
    T(RPAREN, ")", 0)                                                     \
    T(SEMICOLON, ";", 0)                                                  \
                                                                          \
    /* Assignment operators. */                                           \
    /* IsAssignmentOp() relies on */                                      \
    /* this block of enum values being contiguous and sorted in the */    \
    /* same order! */                                                     \
    T(INIT_VAR, "=init_var", 2)  /* AST-use only. */                      \
    T(INIT_CONST, "=init_const", 2)  /* AST-use only. */                  \
    T(ASSIGN, "=", 2)                                                     \
                                                                          \
    /* Binary operators sorted by precedence. */                          \
    /* IsBinaryOp() relies on this block of enum values */                \
    /* being contiguous and sorted in the same order! */                  \
    T(COMMA, ",", 1)                                                      \
    T(ADD, "+", 12)                                                       \
    T(SUB, "-", 12)                                                       \
    T(MUL, "*", 13)                                                       \
    T(DIV, "/", 13)                                                       \
    T(MOD, "%", 13)                                                       \
    T(POW, "^", 13)                                                       \
                                                                          \
    /* Unary operators. */                                                \
    /* IsUnaryOp() relies on this block of enum values */                 \
    /* being contiguous and sorted in the same order! */                  \
    T(FACTORIAL, "!", 0)                                                  \
                                                                          \
    /* Literals. */                                                       \
    T(NUMBER_INTEGER, NULL, 0)                                            \
    T(NUMBER_FLOAT, NULL, 0)                                              \
                                                                          \
    /* Keywords. */                                                       \
    K(INT, "int", 0)                                                      \
    K(LONG, "long", 0)                                                    \
    K(FLOAT, "float", 0)                                                  \
    K(DOUBLE, "double", 0)                                                \
    K(CONST, "const", 0)                                                  \
                                                                          \
    /* Identifiers (not keywords or future reserved words). */            \
    T(IDENTIFIER, NULL, 0)                                                \
                                                                          \
    /* Illegal token - not able to scan. */                               \
    T(ILLEGAL, "ILLEGAL", 0)                                              \
                                                                          \
    /* Scanner-internal use only. */                                      \
    T(WHITESPACE, NULL, 0)

struct Token
{
public:
#define T(name, string, precedence) name,
    enum Type
    {
        TOKEN_LIST(T, T)NUM_TOKENS
    };
#undef T

    Type type;

    size_t start;

    size_t end;

    // Returns a string corresponding to the C++ token name
    // (e.g. "LPAREN" for the token LPAREN).
    static const char* Name(Type type)
    {
        ASSERT(type < NUM_TOKENS);
        return tokenName[type];
    }

    // Returns a string corresponding to the token string
    // (.e., "(" for the token LPAREN) or NULL if the token doesn't
    // have a string (e.g. an IDENTIFIER).
    static const char* const String(Type type)
    {
        ASSERT(type < NUM_TOKENS);
        return tokenString[type];
    }

    // Returns the precedence > 0 for binary and compare
    // operators; returns 0 otherwise.
    static int Precedence(Type type)
    {
        ASSERT(type < NUM_TOKENS);
        return tokenPrecedence[type];
    }

    static bool IsKeyword(Type type)
    {
        ASSERT(type < NUM_TOKENS);
        return tokenIsKeyword[type];
    }

private:
    static const char* const tokenName[NUM_TOKENS];
    static const char* const tokenString[NUM_TOKENS];
    static const bool tokenIsKeyword[NUM_TOKENS];
    static const int tokenPrecedence[NUM_TOKENS];
};

} /* Doppio namespace */

#endif /* DOPPIO_TOKEN_H_ */
