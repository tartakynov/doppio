/*
 * context.h
 *
 *  Created on: 21 апр. 2014 г.
 *      Author: artem
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <map>
#include <string>

typedef double (*Func_Ret_ARG0)(void);
typedef double (*Func_Ret_ARG1)(double);
typedef double (*Func_Ret_ARG2)(double, double);
typedef double (*Func_Ret_ARG3)(double, double, double);
typedef double (*Func_Ret_ARG4)(double, double, double, double);
typedef double (*Func_Ret_ARG5)(double, double, double, double, double);
typedef double (*Func_Ret_ARG6)(double, double, double, double, double, double);
typedef double (*Func_Ret_ARG7)(double, double, double, double, double, double, double);
typedef double (*Func_Ret_ARG8)(double, double, double, double, double, double, double, double);
typedef double (*Func_Ret_ARG9)(double, double, double, double, double, double, double, double, double);

namespace Doppio
{

struct FncPtr
{
	inline FncPtr()
		: name(0), argc(0), ptr(0)
	{
	}

	inline FncPtr(std::string name, int argc, void* ptr)
		: name(name), argc(argc), ptr(ptr)
	{
	}

	std::string name;
	int argc;
	void *ptr;
};

class Context {
private:
	std::map<std::string, double> _variables;
	std::map<std::string, FncPtr> _functions;

public:
	Context();
	virtual ~Context();

	void setFunction(std::string name, int argc, void *ptr);
	FncPtr *getFunction(std::string name) const;

	void setVariable(std::string name, double value);
	double getVariable(std::string name) const;
};

} /* Doppio namespace */

#endif /* CONTEXT_H_ */
