#include "Interpreter.h"
#include "TokenType.h"
#include <string>
#include <iostream>
#include "cppLox.h"


void Interpreter::Interpret(const std::vector<Stmt*>& stmts) {
    try {
        for (const Stmt* stmt : stmts) {
            Execute(stmt);
        }
    }
    catch(RuntimeError error){
        ReportRuntimeError(error);
    }
}

std::any Interpreter::VisitLiteral(const Literal* literalExpr) {
    return literalExpr->data;
}

std::any Interpreter::VisitUnary(const Unary* unaryExpr) {
    std::any right = Evaluate(unaryExpr->right);
    switch (unaryExpr->op.type) {
        case MINUS: 
            CheckNumberOperand(unaryExpr->op, right);
            return -std::any_cast<double>(right);
        case BANG: return !IsTruthy(right);
    }
    // Unreachable
    return NULL;
}

std::any Interpreter::VisitBinary(const Binary* binaryExpr) {
    std::any left = Evaluate(binaryExpr->left);
    std::any right = Evaluate(binaryExpr->right);

    switch (binaryExpr->op.type) {
    case MINUS:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) - std::any_cast<double>(right);
    case SLASH:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) / std::any_cast<double>(right);
    case STAR:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) * std::any_cast<double>(right);
    case PLUS:
        if (left.type() == typeid(double) && right.type() == typeid(double)) {
            return std::any_cast<double>(left) + std::any_cast<double>(right);
        }
        if (left.type() == typeid(std::string) && right.type() == typeid(std::string)) {
            return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
        }
        throw RuntimeError(binaryExpr->op, "Operands must be two numbers or two strings.");
    case GREATER:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) > std::any_cast<double>(right);
    case GREATER_EQUAL:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) >= std::any_cast<double>(right);
    case LESS:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) < std::any_cast<double>(right);
    case LESS_EQUAL:
        CheckNumberOperands(binaryExpr->op, left, right);
        return std::any_cast<double>(left) <= std::any_cast<double>(right);
    case BANG_EQUAL: return !IsEqual(left, right);
    case EQUAL_EQUAL: return IsEqual(left, right);
    }
    // Unreachable
    return NULL;
}

std::any Interpreter::VisitGrouping(const Grouping* groupingExpr) {
    return Evaluate(groupingExpr->expr);
}

std::any Interpreter::VisitVariable(const Variable* variableExpr) {
    return environment.Get(variableExpr->name);
}

std::any Interpreter::VisitAssign(const Assign* assignExpr) {
    std::any value = Evaluate(assignExpr->value);
    environment.Assign(assignExpr->name, value);
    return value;
}

std::any Interpreter::Evaluate(const Expr* expr) {
    return expr->Accept(this);
}

bool Interpreter::IsTruthy(const std::any& value) const{
    if (!value.has_value()) return false; // nil
    if (value.type() == typeid(bool)) return std::any_cast<bool>(value);
    return true;
}

bool Interpreter::IsEqual(const std::any& left, const std::any& right) const{
    if (!left.has_value() && !right.has_value()) return true;

    if (!left.has_value() || !right.has_value()) return false;

    if (left.type() != right.type()) return false;

    if (left.type() == typeid(double))
        return std::any_cast<double>(left) == std::any_cast<double>(right);

    if (left.type() == typeid(std::string))
        return std::any_cast<std::string>(left) == std::any_cast<std::string>(right);
    
    if (left.type() == typeid(bool))
        return std::any_cast<bool>(left) == std::any_cast<bool>(right);

    // Unreachable
    return false;
}
void Interpreter::CheckNumberOperand(const Token& op, const std::any& rand) const{
    if (rand.type() == typeid(double)) return;
    throw RuntimeError(op, "Operand must be a number.");
}

void Interpreter::CheckNumberOperands(const Token& op, const std::any& left, const std::any& right) const{
    if (left.type() == typeid(double) && right.type() == typeid(double)) return;
    throw RuntimeError(op, "Operands must be numbers.");
}

std::string Interpreter::Stringify(const std::any& value) const{
    if (!value.has_value()) return "nil";
    if (value.type() == typeid(double)) return std::to_string(std::any_cast<double>(value));
    if (value.type() == typeid(bool)) return std::any_cast<bool>(value) ? "true" : "false";
    if (value.type() == typeid(std::string)) return std::any_cast<std::string>(value);
    // Unreachable
    return "";
}

void Interpreter::VisitExprStmt(const ExprStmt* exprStmt) {
    Evaluate(exprStmt->expr);
}

void Interpreter::VisitPrintStmt(const Print* printStmt) {
    std::any value = Evaluate(printStmt->expr);
    std::cout << Stringify(value) << std::endl;
}

void Interpreter::VisitVarStmt(const Var* varStmt) {
    std::any value = std::any();
    if (varStmt->initializer) value = Evaluate(varStmt->initializer);
    environment.Define(varStmt->name.lexeme, value);
}

void Interpreter::Execute(const Stmt* stmt) {
    stmt->Accept(this);
}

void Interpreter::ExecuteBlock(const std::vector<Stmt*> stmts, const Environment& environment) {
    Environment previous = this->environment;
    try {
        this->environment = environment;
        for (const Stmt* stmt : stmts) Execute(stmt);
    }
    catch (std::runtime_error e){
        std::cerr << "Error in ExecuteBlock(): " << e.what() << std::endl;
    }
    this->environment = previous;
}

void Interpreter::VisitBlockStmt(const Block* blockStmt) {
    ExecuteBlock(blockStmt->stmts, new Environment(environment));
}

RuntimeError::RuntimeError(const Token& token, const std::string& message){
    this->token = token;
    this->message = message;
}
