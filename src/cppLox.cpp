#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "cppLox.h"
#include "Scanner.h"
#include "Parser.h"
#include "Expr.h"
#include "Stmt.h"
#include "Resolver.h"

void RunFile(const std::string& path);
void RunPrompt();
void Run(const std::string& source);


bool hadError = false;
bool hadRuntimeError = false;

Interpreter interpreter = Interpreter();

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: cppLox [script]" << std::endl;
        return 1;
    }
    else if (argc == 2) RunFile(argv[1]);
    else RunPrompt();
    return 0;
}
void RunFile(const std::string& path) {
    std::ifstream fileStream(path);

    if (!fileStream) {
        std::cerr << "Could not open file at path [" << path << "]" << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();

    Run(buffer.str());
    if (hadError || hadRuntimeError) exit(1);
}
void RunPrompt() {
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "exit") break;
        Run(line);
        hadError = false;
    }
}
void Run(const std::string& source) {
    Scanner scanner = Scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();

    Parser parser = Parser(tokens);
    std::vector<Stmt*> stmts = parser.Parse();

    if (hadError) return;

    Resolver resolver(&interpreter);
    resolver.Resolve(stmts);

    interpreter.Interpret(stmts);
}
void Error(int line, const std::string& message) {
    Report(line, "", message);
}
void Report(int line, const std::string& where, const std::string& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}
void ReportRuntimeError(const RuntimeError& error){
    std::cerr << error.message << "\n[line " << error.token.line << "]" << std::endl;
    hadRuntimeError = true;
}
void Error(const Token& token, const std::string& message) {
    if (token.type == _EOF) {
        Report(token.line, " at end", message);
    }
    else {
        Report(token.line, " at '" + token.lexeme + "'", message);
    }
}