#include <iostream>
#include <string>
#include "Tree.h"

int main() {
	try {
		std::string string;
		std::getline(std::cin, string);
		Tree tree(string);
		Tree a = tree.derivative();
		a.print();
		std::cout <<std::endl;
		for (int i = 1; i < 10; ++i) {
			std::cout << i << ": " << a.evaluate(i) << ' ' << tree.evaluateDerivative(i) << std::endl;
		}
	}
	catch(...) {}
	return 0;
}
