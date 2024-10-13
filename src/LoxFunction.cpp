#include "LoxFunction.h"
#include "Environment.h"

LoxFunction::LoxFunction(Function* decleration){
	this->decleration = decleration;
}

std::any LoxFunction::Call(Interpreter* interpreter, const std::vector<std::any>& arguments){
	Environment* environment = new Environment(interpreter->globals);

	for (int i = 0; i < decleration->params.size(); i++) {
		environment->Define(decleration->params[i].lexeme, arguments[i]);
	}
	try {
		interpreter->ExecuteBlock(decleration->body, environment);
	}
	catch (const ReturnException& e) {
		return e.value;
	}
	return std::any();
}
int LoxFunction::Arity() {
	return decleration->params.size();
}
