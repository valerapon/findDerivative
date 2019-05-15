#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "../headers/Tree.h"

bool isPass(char ch) {
	if (ch == ' ' || ch == '\t') {
		return true;
	}
	return false;
}

bool isDigit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}


std::vector<Node *> Tree::buildInfix(std::string string) {
	std::vector<Node *> infix;
	for (int i = 0; i < string.size(); ++i) {
		if (isPass(string[i])) {
			continue;
		} else if (string[i] == 'x'){
			std::string name = "x";
			infix.push_back(new Variable(name));
		} else if (isDigit(string[i])) {
			std::string number;
			while (isDigit(string[i]) || string[i] == '.') {
				number += string[i];
				++i;
			}
			--i;
			infix.push_back(new Number(std::stod(number)));
		} else if (string[i] == '+') {
			infix.push_back(new Plus);
		} else if (string[i] == '-') {
			infix.push_back(new Minus);
		} else if (string[i] == '*') {
			infix.push_back(new Multiply);
		} else if (string[i] == '/') {
			infix.push_back(new Division);
		} else if (string[i] == '^' ) {
			infix.push_back(new Power);
		} else if (string[i] == '(') {
			infix.push_back(new LBracket);
		} else if (string[i] == ')') {
			infix.push_back(new RBracket);
		} else if (string.substr(i, 3) == "sin") {
			i += 2;
			infix.push_back(new Sin);
		} else if (string.substr(i, 3) == "cos") {
			i += 2;
			infix.push_back(new Cos);
		} else if (string.substr(i, 2) == "tg") {
			i += 1;
			infix.push_back(new Tg);
		} else if (string.substr(i, 3) == "ctg") {
			i += 2;
			infix.push_back(new Ctg);
		} else if (string.substr(i, 2) == "ln") {
			i += 1;
			infix.push_back(new Ln);
		} else if (string.substr(i, 4) == "sqrt") {
			i += 3;
			infix.push_back(new Sqrt);
		} else if (string.substr(i, 6) == "arcsin") {
			i += 5;
			infix.push_back(new Arcsin);
		} else if (string.substr(i, 6) == "arccos") {
			i += 5;
			infix.push_back(new Arccos);
		} else if (string.substr(i, 5) == "arctg") {
			i += 4;
			infix.push_back(new Arctg);
		} else if (string.substr(i, 6) == "arcctg") {
			i += 5;
			infix.push_back(new Arcctg);
		} else if (string.substr(i, 3) == "exp") {
			i += 2;
			infix.push_back(new Exp);
		} else {
			std::cout << "Error:" << string[i] << ':'<< std::endl;
			exit(0);
		}
	}
	return infix;
}

std::vector<Node *> Tree::buildPostfix(std::vector<Node *> infix) {
	std::stack<Node *> stack;
	std::vector<Node *> postfix;
	for (int i = 0; i < infix.size(); ++i) {
		if (infix[i]->getType() == NUMBER || infix[i]->getType() == VARIABLE) {
			postfix.push_back(infix[i]);
		} else if (!stack.empty()) {
			if (infix[i]->getType() == LBRACKET) {
				stack.push(infix[i]);
			} else if (infix[i]->getType() == RBRACKET) {
				while (stack.top()->getType() != LBRACKET) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
			} else if (isFunction(infix[i]->getType())) {
				while (!stack.empty() && stack.top()->getPriority() != LBRACKET
						      && stack.top()->getPriority() > infix[i]->getPriority()) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				stack.push(infix[i]);
			} 
			else if (stack.top()->getType() != LBRACKET && stack.top()->getPriority() >= infix[i]->getPriority()) {
				while (!stack.empty() && stack.top()->getPriority() != LBRACKET
						      && stack.top()->getPriority() >= infix[i]->getPriority()) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				stack.push(infix[i]);
			} else {
				stack.push(infix[i]);
			}
		} else {
			stack.push(infix[i]);
		}
	}
	while (!stack.empty()) {
		postfix.push_back(stack.top());
		stack.pop();
	}
	return postfix;
}

void checkStack(bool isEmpty) {
	if (isEmpty) {
		std::cout << "Stack is empty" << std::endl;
		throw 0;
	}
}

