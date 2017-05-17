// Name  : Brandon Alvino
// Email : null793@gmail.com
// Project 7

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
using namespace std;

struct Node
{
	int data;
	int balance = 0;
	Node * left = NULL;
	Node * right = NULL;
};

class Tree
{
private:
	Node * root = NULL;
	bool done = false;

	void addRecursive(Node * &trav, int data)
	{
		if (!trav)
		{
			trav = new Node;
			trav->data = data;
		}

		else if (trav->data == data)
		{
			cout << data << " already exists in the tree." << endl;
			system("pause");
			done = true;
			return;
		}

		else if (trav->data > data)
		{
			addRecursive(trav->left, data);

			if(!done)
				trav->balance--;

			if (trav->balance == -2)
			{
				if (trav->left && trav->left->balance < 0)
					singleRotateLeft(trav);

				else
					doubleRotateLeft(trav);
			}

			if (trav->balance == 0)
				done = true;

		}

		else
		{
			addRecursive(trav->right, data);

			if(!done)
				trav->balance++;

			if (trav->balance == 2)
			{
				if (trav->right && trav->right->balance > 0)
					singleRotateRight(trav);

				else
					doubleRotateRight(trav);
			}

			if (trav->balance == 0)
				done = true;
		}
	}

	void Delete(Node * &trav, int item)
	{
		if (!trav)
		{
			cout << item << " is not in the tree." << endl;
			done = true;
			return;
		}

		if (trav->data == item)
		{
			if (!(trav->right) && !(trav->left))
			{
				delete trav;
				trav = NULL; // Smile
			}

			else if (trav->right && trav->left)
				trav->data = Pull(trav->left);

			else
			{
				Node * temp = trav;

				if (trav->left)
					trav = trav->left;

				else
					trav = trav->right;

				delete temp;
			}
		}

		else if (trav->data > item)
		{
			Delete(trav->left, item);

			if (!done)
			{
				trav->balance++;

				if (trav->balance == 1)
					done = true;

				if (trav->balance == 2)
				{
					if (trav->right->balance > 0)
						singleRotateRight(trav); 

					else
						doubleRotateRight(trav); 
				}
			}
		}

		else 
		{
			Delete(trav->right, item);

			if (!done)
			{
				trav->balance--;

				if (trav->balance == -1)
					done = true;

				else if (trav->balance == -2)
				{
					if (trav->left->balance < 0)
						singleRotateLeft(trav);

					else
						doubleRotateLeft(trav); 
				}
			}
		}
	}

	int Pull(Node * &trav)
	{
		if (!trav->right)
		{
			int data = trav->data;
			Node * temp = trav;
			trav = temp->left;
			delete temp;

			return data;
		}
	}

	void singleRotateRight(Node * &trav)
	{
		Node * temp = trav->right;

		trav->right = temp->left;
		temp->left = trav;
		trav = temp;

		trav->left->balance = 0;
		trav->balance = 0;
	}

	void singleRotateLeft(Node * &trav)
	{
		Node * temp = trav->left;

		trav->left = temp->right;
		temp->right = trav;
		trav = temp;

		trav->right->balance = 0;
		trav->balance = 0;
	}

	void doubleRotateRight(Node * &trav)
	{
		Node * temp = trav;

		trav = temp->right->left;
		temp->right->left = trav->right;
		trav->right = temp->right;
		temp->right = trav->left;
		trav->left = temp;

		cbal(trav);
	}

	void doubleRotateLeft(Node * &trav)
	{
		Node * temp = trav;

		trav = temp->left->right;
		temp->left->right = trav->left;
		trav->left = temp->left;
		temp->left = trav->right;
		trav->right = temp;

		cbal(trav);
	}

	void cbal(Node * &trav)
	{
		if (trav->balance == 1)
		{
			trav->left->balance = -1;
			trav->right->balance = 0;
		}

		else if (trav->balance == -1)
		{
			trav->right->balance = 1;
			trav->left->balance = 0;
		}

		else
			trav->left->balance = trav->right->balance = 0;

		trav->balance = 0;
	}

	void goTo(int x, int y)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hConsole, pos);
	}

	void recPrintTree(int low, int high, int lev, Node * &trav)
	{
		int mid = (high + low) / 2;

		goTo(mid, lev);
		cout << trav->data;

		goTo(mid, lev + 1);
		cout << trav->balance;

		if (trav->left)
			recPrintTree(low, mid, lev + 3, trav->left);

		if (trav->right)
			recPrintTree(mid, high, lev + 3, trav->right);
	}

	void postorderClear(Node * &x)
	{
		if(x->left)
			postorderClear(x->left);

		if(x->right)
		postorderClear(x->right);

		delete x;
		x = NULL;
	}

	void ordered(Node * &x)
	{
		cout << x->data << " ";
		
		if (x->left)
			ordered(x->left);

		if (x->right)
			ordered(x->right);
	}

public:
	void addnode(int data)
	{
		done = false;
		addRecursive(root, data);
	}

	void deletenode(int data)
	{
		done = false;
		Delete(root, data);
	}

	void showtree()
	{
		if (root)
		{
			recPrintTree(0, 78, 0, root);
			cout << endl;
		}

		else
			cout << "Tree is empty." << endl;
	}

	void inorder()
	{
		if (root)
		{
			cout << "[ ";
			ordered(root);
			cout << "]" << endl;
		}

		else
			cout << "Tree is empty." << endl;
	}

	void cleartree()
	{
		if (root)
		{
			postorderClear(root);
			cout << "Cleared the tree." << endl;
		}

		else
			cout << "Tree is already empty" << endl;
	}

	void testing()
	{
		cout << root->right->left->data<< endl;
		
	}
};

int main()
{
	Tree t;
	bool c = true;
	int cond;
	int val;
	//t.addnode(42);
	//t.addnode(50);
	//t.addnode(49);
	//t.testing();
	while (c)
	{
		cout << "1. Add Node       4. Clear Tree" << endl;
		cout << "2. Delete Node    5. Show Tree" << endl;
		cout << "3. Print Inorder  6. Exit" << endl;
		cout << "Input: ";

		cin >> cond;

		switch (cond)
		{
		case 1: 
			cout << "\nEnter data: ";
			cin >> val;
			t.addnode(val);
			break;

		case 2: 
			cout << "\nEnter data: ";
			cin >> val;
			t.deletenode(val);
			break;

		case 3: 
			t.inorder();
			system("pause");
			break;

		case 4:
			t.cleartree();
			system("pause");
			break;

		case 5:
			system("cls");
			t.showtree();
			system("pause");
			break;

		case 6: 
			c = false;
			break;

		default:
			cout << "Invalid input." << endl;
		}

		system("cls");

	}
}