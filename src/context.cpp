/*
 * context.cpp
 *
 *  Created on: 21 апр. 2014 г.
 *      Author: artem
 */

#include "context.h"

namespace Doppio
{

Context::Context()
{
}

Context::~Context()
{
	_functions.clear();
	_variables.clear();
}

void Context::setFunction(std::string name, int argc, void* ptr)
{
	_functions[name] = FncPtr(name, argc, ptr);
}

void Context::setVariable(std::string name, double value)
{
	_variables[name] = value;
}


FncPtr* Context::getFunction(std::string name) const
{
	return NULL;
}

double Context::getVariable(std::string name) const
{
	return 0.0d;
}

} /* Doppio namespace */
