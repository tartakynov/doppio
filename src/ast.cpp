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

#include "ast.h"

namespace Doppio
{

inline double UnaryOperationExpression::evaluate(Context* context) const
{
	if (_operation == Token::FACTORIAL)
	{
		int result = 1;
		for (int i = 2; i <= _expression->evaluate(context); i++)
		{
			result *= i;
		}

		return result;
	}

	ASSERT_NOT_REACHED();
	return 0; // it makes compiler happy
}

inline double BinaryOperationExpression::evaluate(Context* context) const
{
	switch ((int)_operation)
	{
	case Token::ADD:
		return _left->evaluate(context) + _right->evaluate(context);
	case Token::SUB:
		return _left->evaluate(context) - _right->evaluate(context);
	case Token::MUL:
		return _left->evaluate(context) * _right->evaluate(context);
	case Token::DIV:
		return _left->evaluate(context) / _right->evaluate(context);
	case Token::POW:
		return pow(_left->evaluate(context), _right->evaluate(context));
	case Token::MOD:
		return fmod(_left->evaluate(context), _right->evaluate(context));
	default:
		ASSERT_NOT_REACHED();
	}

	return 0; // it makes compiler happy
}

inline double FunctionExpression::evaluate(Context* context) const
{
	Identifier *id = (Identifier *)this->_identifier;
	if (id)
	{
		FncPtr *ptr = context->getFunction(id->getValue());

		ASSERT(ptr->argc >= 0 && ptr->argc <= 9);

		double argv[ptr->argc];
		for (int i = 0; i < ptr->argc; i++)
		{
			argv[i] = this->_arguments[i]->evaluate(context);
		}

		if (ptr)
		{
			switch (ptr->argc)
			{
			case 0:
				return ((Func_Ret_ARG0)ptr->ptr)();
			case 1:
				return ((Func_Ret_ARG1)ptr->ptr)(argv[0]);
			case 2:
				return ((Func_Ret_ARG2)ptr->ptr)(argv[0], argv[1]);
			case 3:
				return ((Func_Ret_ARG3)ptr->ptr)(argv[0], argv[1], argv[2]);
			case 4:
				return ((Func_Ret_ARG4)ptr->ptr)(argv[0], argv[1], argv[2], argv[3]);
			case 5:
				return ((Func_Ret_ARG5)ptr->ptr)(argv[0], argv[1], argv[2], argv[3], argv[4]);
			case 6:
				return ((Func_Ret_ARG6)ptr->ptr)(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
			case 7:
				return ((Func_Ret_ARG7)ptr->ptr)(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
			case 8:
				return ((Func_Ret_ARG8)ptr->ptr)(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
			case 9:
				return ((Func_Ret_ARG9)ptr->ptr)(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
			default:
				ASSERT_NOT_REACHED();
			}
		}
	}

	return 0; // it makes compiler happy
}

inline double Identifier::evaluate(Context* context) const
{
	return context->getVariable(_value);
}

inline double Number::evaluate(Context* context) const
{
	return real();
}

} /* Doppio namespace */
