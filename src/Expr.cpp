#include "Expr.h"

Unary::Unary(const Token& op, Expr* right){
	this->op = op;
	this->right = right;
}
Binary::Binary(Expr* left, const Token& op, Expr* right) {
	this->left = left;
	this->op = op;
	this->right = right;
}

std::any Unary::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitUnary(this);
}
Unary::~Unary(){
	delete right;
}
Binary::~Binary() {
	delete left;
	delete right;
}
Grouping::~Grouping() {
	delete expr;
}
std::any Binary::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitBinary(this);
}
Grouping::Grouping(Expr* expr) {
	this->expr = expr;
}
std::any Grouping::Accept(ExprVisitor<std::any>* visitor) const {
	return visitor->VisitGrouping(this);
}
Literal::Literal(const std::string& s){
	data = s;
	type = STRING;
}
Literal::Literal(const double d){
	data = d;
	type = NUMBER;
}
Literal::Literal(const bool b){
	data = b;
	type = BOOL;
}
Literal::Literal() {
	data = std::any();
	type = NIL;
}
std::string Literal::ToString() const{
	if (type == NUMBER) return std::to_string(std::any_cast<double>(data));
	else if (type == STRING) return std::any_cast<std::string>(data);
	else if (type == BOOL) return std::any_cast<bool>(data) ? "true" : "false";
	else return "nil";
}
std::any Literal::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitLiteral(this);
}

Expr::~Expr(){}

Variable::Variable(const Token& name){
	this->name = name;
}

std::any Variable::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitVariable(this);
}

Assign::Assign(const Token& name, Expr* value){
	this->name = name;
	this->value = value;
}

std::any Assign::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitAssign(this);
}

Assign::~Assign(){
	delete value;
}

Logical::Logical(Expr* left, const Token& op, Expr* right){
	this->left = left;
	this->op = op;
	this->right = right;
}

std::any Logical::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitLogical(this);
}

Logical::~Logical(){
	delete left;
	delete right;
}

Call::Call(Expr* callee, const Token& paren, const std::vector<Expr*>& arguments){
	this->callee = callee;
	this->paren = paren;
	this->arguments = arguments;
}
std::any Call::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitCall(this);
}
Call::~Call() {
	delete callee;
	for (const Expr* arg : arguments) delete arg;
}

Get::Get(Expr* object, const Token& name){
	this->object = object;
	this->name = name;
}

std::any Get::Accept(ExprVisitor<std::any>* visitor) const{
	return visitor->VisitGet(this);
}

Get::~Get(){
	delete object;
}