void Tree::buildTree(std::vector<Node *> postfix) {
	std::stack<Node *> stack;
	for (int i = 0; i < postfix.size(); ++i) {
		OBJECT elemType = postfix[i]->getType();
		if (elemType == VARIABLE || elemType == NUMBER) {
			stack.push(postfix[i]);
		} else if (isFunction(elemType)) {
			checkStack(stack.empty());
			postfix[i]->setUnder(stack.top());
			stack.pop();
			stack.push(postfix[i]);	
		} else {
			checkStack(stack.empty());
			postfix[i]->setRight(stack.top());
			stack.pop();
			checkStack(stack.empty());
			postfix[i]->setLeft(stack.top());
			stack.pop();
			stack.push(postfix[i]);
		}
	}
	head_ = stack.top();
	stack.pop();
}

Tree::Tree() {
	head_ = nullptr;
}

Tree::Tree(std::string string) {
	build(string);
	simplify();
}

void Tree::build(std::string string) {
	buildTree(buildPostfix(buildInfix(string)));
	simplify();
}

Tree Tree::derivative() {
	Tree newTree;
	newTree.head_ = head_->derivative();
	newTree.simplify();
	return newTree;
}

bool isTerm(OBJECT type) {
	if (type == NUMBER || type == VARIABLE) {
		return true;
	}
	return false;
}

void Tree::printRecursive(Node *node) {
	if (node == nullptr) {
		return;
	}
	if (node->getType() == NUMBER || node->getType() == VARIABLE) {
		node->print();
	} else if (isFunction(node->getType())) {
		node->print();
		if (isTerm(node->getUnder()->getType()) || isFunction(node->getUnder()->getType())) {
			printRecursive(node->getUnder());
		}
		else {
			std::cout << '(';
			printRecursive(node->getUnder());
			std::cout << ')';
		}
	} else if (node->getType() == POWER && isFunction(node->getLeft()->getType())) {
		node->getLeft()->print();
		std::cout << '^';
		if (isTerm(node->getRight()->getType())) {
			node->getRight()->print();
		}
		else {
			std::cout << '(';
			printRecursive(node->getRight());
			std::cout << ')';
		}
		std::cout << '(';
		printRecursive(node->getLeft()->getUnder());
		std::cout << ')';
	}
	else {
		if (isTerm(node->getLeft()->getType()) || isFunction(node->getLeft()->getType())) {
			printRecursive(node->getLeft());
		}
		else {
			std::cout << '(';
			printRecursive(node->getLeft());
			std::cout << ')';	
		}
		node->print();
		if (isTerm(node->getRight()->getType()) || isFunction(node->getRight()->getType())) {
			printRecursive(node->getRight());
		}
		else {
			std::cout << '(';
			printRecursive(node->getRight());
			std::cout << ')';
		}
	}
}

void Tree::simplify() {
	Node *tmp = nullptr;
	while(true) {
		tmp = head_->makeSimple();
		if (tmp == nullptr) {
			return;
		}
		head_ = tmp;
	}
}

void Tree::specialPrint() {
	std::vector<Node *> one, two;
	int hmax = 6 , width = 1 << hmax ;
	one.push_back(head_);
	for ( int level = 0; level < hmax ; ++ level ) {
		std::string filler ( width - 1 , ' ' );
		for ( auto elem : one ) {
			if ( elem ) {
				std::cout << filler;
			       	elem->print();
				std::cout << filler ;
				if (isFunction(elem->getType())) {
					two.push_back(elem->getUnder());
					two.push_back(nullptr);
				}
				else {
					two.push_back(elem-> getLeft());
					two.push_back(elem->getRight());
				}
			} else {
				std :: cout << filler << " --" << filler ;
				two.push_back ( nullptr );
				two.push_back ( nullptr );
			}
		}
		std::cout << std::endl;
		one = two;
		two.clear();
		width /= 2;
	}
}

double Tree::evaluate(double value) {
	return head_->evaluate(value);
}

double Tree::evaluateDerivative(double value) {
	return head_->evaluateDerivative(value);
}

void Tree::print() {
	//specialPrint();
	printRecursive(head_);
}
