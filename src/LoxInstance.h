#pragma once
#include "LoxClass.h"

struct LoxInstance{
public:
	LoxInstance(LoxClass* klass);
private:
	LoxClass* klass;
};

