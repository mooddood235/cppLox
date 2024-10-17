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
			interpreter.Resolve(expr, scopes.size() - 1 - i);
			return;
		}
	}
}

void Resolver::VisitLiteral(const Literal* literalExpr)
{
	
}

void Resolver::VisitUnary(const Unary* unaryExpr)
{
	
}

void Resolver::VisitBinary(const Binary* binaryExpr)
{
	
}

void Resolver::VisitGrouping(const Grouping* groupingExpr)
{
	
}

void Resolver::VisitVariable(const Variable* variableExpr){
	if (!scopes.empty() && !scopes.top()->at(variableExpr->name.lexeme)) {
		Error(variableExpr->name, "Can't read local variable in its own initializer");
	}
	ResolveLocal(variableExpr, variableExpr->name);
}

void Resolver::VisitAssign(const Assign* assignExpr)
{
	
}

void Resolver::VisitLogical(const Logical* logicalExpr)
{
	
}

void Resolver::VisitCall(const Call* callExpr)
{
	
}

void Resolver::VisitExprStmt(const ExprStmt* exprStmt)
{
	
}

void Resolver::VisitPrintStmt(const Print* printStmt)
{
	
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

void Resolver::VisitIfStmt(const If* ifStmt)
{
	
}

void Resolver::VisitWhileStmt(const While* whileStmt)
{
	
}

void Resolver::VisitFunctionStmt(const Function* functionStmt)
{
	
}

void Resolver::VisitReturnStmt(const Return* returnStmt)
{
	
}
