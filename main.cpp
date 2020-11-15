#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct stack
{
	T Data;
	stack* next;
};

stack<double>* top1 = NULL;
stack<char>* top2 = NULL;
bool error = false;

template <typename T>
void push(stack<T>*& top, T D)
{
	stack<T>* a = new stack<T>;
	a->Data = D;
	if (top == NULL)
	{
		a->next = NULL;
	}
	else
	{
		a->next = top;
	}
	top = a;
}

template <typename T>
bool stack_empty(stack<T>*& top)
{
	if (top == NULL)
		return true;
	else
		return false;
}

template <typename T>
T pop(stack<T>*& top)
{
	T k = top->Data;
	if (top->next != NULL)
	{
		stack<T>* q = top;
		top = top->next;
		delete q;
	}
	else
	{
		top = NULL;
	}
	return k;
}

template <typename T>
T show_top(stack<T>*& top)
{
	if (top != NULL)
		return top->Data;
}

bool is_digit(char D)
{
	if (D >= '0' && D <= '9' || D == '.' || D == 'e')
		return true;
	else
		return false;
}

double prod_oper(double a, double b, char op)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return b - a;
	case '*':
		return a * b;
	case '/':
		if (a == 0)
		{
			cout << "\nError: zero denominator\n";
			error = true;
			return 0;
		}
		return b / a;
	}
}

int check_priority(char op)
{
	if (op == '*' || op == '/')
		return 4;
	else if (op == '+' || op == '-')
		return 3;
	else if (op == '(')
		return 2;
	else if (op == '=')
		return 1;
	else
		return 0;
}

void make_pf()
{
	string s, buf;
	bool neg = false;
	cin >> s;
	if (s[s.length() - 1] != '=')
	{
		cout << "Forgotten equal sign\n";
		s += '=';
	}
	for (int i = 0; i < s.length() - 1; i++)
	{
		if (i == 0 && s[i] == '-')
		{
			buf += s[i];
			neg = true;
			continue;
		}
		if (is_digit(s[i]) || (s[i] == '-' || s[i] == '+') && s[i - 1] == 'e' || s[i] == '-' && neg)
		{
			buf += s[i];
		}
		else if (s[i] == ')')
		{
			if (buf != "")
			{
				cout << stod(buf) << ' ';
				push<double>(top1, stod(buf));
				buf = "";
			}
			if (neg)
			{
				neg = false;
				continue;
			}
			char operation = pop<char>(top2);
			while (operation != '(')
			{
				double a, b;
				a = pop<double>(top1);
				b = pop<double>(top1);
				push<double>(top1, prod_oper(a, b, operation));
				if (error)
					break;
				cout << operation << ' ';
				operation = pop<char>(top2);
			}
		}
		else
		{
			if (s[i] == '(' && s[i + 1] == '-')
			{
				neg = true;
				continue;
			}
			if (buf != "")
			{
				push<double>(top1, stod(buf));
				cout << stod(buf) << ' ';
				buf = "";
			}
			if (!stack_empty(top2))
			{
				if (check_priority(show_top<char>(top2)) < check_priority(s[i]) || check_priority(s[i]) == 2)
				{
					push<char>(top2, s[i]);
				}
				else
				{
					char operation = pop<char>(top2);
					double a = pop<double>(top1);
					double b = pop<double>(top1);
					push<double>(top1, prod_oper(a, b, operation));
					if (error)
						break;
					push<char>(top2, s[i]);
					cout << operation << ' ';
				}
			}
			else
			{
				push<char>(top2, s[i]);
			}
		}
	}
	if (!error)
	{
		if (buf != "")
		{
			cout << stod(buf) << ' ';
			push<double>(top1, stod(buf));
		}
		while (!stack_empty(top2))
		{
			char operation = pop<char>(top2);
			double a, b;
			a = pop<double>(top1);
			b = pop<double>(top1);
			push<double>(top1, prod_oper(a, b, operation));
			if (error)
				break;
			cout << operation << ' ';
		}
	}
	if (!error)
		cout << "= ";
}

int main()
{
	make_pf();
	if (!error)
		cout << pop(top1);
	return 0;
}
