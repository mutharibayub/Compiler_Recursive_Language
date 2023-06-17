#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

string BP="1004";
string stackString = string();

void initGlobals();

string subStr(const string& s, int startIndex, int endIndex)
{
	string out="";
	for (int i = startIndex; i < endIndex; i++)
	{
		out.push_back(s[i]);
	}
	return out;
}
string lStrip(string s)
{
	int startIndex = 0;
	while (s[startIndex] == ' ' || s[startIndex]== '\t')
	{
		startIndex++;
	}
	return subStr(s,startIndex,s.length());
}
string rStrip(string s)
{
	int endIndex = s.length() - 1;
	while (s[endIndex] == ' ' || s[endIndex] == '\t')
	{
		endIndex--;
	}
	return subStr(s, 0, endIndex + 1);
}
string strip(string s)
{
	return rStrip(lStrip(s));
}
bool alphString(string s)
{
	for (int i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)){}
		else 
		{
			return false;
		}
	}
	return true;
}
string removeSpaces(string s)
{
	string out="";
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			out.push_back(s[i]);
		}
	}
	return out;
}
string replace(string main, string s1, string s2)
{
	int index = main.find(s1);
	if (index != -1)
	{
		return subStr(main, 0, index) + s2 + subStr(main, index+s1.length(), main.length());
	}
	else
	{
		return main;
	}
}

template<typename T>
struct QueueNode {
	T value = T();
	QueueNode* next = nullptr;
};

template<typename T>
struct Queue {//use linked list base implementation 
	QueueNode<T>* front; //ptr to save address of front node
	QueueNode<T>* rear;	 //ptr to save address of rear node
public:
	Queue() :front(nullptr), rear(nullptr){} //default constructor to initialize empty Queue
	~Queue() //Destructor. Empties Queue
	{
		while (!isEmpty())
		{
			dequeue();
		}
	}
	Queue(const Queue&) = delete;	//deleting copy constructor to define later if needed
	Queue& operator=(const Queue&) = delete;  //deleting = operator to define later if needed
	bool isEmpty() { return !bool(front) && !bool(rear); }
	T Front() { return front->value; }
	void enqueue(const T& ele) //Adding ele to rear of queue
	{
		QueueNode<T>* newNode = new QueueNode<T>;
		newNode->value = ele;
		newNode->next = nullptr;
		if (isEmpty())
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
	}
	void dequeue()		//removing the element at front of queue
	{
		QueueNode<T>* temp = nullptr;
		if (isEmpty())
		{
			cout << "CANNOT DEQUEUE since Queue is already empty!\n";
		}
		else
		{
			temp = front;
			front = front->next;
			delete temp;
			if (!front)
			{
				rear = nullptr;
			}
		}
	}
	void printQueue() //function to print entire queue (used for debugging)
	{
		QueueNode<T>* ptr = front;
		while (ptr)
		{
			cout << ptr->value;
			ptr = ptr->next;
			if (ptr)
			{
				cout << "<-";
			}
		}
		cout << endl;
	}
};

