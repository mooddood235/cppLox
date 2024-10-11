#include "LoxCallable.h"

std::any LoxCallable::Call(Interpreter* interpreter, const std::vector<std::any>& arguments){
	return std::any();
}

int LoxCallable::Arity(){
	return 0;
}
