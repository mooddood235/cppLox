#pragma once
#include <any>
#include "Interpreter.h"

class LoxCallable {
public:
	virtual std::any Call(Interpreter* interpreter,
		const std::vector<std::any>& arguments);
	virtual int Arity();
};
