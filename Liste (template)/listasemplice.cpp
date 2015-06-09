/*
 * Coded By Helias
 *
 * Lista Semplice
 */
#include <iostream>
using namespace std;

template <class T>
class Node
{
	public:
		Node<T> (T val) { value = val; next = NULL;}
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
		Node<T> *min();
		Node<T> *max();
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
		head = new Node<T>(val);
	else
	{
		Node<T> *tmp = head;

		while (tmp->getNext() != NULL)
			tmp = tmp->getNext();

		Node<T> *aux = new Node<T>(val);
		tmp->setNext(aux);
	}
}

template <class T>
void List<T> :: search(T val)
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node<int> *tmp = head;
		while (tmp != NULL)
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

		while (tmp->getNext() != NULL)
		{
			if (tmp->getNext()->getVal() == val)
				aux = tmp;
			tmp = tmp->getNext();
		}
		
		// controlla l'ultimo nodo
		if (tmp->getVal() == val)
		{
			aux->setNext(NULL);
			delete tmp;
			return;
		}

		if (aux != NULL)
		{
			Node<T> *n = aux->getNext();
			aux->setNext(aux->getNext()->getNext());
			delete n;
			return;
		}
		else
		{
			Node<T> *n = head;
			head = head->getNext();
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
		while (tmp != NULL)
		{
			cout << tmp->getVal() << endl;
			tmp = tmp->getNext();
		}
	}
}

template <class T>
Node<T>* List<T> :: min()
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node<T> *tmp = head->getNext();
		Node<T> *min = head;

		while (tmp->getNext() != NULL)
		{
			if (tmp->getVal() < min->getVal())
				min = tmp;
			tmp = tmp->getNext();
		}

		if (tmp->getVal() < min->getVal())
			min = tmp;

		return min;
	}	
}

template <class T>
Node<T>* List<T> :: max()
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node<T> *tmp = head->getNext();
		Node<T> *max = head;

		while (tmp->getNext() != NULL)
		{
			if (tmp->getVal() > max->getVal())
				max = tmp;
			tmp = tmp->getNext();
		}

		if (tmp->getVal() > max->getVal())
			max = tmp;

		return max;
	}
}

int main()
{
	// Dichiarazione lista
	List<int> list;
	
	// Inserimento nodi nella lista
	list.insert(3);
	list.insert(10);
	list.insert(5);
	list.insert(6);
	list.insert(4);

	list.printList(); // stampa la lista
	
	list.search(6); // cerca nodo nella lista
	
	list.remove(5); // rimuove un elemento dalla lista
	
	list.printList(); //stampa la lista

	cout << endl;
	
	if ( !list.isEmpty() )
	{	
		cout << "min: " << list.min()->getVal() << endl; // uso la funzione min() e stampo il valore del nodo restituito

		cout << "max: " << list.max()->getVal() << endl; // uso la funzione max() e stampo il valore del nodo restituito
	}

	return 0;
}
