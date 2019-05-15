#include <iostream>
#include <string>
#include <cmath>
#include "../headers/Node.h"

int PRIORITY[] = {
	-100,
	0, 0,
	10, 10,
	15, 15,
	50,
	25, 25, 25,
	25, 25, 25, 25,
	25, 25, 25, 25,
	100, 100
};

OBJECT LBracket::type_ = LBRACKET;
OBJECT RBracket::type_ = RBRACKET;
OBJECT Plus::type_ = PLUS;
OBJECT Minus::type_ = MINUS;
OBJECT Multiply::type_ = MULTIPLY;
OBJECT Division::type_ = DIVISION;
OBJECT Power::type_ = POWER;
OBJECT Ln::type_ = LN;
OBJECT Sqrt::type_ = SQRT;
OBJECT Exp::type_ = EXP;
OBJECT Sin::type_ = SIN;
OBJECT Cos::type_ = COS;
OBJECT Tg::type_ = TG;
OBJECT Ctg::type_ = CTG;
OBJECT Arcsin::type_ = ARCSIN;
OBJECT Arccos::type_ = ARCCOS;
OBJECT Arctg::type_ = ARCTG;
OBJECT Arcctg::type_ = ARCCTG;
OBJECT Variable::type_ = VARIABLE;
OBJECT Number::type_ = NUMBER;

//Node:	
double Node::getValue() const {
	return 0.0;
}

std::string Node::getName() const {
	return "";
}

Node *Node::getUnder() const {
	return nullptr;
}

Node *Node::getLeft() const {
	return nullptr;
}

Node *Node::getRight() const {
	return nullptr;
}

void Node::setUnder(Node *under) {}

void Node::setLeft(Node *left) {}

void Node::setRight(Node *right) {}

Node *Node::makeSimple() {
	return nullptr;
}

double Node::evaluate(double value) const {
	return 0;
}

double Node::evaluateDerivative(double value) const {
	return 0;
}

//Unary:
Unary::Unary() {
	under_ = nullptr;
}

OBJECT Unary::getType() const {
	return NONE;
}

int Unary::getPriority() const {
	return PRIORITY[NONE];
}

Node *Unary::getUnder() const {
	return under_;
}

void Unary::setUnder(Node *under) {
	under_ = under;
}

Node *Unary::derivative() const {
	return nullptr;
}

Node *Unary::copy() const {
	return nullptr;
}

void Unary::print() const {}

//Binary:
Binary::Binary() {
	left_ = nullptr;
	right_ = nullptr;
}

OBJECT Binary::getType() const {
	return NONE;
}

int Binary::getPriority() const {
	return PRIORITY[NONE];
}

Node *Binary::getLeft() const {
	return left_;
}

Node *Binary::getRight() const {
	return right_;
}

void Binary::setLeft(Node *left) {
	left_ = left;
}

void Binary::setRight(Node *right) {
	right_ = right;
}

Node *Binary::derivative() const {
	return nullptr;
}

Node *Binary::copy() const {
	return  nullptr;
}

void Binary::print() const {}

//Term:
OBJECT Term::getType() const {
	return NONE;
}

int Term::getPriority() const {
	return PRIORITY[NONE];
}

Node *Term::derivative() const {
	return nullptr;
}

Node *Term::copy() const {
	return nullptr;
}

void Term::print() const {}

//Variable:
Variable::Variable() {
	value_ = 0.0;
	name_ = "unknow";
}

Variable::Variable(std::string name) {
	value_ = 0.0;
	name_ = name;
}

OBJECT Variable::getType() const {
	return type_;
}

int Variable::getPriority() const {
	return PRIORITY[type_];
}

std::string Variable::getName() const {
	return name_;
}

Node *Variable::derivative() const {
	return new Number(1.0);
}

Node *Variable::makeSimple() {
	return nullptr;
}

double Variable::evaluate(double value) const {
	return value;
}

double Variable::evaluateDerivative(double value) const {
	return 1;
}

Node *Variable::copy() const {
	return new Variable(name_);
}

void Variable::print() const {
	std::cout << name_;
}

//Number:
Number::Number() {
	value_ = 0.0;
}

Number::Number(double value) {
	value_ = value;
}

OBJECT Number::getType() const {
	return type_;
}

int Number::getPriority() const {
	return PRIORITY[type_];
}

double Number::getValue() const {
	return value_;
}

