#include "Environment.h"
#include "Interpreter.h"

Environment::Environment(){
	enclosing = nullptr;
}

Environment::Environment(Environment* enclosing){
	this->enclosing = enclosing;
}

void Environment::Define(const std::string& name, const std::any& value) {
	values[name] = value;
}

void Environment::Assign(const Token& name, const std::any& value){
	if (values.contains(name.lexeme)) {
		values[name.lexeme] = value;
		return;
	}
	if (enclosing) {
		enclosing->Assign(name, value);
		return;
	}
	throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

std::any Environment::Get(const Token& name) const{
	if (values.contains(name.lexeme)) return values.at(name.lexeme);
	if (enclosing) return enclosing->Get(name);
	throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

std::any Environment::GetAt(int distance, const std::string& name){
	return Ancestor(distance)->values.at(name);
}

const Environment* Environment::Ancestor(int distance) const{
	const Environment* environment = this;

	for (int i = 0; i < distance; i++)
		environment = environment->enclosing;

	return environment;
}
