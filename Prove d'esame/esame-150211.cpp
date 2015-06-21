/*
 * Coded By Helias (Stefano Borzì)
 */
#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T val;
	Node<T> *next;
	Node<T> *prev;
};

template <class H>
class Table
{
	public:
		virtual void del(H x) = 0;
		virtual void insert(H x) = 0;
		virtual H* max() = 0;
		virtual H* min() = 0;
		virtual void print() = 0;
};

template <class T>
class MyTable : public Table<T>
{
	protected:
		Node<T> *head;
		Node<T> *tail;
	public:
		MyTable() { head = NULL; tail = NULL; }
		void insert(T x);
		void del(T x);
		T* max();
		T* min();
		void print();
};

template <class T>
class OrderedTable : public MyTable<T>
{
	public:
		OrderedTable() { this->head = NULL; this->tail = NULL; }
		void insert(T x);
};

template <class T>
class CircularTable : public MyTable<T>
{
	public:
		CircularTable() { this->head = this->tail = NULL; }
		void insert(T x);
		void del(T x);
		void print();
};

template <class T>
T* MyTable<T> :: max()
{
	Node<T> *tmp = head->next;
	T *max = &(head->val);
	while (tmp != NULL)
	{
		if (*max < tmp->val){
			*max = tmp->val;
		}
		tmp = tmp->next;
	}
	return max;
}

template <class T>
T* MyTable<T> :: min()
{
	Node<T> *tmp = head->next;
	T *min = &(head->val);
	while (tmp != NULL)
	{
		if (*min > tmp->val){
			*min = tmp->val;
		}
		tmp = tmp->next;
	}
	return min;
}

template <class T>
void MyTable<T> :: insert(T x)
{
	if (head == NULL)
	{
		head = new Node<T>;
		head->val = x;
	}
	else
	{
		Node<T> *tmp = head;

		while (tmp->next != NULL)
			tmp = tmp->next;

		Node<T> *aux = new Node<T>;

		aux->val = x;
		tmp->next = aux;
		aux->next = NULL;
		aux->prev = tmp;

		tail = aux;
	}
}

template <class T>
void MyTable<T> :: del(T x)
{
	Node<T> *tmp = head;
	Node<T> *aux = new Node<T>;
	
	while (tmp != NULL)
	{
		if (tmp->val == x)
			aux = tmp;
		tmp = tmp->next;
	}

	if (aux != NULL)
	{
		aux->prev->next = aux->next;
		if (aux->next != NULL)
			aux->next->prev = aux->prev;
		delete aux;
	}
}


template <class T>
void MyTable<T> :: print()
{
	Node<T> *tmp = head;

	cout << endl << "[";
	while (tmp != NULL)
	{
		cout << tmp->val << ",";
		tmp = tmp->next;
	}
	cout << "]" << endl;
}

template <class T>
void OrderedTable<T> :: insert(T x)
{
	if (this->head == NULL)
	{
		this->head = new Node<T>;
		this->head->val = x;
	}
	else
	{
		Node<T> *tmp = this->head;

		while (tmp->next != NULL)
		{
			if (x <= tmp->val)
			{
				Node<T> *aux = new Node<T>;
				aux->val = x;
				tmp->prev->next = aux;
				aux->next = tmp;
				tmp->prev = aux;
				return;
			}
			tmp = tmp->next;
		}

		Node<T> *aux = new Node<T>;

		aux->val = x;
		tmp->next = aux;
		aux->next = NULL;
		aux->prev = tmp;

		this->tail = aux;
	}
}

template <class T>
void CircularTable<T> :: insert(T x)
{
	if (this->head == NULL)
	{
		this->head = new Node<T>;
		this->head->val = x;
		this->head->next = this->head;
	}
	else
	{
		Node<T> *tmp = this->head;
		while (tmp->next != this->head)
			tmp = tmp->next;

		Node<T> *aux = new Node<T>;

		aux->val = x;
		tmp->next = aux;
		aux->next = this->head;
		aux->prev = tmp;
	}
}

template <class T>
void CircularTable<T> :: del(T x)
{
	Node<T> *tmp = this->head;
	Node<T> *aux = new Node<T>;

	while (tmp->next != this->head)
	{
		if (tmp->val == x)
			aux = tmp;
		tmp = tmp->next;
	}
	
	if (aux->val != x && tmp->val == x)
		aux = tmp;

	if (aux != NULL)
	{
		aux->prev->next = aux->next;
		if (aux->next != NULL)
			aux->next->prev = aux->prev;
		delete aux;
	}
}

template <class T>
void CircularTable<T> :: print()
{
	Node<T> *tmp = this->head;
	
	cout << "[";
	while (tmp->next != this->head)
	{
		cout << tmp->val << ",";
		tmp = tmp->next;
	}
	cout << tmp->val;
	cout << "]" << endl;
}

int main()
{
	// MyTable
	cout << endl << "MyTable" << endl;
	MyTable<int> table;

	table.insert(3);
	table.insert(7);
	table.insert(1);
	table.insert(8);
	table.insert(5);
	table.insert(2);
	table.insert(6);
	table.insert(1);
	table.insert(8);
	// table.print();
	
	table.del(8);
	table.del(7);
	table.del(1);

	table.print();
	
	cout << *(table.max()) << endl;
	cout << *(table.min()) << endl;
	

	// Ordered Table
	cout << endl << "OrderedTable" << endl;
	OrderedTable<int> ordered;

	ordered.insert(3);
	ordered.insert(7);
	ordered.insert(1);
	ordered.insert(8);
	ordered.insert(5);
	ordered.insert(2);
	ordered.insert(6);
	ordered.insert(1);
	ordered.insert(8);

	ordered.print();

	// Circular Table
	cout << endl << "CircularTable" << endl;
	CircularTable<int> circular;
	
	circular.insert(3);
	circular.insert(7);
	circular.insert(1);
	circular.insert(8);
	circular.insert(5);
	circular.insert(2);
	circular.insert(6);
	circular.insert(1);
	circular.insert(8);

	circular.del(8);
	circular.del(7);
	circular.del(1);

	circular.print();


	return 0;
}
