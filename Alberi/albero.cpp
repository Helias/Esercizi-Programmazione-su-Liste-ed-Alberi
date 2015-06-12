/*
 * Coded By Helias (Stefano Borzì)
*/
#include <iostream>
using namespace std;

template <class H>
struct Node
{
	Node *left, *right, *parent;
	H key; // valore del nodo
	H mul;
};

template <class H>
class Tree
{
	private:
		Node<H> *root;
		int size; //numero di elementi nell'albero
	public:
		Tree() { root = NULL; size = 0;  }
		Tree<H>* ins(H x);
		Tree<H>* del(H x);
		int search(H x);
		int multiplicity(H x);
		void printTree();
		void inorder(Node<H> *p);
		void Trapianta(Node<H> *u, Node<H> *v);
		Node<H> *min(Node<H> *p);
		Node<H> *searchPointer(H x);
};

template <class H>
Tree<H>* Tree<H> :: ins(H x)
{
	if (root == NULL)
	{
		root = new Node<H>();
		root->key = x;
		root->mul = 1;
	}
	else
	{
		Node<H> *tmp = root;
		Node<H> *aux;

		while (tmp != NULL)
		{
			aux = tmp;
			if (tmp->key == x)
			{
				tmp->mul++;
				size++;
				return this;
			}
			else if (tmp->key > x)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}

		Node<H> *New = new Node<H>();
		New->key = x;
		New->right = NULL;
		New->left = NULL;
		New->mul = 1;

		if (aux->key > x)
			aux->left = New;
		else
			aux->right = New;

		New->parent = aux;
		size++;
		return this;
	}
}

template <class H>
int Tree<H> :: multiplicity(H x)
{
	Node<H> *tmp = root;
	
	while (tmp->key != x && tmp != NULL)
	{
		if (tmp->key == x)
			return tmp->mul;
		else if (tmp->key > x)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return 0;
}

template <class H>
void Tree<H> :: printTree()
{
	cout << endl;
	inorder(root);
	cout << endl;
}

template <class H>
void Tree<H> :: inorder(Node<H> *p)
{
	if (p != NULL)
	{
		inorder(p->left);

		for (int j = 0; j < p->mul; j++)
			cout << p->key << "\t";

		inorder(p->right);
	}
}

template <class H>
Node<H>* Tree<H> :: min(Node<H> *p)
{
	Node<H> *tmp = p;

	while (tmp->left != NULL)
		tmp = tmp->left;

	return tmp;
}

template <class H>
int Tree<H> :: search(H x)
{
	Node<H> *tmp = root;
	
	while (tmp != NULL)
	{
		if (tmp->key == x)
			return 1;		  // nodo trovato
		else if(tmp->key > x)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	return 0;
}

template <class H>
Node<H>* Tree<H> :: searchPointer(H x)
{
	Node<H> *tmp = root;
	
	while (tmp != NULL)
	{
		if (tmp->key == x)
			return tmp;		  // nodo trovato
		else if(tmp->key > x)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	return NULL;
}

template <class H>
void Tree<H> :: Trapianta(Node<H> *u, Node<H> *v)
{
	if (u->parent == NULL)
		root = v;
	else if (u->parent->left == u)
		u->parent->left = v;	
	else
		u->parent->right = v;

	if (v != NULL)
		v->parent = u->parent;
}

template <class H>
Tree<H>* Tree<H> :: del(H x)
{
	Node<H> *tmp = searchPointer(x);
	Node<H> *aux;
	
	if (tmp == NULL)
		return this;

	if (tmp->mul > 1)
		tmp->mul--;
	else
	{
		if (tmp->left == NULL)
			Trapianta(tmp, tmp->right);
		else if(tmp->right == NULL)
			Trapianta(tmp, tmp->left);
		else
		{
			aux = min(tmp->right);
			if (aux->parent != tmp)
			{
				Trapianta(aux, aux->right);
				aux->right = tmp->right;
				aux->right->parent = aux;
			}
			Trapianta(tmp, aux);
			aux->left = tmp->left;
			aux->left->parent = aux;
		}
		delete tmp;
	}
	
	size--;
	return this;
}

int main()
{
	Tree<int> tree;
	int arr[] = {10, 7, 7, 23, 30, 4, 1, 5, 9, 5, 1, 7, 1, 9};

	for(int i = 0; i < 14; i++)
		tree.ins(arr[i]);

	tree.printTree();

	tree.del(7);
	tree.del(4);
	tree.del(23);
	tree.del(7);
	tree.del(7);

	tree.printTree();

	return 0;
}











