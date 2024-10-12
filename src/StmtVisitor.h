#pragma once

struct ExprStmt;
struct Print;
struct Var;
struct Block;
struct If;
struct While;
struct Function;

template <typename T>
class StmtVisitor {
public:
	virtual T VisitExprStmt(const ExprStmt* exprStmt) = 0;
	virtual T VisitPrintStmt(const Print* printStmt) = 0;
	virtual T VisitVarStmt(const Var* varStmt) = 0;
	virtual T VisitBlockStmt(const Block* blockStmt)  = 0;
	virtual T VisitIfStmt(const If* ifStmt) = 0;
	virtual T VisitWhileStmt(const While* whileStmt) = 0;
	virtual T VisitFunctionStmt(const Function* functionStmt) = 0;
};