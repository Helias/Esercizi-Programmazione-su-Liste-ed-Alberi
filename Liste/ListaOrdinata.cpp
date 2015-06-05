/*
 * Coded By Helias
 *
 * Lista Semplice Ordinata
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
		void printList();
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
	
void List :: insert(int val)
{
	if(head == NULL)
		head = new Node(val);
	else
	{
		if (head->getVal() >= val)
		{
			Node *tmp = new Node(val);
			Node *aux = head;
			head = tmp;
			head->setNext(aux);
		}
		else
		{
			Node *tmp = head;
			while (tmp->getNext() != NULL)
			{
				if (tmp->getNext()->getVal() >= val)
				{
					Node *aux = new Node(val);
					aux->setNext(tmp->getNext());
					tmp->setNext(aux);
					return;
				}
				tmp = tmp->getNext();
			}

			Node *aux = new Node(val);
			tmp->setNext(aux);
		}
	}
}

void List :: printList()
{
	Node *tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->getVal() << endl;
		tmp = tmp->getNext();
	}
}

int main()
{
	// Dichiarazione lista
	List list;
	
	// Inserimento nodi nella lista
	list.insert(4);
	list.insert(4);
	list.insert(3);
	list.insert(5);
	list.insert(2);
	list.insert(4);
	list.insert(7);
	list.insert(6);
	list.insert(0);

	list.printList(); // stampa la lista

	return 0;
}
