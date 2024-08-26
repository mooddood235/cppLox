#pragma once

struct ExprStmt;
struct Print;
struct Var;
struct Block;
struct If;

template <typename T>
class StmtVisitor {
public:
	virtual T VisitExprStmt(const ExprStmt* exprStmt) = 0;
	virtual T VisitPrintStmt(const Print* printStmt) = 0;
	virtual T VisitVarStmt(const Var* varStmt) = 0;
	virtual T VisitBlockStmt(const Block* blockStmt)  = 0;
	virtual T VisitIfStmt(const If* ifStmt) = 0;
};