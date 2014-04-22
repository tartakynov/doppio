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

#ifndef DOPPIO_ASSERTS_H_
#define DOPPIO_ASSERTS_H_

#include <cstdio>
#include <cstdlib>

namespace Doppio
{

void assertionFailure(const char* file, const char* expression, int line);

#define ASSERT(exp) do { if (!(exp)) assertionFailure(__FILE__, #exp, __LINE__); } while (0)

#define ASSERT_NOT_REACHED() do { assertionFailure(__FILE__, "Reached unreachable", __LINE__); } while (0)

} /* Doppio namespace */

#endif /* DOPPIO_ASSERTS_H_ */

