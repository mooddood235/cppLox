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
	void Interpret(const std::vector<Stmt*>& stmts);
private:
	std::any VisitLiteral(const Literal* literalExpr) override;
	std::any VisitUnary(const Unary* unaryExpr) override;
	std::any VisitBinary(const Binary* binaryExpr) override;
	std::any VisitGrouping(const Grouping* groupingExpr) override;
	std::any VisitVariable(const Variable* variableExpr) override;
	std::any VisitAssign(const Assign* assignExpr) override;

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

	void Execute(const Stmt* stmt);
	void ExecuteBlock(const std::vector<Stmt*> stmts, const Environment& environment) ;
private:
	Environment environment = Environment();
};
struct RuntimeError {
public:
	RuntimeError(const Token& token, const std::string& message);
	Token token;
	std::string message;
};

