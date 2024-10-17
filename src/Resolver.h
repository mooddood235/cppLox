#pragma once
#include <unordered_map>
#include <stack>
#include <string>
#include "ExprVisitor.h"
#include "StmtVisitor.h"
#include "Interpreter.h"

class Resolver : ExprVisitor<std::any>, StmtVisitor<void>{
public:
	Resolver(Interpreter* interpreter);
private:
	void Resolve(const std::vector<Stmt*> statements);
	void Resolve(const Stmt* stmt);
	void Resolve(const Expr* expr);
	void BeginScope();
	void EndScope();
	void Declare(const Token& name);
	void Define(const Token& name);
	void ResolveLocal(const Expr* expr, const Token& name);

	// Inherited via ExprVisitor
	std::any VisitLiteral(const Literal* literalExpr) override;
	std::any VisitUnary(const Unary* unaryExpr) override;
	std::any VisitBinary(const Binary* binaryExpr) override;
	std::any VisitGrouping(const Grouping* groupingExpr) override;
	std::any VisitVariable(const Variable* variableExpr) override;
	std::any VisitAssign(const Assign* assignExpr) override;
	std::any VisitLogical(const Logical* logicalExpr) override;
	std::any VisitCall(const Call* callExpr) override;

	// Inherited via StmtVisitor
	void VisitExprStmt(const ExprStmt* exprStmt) override;
	void VisitPrintStmt(const Print* printStmt) override;
	void VisitVarStmt(const Var* varStmt) override;
	void VisitBlockStmt(const Block* blockStmt) override;
	void VisitIfStmt(const If* ifStmt) override;
	void VisitWhileStmt(const While* whileStmt) override;
	void VisitFunctionStmt(const Function* functionStmt) override;
	void VisitReturnStmt(const Return* returnStmt) override;
private:
	Interpreter* interpreter;
	std::stack<std::unordered_map<std::string, bool>*> scopes;
};

