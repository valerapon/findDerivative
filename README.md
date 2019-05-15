### How to compile:  
<code>make</code>   
### How to run:  
<code>./bin/main</code>  
### Functions:  
<code>ln, sqrt, sin, cos, tg, ctg, exp, arcsin, arccos, arctg, arcctg</code>  
### Description:   
User enter function. Program buid function tree and derivative tree. After that perform computing derivative using 2 methods (using derivative tree and find derivative in point without generation analytical function) in nine different points from 1 to 9.   
### Input:  
<code>sin(x+cosx)</code>  
  
### Ouput:  
```  
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
```  
### Tree methods:    
<strong>public:</strong>  
&nbsp;<code>void build(std::string)</code> - build function tree  
&nbsp;<code>double evaluate(double)</code> - evaluate function at value  
&nbsp;<code>double evaluateDerivative(double)</code> - evaluate derivative at value  
&nbsp;<code>void print()</code> - print function  
<strong>private:</strong>  
&nbsp;<code>void simplify()</code> - make function more simple  
&nbsp;<code>void buildTree(std::vector<Node *>)</code> - create tree  
&nbsp;<code>void printRecursive(Node *)</code> - print tree using recursion  
&nbsp;<code>void specialPrint()</code> - print tree like "Tree"  
