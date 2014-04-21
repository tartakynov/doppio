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

#ifndef DOPPIO_SCANNER_H_
#define DOPPIO_SCANNER_H_

#include <cstdlib>
#include <cctype>
#include <cstring>
#include "token.h"

namespace Doppio
{

class Scanner
{
public:
    Scanner(const char *input, size_t length);
    virtual ~Scanner();

    Token::Type next();
    Token::Type peek() const;
    Token::Type current() const;
    Token currentToken() const;

protected:
    const char* _beg;
    const char* _cur;
    const char* _end;

private:
    Token _current;
    Token _next;
    char _c0;

    inline void advance();
    inline Token::Type select(Token::Type type);
    Token::Type scanIdentifierOrKeyword();
    Token::Type scanNumber();
    void scan();
};

} /* Doppio namespace */

#endif /* DOPPIO_SCANNER_H_ */