Node *Number::derivative() const {
	return new Number(0.0);
}

Node *Number::makeSimple() {
	return nullptr;
}

double Number::evaluate(double value) const {
	return value_;
}

double Number::evaluateDerivative(double value) const {
	return 0;
}

Node *Number::copy() const {
	return new Number(value_);
}

void Number::print() const {
	std::cout << value_;
}

//LBracket:
LBracket::LBracket() {}

OBJECT LBracket::getType() const {
	return type_;
}

int LBracket::getPriority() const {
	return PRIORITY[type_];
}

Node *LBracket::derivative() const {
	return nullptr;
}

Node *LBracket::copy() const {
	return new LBracket;
}

void LBracket::print() const {
	std::cout << '(';
}

//RBracket:
RBracket::RBracket() {}

OBJECT RBracket::getType() const {
	return type_;
}

int RBracket::getPriority() const {
	return PRIORITY[type_];
}

Node *RBracket::derivative() const {
	return nullptr;
}

Node *RBracket::copy() const {
	return new RBracket;
}

void RBracket::print() const {
	std::cout << ')';
}

//Plus:
Plus::Plus() {}

Plus::Plus(Node *left, Node *right) {
	setLeft(left);
	setRight(right);
}

OBJECT Plus::getType() const {
	return type_;
}

int Plus::getPriority() const {
	return PRIORITY[type_];
}

Node *Plus::derivative() const {
	return new Plus(getLeft()->derivative(),
			getRight()->derivative());
}

double Plus::evaluate(double value) const {
	return getLeft()->evaluate(value) + getRight()->evaluate(value);
}

double Plus::evaluateDerivative(double value) const {
	return getLeft()->evaluateDerivative(value) + getRight()->evaluateDerivative(value);
}

Node *Plus::copy() const {
	return new Plus(getLeft(), getRight());
}

