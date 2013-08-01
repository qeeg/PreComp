#include <cstdio>
#include <cmath>
#include <vector>

#include "basic.h"

enum class operations
{
	NONE,
	EQUAL,
	PLUS,
	MINUS,
	DIVIDE,
	MULTIPLY,
	POWER,
};

//a + b
struct node
{
	operations op;
	var vars[2];
	node* parent;
	node* children[2];
	node(node* par) : op(operations::NONE), parent(par)
	{
		children[0] = nullptr;
		children[1] = nullptr;
	}

	~node()
	{
		if(children[0] != nullptr) delete children[0];
		if(children[1] != nullptr) delete children[1];
		if(parent != nullptr) delete parent;
	}
};

node* buildtree(string equation)
{
	node* root = new node(nullptr);
	var x;

	node* child1 = new node(root);
	node* child2 = new node(root);

	int i = equation.find_first_of(' ');

	if(equation.at(0) == '(')
	{
		int j = equation.find_first_of(')');
		child1 = buildtree(equation.substr(1,j-2));
	}

	else
	{
		x.name = equation.substr(0,i);
		bool valid = true;
		for(int j = 0;j<i;j++)
		{
			if(equation.at(j) < '0' || equation.at(j) > '9' || equation.at(j) == '.')
			{
				valid = false;
				break;
			}
		}

		if(valid == true)
		{
			x.value = atof(x.name.c_str());
			x.namevalid = false;
		}
		else x.namevalid = true;

		root->vars[0] = x;
	}

	i = equation.find(' ',i);

	i++;

	switch(equation.at(i))
	{
	case '=':
		{
			root->op = operations::EQUAL;
			break;
		}
	case '+':
		{
			root->op = operations::PLUS;
			break;
		}
	case '-':
		{
			root->op = operations::MINUS;
			break;
		}
	case '*':
		{
			root->op = operations::MULTIPLY;
			break;
		}
	case '/':
		{
			root->op = operations::DIVIDE;
			break;
		}
	case '^':
		{
			root->op = operations::POWER;
			break;
		}
	}

	i+=2;

	if(equation.at(i) == '(')
	{
		int j = equation.find_last_of(')');
		child2 = buildtree(equation.substr(i+1,j-i-1));
	}

	else
	{
		int k = equation.find(' ',i);
		if(k!=-1) x.name = equation.substr(k,string::npos);
		else x.name = equation.substr(i,string::npos);
		bool valid = true;
		for(int j = 0;j<k;j++)
		{
			if(equation.at(j) < '0' || equation.at(j) > '9' || equation.at(j) == '.')
			{
				valid = false;
				break;
			}
		}

		if(valid == true)
		{
			x.value = atof(x.name.c_str());
			x.namevalid = false;
		}
		else x.namevalid = true;

		root->vars[1] = x;
	}

	if(child1->op != operations::NONE) root->children[0] = child1;
	else root->children[0] = nullptr;
	if(child2->op != operations::NONE) root->children[1] = child2;
	else root->children[1] = nullptr;

	return root;
}

//NOT DONE.
//ZOMG DON'T USE.
//STAHP.
node* rebuild(node* root)
{
	node* res = new node(nullptr);
	node* child1;
	node* child2;

	if(root->op == operations::EQUAL)
	{
		if(root->children[0] != nullptr)
		{
			
		}
		else
		{
			res->vars[0] = root->vars[0];
		}
		if(root->children[1] != nullptr)
		{
			
		}
		else
		{
			res->vars[1] = root->vars[1];
		}
		return res;
	}
	else return root;
}

//This is done, though.
var evalpart(node* root)
{
	var child1, child2;
	var res;

	if(root->children[0] != nullptr)
	{
		child1 = evalpart(root->children[0]);
	}
	else
	{
		child1 = root->vars[0];
	}
	if(root->children[1] != nullptr)
	{
		child2 = evalpart(root->children[1]);
	}
	else
	{
		child2 = root->vars[1];
	}
	switch(root->op)
	{
	case operations::EQUAL:
		{
			res.value = child2.value;
			break;
		}
	case operations::PLUS:
		{
			res.value = child1.value + child2.value;
			break;
		}
	case operations::MINUS:
		{
			res.value = child1.value - child2.value;
			break;
		}
	case operations::MULTIPLY:
		{
			res.value = child1.value * child2.value;
			break;
		}
	case operations::DIVIDE:
		{
			res.value = child1.value / child2.value;
			break;
		}
	case operations::POWER:
		{
			res.value = pow(child1.value,child2.value);
			break;
		}
	}
	return res;
}

var eval(string equation)
{
	var res;
	node* tmp = buildtree(equation);

	res = evalpart(tmp);

	delete tmp;

	return res;
}

int main(int argc, char** argv[])
{
	return eval("x = (5 * (2 ^ 3))").value;
}

