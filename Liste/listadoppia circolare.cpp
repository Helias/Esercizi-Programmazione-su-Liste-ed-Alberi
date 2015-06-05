/*
 * Coded By Helias
 *
 * Lista Doppia Circolare
*/
#include <iostream>
using namespace std;

class Node
{
	public:
		Node(int val) { value = val; next = NULL; prev = NULL; }
		Node *getNext() { return next; }
		Node *getPrev() { return prev; }
		int getVal() { return value; }
		void setVal(int val) { value = val; }
		void setNext(Node *nex) { next = nex; }
		void setPrev(Node *pre) { prev = pre; }
	private:
		Node *next;		
		Node *prev;
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
	Node *tmp = head;
	while (tmp->getNext() != NULL)
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
		head->setPrev(head);
	}
	else
	{
		Node *tmp = head;

		while (tmp->getNext() != head)
			tmp = tmp->getNext();

		Node *aux = new Node(val);
		tmp->setNext(aux);
		aux->setPrev(tmp);
		
		aux->setNext(head);
		head->setPrev(aux);
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
		Node *aux;

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
	list.insert(2);

	list.printList(); // stampa la lista

	list.search(5); // cerca nodo nella lista

	list.remove(5); // rimuove un elemento dalla lista

	list.printList(); //stampa la lista

	return 0;
}
