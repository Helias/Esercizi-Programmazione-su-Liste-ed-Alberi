/*
 * Coded By Helias
 *
 * Pila (Stack)
 * LIFO (Last In First Out)
 */

#include <iostream>
using namespace std;

template <class T>
class Node
{
	private:
		Node<T> *next;
		T val;
	public:
		Node(T value) { val = value; next = NULL; };
		Node<T> *getNext() { return next; }
		void setNext(Node<T> *nex) { next = nex; }
		T getVal() { return val; }
//		void setVal(T value) { val = value; }  Questo metodo non serve
};

template <class T>
class Stack
{
	private:
		Node<T> *first; // Primo elemento della Pila (l'ultimo inserito)
	public:
		Stack();
		~Stack();
		bool isEmpty() { return first == NULL; }					// vede se la pila è vuota
		bool isFull() { return false; } 		    					// vede se la pila è piena
		void Push(T elem);  				    					// aggiungi nodo
		T Pop();							   					// elimina l'ultimo nodo
		void PrintStack();      				   					// stampa pila
		void EmptyStack();   				   					// svuota pila
		void Search(T val);				   					// cerca un nodo nella Pila
		T FirstElement() { if(first != NULL) return first->getVal(); }	// restituisce il primo elemento della Pila (l'ultimo inserito)
};

template <class T>
Stack<T> :: Stack() : first(NULL) {}

template <class T>
Stack<T> :: ~Stack()
{
	if ( !isEmpty() )
	{
		Node<T> *tmp = first;
		while (tmp != NULL)
		{
			Node<T> *aux = tmp;
			tmp = tmp->getNext();
			delete aux;
		}
	}
}

template <class T>
void Stack<T> :: Push(T elem)
{
	if (isEmpty())
		first = new Node<T>(elem);
	else
	{
		Node<T> *tmp = first;
		first = new Node<T>(elem);
		first->setNext(tmp);
	}
}

template <class T>
T Stack<T> :: Pop()
{
	if(isEmpty())
		cout << "La Pila e' vuota!" << endl;
	else
	{
		T x = FirstElement();
		Node<T> *tmp = first->getNext();
		delete first;
		first = tmp;
		return x;
	}
}

template <class T>
void Stack<T> :: PrintStack()
{
	if (isEmpty())
		cout << "La Pila e' vuota!" << endl;
	else
	{
		Node<T> *tmp = first;
		while (tmp != NULL)
		{
			cout << tmp->getVal() << endl;
			tmp = tmp->getNext();
		}
	}
}

template <class T>
void Stack<T> :: Search(T val)
{
	if (isEmpty())
		cout << "La Pila e' vuota!" << endl;
	else
	{
		Node<T> *tmp = first;
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
	Stack<int> pila;		// Dichiarazione Pila

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