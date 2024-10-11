#pragma once
#include "LoxCallable.h"

class ClockNative : LoxCallable{
public:
	std::any Call(Interpreter* interpreter,
		const std::vector<std::any>& arguments) override;
	int Arity() override;
};

