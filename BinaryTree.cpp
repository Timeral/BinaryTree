#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Tree
{
private:
	char data;
	void buildTree(Tree* p,int len, string& front, string& middle, int i, int j)
	{
		if (len <= 0)
		{
			p->data = '#';
			return;
		}
		p->data = front[i];
		int h;
		for (h = j; h < j + len; ++h)
		{
			if (middle[h] == front[i]) break;
		}
		p->lchild = new Tree('#');
		buildTree(p->lchild,h - j, front, middle, i + 1, j);
		p->rchild = new Tree('#');
		buildTree(p->rchild,len - h + j - 1, front, middle, i + h - j + 1, h + 1);
	}
public:
	Tree* lchild;
	Tree* rchild;
	Tree(char c)
	{
		this->data = c;
		this->lchild = NULL;
		this->rchild = NULL;
	}
	Tree(string& s)
	{
		stack<Tree*> a;
		int i = 1;
		Tree* p = this;
		this->data = s[0];
		this->lchild = NULL;
		this->rchild = NULL;
		if (this->data != '#')
			while (i < s.size())
			{
				if (p != NULL && p->data == '#')
				{
					if (!a.empty())
					{
						p = a.top();
						a.pop();
					}
					else
						break;
				}
				else if (p->lchild != NULL && p->lchild->data == '#')
				{
					if (!a.empty())
					{
						p = a.top();
						a.pop();
					}
					else
						break;
				}
				else if (p->lchild == NULL)
				{
					p->lchild = new Tree(s[i]);
					++i;
					if (s[i - 1] == '#')
					{
						if (i < s.size())
						{
							p->rchild = new Tree(s[i]);
							++i;
							a.push(p);
							p = p->rchild;
						}
					}
					else
					{
						a.push(p);
						p = p->lchild;
					}
				}
				else if (p->rchild == NULL)
				{
					p->rchild = new Tree(s[i]);
					++i;
					if (s[i - 1] == '#')
					{
						if (!a.empty())
						{
							p = a.top();
							a.pop();
						}
						else
							break;
					}
					else
					{
						a.push(p);
						p = p->rchild;
					}
				}
				else if (p->lchild != NULL && p->lchild->data != '#')
				{
					if (!a.empty())
					{
						p = a.top();
						a.pop();
					}
					else
						break;
				}
				else
					break;
			}
	}
	Tree(string& front, string& middle)
	{
		buildTree(this,front.size(), front, middle, 0, 0);
	}
	void frontPrint()
	{
		stack<Tree*> a;
		Tree* p = this;
		while (p != NULL)
		{
			if (p->data != '#')
			{
				cout << p->data;
				a.push(p);
				p = p->lchild;
			}
			else
			{
				if (!a.empty())
				{
					p = a.top()->rchild;
					a.pop();
				}
				else
					break;
			}
		}
		cout << endl;
	}
	void middlePrint()
	{
		stack<Tree*> a;
		Tree* p = this;
		while (p != NULL || !a.empty())
		{
			while (p != NULL && p->data != '#')
			{
				a.push(p);
				p = p->lchild;
			}
			if (!a.empty())
			{
				cout << a.top()->data;
				p = a.top()->rchild;
				a.pop();
			}
			else
				break;
		}
		cout << endl;
	}
	void backPrint()
	{
		stack<Tree*> a;
		Tree* p = this;
		Tree* q = NULL;
		a.push(p);
		if (p->data != '#')
			while (!a.empty())
			{
				p = a.top();
				if ((p->lchild != NULL) && (p->rchild != NULL) && ((p->lchild->data == '#' && p->rchild->data == '#') || (q != NULL && (q == p->lchild || q == p->rchild))))
				{
					cout << a.top()->data;
					a.pop();
					q = p;
				}
				else
				{
					if (p->rchild != NULL && p->rchild->data != '#')
					{
						a.push(p->rchild);
					}
					if (p->lchild != NULL && p->lchild->data != '#')
					{
						a.push(p->lchild);
					}
				}
			}
		cout << endl;
	}
	int getLeafNum()
	{
		int num = 0;
		stack<Tree*> a;
		Tree* p = this;
		a.push(p);
		while (p != NULL && !a.empty())
		{
			if (p->lchild != NULL && p->rchild != NULL && p->rchild->data == '#' && p->lchild->data == '#')
			{
				num++;
			}
			if (p->data != '#')
			{
				a.push(p);
				p = p->lchild;
			}
			else
			{
				if (!a.empty())
				{
					p = a.top()->rchild;
					a.pop();
				}
				else
					break;
			}
		}
		return num;
	}
	int getNodeNum()
	{
		int num = 0;
		stack<Tree*> a;
		Tree* p = this;
		a.push(p);
		while (p != NULL && !a.empty())
		{
			if (p->data != '#')
			{
				num++;
				a.push(p);
				p = p->lchild;
			}
			else
			{
				if (!a.empty())
				{
					p = a.top()->rchild;
					a.pop();
				}
				else
					break;
			}
		}
		return num;
	}
	int getNodeNum(int floor)
	{
		int num = 0, currFloor = 1, maxFloor = getFloor();
		if (floor == 1 && this->data == '#')
			return 0;
		else if (floor == 1)
			return 1;
		else if (floor > maxFloor)
			return -1;
		stack<pair<Tree*, int>> a;
		Tree* p = this;
		while (p != NULL)
		{
			if (currFloor == floor && p->data != '#')
			{
				num++;
			}
			if (p->data != '#')
			{
				a.push(make_pair(p, currFloor));
				++currFloor;
				p = p->lchild;
			}
			else
			{
				if (!a.empty())
				{
					p = a.top().first->rchild;
					currFloor = a.top().second + 1;
					a.pop();
				}
				else
					break;
			}
		}
		return num;
	}
	int getFloor(char c = '#')
	{

		stack<pair<Tree*, int>> a;
		Tree* p = this;
		int floor = 1;
		int maxFloor = 0;
		while (p != NULL)
		{
			if (c != '#')
			{
				if (p != NULL && c == p->data)
				{
					return floor;
				}
			}
			if (p->lchild != NULL && p->rchild != NULL && p->rchild->data == '#' && p->lchild->data == '#')
			{
				if (floor > maxFloor)
					maxFloor = floor;
			}
			if (p->data != '#')
			{
				a.push(make_pair(p, floor));
				++floor;
				p = p->lchild;
			}
			else
			{
				if (!a.empty())
				{
					p = a.top().first->rchild;
					floor = a.top().second + 1;
					a.pop();
				}
				else
					break;
			}
		}
		if (c == '#')
			return maxFloor;
		else
			return -1;
	}
	void swapPrint()
	{
		stack<Tree*> a;
		Tree* p = this;
		while (p != NULL)
		{
			if (p->data != '#')
			{
				cout << p->data;
				a.push(p);
				p = p->rchild;
			}
			else
			{
				if (!a.empty())
				{
					p = a.top()->lchild;
					a.pop();
				}
				else
					break;
			}
		}
		cout << endl;
	}
};

int main()
{
	return 0;
}
