#pragma once
#include "ExprVisitor.h"
#include "StmtVisitor.h"
#include "Expr.h"
#include "Token.h"
#include <any>
#include "Stmt.h"
#include "Environment.h"

class Interpreter : ExprVisitor<std::any>, StmtVisitor<void>{
public:
	Interpreter();
	void Interpret(const std::vector<Stmt*>& stmts);
	void ExecuteBlock(const std::vector<Stmt*> stmts, Environment* environment);
	void Resolve(const Expr* expr, int depth);
private:
	std::any VisitLiteral(const Literal* literalExpr) override;
	std::any VisitUnary(const Unary* unaryExpr) override;
	std::any VisitBinary(const Binary* binaryExpr) override;
	std::any VisitGrouping(const Grouping* groupingExpr) override;
	std::any VisitVariable(const Variable* variableExpr) override;
	std::any VisitAssign(const Assign* assignExpr) override;
	std::any VisitLogical(const Logical* logicalExpr) override;
	std::any VisitCall(const Call* callExpr) override;

	std::any Evaluate(const Expr* expr) ;
	bool IsTruthy(const std::any& value) const;
	bool IsEqual(const std::any& left, const std::any& right) const;
	void CheckNumberOperand(const Token& op, const std::any& rand) const;	
	void CheckNumberOperands(const Token& op, const std::any& left, const std::any& right) const;
	std::string Stringify(const std::any& value) const;

	void VisitExprStmt(const ExprStmt* exprStmt)  override;
	void VisitPrintStmt(const Print* printStmt)  override;
	void VisitVarStmt(const Var* varStmt) override;
	void VisitBlockStmt(const Block* blockStmt)  override;
	void VisitIfStmt(const If* ifStmt) override;
	void VisitWhileStmt(const While* whileStmt) override;
	void VisitFunctionStmt(const Function* functionStmt) override;
	void VisitReturnStmt(const Return* returnStmt) override;

	void Execute(const Stmt* stmt);
	std::any LookUpVariable(const Token& name, const Expr* expr);
public:
	Environment* globals = new Environment();
	Environment* environment = globals;
private:
	std::unordered_map<const Expr*, int> locals;
};
struct RuntimeError {
public:
	RuntimeError(const Token& token, const std::string& message);
	Token token;
	std::string message;
};
struct ReturnException {
	ReturnException(const std::any& value);
	std::any value;
};

