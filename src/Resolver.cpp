#include "Resolver.h"
#include "cppLox.h"

Resolver::Resolver(Interpreter* interpreter){
	this->interpreter = interpreter;
}

void Resolver::Resolve(const std::vector<Stmt*> statements){
	for (const Stmt* stmt : statements) Resolve(stmt);
}

void Resolver::Resolve(const Stmt* stmt){
	stmt->Accept(this);
}

void Resolver::Resolve(const Expr* expr){
	expr->Accept(this);
}

void Resolver::ResolveFunction(const Function* functionStmt){
	BeginScope();
	for (const Token& param : functionStmt->params) {
		Declare(param);
		Define(param);
	}
	Resolve(functionStmt->body);
	EndScope();
}

void Resolver::BeginScope(){
	scopes.emplace();
}

void Resolver::EndScope(){
	scopes.pop();
}

void Resolver::Declare(const Token& name){
	if (scopes.empty()) return;
	std::unordered_map<std::string, bool>* scope = scopes.top();
	(*scope)[name.lexeme] = false;
}

void Resolver::Define(const Token& name){
	if (scopes.empty()) return;
	(*scopes.top())[name.lexeme] = true;
}

void Resolver::ResolveLocal(const Expr* expr, const Token& name){
	for (int i = scopes.size() - 1; i >= 0; i--) {
		if (scopes._Get_container()[i]->contains(name.lexeme)) {
			interpreter->Resolve(expr, scopes.size() - 1 - i);
			return;
		}
	}
}

std::any Resolver::VisitLiteral(const Literal* literalExpr){}

std::any Resolver::VisitUnary(const Unary* unaryExpr){
	Resolve(unaryExpr->right);
}

std::any Resolver::VisitBinary(const Binary* binaryExpr){
	Resolve(binaryExpr->left);
	Resolve(binaryExpr->right);
}

std::any Resolver::VisitGrouping(const Grouping* groupingExpr){
	Resolve(groupingExpr->expr);
}

std::any Resolver::VisitVariable(const Variable* variableExpr){
	if (!scopes.empty() && !scopes.top()->at(variableExpr->name.lexeme)) {
		Error(variableExpr->name, "Can't read local variable in its own initializer");
	}
	ResolveLocal(variableExpr, variableExpr->name);
}

std::any Resolver::VisitAssign(const Assign* assignExpr){
	Resolve(assignExpr->value);
	ResolveLocal(assignExpr, assignExpr->name);
}

std::any Resolver::VisitLogical(const Logical* logicalExpr){
	Resolve(logicalExpr->left);
	Resolve(logicalExpr->right);
}

std::any Resolver::VisitCall(const Call* callExpr){
	Resolve(callExpr->callee);
	for (const Expr* arg : callExpr->arguments) Resolve(arg);
}

void Resolver::VisitExprStmt(const ExprStmt* exprStmt){
	Resolve(exprStmt->expr);
}

void Resolver::VisitPrintStmt(const Print* printStmt){
	Resolve(printStmt->expr);
}

void Resolver::VisitVarStmt(const Var* varStmt){
	Declare(varStmt->name);
	if (varStmt->initializer) Resolve(varStmt->initializer);
	Define(varStmt->name);
}

void Resolver::VisitBlockStmt(const Block* blockStmt){
	BeginScope();
	Resolve(blockStmt->stmts);
	EndScope();
}

void Resolver::VisitIfStmt(const If* ifStmt){
	Resolve(ifStmt->conditional);
	Resolve(ifStmt->thenBranch);
	if (ifStmt->elseBranch) Resolve(ifStmt->elseBranch);
}

void Resolver::VisitWhileStmt(const While* whileStmt){
	Resolve(whileStmt->condition);
	Resolve(whileStmt->body);
}

void Resolver::VisitFunctionStmt(const Function* functionStmt){
	Declare(functionStmt->name);
	Define(functionStmt->name);
	ResolveFunction(functionStmt);
}

void Resolver::VisitReturnStmt(const Return* returnStmt){
	if (returnStmt->value) Resolve(returnStmt->value);
}
