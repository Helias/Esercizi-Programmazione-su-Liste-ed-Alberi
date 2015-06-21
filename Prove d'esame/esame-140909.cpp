/*
 * Coded By Helias (Stefano Borzì)
 */
 
#include <iostream>
#define K 5
using namespace std;

template <class H>
struct Node
{
	Node<H> *next;
	Node<H> *prev;
	H val[K];
};


template <class H>
class ArrayList
{
	public:
		virtual ArrayList<H>* ins(H x) = 0;
		virtual ArrayList<H>* del(H x) = 0;
		virtual int search(H x) = 0;
		virtual void print() = 0;
};


template <class H>
class MyArrayList : public ArrayList<H>
{
	protected:
		Node<H> *head;
		Node<H> *tail;
	public:
		MyArrayList() { head = NULL; tail = NULL; }
		ArrayList<H>* ins(H x);
		ArrayList<H>* del(H x);
		int search(H x);
		void print();
};

template <class H>
class OrderedArrayList : public MyArrayList<H>
{
	public:
		OrderedArrayList() { this->head = NULL; this->tail = NULL; }
		ArrayList<H>* ins(H x);
		int rank(H x);
};



template <class H>
ArrayList<H>* MyArrayList<H> :: ins(H x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val[0] = x;
		return this;
	}

	Node<H> *tmp = head;
	Node<H> *aux;

	while (tmp != NULL)
	{
		if (tmp->val[K-1] == 0)		// se l'ultimo elemento dell'array contenuto nel nodo è vuoto
		{
			for (int i = 0; i < K; i++)
			{
				if (tmp->val[i] == 0)
				{
					tmp->val[i] = x;
					return this;
				}
			}
		}
		aux = tmp;
		tmp = tmp->next;
	}

	tmp = new Node<H>;
	tmp->val[0] = x;
	aux->next = tmp;
	tmp->prev = aux;
	tail = tmp;
	return this;
}


template <class H>
ArrayList<H>* MyArrayList<H> :: del(H x)
{
	if (search(x))
	{
		Node<H> *tmp = tail;
		while (tmp != NULL)
		{
			for (int i = K-1; i >= 0; i--)
			{
				if (tmp->val[i] == x)
				{
					tmp->val[i] = 0;
					return this;
				}
			}
			tmp = tmp->prev;
		}
	}
}


template <class H>
void MyArrayList<H> :: print()
{
	if (head != NULL)
	{
		Node<H> *tmp = head;
		while (tmp != NULL)
		{
			for (int i = 0; i < K; i++)
				if (tmp->val[i] != 0)			// Se tmp->val[i] non è vuoto
					cout << tmp->val[i] << "\t";
			tmp = tmp->next;
		}
	}
	cout << endl;
}
 

template <class H>
int MyArrayList<H> :: search(H x)
{
	if (head == NULL)
		return 0;

	Node<H> *tmp = head;
	while (tmp != NULL)
	{
		for (int i = 0; i < K; i++)
			if (tmp->val[i] == x)
				return 1;

		tmp = tmp->next;
	}

	return 0;
}



template <class H>
ArrayList<H>* OrderedArrayList<H> :: ins(H x)
{
	if (this->head == NULL)
	{
		this->head = new Node<H>;
		this->head->val[0] = x;
		return this;
	}

	Node<H> *tmp = this->head;
	Node<H> *aux;
	H y,z;

	while (tmp != NULL)
	{
		for (int i = 0; i < K; i++)
		{
			if (x <= tmp->val[i])
			{
				y = tmp->val[i];
				tmp->val[i] = x;
				while (tmp != NULL)
				{
					for(int j = i+1; j < K; j++)
					{
						z = tmp->val[j];
						tmp->val[j] = y;
						y = z;
					}
					i = -1;
					if (tmp->next == NULL && tmp->val[K-1] != 0)
					{
						aux = new Node<H>;
						tmp->next = aux;
						aux->prev = tmp;
						this->tail = tmp;
					}
					tmp = tmp->next;
				}
				return this;
			}
		}
		aux = tmp;
		tmp = tmp->next;
	}

	tmp = new Node<H>;
	tmp->val[0] = x;
	aux->next = tmp;
	tmp->prev = aux;
	this->tail = tmp;

	return this;
}



template <class H>
int OrderedArrayList<H> :: rank(H x)
{
	if (this->head != NULL)
	{
		Node<H> *tmp = this->head;
		int rank = 0;

		while (tmp != NULL)
		{
			for (int i = 0; i < K; i++)
			{
				if (tmp->val[i] == x)
					return rank+1;
				
				if (tmp->val[i] <= x && tmp->val[i] != 0)
					rank++;
			}
			tmp = tmp->next;
		}
	}
}


int main()
{
	int arr[] = {23, 4, 6, 8, 12, 21, 5, 9, 7, 3, 16, 2, 24};

	// ArrayList
	MyArrayList<int> list;
	
	for (int i = 0; i < 13; i++)
		list.ins(arr[i]);
	list.print();

	list.del(4);
	list.del(5);
	list.del(16);
	list.del(2);

	list.print();

	cout << endl;

	// OrderedArrayList
	OrderedArrayList<int> ordered;
	
	for (int i = 0; i < 13; i++)
		ordered.ins(arr[i]);
	ordered.print();
	
	ordered.del(4);
	ordered.del(5);
	ordered.del(16);
	ordered.del(2);

	ordered.print();

	cout << endl;

	cout << ordered.rank(3) << "\t";
	cout << ordered.rank(8) << "\t";
	cout << ordered.rank(23) << "\t";
	
	cout << endl;

	return 0;
}
 