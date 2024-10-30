#include "LoxClass.h"
#include "LoxInstance.h"

LoxClass::LoxClass(const std::string& name){
	this->name = name;
}

std::any LoxClass::Call(Interpreter* interpreter, const std::vector<std::any>& arguments){
	LoxInstance* instance = new LoxInstance(this);
	return instance;
}

int LoxClass::Arity(){
	return 0;
}
