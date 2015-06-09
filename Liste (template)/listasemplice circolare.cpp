/*
 * Coded By Helias
 *
 * Lista Semplice Circolare
 */
#include <iostream>
using namespace std;

template <class T>
class Node
{
	public:
		Node(T val) { value = val; next = NULL;}
		Node<T> *getNext() { return next; }
		T getVal() { return value; }
		void setVal(T val) { value = val; }
		void setNext(Node<T> *nex) { next = nex; }
	private:
		Node<T> *next;		
		T value;
};

template <class T>
class List
{
	public:
		List();
		~List();
		void insert(T val);
		void remove(T val);
		void printList();
		void search(T val);
		bool isEmpty() { return head == NULL; }
		bool isFull() { return ( !isEmpty() ); }
	private:
		Node<T> *head;
};

template <class T>
List<T> :: List() : head(NULL) {}

template <class T>
List<T> :: ~List()
{
	if (isEmpty())
		return;
	
	Node<T> *tmp = head;
	while (tmp->getNext() != head)
	{
		Node<T> *aux = tmp;
		tmp = tmp->getNext();
		delete aux;
	}
	delete tmp;
}

template <class T>
void List<T> :: insert(T val)
{
	if(head == NULL)
	{
		head = new Node<T>(val);
		head->setNext(head);
	}
	else
	{
		Node<T> *tmp = head;

		while (tmp->getNext() != head)
			tmp = tmp->getNext();

		Node<T> *aux = new Node<T>(val);
		tmp->setNext(aux);
		aux->setNext(head);
	}
}

template <class T>
void List<T> :: search(T val)
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node<T> *tmp = head;
		while (tmp->getNext() != head)
		{
			if (tmp->getVal() == val)
			{
				cout << "Nodo trovato!" << endl;
				return;
			}
			tmp = tmp->getNext();
		}
		cout << "Nodo non trovato =(" << endl;
	}
}

template <class T>
void List<T> :: remove(T val)
{
	if(isEmpty())
		cout << "Impossibile cancellare il nodo, la lista e' vuota!" << endl;
	else
	{		
		Node<T> *tmp = head;
		Node<T> *aux = NULL;

		while (tmp->getNext() != head)
		{
			if (tmp->getNext()->getVal() == val)
				aux = tmp;
			tmp = tmp->getNext();
		}
		
		// controlla l'ultimo nodo
		if (tmp->getVal() == val)
		{
			aux->setNext(head);
			delete tmp;
			return;
		}
		
		if(head->getVal() == val)
		{
			tmp->setNext( head->getNext() );
			delete head;
			head = tmp->getNext();
			return;
		}

		if (aux != NULL)
		{
			Node<T> *n = aux->getNext();
			aux->setNext(aux->getNext()->getNext());
			delete n;
			return;
		}
		cout << "Impossibile cancellare il nodo, Nodo non trovato." << endl;
	}
}

template <class T>
void List<T> :: printList()
{
	if(isEmpty())
		cout << "Impossibile stampare la lista (la lista e' vuota)." << endl;
	else
	{
		Node<T> *tmp = head;
		while (tmp->getNext() != head)
		{
			cout << tmp->getVal() << endl;
			tmp = tmp->getNext();
		}
		cout << tmp->getVal() << endl;
	}
}

int main()
{
	// Dichiarazione lista
	List<int> list;
	
	// Inserimento nodi nella lista
	list.insert(4);
	list.insert(10);
	list.insert(5);
	list.insert(6);
	list.insert(4);

	list.printList(); // stampa la lista
	
	list.search(3); // cerca nodo nella lista

	list.remove(4); // rimuove un elemento dalla lista
	
	list.printList(); //stampa la lista

	return 0;
}
