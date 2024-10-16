#include "Resolver.h"

Resolver::Resolver(Interpreter* interpreter){
	this->interpreter = interpreter;
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

void Resolver::VisitVariable(const Variable* variableExpr)
{
	
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

void Resolver::VisitVarStmt(const Var* varStmt)
{
	
}

void Resolver::VisitBlockStmt(const Block* blockStmt){
	
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
