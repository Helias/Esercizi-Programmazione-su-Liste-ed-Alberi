/*
 * Coded By Helias
 *
 * Coda (Tail)
 * FIFO (First In First Out)
 */

#include <iostream>
#define MaxDimTail 10
using namespace std;

template <class T>
class Tail
{
	private:
		T head;
		T tail;
		T VettTail[MaxDimTail];
	public:
		Tail();
		void Enqueue(T x);
		T Dequeue();
		void PrintTail();
//		T getHead() { return head; }
		T isEmpty() { return (head== -1); }
		T isFull() { return ( (tail+1) % MaxDimTail == head); }
};

template <class T>
Tail<T> :: Tail() : head(-1), tail(-1) {}

template <class T>
void Tail<T> :: Enqueue(T x)
{
	if (isFull())
	{
		cout << "La Coda e' piena!" << endl;
	}
	else
	{
		tail = (tail + 1) % MaxDimTail;
		VettTail[tail] = x;
		if (head == -1)
			head++;
	}
}

template <class T>
T Tail<T> :: Dequeue()
{
	if(isEmpty())
		cout << "La Coda e' vuota!" << endl;
	else
	{
		T x = VettTail[head];
		head = (head + 1) % MaxDimTail;

		if ( (head - 1) % MaxDimTail == tail)
			head = tail = -1;
		
		return x;
	}
}

template <class T>
void Tail<T> :: PrintTail()
{	
	if (isEmpty())
		cout << "La Coda e' vuota!" << endl;
	else
	{
		T i = head, x = 0;
		while ( (i % MaxDimTail) != tail)
		{
			cout << "Posizione " << x << " : " << VettTail[i % MaxDimTail] << endl;
			x++;
			i++;
		}
		cout << "Posizione " << x << " : " << VettTail[i % MaxDimTail] << endl;
	}
}

int main()
{
	Tail<int> coda;
	
	for (int i = 0; i < MaxDimTail; i++)
		coda.Enqueue( (i+1) * 10 );

	coda.PrintTail();

	cout << endl;

	for (int i = 0; i < MaxDimTail; i++)
		coda.Dequeue();

	coda.PrintTail();

	return 0;
}
