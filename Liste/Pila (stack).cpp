/*
 * Coded By Helias
 *
 * Pila (Stack)
 * LIFO (Last In First Out)
 */

#include <iostream>
using namespace std;

class Node
{
	private:
		Node *next;
		int val;
	public:
		Node(int value) { val = value; next = NULL; };
		Node *getNext() { return next; }
		void setNext(Node *nex) { next = nex; }
		int getVal() { return val; }
//		void setVal(int value) { val = value; }  Questo metodo non serve
};

class Stack
{
	private:
		Node *first; // Primo elemento della Pila (l'ultimo inserito)
	public:
		Stack();
		~Stack();
		bool isEmpty() { return first == NULL; }				// vede se la pila è vuota
		bool isFull() { return false; } 		    				// vede se la pila è piena
		void Push(int elem);  				    				// aggiungi nodo
		int Pop();							   				// elimina l'ultimo nodo
		void PrintStack();      				   				// stampa pila
		void EmptyStack();   				   				// svuota pila
		void Search(int val);				   				// cerca un nodo nella Pila
		int FirstElement() { if(first != NULL) return first->getVal(); }	// restituisce il primo elemento della Pila (l'ultimo inserito)
};

Stack :: Stack() : first(NULL) {}

Stack :: ~Stack()
{
	if ( !isEmpty() )
	{
		Node *tmp = first;
		while (tmp != NULL)
		{
			Node *aux = tmp;
			tmp = tmp->getNext();
			delete aux;
		}
	}
}

void Stack :: Push(int elem)
{
	if (isEmpty())
		first = new Node(elem);
	else
	{
		Node *tmp = first;
		first = new Node(elem);
		first->setNext(tmp);
	}
}

int Stack :: Pop()
{
	if(isEmpty())
		cout << "La Pila e' vuota!" << endl;
	else
	{
		int x = FirstElement();
		Node *tmp = first->getNext();
		delete first;
		first = tmp;
		return x;
	}
}

void Stack :: PrintStack()
{
	if (isEmpty())
		cout << "La Pila e' vuota!" << endl;
	else
	{
		Node *tmp = first;
		while (tmp != NULL)
		{
			cout << tmp->getVal() << endl;
			tmp = tmp->getNext();
		}
	}
}


void Stack :: Search(int val)
{
	if (isEmpty())
		cout << "La Pila e' vuota!" << endl;
	else
	{
		Node *tmp = first;
		while (tmp != NULL)
		{
			if (tmp->getVal() == val)
			{
				cout << "Nodo trovato nella Pila!" << endl;
				return;
			}
		}
		cout << "Nodo non trovato =(" << endl;
	}
}

int main()
{
	Stack pila;		// Dichiarazione Pila

	// Inserimento Nodi
	pila.Push(3);
	pila.Push(2);
	pila.Push(6);
	pila.Push(63);
	pila.Push(20);
	
	pila.PrintStack();	// Stampo la Pila
	
	pila.Pop();		// Elimina un nodo
	pila.Pop();		// Elimina un nodo
	
	cout << endl;

	pila.PrintStack();	// Stampa la Pila


	return 0;
}