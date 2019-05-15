#include <iostream>
#include <vector>
#include <string>
#include "../headers/Node.h"

class Tree {
	Node *head_;
	std::vector<Node *> buildInfix(std::string function);
	std::vector<Node *> buildPostfix(std::vector<Node *> infix);
	void simplify();
	void buildTree(std::vector<Node *> postfix);
	void printRecursive(Node *node);
	void specialPrint();
public:
	Tree();
	Tree(std::string function);
	void build(std::string function);
	Tree derivative();
	double evaluate(double value);
	double evaluateDerivative(double value);
	void print();
};

bool isDigit(char ch);

bool isPass(char ch);

bool isFunction(OBJECT type);

bool isTerm(OBJECT type);
