#pragma once
#include <string>
#include "LoxCallable.h"

struct LoxClass : LoxCallable {
public:
	LoxClass(const std::string& name);
	std::any Call(Interpreter* interpreter,
		const std::vector<std::any>& arguments) override;
	int Arity() override;
private:
	std::string name;
};

