/*
 * Coded By Helias (Stefano Borzì)
 */
 
#include <iostream>
using namespace std;

template <class H>
struct Node
{
	Node<H> *next;
	H val;
	int mul;
};


template <class H>
class MultiList {
	public:
		virtual MultiList<H>* ins(H x) = 0;
		virtual int multiplicity(H x) = 0;
		virtual void print() = 0;
		virtual MultiList<H>* del(H x) = 0;
};


template <class H>
class MyMultiList : public MultiList<H>
{
	private:
		Node<H> *head;
		int size;
	public:
		MyMultiList() { size = 0; head = NULL; }
		MultiList<H>* ins(H x);
		void print();
		int multiplicity(H x);
		Node<H>* searchPointer(H x);
		MultiList<H>* del(H x);
		int rank(H x);
};

template <class H>
MultiList<H>* MyMultiList<H> :: ins(H x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val = x;
		head->mul = 1;
		return this;
	}
	else
	{
		if (head->val == x)
		{
			head->mul++;
			return this;
		}
		
		Node<H> *tmp = head;
		Node<H> *aux = new Node<H>;

		if (x < head->val)
		{
			aux->val = x;
			aux->mul = 1;
			aux->next = head;
			head = aux;
			return this;
		}
		
		aux = head;
		tmp = head->next;
		while (tmp != NULL)
		{
			if (tmp->val == x)
			{
				tmp->mul++;
				return this;
			}

			if (x < tmp->val)
			{
				Node<H> *aux2 = new Node<H>;
				aux2->val = x;
				aux2->mul = 1;
				aux2->next = tmp;
				aux->next = aux2;
				return this;
			}
			aux = tmp;
			tmp = tmp->next;
		}

		tmp = new Node<H>;
		tmp->val = x;
		tmp->mul = 1;
		aux->next = tmp;
		tmp->next = NULL;
		return this;
	}
}

template <class H>
void MyMultiList<H> :: print()
{
	Node<H> *tmp = head;
	while(tmp != NULL)
	{
		if (tmp->mul == 1)
			cout << tmp->val << "\t";
		else
		{
			for (int i = 0; i < tmp->mul; i++)
				cout << tmp->val << "\t";
		}
		tmp = tmp->next;
	}
	cout << endl;
}


template <class H>
Node<H>* MyMultiList<H> :: searchPointer(H x)
{
	Node<H> *tmp = head;
	
	while (tmp != NULL)
	{
		if (tmp->val == x)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}


template <class H>
int MyMultiList<H> :: multiplicity(H x)
{
	Node<H> *tmp = searchPointer(x);
	if (tmp != NULL)
	{
		cout << endl << "Molteplicità: " << tmp->mul << endl;
	}
}


template <class H>
MultiList<H>* MyMultiList<H> :: del(H x)
{
	Node<H> *tmp = head;
	Node<H> *aux = new Node<H>;
	
	while (tmp != NULL)
	{
		if (tmp->val == x)
			break;
		aux = tmp;
		tmp = tmp->next;
	}
	
	if (tmp != NULL)
	{
		if (tmp->mul == 1)
		{
			aux->next = tmp->next;
			delete tmp;
		}
		else
			tmp->mul--;
	}
	
	return this;
}


template <class H>
int MyMultiList<H> :: rank(H x)
{
	if (searchPointer(x) == NULL)
		return 0;

	Node<H> *tmp = head;
	int rank = 0;

	while (tmp != NULL)
	{
		if (tmp->val < x)
		{
			for(int i = 0; i < tmp->mul; i++)
				rank++;
		}

		if (tmp->val == x)
			return rank+1;

		tmp = tmp->next;
	}
}

int main()
{
	int arr[] = {10, 5, 8, 3, 5, 1, 6, 5, 8, 1, 12, 7};
	int del[] = {6, 5, 8, 3, 8};

	MyMultiList<int> list;

	for (int i = 0; i < 12; i++)
		list.ins(arr[i]);
	list.print();
	
	for (int i = 0; i < 5; i++)
		list.del(del[i]);
	list.print();

	cout << endl;
	cout << "5 rank: [" << list.rank(5) << "]" << endl;
	cout << "6 rank: [" << list.rank(6) << "]" << endl;
	cout << "12 rank: [" << list.rank(12) << "]" << endl;
	cout << endl;

	return 0;
}
