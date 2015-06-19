/*
 * Coded By Helias (Stefano Borzì)
 */
 
#include <iostream>
using namespace std;

template <class H>
class List
{
	public:
		virtual List<H>* ins(H *x) = 0;
		virtual List<H>* del(H *x) = 0;
		virtual int search(H *x) = 0;
		virtual void print() = 0;
};

template <class H>
struct Node
{
	Node<H> *next;
	H val;
};

template <class H>
class MyList : public List<H>
{
	private:
		Node<H> *head;
	public:
		MyList() { head = NULL; }
		List<H>* ins(H *x);
		List<H>* del(H *x);
		int search(H *x);
		void print();
};


template <class H>
class OrderedList : public MyList<H>
{
	private:
		Node<H> *head;
	public:
		OrderedList() { head = NULL; }
		List<H>* ins(H *x);
		List<H>* del(H *x);
		void print();
};


template <class H>
class Stack {
	public:
		virtual void push(H *x) = 0;
		virtual H pop() = 0;
};


template <class H>
class MyStack : public MyList<H>, public Stack<H>
{
	private:
		Node<H> *head;
	public:
		MyStack() { head = NULL; }
		void push(H *x);
		H pop();
		void print();
};


template <class H>
class Queue {
	public:
		virtual void enqueue(H *x) = 0;
		virtual H dequeue() = 0;
};

template <class H>
class MyQueue : public MyList<H>, public Queue<H>
{
	private:
		Node<H> *head;
		Node<H> *tail;
	public:
		MyQueue() { head = NULL; tail = NULL; }
		void enqueue(H *x);
		H dequeue();
		void print();
};

template <class H>
List<H>* MyList<H> :: ins(H *x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val = *x;
		head->next = NULL;
		return this;
	}

	Node<H> *tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	Node<H> *aux = new Node<H>;
	aux->val = *x;
	aux->next = NULL;
	tmp->next = aux;

	return this;
}

template <class H>
int MyList<H> :: search(H *x)
{
	if (head == NULL)
		return 0;

	Node<H> *tmp = head;
	while (tmp != NULL)
	{
		if (tmp->val == *x)
			return 1;
		tmp = tmp->next;
	}

	return 0;
}

template <class H>
List<H>* MyList<H> :: del(H *x)
{
	if(!search(x))
	{
		cout << "Nodo non presente nella lista!" << endl;
		return this;
	}
	
	if(head->val == *x)
	{
		Node<H> *tmp = head;
		head = tmp->next;
		delete tmp;
		return this;
	}
	
	Node<H> *tmp = head;
	Node<H> *aux;

	while (tmp != NULL)
	{
		aux = tmp;
		tmp = tmp->next;
		if (tmp->val == *x)
		{
			aux->next = tmp->next;
			delete tmp;
			return this;
		}
	}

	return this;
}

template <class H>
void MyList<H> :: print()
{
	if (head == NULL)
	{
		cout << "La lista è vuota!!" << endl;
		return;
	}

	Node<H> *tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->val << "\t";
		tmp = tmp->next;
	}
	cout << endl;
}


template <class H>
List<H>* OrderedList<H> :: ins(H *x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val = *x;
		head->next = NULL;
		return this;
	}
	
	if (head->val >= *x)
	{
		Node<H> *tmp = new Node<H>;
		Node<H> *aux = head;
		tmp->val = *x;
		tmp->next = aux;
		head = tmp;
		return this;
	}

	Node<H> *tmp = head;
	while (tmp->next != NULL)
	{
		if (tmp->next->val >= *x)
		{
			Node<H> *aux = new Node<H>;
			aux->val = *x;
			aux->next = tmp->next;
			tmp->next = aux;
			return this;
		}
		tmp = tmp->next;
	}

	Node<H> *aux = new Node<H>;
	aux->val = *x;
	aux->next = NULL;
	tmp->next = aux;

	return this;
}

template <class H>
void OrderedList<H> :: print()
{
	if (head == NULL)
	{
		cout << "La lista è vuota!!" << endl;
		return;
	}

	Node<H> *tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->val << "\t";
		tmp = tmp->next;
	}
	cout << endl;
}

template <class H>
List<H>* OrderedList<H> :: del(H *x)
{	
	if(head->val == *x)
	{
		Node<H> *tmp = head;
		head = tmp->next;
		delete tmp;
		return this;
	}
	
	Node<H> *tmp = head;
	Node<H> *aux;

	while (tmp != NULL)
	{
		aux = tmp;
		tmp = tmp->next;
		if (tmp->val == *x)
		{
			aux->next = tmp->next;
			delete tmp;
			return this;
		}
	}
	return this;
}

template <class H>
H MyStack<H> :: pop()
{
	if (head != NULL)
	{
		Node<H> *tmp = head;
		head = tmp->next;
		H x = tmp->val;
		delete tmp;
		return x;
	}
}

template <class H>
void MyStack<H> :: push(H *x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val = *x;
		head->next = NULL;
	}
	else
	{
		Node<H> *tmp = new Node<H>;
		tmp->val = *x;
		tmp->next = head;
		head = tmp;
	}
}

template <class H>
void MyStack<H> :: print()
{
	if (head != NULL)
	{
		Node<H> *tmp = head;
		while (tmp != NULL)
		{
			cout << tmp->val << "\t";
			tmp = tmp->next;
		}
		cout << endl;
	}
}



template <class H>
void MyQueue<H> :: enqueue(H *x)
{
	if (head == NULL)
	{
		head = new Node<H>;
		head->val = *x;
		head->next = NULL;
		tail = head;
		return;
	}

	Node<H> *tmp = new Node<H>;
	tmp->val = *x;
	tail->next = tmp;
	tail = tmp;
}


template <class H>
H MyQueue<H> :: dequeue()
{
	Node<H> *tmp = head;
	head = tmp->next;
	delete tmp;
}


template <class H>
void MyQueue<H> :: print()
{
	if (head != NULL)
	{
		Node<H> *tmp = head;
		while (tmp != NULL)
		{
			cout << tmp->val << "\t";
			tmp = tmp->next;
		}
		cout << endl;
	}
}


int main()
{
	MyList<int> list;

	// inserimento nodi
	int arr[] = {23,4,6,8,12,21,5,9,7,3,16,2,24};
	int del[] = {4,5,16,2};

	
	cout << "MyList" << endl;
	for (int i = 0; i < 13; i++)
		list.ins(&arr[i]);
	list.print();

	// cancellamento nodi
	for (int i = 0; i < 4; i++)
		list.del(&del[i]);
	list.print();

	// OrderedList
	OrderedList<int> ordered;

	cout << endl << "OrderedList" << endl;
	for (int i = 0; i < 13; i++)
		ordered.ins(&arr[i]);

	for (int i = 0; i < 4; i++)
		ordered.del(&del[i]);

	ordered.print();

	// Stack
	MyStack<int> stack;

	cout << endl << "Stack" << endl;
	for (int i = 0; i < 13; i++)
		stack.push(&arr[i]);

	for (int i = 0; i < 5; i++)
		stack.pop();

	stack.print();
	
	// Queue
	MyQueue<int> queue;
	
	cout << endl << "Queue" << endl;
	for (int i = 0; i < 13; i++)
		queue.enqueue(&arr[i]);

	for (int i = 0; i < 5; i++)
		queue.dequeue();

	queue.print();

	return 0;
 }