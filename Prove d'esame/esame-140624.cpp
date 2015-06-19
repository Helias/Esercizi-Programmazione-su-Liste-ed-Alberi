/*
 * Coded By Helias (Stefano Borzì)
 */
#include <iostream>
using namespace std;

template <class T>
struct Node
{
	Node<T> *left;
	Node<T> *right;
	Node<T> *parent;
	T val;
	T level;
};

template <class T>
class BST
{
	public:
		virtual BST<T>* insert(T *x) = 0;
		virtual BST<T>* delet(T *x) = 0;
		virtual int search(T *x) = 0;
		virtual void naturalFill(T* v) = 0;
		virtual void postorderPrint() = 0;
		virtual void printLevel(int l) = 0;
};

template <class T>
class XBST : public BST<T>
{
	private:
		Node<T> *root;
		int size;
	public:
		XBST() { root = NULL; }
		BST<T>* insert(T *x);
		BST<T>* delet(T *x);
		void postorderPrint();
		void print(Node<T> *p);
		int search(T *x);
		Node<T> *min(Node<T> *tmp);
		void Trapianta(Node<T> *u, Node <T> *v);
		Node<T> *searchPointer(T *x);
		void printLevel(int l);
		void level(Node<T> *p, int depth);
		Node<T> *getNext(Node<T> *p);
		void naturalFill(int *v);
};

template <class T>
BST<T>* XBST<T> :: insert(T *x)
{
	if (root == NULL)
	{
		root = new Node<T>;
		root->val = *x;
		root->level = 0;
		size++;
		return this;
	}

	Node<T> *tmp = root;
	Node<T> *aux;

	while (tmp != NULL)
	{
		aux = tmp;
		if (tmp->val > *x)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	
	tmp = new Node<T>;
	tmp->val = *x;
	tmp->parent = aux;
	if (aux->val > *x)
		aux->left = tmp;
	else
		aux->right = tmp;
	tmp->level = tmp->parent->level + 1;

	size++;
	return this;
}

template <class T>
void XBST<T> :: print(Node<T> *p)
{
	if (p != NULL)
	{
		print(p->left);
		print(p->right);
		cout << p->val << "\t";
	}
}

template <class T>
void XBST<T> :: postorderPrint()
{
	print(root);
	cout << endl;
}

template <class T>
int XBST<T> :: search(T *x)
{
	if (root != NULL)
	{
		Node<T> *tmp = root;
		while (tmp != NULL)
		{
			if (tmp->val == *x)
				return 1;
			else if (tmp->val > *x)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
	}
	return 0;
}

template <class T>
Node<T>* XBST<T> :: searchPointer(T *x)
{
	if (root != NULL)
	{
		Node<T> *tmp = root;
		while (tmp != NULL)
		{
			if (tmp->val == *x)
				return tmp;
			else if (tmp->val > *x)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
	}
	return NULL;
}

template <class T>
Node<T>* XBST<T> :: min(Node<T> *tmp)
{
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}

template <class T>
void XBST<T> :: Trapianta(Node<T> *u, Node<T> *v)
{
	if (u->parent == NULL)
		root = v;
	else if (u->parent->left == u)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v != NULL)
	{
		v->parent = u->parent;
		v->level = u->level;
	}
}

template <class T>
BST<T>* XBST<T> :: delet(T *x)
{
	if (!search(x))
	{
		cout << "Nodo non trovato!" << endl;
		return this;
	}

	Node<T> *tmp = searchPointer(x);
	
	if (tmp->left == NULL)
		Trapianta(tmp, tmp->right);
	else if (tmp->right == NULL)
		Trapianta(tmp, tmp->left);
	else
	{
		Node<T> *aux = min(tmp->right);
		if (aux->parent != tmp)
		{
			Trapianta(aux, aux->right);
			aux->right = tmp->right;
			aux->right->parent = aux;
		}
		Trapianta(tmp, aux);
		aux->left = tmp->left;
		aux->left->parent = aux;
		aux->left->level = aux->parent->level + 1;
	}

	delete tmp;
	size--;

	return this;
}

template <class T>
void XBST<T> :: printLevel(int l)
{
	if (root != NULL)
	{
		cout << endl;
		level(root, l);
		cout << endl;
	}
}

template <class T>
void XBST<T> :: level(Node<T> *p, int depth)
{
	if (p != NULL)
	{
		if (depth == p->level)
			cout << p->val << "[" << p->level << "]" << "\t";
		else
		{
			level(p->left, depth);
			level(p->right, depth);
		}
	}
}

template <class T>
Node<T>* XBST<T> :: getNext(Node<T> *p)
{
	if (p == NULL)
		return NULL;
	
	if (p->right != NULL)
		return min(p->right);
	
	Node<T> *tmp = p->parent;
	
	while (tmp != NULL && (tmp->val < p->val))
		tmp = tmp->parent;

	return tmp;
}

template <class T>
void XBST<T> :: naturalFill(int *v)
{
	Node<T> *current = min(root);
	
	for (int i = 0; i < size; i++)
	{
		if (current != NULL)
			current->val = v[i];
		current = getNext(current);
	}
}

int main()
{
	XBST<int> tree;

	int arr[] = {23,4,6,8,12,21,5,9,7,3,16,2,24};
	int del[] = {23,4,6,8,12};

	for (int i = 0; i < 13; i++)
		tree.insert(&arr[i]);
	tree.postorderPrint();
/*
	for (int i = 0; i < 5; i++)
		tree.delet(&del[i]);
	tree.postorderPrint();
*/	
//	cout << tree.search(&arr[4]) << endl;

	cout << endl << "PrintLevel(3):";
	tree.printLevel(3);
	
	cout << endl << "NaturalFill:" << endl;
	int fill[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	tree.naturalFill(fill);
	tree.postorderPrint();

	return 0;
}
