/*
 * Coded By Helias (Stefano Borzì)
 */
 
#include <iostream>
using namespace std;

template <class H>
struct Node
{
	Node<H> *next;
	Node<H> *prev;
	H val;
};

template <class H>
class SDList {
	public:
		virtual SDList<H>* ins(H x) = 0;
		virtual void print() = 0;
};

template <class H>
class MySDList : public SDList<H>
{
	private:
		Node<H> *head;
	public:
		MySDList() { head = NULL;  }
		SDList<H>* ins(H x);
		void print();
		int search(H x);
		SDList<H>* del(H x);
};


template <class H>
SDList<H>* MySDList<H> :: ins(H x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val = x;
		head->next = NULL;
		return this;
	}

	Node<H> *tmp = new Node<H>;
	if (x < head->val)
	{
		tmp->val = x;
		tmp->next = head;
		head = tmp;
		return this;
	}
	
	tmp = head->next;
	Node<H> *aux = head;
	while (tmp != NULL)
	{
		if (x < tmp->val)
		{
			Node<H> *aux2 = new Node<H>;
			aux2->val = x;
			aux->next = aux2;
			aux2->next = tmp;
			return this;
		}

		aux = tmp;
		tmp = tmp->next;
	}
	
	tmp = new Node<H>;
	tmp->val = x;
	tmp->next = NULL;
	aux->next = tmp;
	return this;
}




template <class H>
void MySDList<H> :: print()
{
	Node<H> *tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->val << "\t";
		tmp = tmp->next;
	}
	cout << endl;
}



template <class H>
int MySDList<H> :: search(H x)
{
	Node<H> *tmp = head;
	while (tmp != NULL)
	{
		if (tmp->val == x)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}



template <class H>
SDList<H>* MySDList<H> :: del(H x)
{
	if (head == NULL || !search(x))
		return this;

	if (head->val == x)
	{
		Node<H> *tmp = head;
		head = head->next;
		delete tmp;
	}
	
	Node<H> *tmp = head->next;
	Node<H> *aux = head;

	while (tmp != NULL)
	{
		if (tmp->val == x)
		{
			aux->next = tmp->next;
			delete tmp;
			return this;
		}
		aux = tmp;
		tmp = tmp->next;
	}
}

int main()
{
	int arr[] = {7,13,2,6,9,10,21,32,4,12};
	int del[] = {7, 4, 32, 10};

	MySDList<int> list;
	
	for (int i = 0; i < 10; i++)
		list.ins(arr[i]);
	list.print();

	for (int i = 0; i < 4; i++)
		list.del(del[i]);
	list.print();

	return 0;
}
