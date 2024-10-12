#pragma once
#include "LoxCallable.h"
#include "Stmt.h"

class LoxFunction : LoxCallable{
public:
	LoxFunction(Function* decleration);
	std::any Call(Interpreter* interpreter,
		const std::vector<std::any>& arguments) override;
	int Arity() override;
	Function* decleration;
};

