#pragma once
#include "LoxCallable.h"
#include "Environment.h"
#include "Stmt.h"

class LoxFunction : LoxCallable{
public:
	LoxFunction(Function* decleration, Environment* closure);
	std::any Call(Interpreter* interpreter,
		const std::vector<std::any>& arguments) override;
	int Arity() override;
	Environment* closure;
	Function* decleration;
};