//stack for evaluation of postfix expression
// Add the required functions 
struct Stack {
	int* array; //saving contents of stack
	int cap;	//saving maximum capacity of stack
	int top;	//saving the index of the the current top of stack
	Stack(int cap) :cap(cap), array(new int[cap]), top(-1)	//constructor to initialize with capacity of stack
	{}
	~Stack()//Destructor. Deallocates memory
	{
		delete []array;
	}
	Stack(const Stack&) = delete;	//deleting default copy constructor to define it later if needed
	Stack& operator=(const Stack&) = delete;	//deleting default = operator to define it later if needed
	bool isEmpty() //returns whether stack is empty or not
	{
		if (top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isFull()	//returns whether stack has reached maximum capacity or not
	{
		if (top == cap - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int Top() { return top; }
	void push(int ele)	//pushes an element top of stack
	{
		if (isFull())
		{
			cout << "CANT PUSH as stack is already full\n";
		}
		else
		{
			top++;
			array[top] = ele;
		}
	}
	int pop()	//removes the element on top of stack and returns it
	{
		if (isEmpty())
		{
			cout << "CANT POP as stack is already empty!\n";
			return -9999;
		}
		else
		{
			top--;
			return array[top];
		}
	}
	void printStack()	//prints entire stack(used for debugging)
	{
		cout << '[';
		for (int i = 0; i <= top; i++)
		{
			cout << array[i];
			if (i != top)
			{
				cout << ',';
			}
		}
		cout << ']';
	}
};

template <typename T>
struct Variables { //A linked list of Variables can be use for finding the variable and associated value 
	T value;
	string Name;

};

template<typename T>
struct ListNode {
	T value=T();
	ListNode* next=nullptr;
};

template<typename T>
class LinkedList {
	ListNode<T>* start; //saves address of starting node of List
	ListNode<T>* end;	//saves address of ending node of List
	int len;
public:
	LinkedList() :start(nullptr),end(nullptr),len(0){} //default constructor to initialize empty List
	~LinkedList() //Destructor. Empties Linked List
	{
		clear();
	}
	LinkedList(const LinkedList<T>& li):start(nullptr), end(nullptr), len(0) //copy constructor which ensures deep copy
	{
		(*this) = li;
	}
	LinkedList<T>& operator=(const LinkedList<T>& li) //overloaded = operator for deep copy
	{
		ListNode<T>* ptr = li.start;
		while (!this->isEmpty())
		{
			this->removeAt(0);
		}
		while (ptr)
		{
			this->insertAt(-1, ptr -> value);
			ptr = ptr->next;
		}
		return *this;
	}
	void clear()
	{
		while (!isEmpty())
		{
			removeAt(0);
		}
	}
	bool isEmpty() { return !bool(start); }	//returns true if List is empty
	int getLen() { return len; }
	ListNode<T>* getStart() { return start; }
	T Start() 
	{
		if (start)
		{
			return start->value;
		}
		else
		{
			cout << "Linked List is Empty. Null Value returned as Start()\n";
			return T();
		} 
	}
	void insert(const T& ele)
	{
		insertAt(-1, ele);
	}
	void insertAt(int pos, const T& ele)	//Inserts an element so that its index will be pos when added to List
	{
		ListNode<T>* newNode = new ListNode<T>;
		ListNode<T>* temp = nullptr;
		newNode->value = ele;
		if (pos<0 || pos>len) //if pos is less than 0 or more than length then insert ele at end
		{
			pos = len;
		}
		if (pos == 0)	//insert at start
		{
			newNode->next = start;
			start = newNode;
			if (len == 0)		//if List was empty before, point end to the new node as well
			{
				end = start;
			}
		}
		else if(pos == len)	//insert at end if position if one more than length(using pointer to end)
		{
			end->next = newNode;
			newNode->next = nullptr;
			end = end->next;
		}
		else //insert at a middle node by traversing to the required node from starting node
		{
			ListNode<T>* ptr = start;
			for (int i = 0; i < pos-1; i++)
			{
				ptr = ptr->next;
			}
			temp = ptr->next;
			ptr->next = newNode;
			newNode->next = temp;
		}
		len++;
	}
	void removeAt(int pos)
	{
		ListNode<T>* temp = nullptr;
		if (isEmpty()) //end function if List already empty
		{
			cout << "CANT REMOVE as List is already empty!\n";
			return;
		}
		if (pos<0 || pos>=len) //if pos is less than 0 or more than length then remove the last element
		{
			pos = len-1;
		}
		if (pos == 0) //remove first element and change start if pos is 0
		{
			temp = start;
			start = start->next;
			delete temp;
			if (len == 1) //change end if length of List was only 1
			{
				end = nullptr;
			}
		}
		else	//remove any element other than first
		{
			ListNode<T>* ptr = start;
			for (int i = 0; i < pos-1; i++)
			{
				ptr = ptr->next;
			}
			temp = ptr->next;
			ptr->next = temp->next;
			delete temp;
			if (len == pos + 1) //Change end if the last element was removed
			{
				end = ptr;
			}
		}
		len--;
	}
	T* getArray()
	{
		if (len == 0)
		{
			return nullptr;
		}
		ListNode<T>* ptr = start;
		T* arr = new T[len];
		for(int i=0;ptr;i++)
		{
			arr[i] = ptr->value;
			ptr = ptr->next;
		}
		return arr;
	}
	void printList() //prints List(used for debugging)
	{
		ListNode<T>* ptr = start;
		cout << '[';
		while (ptr)
		{
			cout << ptr->value;
			ptr = ptr->next;
			if (ptr)
			{
				cout << ',';
			}
		}
		cout << "]\n";
	}
};

// Stack used for converting infix expressions to postfix expressions 
template<typename T>
class SpecialStack {
public:
	Queue<T> queue1;
	Queue<T> queue2;
	SpecialStack() :queue1(), queue2() {} //Default Constructor to initialise empty stack
	~SpecialStack() //Destructor. Empties Stack
	{
		while (!isEmpty())
		{
			pop();
		}
	}
	SpecialStack(const SpecialStack&) = delete; //deleted copy constructor to define later if needed
	SpecialStack& operator=(const SpecialStack&) = delete; //deleted = operator to define later if needed
	T Top()
	{
		return queue1.Front();
	}
	bool isEmpty() { return queue1.isEmpty(); }
	void push(const T& ele)
	{
		while (!queue1.isEmpty())
		{
			queue2.enqueue(queue1.Front());
			queue1.dequeue();
		}
		queue1.enqueue(ele);
		while (!queue2.isEmpty())
		{
			queue1.enqueue(queue2.Front());
			queue2.dequeue();
		}
	}
	T pop()
	{
		T retVal = T();
		if (queue1.isEmpty())
		{
			cout << "CANT POP as special stack is empty!\n";
			return retVal;
		}
		retVal = queue1.Front();
		queue1.dequeue();
		return retVal;
	}
	void printSpecialStack()
	{
		queue1.printQueue();
	}
};

struct FunctionDef
{
	string name = string();
	string retType = string();
	int startLine = int();
	int endLine = int();
	int paramCount = int();
	string* paramTypes = nullptr;
	string* paramNames = nullptr;
	//Constructor/Destructors
	FunctionDef() {}
	~FunctionDef()
	{
		this->clear();
	}
	void clear()
	{
		if (paramCount != 0)
		{
			delete []paramTypes;
			delete []paramNames;
		}
		name = string();
		retType = string();
		startLine = int();
		endLine = int();
		paramCount = int();
		paramTypes = nullptr;
		paramNames = nullptr;
	}
	FunctionDef(const FunctionDef& func)
	{
		(*this) = func;
	}
	FunctionDef& operator= (const FunctionDef& func)
	{
		if (paramTypes)
		{
			delete paramTypes;
		}
		if (paramNames)
		{
			delete paramNames;
		}
		name = func.name;
		retType = func.retType;
		startLine = func.startLine;
		endLine = func.endLine;
		paramCount = func.paramCount;
		if (paramCount != 0)
		{
			paramTypes = new string[paramCount];
			paramNames = new string[paramCount];
		}
		else
		{
			paramTypes = nullptr;
			paramNames = nullptr;
		}
		for (int i = 0; i < paramCount; i++)
		{
			paramTypes[i] = func.paramTypes[i];
			paramNames[i] = func.paramNames[i];
		}
		return *this;
	}
};

string IP;
LinkedList<FunctionDef> funcs;
ListNode<FunctionDef>* getFunction(string);
string incIP(string);
string currFunction(string);

//use this node for creating a Run Time Stack
struct RuntimeNode
{
	string data;
	int val1;
	float val2;
	int mode;		//mode 1 for integer val, mode 2 for float val, mode 3 for lineAddress, mode 4 for BP address
	int nodeAddress; //same will be stored in ESP and EBP
	RuntimeNode* next;
};

class RuntimeStack
{
	int currTopAddress;
	RuntimeNode* top;
	RuntimeNode* findVarNode(string name)
	{
		FunctionDef thisFunc = getFunction(currFunction(IP))->value;
		int paramCount = thisFunc.paramCount;
		RuntimeNode* ptr = top;
		while (ptr && ptr->mode != 3)
		{
			if (ptr->mode != 4 && ptr->data == name)
			{
				return ptr;
			}
			ptr = ptr->next;
		}
		if (ptr)
		{
			ptr = ptr->next;
		}
		for (int i = 0; ptr && i < paramCount; i++)
		{
			if (ptr->mode != 4 && ptr->data == name)
			{
				return ptr;
			}
			ptr = ptr->next;
		}
		return nullptr;
	}
public:
	RuntimeStack() :currTopAddress(1000), top(nullptr) {}
	void push(string ele, int mode)
	{
		string temp;
		RuntimeNode* newNode = new RuntimeNode;
		currTopAddress -= 4;
		newNode->next = top;
		newNode->nodeAddress = currTopAddress;
		newNode->mode = mode;
		ele = removeSpaces(ele);
		if (mode == 1)
		{
			temp = subStr(ele, 0, ele.find('='));
			newNode->data = temp;
			temp = subStr(ele, ele.find('=') + 1, ele.length());
			newNode->val1 = stoi(temp);
			stackString += to_string(int(stof(temp))) + "\n";
		}
		else if (mode == 2)
		{
			temp = subStr(ele, 0, ele.find('='));
			newNode->data = temp;
			temp = subStr(ele, ele.find('=') + 1, ele.length());
			newNode->val1 = stof(temp);
			stackString += to_string(int(stof(temp))) + "\n";
		}
		else if (mode == 3 || mode == 4) { newNode->data = ele; }
		else { cout << "Incorrect mode given to runtime stack push!\n"; }
		if (mode == 3)
		{
			stackString += ele + "\n";
		}
		else if (mode == 4)
		{
			stackString += "EBP=" + ele + "\n";
		}
		top = newNode;
	}
	RuntimeNode* getTop() { return top; }
	string Top()
	{
		if (!top)
		{
			cout << "Top() is returning Null string as RunTimeStack is empty\n";
			return string();
		}
		else
		{
			if (top->mode == 1)
			{
				return to_string(top->val1);
			}
			else if (top->mode == 2)
			{
				return to_string(top->val2);
			}
			else
			{
				return top->data;
			}
		}
	}
	string pop()
	{
		string out = Top();
		RuntimeNode* temp = top;
		if (top)
		{
			top = top->next;
			delete temp;
			currTopAddress += 4;
		}
		return out;
	}
	int getSP() { return currTopAddress; }
	float findVar(string name)
	{
		RuntimeNode* ptr = findVarNode(name);
		if (!ptr)
		{
			cout << "Variable not found in stack!\n";
		}
		else
		{
			if (ptr->mode == 1)
			{
				return ptr->val1;
			}
			else
			{
				return ptr->val2;
			}
		}
		return float();
	}
	void updateVar(string name, string value)
	{
		RuntimeNode* ptr = findVarNode(name);
		if (!ptr)
		{
			cout << "Could not find the variable node!\n";
		}
		else
		{
			if (ptr->mode == 1)
			{
				ptr->val1 = int(stof(value));
			}
			else
			{
				ptr->val2 = stof(value);
			}
		}
	}
};
RuntimeStack rs;

class ExpressionSolver
{
	//+,-,*,/,%,(,)
	bool prec(string oper1, string oper2)
	{
		string operArr[2] = { oper1,oper2 };
		int precArr[2] = { 0,0 };
		for (int i = 0; i < 2; i++)
		{
			if (operArr[i] == "/" || operArr[i] == "%" || operArr[i] == "*")
			{
				precArr[i] = 6;
			}
			else if (operArr[i] == "-" || operArr[i] == "+")
			{
				precArr[i] = 5;
			}
			else if (operArr[i] == ">" || operArr[i] == "<" || operArr[i] == "<=" || operArr[i] == ">=")
			{
				precArr[i] = 4;
			}
			else if (operArr[i] == "==" || operArr[i] == "!=")
			{
				precArr[i] = 3;
			}
			else if (operArr[i] == "&&")
			{
				precArr[i] = 2;
			}
			else if (operArr[i] == "||")
			{
				precArr[i] = 1;
			}
		}
		if (precArr[0] != 0 && precArr[1] != 0)
		{
			return precArr[0] >= precArr[1];
		}
		else
		{
			if (operArr[0] == "(" || (operArr[0] != ")" && operArr[1] == "(") || (operArr[0] == "(" && operArr[1] == ")"))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	bool isOperator(char symb)
	{
		char operArr[] = { '(', ')', '+', '-', '*', '%', '/' ,'>','<','!','=','&','|' };
		for (int i = 0; i < sizeof(operArr); i++)
		{
			if (symb == operArr[i])
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	T execOperation(T operand1, T operand2, string oper)
	{
		if (oper == "+")
		{
			return operand1 + operand2;
		}
		else if (oper == "-")
		{
			return  operand1 - operand2;
		}
		else if (oper == "*")
		{
			return operand1 * operand2;
		}
		else if (oper == "/")
		{
			return operand1 / operand2;
		}
		else if (oper == "%")
		{
			return int(operand1) % int(operand2);
		}
		else if (oper == ">")
		{
			return operand1 > operand2;
		}
		else if (oper == "<")
		{
			return operand1 < operand2;
		}
		else if (oper == ">=")
		{
			return operand1 >= operand2;
		}
		else if (oper == "<=")
		{
			return operand1 <= operand2;
		}
		else if (oper == "==")
		{
			return operand1 == operand2;
		}
		else if (oper == "!=")
		{
			return operand1 != operand2;
		}
		else if (oper == "&&")
		{
			return operand1 && operand2;
		}
		else if (oper == "||")
		{
			return operand1 || operand2;
		}
		else
		{
			cout << "--Invalid operation executed--\n" << endl;
			return NULL;
		}
	}
public:
	LinkedList<float> getVarVals(string infix)
	{
		LinkedList<float> out;
		string var = string();
		string temp;
		for (int i = 0; infix[i] != '\0'; i++,temp = string())
		{
			temp.push_back(infix[i]);
			if (isOperator(infix[i]))
			{
				if(var != "")out.insert(rs.findVar(var));
				var = string();
			}
			else if(!isNum(temp) && temp!=".")
			{
				var.push_back(infix[i]);
			}
		}
		if (var != "")
		{
			out.insert(rs.findVar(var));
			var = string();
		}
		return out;
	}
	bool isNum(string s)
	{
		for (int i = 0; s[i] != '\0'; i++)
		{
			if (s[i] >= 48 && s[i] <= 57) {}
			else { return false; }
		}
		return true;
	}
	string getPostfix(string infix)
	{
		string postfix = "";
		string currOperator = "";
		bool longVar = false;
		SpecialStack<string> opStack;
		for (int i = 0; infix[i] != '\0'; i++)
		{
			if (!isOperator(infix[i]))
			{
				if (!longVar && i != 0 && !isOperator(infix[i - 1]))
				{
					postfix += postfix[postfix.length() - 1];
					postfix[postfix.length() - 2] = '\"';
					longVar = true;
				}
				postfix += infix[i];
			}
			else
			{
				if (longVar)
				{
					longVar = false;
					postfix += "\"";
				}
				currOperator = infix[i];
				if (isOperator(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != ')' && infix[i] != '(' && infix[i] != ')')
				{
					currOperator += infix[i + 1];
					i++;
				}
				while (!opStack.isEmpty() && prec(opStack.Top(), currOperator))
				{
					if (opStack.Top().length() == 2)
					{
						postfix += "\"" + opStack.pop() + "\"";
					}
					else
					{
						postfix += opStack.pop();
					}
				}
				if (opStack.isEmpty() || currOperator != ")")
				{
					opStack.push(currOperator);
				}
				else
				{
					opStack.pop();
				}
			}
		}
		if (longVar)
		{
			longVar = false;
			postfix += "\"";
		}
		while (!opStack.isEmpty())
		{
			if (opStack.Top().length() == 2)
			{
				postfix += "\"" + opStack.pop() + "\"";
			}
			else
			{
				postfix += opStack.pop();
			}
		}
		return postfix;
	}
	template<typename T>
	T solvePostfix(string postfix, LinkedList<T> vars)
	{
		SpecialStack<T> stack;
		T val1;
		T val2;
		string oper;
		for (int i = 0, j; postfix[i] != '\0'; i++)
		{
			if (postfix[i] == '\"')
			{
				j = i + 1;
				for (; postfix[j - 1] != '\"' || i == j - 1; j++)
				{
				}
				if (isOperator(postfix[i + 1]))
				{
					oper = subStr(postfix, i + 1, j - 1);
					val2 = stack.pop();
					val1 = stack.pop();
					stack.push(execOperation(val1, val2, oper));
				}
				else if (postfix[i + 1] >= 48 && postfix[i + 1] <= 57)
				{
					stack.push(stof(subStr(postfix, i + 1, j - 1)));
				}
				else
				{
					stack.push(vars.Start());
					vars.removeAt(0);
				}
				i = j - 1;
			}
			else if (isOperator(postfix[i]))
			{
				oper = postfix[i];
				val2 = stack.pop();
				val1 = stack.pop();
				stack.push(execOperation(val1, val2, oper));
			}
			else if (postfix[i] >= 48 && postfix[i] <= 57)
			{
				stack.push(stoi(string(1, postfix[i])));
			}
			else
			{
				stack.push(vars.Start());
				vars.removeAt(0);
			}
		}
		return stack.pop();
	}
};
ExpressionSolver e;

class ProgramCode
{
	string* backupLines; 
	string* lines;
	string* lineTitles;
	int lineCount;
	bool checkFuncHeader(int lineNum)
	{
		string line = strip(getLine(lineNum));
		if (line.length()>5)
		{
			if (subStr(line, 0, 5) == "void ")
			{
				line = subStr(line, 4, line.length());
			}
			else if (subStr(line, 0, 4) == "int ")
			{
				line = subStr(line, 3, line.length());
			}
			else if (subStr(line, 0, 6) == "float ")
			{
				line = subStr(line, 5, line.length());
			}
			else
			{
				return false;
			}
			line = lStrip(line);
			if (line.find('(') < line.find(')') && line.find('(') != -1 && alphString(subStr(line, 0, line.find('('))))
			{
				return true;
			}
		}
		return false;
	}
	string getFuncRetType(int lineNum)
	{	
		string s = lines[lineNum];
		return subStr(s, 0, s.find(' '));
	}
	string getFuncName(int lineNum)
	{
		string s = lines[lineNum];
		s = strip(subStr(s, getFuncRetType(lineNum).length(), s.length()));
		return subStr(s, 0, s.find('('));
	}
	LinkedList<string> getFuncParams(int lineNum)
	{
		string s = lines[lineNum];
		string temp = "";
		LinkedList<string> params;
		s = subStr(s, s.find('(')+1, s.find(')'));
		for (int i = 0; s[i] != '\0'; i++)
		{
			if(s[i]==',')
			{
				params.insert(temp);
				temp = "";
			}
			else
			{
				temp.push_back(s[i]);
			}
			if (s[i + 1] == '\0')
			{
				params.insert(temp);
				temp = "";
			}
		}
		return params;
	}
	string getParamName(string s)
	{
		s = strip(s);
		return subStr(s, s.find(' ') + 1, s.length());
	}
	string getParamType(string s)
	{
		s = strip(s);
		return subStr(s, 0, s.find(' '));
	}
	int getFuncStartLine(int lineNum)
	{
		while (int(lines[lineNum].find('{')) == -1)
		{
			lineNum++;
		}
		return lineNum;
	}
	int getFuncEndLine(int lineNum)
	{
		int startLine = getFuncStartLine(lineNum);
		SpecialStack<char> stk;
		int currLineNum = startLine;
		string currLine = lines[currLineNum];
		for (int i = currLine.find('{');; i++)
		{
			if (currLine[i] == '\0')
			{
				currLineNum++;
				currLine = lines[currLineNum];
				i = 0;
			}
			if (currLine[i] == '{' || currLine[i] == '(' || currLine[i] == '[')
			{
				stk.push(currLine[i]);
			}
			else if ((currLine[i] == '}' && stk.Top() == '{') || (currLine[i] == ']' && stk.Top() == '[') || (currLine[i] == ')' && stk.Top() == '('))
			{
				stk.pop();
			}
			if (stk.isEmpty())
			{
				break;
			}
		}
		return currLineNum;
	}
	int getLineNum(string lineTitle)
	{
		return stoi(subStr(lineTitle, 1, lineTitle.length()));
	}
	int findFunctionCall(string line)
	{
		FunctionDef* funcsArr = funcs.getArray();
		int funcsArrLen = funcs.getLen();
		int funcIndex = -1;
		for (int i = 0; i < funcsArrLen; i++)
		{
			if (line.find(funcsArr[i].name) < line.find('(') && int(line.find(funcsArr[i].name)) != -1)
			{
				funcIndex = line.find(funcsArr[i].name);
				break;
			}
		}
		delete[]funcsArr;
		return funcIndex;
	}
	void executeDeclaration(string ins)
	{
		string type = subStr(ins, 0, ins.find(' '));
		string name = string();
		string value = string();
		if (int(ins.find('=')) == -1)
		{
			name = subStr(ins, ins.find(' ') + 1, ins.find(';'));
			value.push_back('0');
		}
		else
		{
			name = subStr(ins, ins.find(' ') + 1, ins.find('='));
			value = subStr(ins, ins.find('=') + 1, ins.find(';'));
		}
		if (type == "int")
		{
			rs.push(name+"="+value, 1);
		}
		else if (type == "float")
		{
			rs.push(name + "=" + value, 2);
		}
		else
		{
			cout << "Incorrect Declaration Type!\n";
		}
	}
	void executeAssignment(string ins)
	{
		string name = subStr(ins, 0, ins.find('='));
		string value = subStr(ins, ins.find('=') + 1, ins.find(';'));
		rs.updateVar(name, value);
	}
	string executePrint(string ins)
	{
		int val1 = int();
		float val2 = float();
		ins = subStr(ins, ins.find(' ')+1, ins.find(';'));
		if (ins[0] == '\"')
		{
			ins = subStr(ins, 1, ins.length() - 1);
			while (int(ins.find("\\n")) != -1)
			{
				ins = replace(ins, "\\n", "\n");
			}
			return ins;
		}
		else
		{
			val2 = e.solvePostfix(e.getPostfix(ins), e.getVarVals(ins));
			val1 = val2;
			if (val1 == val2)
			{
				return to_string(val1)+"\n";
			}
			else
			{
				return to_string(val2)+"\n";
			}
		}
	}
	void executeReturn(string ins)
	{
		FunctionDef thisFunc = getFunction(currFunction(IP))->value;
		if (thisFunc.name == "main")
		{
			while (rs.getTop())
			{
				rs.pop();
			}
			return;
		}
		int lineNum = int();
		string retAddr = string();
		string retVal = string();
		string retLine = string();
		ins = subStr(ins, ins.find(' ') + 1, ins.find(';'));
		if (thisFunc.retType == "float")
		{
			retVal = to_string(e.solvePostfix(e.getPostfix(ins), e.getVarVals(ins)));
		}
		else if (thisFunc.retType == "int")
		{
			retVal = to_string(int(e.solvePostfix(e.getPostfix(ins), e.getVarVals(ins))));
		}
		else
		{
			retVal = "";
		}
		while (retAddr.length() != 4 || retAddr[0] != 'C' || int(retAddr.find('=')) != -1)
		{
			retAddr = rs.pop();
		}
		IP = retAddr;
		for (int i = 0;i < thisFunc.paramCount; i++)
		{
			rs.pop();
		}
		lines[stoi(subStr(IP, 1, IP.length()))-100] = backupLines[stoi(subStr(IP, 1, IP.length())) - 100];
		retLine = getLine(IP);
		retLine = replace(retLine, getFunctionCall(retLine, findFunctionCall(retLine)), retVal);
		lineNum = stoi(subStr(IP, 1, IP.length())) - 100;
		lines[lineNum] = retLine;
	}
	void executeJUMP(string ins)
	{
		string lineNum = subStr(ins, ins.find("JUMP ")+5, ins.length());
		::IP = lineNum;
	}
	void executeIF(string ins)
	{
		string condStr = subStr(ins, ins.find('(') + 1, ins.find("JUMP") - 1);
		bool cond = e.solvePostfix(e.getPostfix(condStr), e.getVarVals(condStr));
		if (cond)
		{
			::IP = incIP(::IP);
		}
		else
		{
			IP = subStr(ins, ins.find("JUMP ") + 5, ins.length());
		}
	}
	string getStatementType(string IP)
	{
		int lineNum = stoi(subStr(IP, 1, IP.length())) - 100;
		string s = lines[lineNum];
		s = strip(s);
		if (s.length() == 1 && s[0] == '{')
		{
			return "openBracket";
		}
		else if (s.length() == 1 && s[0] == '}')
		{
			return "closeBracket";
		}
		else if (s.length() >= 7 && subStr(s, 0, 7) == "return ")
		{
			return "return";
		}
		else if (s.length() >= 3 && subStr(removeSpaces(s), 0, 3) == "if(")
		{
			return "if";
		}
		else if (s.length() >= 5 && (subStr(s, 0, 4) == "int " || subStr(s, 0, 6) == "float "))
		{
			return "declaration";
		}
		else if (s.length() >= 6 && subStr(s, 0, 6) == "print ")
		{
			return "print";
		}
		else if (int(s.find("if")) == -1 && int(s.find('=')) != -1)
		{
			return "assignment";
		}
		else if (s.length() >= 4 && subStr(s, 0, 4) == "else")
		{
			return "else";
		}
		else if (s.length() >= 7 && s[0] == '}')
		{
			return "jump";
		}
		else
		{
			return "None";
		}
	}
	string getFunctionCall(string line, int index)
	{
		line = subStr(line, index, line.length());
		line = subStr(line, 0, line.find(')')+1);
		return line;
	}
	void executeFunction(string func)
	{
		string params = string();
		string thisParam = string();
		string temp;
		string* paramsToPush = nullptr;
		FunctionDef newFunc;
		params = subStr(func, func.find('(') + 1, func.find(')'));
		newFunc = getFunction(removeSpaces(subStr(func, 0, func.find('('))))->value;
		if(newFunc.paramCount!=0)paramsToPush = new string[newFunc.paramCount];
		for (int i = 0, strEnd = 0; i < newFunc.paramCount; i++)
		{
			if (int(params.find(',')) == -1)
			{
				strEnd = params.length();
			}
			else
			{
				strEnd = int(params.find(','));
			}
			thisParam = removeSpaces(subStr(params, 0, strEnd));
			e.getVarVals(thisParam);
			thisParam = to_string(e.solvePostfix(e.getPostfix(thisParam), e.getVarVals(thisParam)));
			paramsToPush[i] = newFunc.paramNames[i] + "=" + thisParam;
			if (i + 1 < newFunc.paramCount)
			{
				params = subStr(params, strEnd + 1, params.length());
			}
		}
		for (int i = 0; i < newFunc.paramCount; i++)
		{
			if (newFunc.paramTypes[i] == "int")
			{
				rs.push(paramsToPush[i], 1);
			}
			else
			{
				rs.push(paramsToPush[i], 2);
			}
		}
		rs.push(IP, 3);
		temp = BP;
		BP = to_string(rs.getSP());
		rs.push(temp, 4);
		IP = "C"+to_string(newFunc.startLine + 100);
	}
public:
	ProgramCode() :lines(nullptr), lineTitles(nullptr), lineCount(0), backupLines(nullptr)
	{}
	ProgramCode(string code) :lines(nullptr),lineTitles(nullptr), lineCount(0), backupLines(nullptr)
	{
		(*this) = code;
	}
	~ProgramCode()
	{
		delete[]backupLines;
		delete[]lines;
	}
	ProgramCode& operator=(string code)
	{
		SpecialStack<char> stk;
		if (lines)
		{
			delete[]lines;
		}
		if (backupLines)
		{
			delete[]backupLines;
		}
		lineCount = 0;
		for (int i = 0; code[i] != '\0'; i++)
		{
			if (code[i] == '\n')
			{
				lineCount++;
			}
		}
		lines = new string[lineCount];
		lineTitles = new string[lineCount];
		for (int i = 0, lineNum = 0; code[i] != '\0'; i++)
		{
			if (code[i] != '\n')
			{
				lines[lineNum].push_back(code[i]);
			}
			else
			{
				lineNum++;
			}
		}
		for (int i = 0; i < lineCount; i++)
		{
			if (int(lines[i].find("//")) != -1)
				lines[i] = subStr(lines[i], 0, lines[i].find("//"));
		}
		for (int i = 0; i < lineCount; i++)
		{
			lineTitles[i] = subStr(lines[i], 0, 4);
			lines[i] = string(subStr(lines[i], 8, lines[i].length()));
		}
		for (int i = 0, temp1,temp2; i < lineCount; i++)
		{
			if (getStatementType("C" + to_string(100 + i)) == "if")
			{
				temp1 = i;
				i+=2;
				stk.push('{');
				while (!stk.isEmpty())
				{
					if (getStatementType("C" + to_string(100 + i)) == "closeBracket")
					{
						stk.pop();
					}
					else if (getStatementType("C" + to_string(100 + i)) == "openBracket")
					{
						stk.push('{');
					}
					i++;
				}
				temp2 = i-1;
				lines[temp1] = lines[temp1] + "JUMP " + "C" + to_string(100 + temp2);
				if (getStatementType("C" + to_string(100 + i)) == "else")
				{
					i+=2;
					stk.push('{');
					while (!stk.isEmpty())
					{
						if (getStatementType("C" + to_string(100 + i)) == "closeBracket")
						{
							stk.pop();
						}
						else if (getStatementType("C" + to_string(100 + i)) == "openBracket")
						{
							stk.push('{');
						}
						i++;
					}
					lines[temp2] = lines[temp2] + "JUMP " + "C" + to_string(100 + i-1);
				}
				i--;
			}
		}
		backupLines = new string[lineCount];
		for (int i = 0; i < lineCount; i++)
		{
			backupLines[i] = lines[i];
		}
		return *this;
	}
	string getLineTitle(int lineNum)
	{
		return lineTitles[lineNum];
	}
	string getLine(string lineTitle)
	{
		for (int i = 0; i < lineCount; i++)
		{
			if (lineTitles[i] == lineTitle)
			{
				return lines[i];
			}
		}
		cout << "Empty Line returned since line with title: " << lineTitle << " does not exist.\n";
		return "";
	}
	string getLine(int lineNum)
	{
		if (lineNum >= lineCount)
		{
			cout << "Empty Line returned since lineNum: " << lineNum << " does not exist.\n";
			return "";
		}
		return lines[lineNum];
	}
	LinkedList<FunctionDef> getFunctions()
	{
		LinkedList<FunctionDef> out;
		FunctionDef temp;
		LinkedList<string> stemp;
		string* sArr = nullptr;
		int sArrLen = 0;
		for (int i = 0; i < lineCount; i++)
		{
			if (checkFuncHeader(i))
			{
				temp.name = this->getFuncName(i);
				temp.retType = this->getFuncRetType(i);
				temp.startLine = this->getFuncStartLine(i);
				temp.endLine = this->getFuncEndLine(i);
				
				stemp = this->getFuncParams(i);
				sArrLen = stemp.getLen();
				temp.paramCount = sArrLen;
				if(sArrLen!=0)
				{
					sArr = stemp.getArray();
					temp.paramNames = new string[sArrLen];
					temp.paramTypes = new string[sArrLen];
				}
				for (int i = 0; i < sArrLen; i++)
				{
					temp.paramNames[i] = this->getParamName(sArr[i]);
					temp.paramTypes[i] = this->getParamType(sArr[i]);
				}
				if (sArrLen != 0)
				{
					delete[] sArr;
				}
				out.insert(temp);
				temp.clear();
			}
		}
		return out;
	}
	void printCode()
	{
		for (int i = 0; i < lineCount; i++)
		{
			cout <<lineTitles[i]<<"    "<< lines[i] << endl;
		}
	}
	bool executeFunctionFromLine(string IP)
	{
		int lineNum = stoi(subStr(IP, 1, IP.length()))-100;
		string line = lines[lineNum];
		string func = "";
		int index = findFunctionCall(line);
		if (index != -1)
		{
			func = getFunctionCall(line, index);
			executeFunction(func);
			return true;
		}
		else
		{
			return false;
		}
	}
	string executeLine(string IP)
	{
		int lineNum = stoi(subStr(IP, 1, IP.length())) - 100;
		string line = lines[lineNum];
		string statementType = getStatementType(IP);
		string out = string();
		FunctionDef thisFunc = getFunction(currFunction(IP))->value;
		if (executeFunctionFromLine(IP)) {}
		else if (statementType == "openBracket" || statementType == "None" || statementType == "closeBracket")
		{
			if (thisFunc.endLine == lineNum)
			{
				if (thisFunc.name == "main")
				{
					out = "|xx|";
				}
				executeReturn("return void;");
			}
		}
		else if (statementType == "declaration")
		{
			executeDeclaration(line);
		}
		else if (statementType == "print")
		{
			out = executePrint(line);
			lines[lineNum] = backupLines[lineNum];
		}
		else if (statementType == "assignment")
		{
			executeAssignment(line);
			lines[lineNum] = backupLines[lineNum];
		}
		else if (statementType == "return")
		{
			executeReturn(line);
		}
		else if (statementType == "jump")
		{
			executeJUMP(line);
		}
		else if (statementType == "if")
		{
			executeIF(line);
		}
		if(statementType != "return" || thisFunc.name=="main")::IP = incIP(::IP);
		return out;
	}
	bool isInfinite(FunctionDef func)
	{
		bool containsIF=false;
		bool containsSelfCall=false;
		string temp = string();
		for (int i = func.startLine; i <= func.endLine; i++)
		{
			if (!containsIF && getStatementType("C" + to_string(i + 100)) == "if")
			{
				containsIF = true;
			}
			if (!containsSelfCall && int(findFunctionCall(lines[i])) != -1)
			{
				temp = getFunctionCall(lines[i], findFunctionCall(lines[i]));
				temp = subStr(temp, 0, temp.find('('));
				if (temp == func.name)
				{
					containsSelfCall = true;
				}
			}
		}
		return !containsIF && containsSelfCall;
	}
};
ProgramCode pc;

LinkedList<FunctionDef> allFunctions(string code)
{
	LinkedList<FunctionDef> funcs;
	return funcs;
}

// Simply just read the file
// Use '\n' to sperate each line of code
string readFile(string a = "code.txt") {
	ifstream fin;
	string outStr;
	char c;
	initGlobals();
	fin.open(a, ios::in);
	if (!fin.is_open())
	{
		cout << "File \""<<a<<"\" could not be opened!\n";
	}
	else
	{
		while (!fin.eof())
		{
			c = fin.get();
			if (!fin.eof())
			{
				outStr += c;
			}
			if (fin.eof() && outStr[outStr.length() - 1] != '\n')
			{
				outStr += '\n';
			}
		}
	}
	return outStr;
}

string fixLines(string code)
{
	string out = string();
	const int keywordsCount = 5;
	string keywords[keywordsCount] = { "float", "void", "int", "print", "return" };
	bool quoteStart = 0;
	for (int i = 0; i < keywordsCount; i++)
	{
		while (int(code.find(keywords[i]+" ")) != -1)
		{
			code = replace(code, keywords[i]+" ", "@@"+to_string(i));
		}
	}
	for (int i = 0; code[i] != '\0'; i++)
	{
		if (code[i] == '\"')
		{
			quoteStart = !quoteStart;
		}
		if (code[i] != '\n' && code[i] != '\t' && (code[i]!=' ' || quoteStart))
		{
			out.push_back(code[i]);
		}
	}
	code = out;
	out = string();
	for (int i = 0; i < keywordsCount; i++)
	{
		while (int(code.find("@@" + to_string(i))) != -1)
		{
			code = replace(code, "@@" + to_string(i), keywords[i]+" ");
		}
	}
	for (int i = 0; code[i] != '\0'; i++)
	{
		if (code[i] == '\n')
		{
			continue;
		}
		out.push_back(code[i]);
		if (code[i+1] == '{' || code[i] == '}' || code[i] == '{' || code[i] == ';' || code[i+1]=='}')
		{
			out.push_back('\n');
		}
	}
	return out;
}

// Remove useless lines so line addressing is done properly
string removeLines(string code) {
	bool emptyLine = 1;
	string outStr = "";
	string nextLine = "";
	for (int i = 0; code[i]!='\0'; i++)
	{
		nextLine += code[i];
		if (code[i] != ' ' && code[i] != '\n' && code[i] != '\t')
		{
			emptyLine = 0;
		}
		if (code[i] == '\n')
		{
			if (!emptyLine)
			{
				outStr += nextLine;
			}
			nextLine = "";
			emptyLine = 1;
		}
	}
	return outStr;
}

// Use this for checking indentations (function, loops, if conditions, etc.)
//Only check for the brackets in this function 
string checkIndentationErrors(string code) {
	SpecialStack<char> stk;
	string indentError = "Indentation error not detected";
	for (int i = 0; code[i] != '\0'; i++)
	{
		if (code[i] == '(' || code[i] == '{' || code[i] == '[')
		{
			stk.push(code[i]);
		}
		else if (code[i] == ')' || code[i] == '}' || code[i] == ']')
		{
			if (stk.isEmpty() || (stk.Top() == '(' && code[i] != ')') || (stk.Top() == '{' && code[i] != '}') || (stk.Top() == '[' && code[i] != ']'))
			{
				indentError = "Indentation error detected";
				break;
			}
			stk.pop();
		}
	}
	return indentError;
}

// This prepends a line address to every single line in program
string prependLineAddress(string code) {
	int lineNum = 0;
	bool newLine = 1;
	string outStr = "";
	for (int i = 0; code[i] != '\0'; i++)
	{
		if (newLine)
		{
			outStr += "C" + to_string(100 + lineNum) + "    ";
			lineNum++;
			newLine = 0;
		}
		outStr += code[i];
		if (code[i] == '\n')
		{
			newLine = 1;
		}
	}
	return outStr;
}

// use special stack for converting expressions  
string infixToPostfix(string expression) {
	ExpressionSolver e;
	string outStr = e.getPostfix(expression);
	return outStr;
}

// Use Array based stack for evaluating the expression  
// Values contains the values of the variables used in the postfix expression  for  getting the final result
// You may look at the Test Case for understanding the working of the function   
template<typename T>
T Solving_PostfixExpression(string expression, LinkedList<T> values) {
	ExpressionSolver e;
	T value = e.solvePostfix(expression, values);
	return value;
}

void ExecuteCode(string, string);
// This function create the run time stack of the program file provided 
// Step 1:  Push the passing arguments of the function  into the stack 
// Step 2:  Push the line address of the code line that is calling the function 
// Step 3:  Push EBP to the stack (for first step conside EBP =1004 AS default value )
// Step 4:  Assign the current ESP value to EBP  
// Remember Stack Pointer(ESP) always points at the Top of the Stack and is decreased by 4 bytes whenever 
//   a value is inserted into the stack 
//  (  REPEAT THE ABOVE STEPS 1 TO 4 FOR ALL THE RECURSIVE CALLS  )
// write the output to the outputFile if the string is  not empty
void CreateRunTimeStack(string filename, string outputFile) {
	ExecuteCode(filename, "example.txt");
	ofstream out(outputFile);
	if (stackString!="" && stackString[stackString.length() - 1] == '\n')
	{
		stackString = subStr(stackString, 0, stackString.length() - 1);
	}
	for (int i = 0; stackString[i] != '\0'; i++)
	{
		out.put(stackString[i]);
	}
	out.close();
}


// Check if the function calls itself infinitely
string checkInfiniteLoop(string code) {
	FunctionDef* funcsArr = nullptr;
	int funcsArrCount = 0;
	code = prependLineAddress(fixLines(removeLines(code)));
	pc = code;
	funcs = pc.getFunctions();
	funcsArrCount = funcs.getLen();
	if(funcsArrCount)funcsArr = funcs.getArray();
	for (int i = 0; i < funcsArrCount; i++)
	{
		if (pc.isInfinite(funcsArr[i]))
		{
			delete[]funcsArr;
			return "Infinite loop detected";
		}
	}
	delete[]funcsArr;
	return "Infinite loop not detected";
}


ListNode<FunctionDef>* getFunction(string name)
{
	ListNode<FunctionDef>* ptr = funcs.getStart();
	while (ptr)
	{
		if (ptr->value.name == name)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return nullptr;
}
string incIP(string IP)
{
	return "C" + to_string(stoi(subStr(IP, 1, IP.length())) + 1);
}

string currFunction(string IP)
{
	FunctionDef* funcArr = funcs.getArray();
	int funcArrLen = funcs.getLen();
	int lineNum = stoi(subStr(IP, 1, IP.length()))-100;
	string temp;
	for (int i = 0; i < funcArrLen; i++)
	{
		if (lineNum >= funcArr[i].startLine && lineNum <= funcArr[i].endLine)
		{
			temp = funcArr[i].name;
			delete[] funcArr;
			return temp;
		}
	}
	delete[] funcArr;
	return "No Function";
}

// Start execution from the main function and use outputFile to print the output
// Must use CreateRunTimeStack() for execution of the code 
// write the output to the outputFile if the string is not empty
void ExecuteCode(string filename, string outputFile) {
	string programCode = readFile(filename);
	programCode = prependLineAddress(fixLines(removeLines(programCode)));
	string outputString = string();
	ofstream out(outputFile);
	pc = programCode;
	funcs = pc.getFunctions();
	if (!getFunction("main"))
	{
		cout << "--Program does not have Main Function--\n";
		return;
	}
	IP = pc.getLineTitle(getFunction("main")->value.startLine);
	for (string temp;true;)
	{
		temp = pc.executeLine(IP);
		if (temp == "|xx|")
		{
			break;
		}
		else
		{
			outputString += temp;
		}
	}
	if(out.is_open())
	{
		for (int i = 0; outputString[i] != '\0'; i++)
		{
			out.put(outputString[i]);
		}
		out.close();
	}
}

void initGlobals()
{
	BP = "1004";
	stackString = string();
	IP = "";
	while (rs.getTop())
	{
		rs.pop();
	}
}
