#pragma once

struct Unary;
struct Binary;
struct Grouping;
struct Literal;
struct Variable;
struct Assign;
struct Logical;

template <typename T> 
class ExprVisitor {
public:
	virtual T VisitLiteral(const Literal* literalExpr) = 0;
	virtual T VisitUnary(const Unary* unaryExpr) = 0;
	virtual T VisitBinary(const Binary* binaryExpr) = 0;
	virtual T VisitGrouping(const Grouping* groupingExpr) = 0;
	virtual T VisitVariable(const Variable* variableExpr) = 0;
	virtual T VisitAssign(const Assign* assignExpr) = 0;
	virtual T VisitLogical(const Logical* logicalExpr) = 0;
};