Node *Plus::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getLeft()->getType() == NUMBER && getLeft()->getValue() == 0.0) {
			tmp = getRight();
			delete getLeft();
			delete this;
			return tmp;
		}
		if (getRight()->getType() == NUMBER && getRight()->getValue() == 0.0) {
			tmp = getLeft();
			delete getRight();
			delete this;
			return tmp;
		}
		if (getLeft()->getType() == NUMBER && getRight()->getType() == NUMBER) {
			tmp = new Number(getLeft()->getValue() + getRight()->getValue());
			deleteNode(this);
			return tmp;
		}
		bool isSimple = simplifyLeftAndRight(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Plus::print() const {
	std::cout << '+';
}

//Minus:
Minus::Minus() {}

Minus::Minus(Node *left, Node *right) {
	setLeft(left);
	setRight(right);
}

OBJECT Minus::getType() const {
	return type_;
}

int Minus::getPriority() const {
	return PRIORITY[type_];
}

Node *Minus::derivative() const {
	return new Minus(getLeft()->derivative(),
			 getRight()->derivative());
}

double Minus::evaluate(double value) const {
	return getLeft()->evaluate(value) - getRight()->evaluate(value);
}

double Minus::evaluateDerivative(double value) const {
	return getLeft()->evaluateDerivative(value) - getRight()->evaluateDerivative(value);
}

Node *Minus::copy() const {
	return new Minus(getLeft(), getRight());
}

Node *Minus::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getLeft()->getType() == NUMBER && getLeft()->getValue() == 0.0) {
			tmp = new Multiply(new Number(-1.0), getRight());
			delete getLeft();
			delete this;
			return tmp;
		}
		if (getRight()->getType() == NUMBER && getRight()->getValue() == 0.0) {
			tmp = getLeft();
			delete getRight();
			delete this;
			return tmp;
		}
		if (getLeft()->getType() == NUMBER && getRight()->getType() == NUMBER) {
			tmp = new Number(getLeft()->getValue() - getRight()->getValue());
			deleteNode(this);
			return tmp;
		}
		bool isSimple = simplifyLeftAndRight(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Minus::print() const {
	std::cout << '-';
}

//Multiply:
Multiply::Multiply() {}

Multiply::Multiply(Node *left, Node *right) {
	setLeft(left);
	setRight(right);
}

OBJECT Multiply::getType() const {
	return type_;
}

int Multiply::getPriority() const {
	return PRIORITY[type_];
}

Node *Multiply::derivative() const {
	return new Plus(new Multiply(getLeft()->derivative(),
				     deepCopy(getRight())),
			new Multiply(deepCopy(getLeft()),
				     getRight()->derivative()));
}

double Multiply::evaluate(double value) const {
	return getLeft()->evaluate(value) * getRight()->evaluate(value);
}

double Multiply::evaluateDerivative(double value) const {
	return getLeft()->evaluateDerivative(value) * getRight()->evaluate(value) +
	       getLeft()->evaluate(value) * getRight()->evaluateDerivative(value);
}

Node *Multiply::copy() const {
	return new Multiply(getLeft(), getRight());
}

Node *Multiply::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if ((getLeft()->getType() == NUMBER && getLeft()->getValue() == 0.0) ||
		    (getRight()->getType() == NUMBER && getRight()->getValue() == 0.0)) {
			deleteNode(this);
			return new Number(0.0);
		}
		if (getLeft()->getType() == NUMBER && getLeft()->getValue() == 1.0) {
			tmp = getRight();
			delete getLeft();
			delete this;
			return tmp;
		}
		if (getRight()-> getType() == NUMBER && getRight()->getValue() == 1.0) {
			tmp = getLeft();
			delete getRight();
			delete this;
			return tmp;
		}
		if (getLeft()->getType() == NUMBER && getRight()->getType() == NUMBER) {
			tmp = new Number(getLeft()->getValue() * getRight()->getValue());
			deleteNode(this);
			return tmp;
		}	
		isSimple = simplifyLeftAndRight(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Multiply::print() const {
	std::cout << '*';
}

//Division:
Division::Division() {}

Division::Division(Node *left, Node *right) {
	setLeft(left);
	setRight(right);
}

OBJECT Division::getType() const {
	return type_;
}

int Division::getPriority() const {
	return PRIORITY[type_];
}

Node *Division::derivative() const {
	return new Division(new Minus(new Multiply(getLeft()->derivative(),
						   deepCopy(getRight())),
				      new Multiply(deepCopy(getLeft()),
					      	   getRight()->derivative())),
			    new Power(deepCopy(getRight()),
				      new Number(2.0)));
}

double Division::evaluate(double value) const {
	double tmp = getRight()->evaluate(value);
	if (tmp == 0) {
		std::cout << "Can't devide on zero" << std::endl;
		throw 0;
	}
	return getLeft()->evaluate(value) / tmp;
}

double Division::evaluateDerivative(double value) const {
	double tmp = getRight()->evaluate(value);
	if (tmp == 0) {
		std::cout << "Can't devide on zero" << std::endl;
		throw 0;
	}
	return (getLeft()->evaluateDerivative(value) * tmp -
		getLeft()->evaluate(value) * getRight()->evaluateDerivative(value)) / (tmp * tmp);
}

Node *Division::copy() const {
	return new Division(getLeft(), getRight());
}

Node *Division::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getRight()->getType() == NUMBER && getRight()->getValue() == 0.0) {
			std::cout << "Can't divide on zero" << std::endl;
			throw 0;
		}
		if (getLeft()->getType() == NUMBER && getLeft()->getValue() == 0.0) {
			deleteNode(this);
			return new Number(0.0);
		}
		if (getRight()->getType() == NUMBER && getRight()->getValue() == 1.0) {
			tmp = getLeft();
			delete getRight();
			delete this;
			return tmp;
		}
		if (getLeft()->getType() == NUMBER && getRight()->getType() == NUMBER) {
			tmp = new Number(getLeft()->getValue() / getRight()->getValue());
			deleteNode(this);
			return tmp;
		}
		isSimple = simplifyLeftAndRight(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Division::print() const {
	std::cout << '/';
}

//Power:
Power::Power() {}

Power::Power(Node *left, Node *right) {
	setLeft(left);
	setRight(right);
}

OBJECT Power::getType() const {
	return type_;
}

int Power::getPriority() const {
	return PRIORITY[type_];
}

bool isArgumentHere(Node *node, std::string arg) {
	if (node->getType() == NUMBER) {
		return false;
	}
	if (node->getType() == VARIABLE) {
		if (node->getName() == arg) {
			return true;
		}
		else {
			return false;
		}
	}
	if (isFunction(node->getType())) {
		return isArgumentHere(node->getUnder(), arg);
	}
	else {
		return isArgumentHere(node->getLeft(), arg) || isArgumentHere(node->getRight(), arg);
	}
}

Node *Power::derivative() const {
	if (isArgumentHere(getRight(), "x")) {
		return new Multiply(new Power(deepCopy(getLeft()),
					      deepCopy(getRight())),
				    new Plus(new Multiply(getRight()->derivative(),
						         new Ln(deepCopy(getLeft()))),
				     	new Division(new Multiply(deepCopy(getRight()),
								       getLeft()->derivative()),
							  deepCopy(getLeft()))));
	}
	return new Multiply(deepCopy(getRight()),
			    new Power(deepCopy(getLeft()),
				      new Minus(deepCopy(getRight()),
					        new Number(1.0))));
}

Node *Power::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getLeft()->getType() == NUMBER && getLeft()->getValue() == 0.0 &&
		    getRight()->getValue() == NUMBER && getRight()->getValue() == 0.0) {
			std::cout << "Can't pow(0,0)" <<std::endl;
			throw 0;
		}
		if (getLeft()->getType() == NUMBER && getLeft()->getValue() == 0.0) {
			deleteNode(this);
			return new Number(0.0);
		}
		if (getRight()->getType() == NUMBER && getRight()->getValue() == 0.0) {
			deleteNode(this);
			return new Number(1.0);
		}
		if (getLeft()->getType() == NUMBER && getRight()->getType() == NUMBER) {
			tmp = new Number(pow(getLeft()->getValue(), getRight()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyLeftAndRight(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

double Power::evaluate(double value) const {
	double tmp1 = getLeft()->evaluate(value), tmp2 = getRight()->evaluate(value);
	if (tmp1 == 0 && tmp2 == 0) {
		std::cout << "pow(0,0) is incorrect" << std::endl;
		throw 0;
	}
	return pow(tmp1, tmp2);
}

double Power::evaluateDerivative(double value) const {
	double tmp1 = getLeft()->evaluate(value), tmp2 = getRight()->evaluate(value);
	if (tmp1 == 0 && tmp2 == 0) {
		std::cout << "pow(0,0) is incorrect" << std::endl;
		throw 0;
	}
	if (tmp1 <= 0) {
		std::cout << "log of negative number" << std::endl;
		throw 0;
	}
	if (isArgumentHere(getRight(), "x")) {
		return pow(tmp1, tmp2) * 
		       (getRight()->evaluateDerivative(value) * log(tmp1) +
			tmp2 * getLeft()->evaluateDerivative(value) / tmp1);
	}
	return tmp2 * pow(tmp1, tmp2 - 1);
}

Node *Power::copy() const {
	return new Power(getLeft(), getRight());
}

void Power::print() const {
	std::cout << '^';
}

//Ln:
Ln::Ln() {}

Ln::Ln(Node *under) {
	setUnder(under);
}

OBJECT Ln::getType() const {
	return type_;
}

int Ln::getPriority() const {
	return PRIORITY[type_];
}

Node *Ln::derivative() const {
	return new Division(getUnder()->derivative(),
			    deepCopy(getUnder()));
}

Node *Ln::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER && getUnder()->getValue() <= 0) {
			std::cout << "ln with non-positive number" << std::endl;
			throw 0;
		}
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(log(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

double Ln::evaluate(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp <= 0) {
		std::cout << "Ln non-positive number" << std::endl;
		throw 0;
	}
	return log(tmp);
}

double Ln::evaluateDerivative(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp == 0) {
		std::cout << "Can't devide on zero" << std::endl;
		throw 0;
	}
	return getUnder()->evaluateDerivative(value) / tmp;
}

Node *Ln::copy() const {
	return new Ln(getUnder());
}

void Ln::print() const {
	std::cout << "ln";
}

//Sqrt:
Sqrt::Sqrt() {}

Sqrt::Sqrt(Node *under) {
	setUnder(under);
}

OBJECT Sqrt::getType() const {
	return type_;
}

int Sqrt::getPriority() const {
	return PRIORITY[type_];
}

Node *Sqrt::derivative() const {
	return new Division(getUnder()->derivative(),
			    new Multiply(new Number(2.0),
				         new Sqrt(deepCopy(getUnder()))));
}

double Sqrt::evaluate(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp < 0) {
		std::cout << "Sqrt with negative number" << std::endl;
		throw 0;
	}
	return sqrt(tmp);

}

double Sqrt::evaluateDerivative(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp <= 0) {
		std::cout << "sqrt and devide on non-positive number" << std::endl;
		throw 0;
	}
	return getUnder()->evaluateDerivative(value) / (2 * sqrt(tmp));
}

Node *Sqrt::copy() const {
	return new Sqrt(getUnder());
}

Node *Sqrt::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER && getUnder()->getValue() < 0) {
			std::cout << "sqrt with non-positive number" << std::endl;
			throw 0;
		}
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(sqrt(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Sqrt::print() const {
	std::cout << "sqrt";
}

//Exp:
Exp::Exp() {}

Exp::Exp(Node *under) {
	setUnder(under);
}

OBJECT Exp::getType() const {
	return type_;
}

int Exp::getPriority() const {
	return PRIORITY[type_];
}

Node *Exp::derivative() const {
	return new Multiply(new Exp(deepCopy(getUnder())),
			    getUnder()->derivative());
}

double Exp::evaluate(double value) const {
	return exp(getUnder()->evaluate(value));
}

double Exp::evaluateDerivative(double value) const {
	return getUnder()->evaluateDerivative(value) * exp(getUnder()->evaluate(value));
}

Node *Exp::copy() const {
	return new Exp(getUnder());
}

Node *Exp::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(exp(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Exp::print() const {
	std::cout << "exp";
}

//Sin:
Sin::Sin() {}

Sin::Sin(Node *under) {
	setUnder(under);
}

OBJECT Sin::getType() const {
	return type_;
}

int Sin::getPriority() const {
	return PRIORITY[type_];
}

Node *Sin::derivative() const {
	return new Multiply(new Cos(deepCopy(getUnder())),
			    getUnder()->derivative());
}

double Sin::evaluate(double value) const {
	return sin(getUnder()->evaluate(value));
}

double Sin::evaluateDerivative(double value) const {
	return getUnder()->evaluateDerivative(value) * cos(getUnder()->evaluate(value));
}

Node *Sin::copy() const {
	return new Sin(getUnder());
}

Node *Sin::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(sin(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Sin::print() const {
	std::cout << "sin";
}

//Cos::
Cos::Cos() {}

Cos::Cos(Node *under) {
	setUnder(under);
}

OBJECT Cos::getType() const {
	return type_;
}

int Cos::getPriority() const {
	return PRIORITY[type_];
}

Node *Cos::derivative() const {
	return new Multiply(new Number(-1.0),
			    new Multiply(new Sin(deepCopy(getUnder())),
				         getUnder()->derivative()));
}

double Cos::evaluate(double value) const {
	return cos(getUnder()->evaluate(value));
}

double Cos::evaluateDerivative(double value) const {
	return -getUnder()->evaluateDerivative(value) * sin(getUnder()->evaluate(value));
}

Node *Cos::copy() const {
	return new Cos(getUnder());
}

Node *Cos::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(cos(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Cos::print() const {
	std::cout << "cos";
}

//Tg:
Tg::Tg() {}

Tg::Tg(Node *under) {
	setUnder(under);
}

OBJECT Tg::getType() const {
	return type_;
}

int Tg::getPriority() const {
	return PRIORITY[type_];
}

Node *Tg::derivative() const {
	return new Division(getUnder()->derivative(),
			    new Power(new Cos(deepCopy(getUnder())),
				      new Number(2.0)));
}

double Tg::evaluate(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (getUnder()->getType() == NUMBER &&
	    (2 * tmp / M_PI - (int)(2 * tmp / M_PI) == 0.0) && (int)(2 * tmp / M_PI) % 2 == 1) {
		std::cout << "tg(n*Pi/2), where n = 2k+1 doesn't exist" << std::endl;
		throw(0);	
	}
	return tan(tmp);
}

double Tg::evaluateDerivative(double value) const {
	double tmp = cos(getUnder()->evaluate(value));
	if (tmp == 0) {
		std::cout << "tg(pi/2) not exist" << std::endl;
		throw 0;
	}
	return getUnder()->evaluateDerivative(value) / (tmp * tmp);
}

Node *Tg::copy() const {
	return new Tg(getUnder());
}

Node *Tg::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER &&
		    (2 * getUnder()->getValue() / M_PI - (int)(2 * getUnder()->getValue() / M_PI) == 0.0) &&
		    (int)(2 * getUnder()->getValue() / M_PI) % 2 == 1) {
			std::cout << "tg(n*Pi/2), where n = 2k+1 doesn't exist" << std::endl;
			throw(0);	
		}
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(tan(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Tg::print() const {
	std::cout << "tg";
}

//Ctg:
Ctg::Ctg() {}

Ctg::Ctg(Node *under) {
	setUnder(under);
}

OBJECT Ctg::getType() const {
	return type_;
}

int Ctg::getPriority() const {
	return PRIORITY[type_];
}

Node *Ctg::derivative() const {
	return new Division(new Multiply(new Number(-1.0),
					 getUnder()->derivative()),
			    new Power(new Sin(deepCopy(getUnder())),
					 new Number(2.0)));
}

double Ctg::evaluate(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp / M_PI - (int)(tmp / M_PI) == 0.0) {
		std::cout << "ctg(n*Pi) not exist" << std::endl;
		throw 0;
	}
	return 1 / tan(tmp);
}

double Ctg::evaluateDerivative(double value) const {
	double tmp = sin(getUnder()->evaluate(value));
	if (tmp == 0) {
		std::cout << "ctg(Pi) not exist" << std::endl;
		throw 0; 
	}
	return -getUnder()->evaluateDerivative(value) / (tmp * tmp);
}

Node *Ctg::copy() const {
	return new Ctg(getUnder());
}

Node *Ctg::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER &&
		    (getUnder()->getValue() / M_PI - (int)(getUnder()->getValue() / M_PI) == 0.0)) {
			std::cout << "ctg(n*Pi) doesn't exist" << std::endl;
			throw(0);	
		}
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(1 / tan(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Ctg::print() const {
	std::cout << "ctg";
}

//Arcsin:
Arcsin::Arcsin() {}

Arcsin::Arcsin(Node *under) {
	setUnder(under);
}

OBJECT Arcsin::getType() const {
	return type_;
}

int Arcsin::getPriority() const {
	return PRIORITY[type_];
}

Node *Arcsin::derivative() const {
	return new Division(getUnder()->derivative(),
			    new Sqrt(new Minus(new Number(1.0),
					       new Power(deepCopy(getUnder()),
						         new Number(2.0)))));
}

double Arcsin::evaluate(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp < -1 || tmp > 1) {
		std::cout << "arcsin is not define outside of [-1;1]" << std::endl;
		throw(0);
	}
	return asin(tmp);
}

double Arcsin::evaluateDerivative(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp == 1 || tmp == -1) {
		std::cout << "arcsin: can't devide on zero" << std::endl;
		throw 0;
	}
	return getUnder()->evaluateDerivative(value) / sqrt(1 - tmp * tmp);
}

Node *Arcsin::copy() const {
	return new Arcsin(getUnder());
}

Node *Arcsin::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER && (getUnder()->getValue() < -1 || getUnder()->getValue() > 1)) {
			std::cout << "arcsin on [-1,1] outside not define" << std::endl;
			throw(0);
		}
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(asin(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Arcsin::print() const {
	std::cout << "arcsin";
}

//Arccos:
Arccos::Arccos() {}

Arccos::Arccos(Node *under) {
	setUnder(under);
}

OBJECT Arccos::getType() const {
	return type_;
}

int Arccos::getPriority() const {
	return PRIORITY[type_];
}

Node *Arccos::derivative() const {
	return new Division(new Multiply(new Number(-1.0),
					 getUnder()->derivative()),
			    new Sqrt(new Minus(new Number(1.0),
					       new Power(deepCopy(getUnder()),
						         new Number(2.0)))));
}

Node *Arccos::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER && (getUnder()->getValue() < -1 || getUnder()->getValue() > 1)) {
			std::cout << "arccos on [-1,1] outside not define" << std::endl;
			throw(0);
		}
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(acos(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

double Arccos::evaluate(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp < -1 || tmp > 1) {
		std::cout << "arccos is not define on outside of [-1,1]" << std::endl;
		throw(0);
	}
	return acos(tmp);
}

double Arccos::evaluateDerivative(double value) const {
	double tmp = getUnder()->evaluate(value);
	if (tmp == 1 || tmp == -1) {
		std::cout << "arccos: can't devide on zero" << std::endl;
		throw 0;
	}
	return -getUnder()->evaluateDerivative(value) / sqrt(1 - tmp * tmp);
}

Node *Arccos::copy() const {
	return new Arccos(getUnder());
}

void Arccos::print() const {
	std::cout << "arccos";
}

//Arctg:
Arctg::Arctg() {}

Arctg::Arctg(Node *under) {
	setUnder(under);
}

OBJECT Arctg::getType() const {
	return type_;
}

int Arctg::getPriority() const {
	return PRIORITY[type_];
}

Node *Arctg::derivative() const {
	return new Division(getUnder()->derivative(),
			    new Plus(new Number(1.0),
				     new Power(deepCopy(getUnder()),
					       new Number(2.0))));
}

double Arctg::evaluate(double value) const {
	return atan(getUnder()->evaluate(value));
}

double Arctg::evaluateDerivative(double value) const {
	double tmp = getUnder()->evaluate(value);
	return 1 / (1 + tmp * tmp);
}

Node *Arctg::copy() const {
	return new Arctg(getUnder());
}

Node *Arctg::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(atan(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Arctg::print() const {
	std::cout << "arctg";
}

//Arcctg:
Arcctg::Arcctg() {}

Arcctg::Arcctg(Node *under) {
	setUnder(under);
}

OBJECT Arcctg::getType() const {
	return type_;
}

int Arcctg::getPriority() const {
	return PRIORITY[type_];
}

Node *Arcctg::derivative() const {
	return new Division(new Multiply(new Number(-1.0),
					 getUnder()->derivative()),
			    new Plus(new Number(1.0),
				     new Power(deepCopy(getUnder()),
					       new Number(2.0))));	
}

double Arcctg::evaluate(double value) const {
	return M_PI / 2 - atan(getUnder()->evaluate(value));
}

double Arcctg::evaluateDerivative(double value) const {
	double tmp = getUnder()->evaluate(value);
	return -1 / (1 + tmp * tmp);
}

Node *Arcctg::copy() const {
	return new Arcctg(getUnder());
}

Node *Arcctg::makeSimple() {
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		if (getUnder()->getType() == NUMBER) {
			tmp = new Number(M_PI / 2 - atan(getUnder()->getValue()));
			deleteNode(this);
			return tmp;
		}	
		bool isSimple = simplifyUnder(this);
		if (isSimple) {
			return nullptr;
		}
	}
}

void Arcctg::print() const {
	std::cout << "arcctg";
}

Node* deepCopy(Node *node) {
	if (node->getType() == NUMBER || node->getType() == VARIABLE) {
		return node->copy();
	}
	Node *newNode = node->copy();
	if (isFunction(node->getType())) {
		newNode->setUnder(deepCopy(node->getUnder()));
	}
	else {
		newNode->setLeft(deepCopy(node->getLeft()));
		newNode->setRight(deepCopy(node->getRight()));
	}
	return newNode;
}

void deleteNode(Node *node) {
	if (node == nullptr) {
		return;
	}
	if (isFunction(node->getType())) {
		deleteNode(node->getUnder());
	}
	else {
		deleteNode(node->getLeft());
		deleteNode(node->getRight());
	}
	delete node;
}

bool isFunction(OBJECT type) {
	if (type == LN || type == SQRT || type == SIN || type == COS ||
	    type == TG || type == CTG || type == ARCSIN || type == ARCCOS ||
	    type == ARCTG || type == ARCCTG || type == EXP) {
		return true;
	}
	return false;
}

bool simplifyLeftAndRight(Node *node) {
	//node->print();
	//std::cout << std::endl;
	//print(node);
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		tmp = node->getLeft()->makeSimple();
		if (tmp == nullptr) {
			break;
		}
		isSimple = false;
		node->setLeft(tmp);
	}
	while (true) {
		tmp = node->getRight()->makeSimple();
		if (tmp == nullptr) {
			break;
		}
		isSimple = false;
		node->setRight(tmp);
	}
	return isSimple;
}

bool simplifyUnder(Node *node) {
	//node->print();
	//std::cout << std::endl;
	//print(node);
	Node *tmp = nullptr;
	bool isSimple = true;
	while (true) {
		tmp = node->getUnder()->makeSimple();
		if (tmp == nullptr) {
			break;
		}
		isSimple = false;
		node->setUnder(tmp);
	}
	return isSimple;
}

void print(Node *node) {
	if (node == nullptr) {
		return;
	}
	if (node->getType() == NUMBER || node->getType() == VARIABLE) {
		node->print();
	} else if (isFunction(node->getType())) {
		node->print();
		print(node->getUnder());
	} else {
		print(node->getLeft());
		node->print();
		print(node->getRight());
	}
	std::cout << std::endl;
}
