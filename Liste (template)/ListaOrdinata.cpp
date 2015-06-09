/*
 * Coded By Helias
 *
 * Lista Semplice Ordinata
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
		void printList();
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
		head = new Node<T>(val);
	else
	{
		if (head->getVal() >= val)
		{
			Node<T> *tmp = new Node<T>(val);
			Node<T> *aux = head;
			head = tmp;
			head->setNext(aux);
		}
		else
		{
			Node<T> *tmp = head;
			while (tmp->getNext() != NULL)
			{
				if (tmp->getNext()->getVal() >= val)
				{
					Node<T> *aux = new Node<T>(val);
					aux->setNext(tmp->getNext());
					tmp->setNext(aux);
					return;
				}
				tmp = tmp->getNext();
			}

			Node<T> *aux = new Node<T>(val);
			tmp->setNext(aux);
		}
	}
}

template <class T>
void List<T> :: printList()
{
	Node<T> *tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->getVal() << endl;
		tmp = tmp->getNext();
	}
}

int main()
{
	// Dichiarazione lista
	List<int> list;
	
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
