/*
 * Coded By Helias
 *
 * Lista Semplice
 */
#include <iostream>
using namespace std;

class Node
{
	public:
		Node(int val) { value = val; next = NULL;}
		Node *getNext() { return next; }
		int getVal() { return value; }
		void setVal(int val) { value = val; }
		void setNext(Node *nex) { next = nex; }
	private:
		Node *next;
		int value;
};

class List
{
	public:
		List();
		~List();
		void insert(int val);
		void remove(int val);
		void printList();
		void search(int val);
		bool isEmpty() { return head == NULL; }
		bool isFull() { return ( !isEmpty() ); }
	private:
		Node *head;
};

List :: List() : head(NULL) {}

List :: ~List()
{
	if (isEmpty())
		return;
	
	Node *tmp = head;
	while (tmp->getNext() != NULL)
	{
		Node *aux = tmp;
		tmp = tmp->getNext();
		delete aux;
	}
	delete tmp;
}

void List :: insert(int val)
{
	if(head == NULL)
		head = new Node(val);
	else
	{
		Node *tmp = head;

		while (tmp->getNext() != NULL)
			tmp = tmp->getNext();

		Node *aux = new Node(val);
		tmp->setNext(aux);
	}
}

void List :: search(int val)
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node *tmp = head;
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

void List :: remove(int val)
{
	if(isEmpty())
		cout << "Impossibile cancellare il nodo, la lista e' vuota!" << endl;
	else
	{		
		Node *tmp = head;
		Node *aux = NULL;

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
			Node *n = aux->getNext();
			aux->setNext(aux->getNext()->getNext());
			delete n;
			return;
		}
		else
		{
			Node *n = head;
			head = head->getNext();
			delete n;
			return;
		}			
		cout << "Impossibile cancellare il nodo, Nodo non trovato." << endl;
	}
}

void List :: printList()
{
	if(isEmpty())
		cout << "Impossibile stampare la lista (la lista e' vuota)." << endl;
	else
	{
		Node *tmp = head;
		while (tmp != NULL)
		{
			cout << tmp->getVal() << endl;
			tmp = tmp->getNext();
		}
	}
}

Node* List :: min()
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node *tmp = head->getNext();
		Node *min = head;

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

Node* List :: max()
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node *tmp = head->getNext();
		Node *max = head;

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
	List list;
	
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
