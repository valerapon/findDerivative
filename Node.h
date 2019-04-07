#include <iostream>
#include <string>

extern int PRIORITY[];

enum OBJECT {
	NONE,
	LBRACKET, RBRACKET,
	PLUS, MINUS,
	MULTIPLY, DIVISION,
	POWER,
	LN, SQRT, EXP,
	SIN, COS, TG, CTG,
	ARCSIN, ARCCOS, ARCTG, ARCCTG,
	VARIABLE, NUMBER
};

class Node {
public:
	virtual OBJECT getType() const = 0;
	virtual int getPriority() const = 0;
	virtual double getValue() const;
	virtual std::string getName() const;
	virtual Node *getUnder() const;
	virtual Node *getLeft() const;
	virtual Node *getRight() const;
	virtual void setUnder(Node *under);
	virtual void setLeft(Node *left);
	virtual void setRight(Node *right);
	virtual Node *derivative() const = 0;
	virtual Node *copy() const = 0;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const = 0;
};

class Operator: public Node {
public:
	virtual OBJECT getType() const = 0;
	virtual int getPriority() const = 0;
	virtual Node *derivative() const = 0;
	virtual Node *copy() const = 0;
	virtual void print() const = 0;
};

class Unary: public Operator {
	Node *under_;
public:
	Unary();
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *getUnder() const;
	virtual void setUnder(Node *under);
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual void print() const;
};

class Binary: public Operator {
	Node *left_, *right_;
public:
	Binary();
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *getLeft() const;
	virtual Node *getRight() const;
	virtual void setLeft(Node *left);
	virtual void setRight(Node *right);
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual void print() const;
};

class Term: public Node {
public:
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual void print() const;
};

class Variable: public Term {
	static OBJECT type_;
	std::string name_;
	double value_;
public:
	Variable();
	Variable(std::string name);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual std::string getName() const;
	virtual Node *derivative() const;
	virtual Node *makeSimple();
	virtual Node *copy() const;
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Number: public Term {
	static OBJECT type_;
	double value_;
public:
	Number();
	Number(double value);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual double getValue() const;
	virtual Node *derivative() const;
	virtual Node *makeSimple();
	virtual Node *copy() const;
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class LBracket: public Operator {
	static OBJECT type_;
public:
	LBracket(); 
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual void print() const;
};

class RBracket: public Operator {
	static OBJECT type_;
public:
	RBracket();
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual void print() const;
};

class Plus: public Binary {
	static OBJECT type_;
public:
	Plus();
	Plus(Node *left, Node *right);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Minus: public Binary {
	static OBJECT type_;
public:
	Minus();
	Minus(Node *left, Node *right);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Multiply: public Binary {
	static OBJECT type_;
public:
	Multiply();
	Multiply(Node *left, Node *right);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Division: public Binary {
	static OBJECT type_;
public:
	Division();
	Division(Node *left, Node *right);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Power: public Binary {
	static OBJECT type_;
public:
	Power();
	Power(Node *left, Node *right);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Ln: public Unary {
	static OBJECT type_;
public:
	Ln();
	Ln(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Sqrt: public Unary {
	static OBJECT type_;
public:
	Sqrt();
	Sqrt(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Exp: public Unary {
	static OBJECT type_;
public:
	Exp();
	Exp(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Sin: public Unary {
	static OBJECT type_;
public:
	Sin();
	Sin(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Cos: public Unary {
	static OBJECT type_;
public:
	Cos();
	Cos(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Tg: public Unary {
	static OBJECT type_;
public:
	Tg();
	Tg(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Ctg: public Unary {
	static OBJECT type_;
public:
	Ctg();
	Ctg(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Arcsin: public Unary {
	static OBJECT type_;
public:
	Arcsin();
	Arcsin(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Arccos: public Unary {
	static OBJECT type_;
public:
	Arccos();
	Arccos(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Arctg: public Unary {
	static OBJECT type_;
public:
	Arctg();
	Arctg(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

class Arcctg: public Unary {
	static OBJECT type_;
public:
	Arcctg();
	Arcctg(Node *under);
	virtual OBJECT getType() const;
	virtual int getPriority() const;
	virtual Node *derivative() const;
	virtual Node *copy() const;
	virtual Node *makeSimple();
	virtual double evaluate(double value) const;
	virtual double evaluateDerivative(double value) const;
	virtual void print() const;
};

Node *deepCopy(Node *node);

bool isFunction(OBJECT type);

void deleteNode(Node *node);

bool simplifyLeftAndRight(Node *node);

bool simplifyUnder(Node *node);

void print(Node *node);
