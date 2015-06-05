/*
 * Coded By Helias
 *
 * Lista Semplice Circolare
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
		bool isEmpty();
		bool isFull() { return !(isEmpty()); }
	private:
		Node *head;
};

List :: List() : head(NULL) {}

List :: ~List()
{
	if (isEmpty())
		return;
	
	Node *tmp = head;
	while (tmp->getNext() != head)
	{
		Node *aux = tmp;
		tmp = tmp->getNext();
		delete aux;
	}
	delete tmp;
}

bool List :: isEmpty()
{
	if(head == NULL)
		return true;
	return false;
}
	
void List :: insert(int val)
{
	if(head == NULL)
	{
		head = new Node(val);
		head->setNext(head);
	}
	else
	{
		Node *tmp = head;

		while (tmp->getNext() != head)
			tmp = tmp->getNext();

		Node *aux = new Node(val);
		tmp->setNext(aux);
		aux->setNext(head);
	}
}

void List :: search(int val)
{
	if(isEmpty())
		cout << "La lista e' vuota!" << endl;
	else
	{
		Node *tmp = head;
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

void List :: remove(int val)
{
	if(isEmpty())
		cout << "Impossibile cancellare il nodo, la lista e' vuota!" << endl;
	else
	{		
		Node *tmp = head;
		Node *aux = NULL;

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
			Node *n = aux->getNext();
			aux->setNext(aux->getNext()->getNext());
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
	List list;
	
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
