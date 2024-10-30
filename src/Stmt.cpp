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

Var::~Var(){
	delete initializer;
}

Block::Block(const std::vector<Stmt*>& stmts){
	this->stmts = stmts;
}

void Block::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitBlockStmt(this);
}

Block::~Block(){
	for (const Stmt* stmt : stmts) delete stmt;
}

If::If(Expr* conditional, Stmt* thenBranch, Stmt* elseBranch){
	this->conditional = conditional;
	this->thenBranch = thenBranch;
	this->elseBranch = elseBranch;
}

void If::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitIfStmt(this);
}

If::~If(){
	delete conditional;
	delete elseBranch;
	delete elseBranch;
}

While::While(Expr* condition, Stmt* body){
	this->condition = condition;
	this->body = body;
}

void While::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitWhileStmt(this);
}

While::~While(){
	delete body;
	delete condition;
}

Function::Function(){
}

Function::Function(const Token& name, const std::vector<Token> params, const std::vector<Stmt*> body){
	this->name = name;
	this->params = params;
	this->body = body;
}

void Function::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitFunctionStmt(this);
}

Function::~Function(){
	for (const Stmt* stmt : body) delete stmt;
}

Return::Return(const Token& keyword, Expr* value){
	this->keyword = keyword;
	this->value = value;
}
void Return::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitReturnStmt(this);
}
Return::~Return() {
	delete value;
}

Class::Class(const Token& name, const std::vector<Function*>& methods){
	this->name = name;
	this->methods = methods;
}
void Class::Accept(StmtVisitor<void>* visitor) const{
	visitor->VisitClassStmt(this);
}
Class::~Class() {
	for (const Function* func : methods) delete func;
}
