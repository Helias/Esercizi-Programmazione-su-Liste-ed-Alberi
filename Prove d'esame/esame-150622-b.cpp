/*
 * Coded By Helias (Stefano Borzì)
 */

#include <iostream>
#define DIM 10
using namespace std;

template <class H>
struct Node
{
	Node<H> *next;
	Node<H> *prev;
	H val;
};

template <class H>
class SDList
{
	public:
		virtual SDList<H>* ins(H x) = 0;
		virtual void print() = 0;
};

template <class H>
class MySDList : public SDList<H>
{
	private:
		Node<H> *head;
		Node<H> *tail;
		Node<H> *shortcuts[DIM];
	public:
		MySDList() { head = NULL; shortcuts[DIM] = NULL; }

		void fixArray()
		{
			if (head == NULL) return;

			Node<H> *tmp = head;
			for (int i = 0; i < DIM; i++)
			{
				shortcuts[i] = NULL;

				int j = 10 * (i+1);
				while (tmp != NULL)
				{
					if (tmp->val <= j  && tmp->val > (j-10))
					{
						shortcuts[i] = tmp;
						break;
					}
					tmp = tmp->next;
				}
				// cout << j << "\t";
				j *= (i+1);
			}
		}
		
		void printArray()
		{
			for (int i = 0; i < DIM; i++)
				if (shortcuts[i] != NULL)
					cout << shortcuts[i]->val << ",";
			cout << endl;
		}

		SDList<H> *ins(H x)
		{
			if (x < 1 || x > 100)
				return this;

			if (head == NULL)
			{
				head = new Node<H>;
				head->val = x;
				head->next = NULL;
				fixArray();
				return this;
			}
			
			if (x <= head->val )
			{
				Node<H> *tmp = new Node<H>;
				tmp->val = x;
				tmp->next = head;
				head->prev = tmp;
				head = tmp;
				fixArray();
				return this;
			}

			Node<H> *tmp = head;
			Node<H> *tmp2;

			while (tmp != NULL)
			{
				if (x <= tmp->val)
				{
					Node<H> *aux = new Node<H>;
					aux->val = x;
					aux->prev = tmp->prev;
					tmp->prev->next = aux;
					aux->next = tmp;
					tmp->prev = aux;
					fixArray();
					return this;
				}
				tmp2 = tmp;
				tmp = tmp->next;
			}

			Node<H> *aux = new Node<H>;
			aux->val = x;
			aux->prev = tmp2;
			tmp2->next = aux;
			aux->next = NULL;
			tail = aux;
			fixArray();
			return this;
		}
		
		void print()
		{
			Node<H> *tmp = head;
			while (tmp != NULL)
			{
				cout << tmp->val << "\t";
				tmp = tmp->next;
			}
			cout << endl;
		}

		int search(H x)
		{
			if (head == NULL)
				return 0;

			Node<H> *tmp = head;
			while (tmp != NULL)
			{
				if (tmp->val == x)
					return 1;
				tmp = tmp->next;
			}
			return 0;
		}

		MySDList<H>* del(H x)
		{
			if (head == NULL)
				return this;

			Node<H> *tmp = head;
			while (tmp != NULL)
			{
				if (tmp->val == x)
				{
					tmp->prev->next = tmp->next;
					if (tmp != tail)
						tmp->next->prev = tmp->prev;
					delete tmp;
					fixArray();
					return this;
				}
				tmp = tmp->next;
			}
			return this;
		}
};


int main()
{
	MySDList<int> list;

	int arr[] = {7,13,2,6,9,10,21,32,4,12};

	for (int i = 0; i < 10; i++)
		list.ins(arr[i]);
	list.print();

//	cout << endl << list.search(21) << endl;

	list.del(7);
	list.del(4);
	list.del(32);
	list.del(10);

	list.print();

//	list.printArray();

	return 0;
}
