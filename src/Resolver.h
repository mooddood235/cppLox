#pragma once
#include "ExprVisitor.h"
#include "StmtVisitor.h"
#include "Interpreter.h"

class Resolver : ExprVisitor<void>, StmtVisitor<void>{
public:
	Resolver(Interpreter* interpreter);
	Interpreter* interpreter;

	// Inherited via ExprVisitor
	void VisitLiteral(const Literal* literalExpr) override;
	void VisitUnary(const Unary* unaryExpr) override;
	void VisitBinary(const Binary* binaryExpr) override;
	void VisitGrouping(const Grouping* groupingExpr) override;
	void VisitVariable(const Variable* variableExpr) override;
	void VisitAssign(const Assign* assignExpr) override;
	void VisitLogical(const Logical* logicalExpr) override;
	void VisitCall(const Call* callExpr) override;

	// Inherited via StmtVisitor
	void VisitExprStmt(const ExprStmt* exprStmt) override;
	void VisitPrintStmt(const Print* printStmt) override;
	void VisitVarStmt(const Var* varStmt) override;
	void VisitBlockStmt(const Block* blockStmt) override;
	void VisitIfStmt(const If* ifStmt) override;
	void VisitWhileStmt(const While* whileStmt) override;
	void VisitFunctionStmt(const Function* functionStmt) override;
	void VisitReturnStmt(const Return* returnStmt) override;
};

