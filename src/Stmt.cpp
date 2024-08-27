#include "Stmt.h"
#include "StmtVisitor.h"

void ExprStmt::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitExprStmt(this);
}

ExprStmt::ExprStmt(Expr* expr){
	this->expr = expr;
}
ExprStmt::~ExprStmt() {
	delete expr;
}
void Print::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitPrintStmt(this);
}
Print::Print(Expr* expr) {
	this->expr = expr;
}
Print::~Print() {
	delete expr;
}

Stmt::~Stmt(){}

void Var::Accept(StmtVisitor<void>* visitor) const {
	visitor->VisitVarStmt(this);
}
Var::Var(const Token& name, Expr* initializer) {
	this->name = name;
	this->initializer = initializer;
}

Block::Block(const std::vector<Stmt*>& stmts){
	this->stmts = stmts;
}

void Block::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitBlockStmt(this);
}

If::If(Expr* conditional, Stmt* thenBranch, Stmt* elseBranch){
	this->conditional = conditional;
	this->thenBranch = thenBranch;
	this->elseBranch = elseBranch;
}

void If::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitIfStmt(this);
}

While::While(Expr* condition, Stmt* body){
	this->condition = condition;
	this->body = body;
}

void While::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitWhileStmt(this);
}
