/*
 * Coded By Helias
 *
 * Lista Doppia Circolare
 */
#include <iostream>
using namespace std;

template <class T>
class Node
{
	public:
		Node(T val) { value = val; next = NULL; prev = NULL; }
		Node<T> *getNext() { return next; }
		Node<T> *getPrev() { return prev; }
		T getVal() { return value; }
		void setVal(T val) { value = val; }
		void setNext(Node<T> *nex) { next = nex; }
		void setPrev(Node<T> *pre) { prev = pre; }
	private:
		Node<T> *next;		
		Node<T> *prev;
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
	Node<T> *tmp = head;
	while (tmp->getNext() != NULL)
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
		head->setPrev(head);
	}
	else
	{
		Node<T> *tmp = head;

		while (tmp->getNext() != head)
			tmp = tmp->getNext();

		Node<T> *aux = new Node<T>(val);
		tmp->setNext(aux);
		aux->setPrev(tmp);
		
		aux->setNext(head);
		head->setPrev(aux);
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
		Node<T> *aux;

		while (tmp->getNext() != head)
		{
			if (tmp->getVal() == val)
				aux = tmp;
			tmp = tmp->getNext();
		}
		
		if (tmp->getVal() == val)
		{
			tmp->getNext() -> setPrev( tmp->getPrev() );
			tmp->getPrev() -> setNext( tmp->getNext() );
			return;
		}

		if (aux == head)
		{
			head->getNext() -> setPrev( head->getPrev() );
			head->getPrev() -> setNext( head->getNext() );
			head = head->getNext();
			return;
		}
		
		if (aux != NULL)
		{
			aux->getNext() -> setPrev( aux->getPrev() );
			aux->getPrev() -> setNext( aux->getNext() );
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
	list.insert(2);

	list.printList(); // stampa la lista

	list.search(5); // cerca nodo nella lista

	list.remove(5); // rimuove un elemento dalla lista

	list.printList(); //stampa la lista

	return 0;
}
