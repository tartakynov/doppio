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

#include "token.h"

#define T(name, string, precedence) #name,
const char* const Token::tokenName[NUM_TOKENS] =
{ TOKEN_LIST(T, T) };
#undef T

#define T(name, string, precedence) string,
const char* const Token::tokenString[NUM_TOKENS] =
{ TOKEN_LIST(T, T) };
#undef T

#define T(name, string, precedence) precedence,
const int Token::tokenPrecedence[NUM_TOKENS] =
{ TOKEN_LIST(T, T) };
#undef T

#define T(a, b, c) false,
#define K(a, b, c) true,
const bool Token::tokenIsKeyword[] =
{ TOKEN_LIST(T, K) };
#undef T
#undef K

