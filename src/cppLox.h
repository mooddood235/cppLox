#pragma once
#include "Token.h"
#include "Interpreter.h"

void Error(int line, const std::string& message);
void Error(const Token& token, const std::string& message);
void Report(int line, const std::string& where, const std::string& message);
void ReportRuntimeError(const RuntimeError& error);