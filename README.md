# findDerivative  
  
### How to compile:  
make  
  
### Functions:  
ln, sqrt, sin, cos, tg, ctg, exp, arcsin, arccos, arctg, arcctg  
  
### Input:  
sin(x+cosx)  
  
### Ouput:  
cos(x+cosx)*(1+(-1*sinx))  
1: 0.00483344 0.00483344  
2: -0.00118426 -0.00118426  
3: -0.365218 -0.365218  
4: -1.7201 -1.7201  
5: 1.0592 1.0592  
6: 0.99726 0.99726  
7: 0.0342713 0.0342713  
8: -5.51596e-06 -5.51596e-06  
9: -0.13682 -0.13682  
  
### Methods:  
<strong>public:</strong>  
&nbsp;void build(std::string) - build function tree  
&nbsp;double evaluate(double) - evaluate function at value  
&nbsp;double evaluateDerivative(double) - evaluate derivative at value  
&nbsp;void print() - print function  
<strong>private:</strong>  
&nbsp;void simplify() - make function more simple  
&nbsp;void buildTree(std::vector<Node \*>) - create tree  
&nbsp;void printRecursive(Node \*) - print tree using recursion  
&nbsp;void specialPrint() - print tree like "Tree"  
