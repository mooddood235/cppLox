#pragma once
#include <unordered_map>
#include <string>
#include <any>
#include "Token.h"

class Environment{
public:
	Environment();
	Environment(const Environment& other);
	Environment(Environment* enclosing);
	void Define(const std::string& name, const std::any& value);
	void Assign(const Token& name, const std::any& value);
	std::any Get(const Token& name) const;
private:
	Environment* enclosing;
	std::unordered_map<std::string, std::any> values =
		std::unordered_map<std::string, std::any>();
};

