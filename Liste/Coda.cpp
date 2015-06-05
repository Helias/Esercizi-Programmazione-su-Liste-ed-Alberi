/*
 * Coded By Helias
 *
 * Coda (Tail)
 * FIFO (First In First Out)
 */

#include <iostream>
#define MaxDimTail 10
using namespace std;

class Tail
{
	private:
		int head;
		int tail;
		int VettTail[MaxDimTail];
	public:
		Tail();
		void Enqueue(int x);
		int Dequeue();
		void PrintTail();
//		int getHead() { return head; }
		int isEmpty() { return (head== -1); }
		int isFull() { return ( (tail+1) % MaxDimTail == head); }
};

Tail :: Tail() : head(-1), tail(-1) {}

void Tail :: Enqueue(int x)
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

int Tail :: Dequeue()
{
	if(isEmpty())
		cout << "La Coda e' vuota!" << endl;
	else
	{
		int x = VettTail[head];
		head = (head + 1) % MaxDimTail;

		if ( (head - 1) % MaxDimTail == tail)
			head = tail = -1;
		
		return x;
	}
}

void Tail :: PrintTail()
{	
	if (isEmpty())
		cout << "La Coda e' vuota!" << endl;
	else
	{
		int i = head, x = 0;
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
	Tail coda;
	
	for (int i = 0; i < MaxDimTail; i++)
		coda.Enqueue( (i+1) * 10 );

	coda.PrintTail();

	cout << endl;

	for (int i = 0; i < MaxDimTail; i++)
		coda.Dequeue();

	coda.PrintTail();

	return 0;
}
