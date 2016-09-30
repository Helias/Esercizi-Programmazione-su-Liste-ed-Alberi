#include <iostream>
using namespace std;

/********** CLASSE DLIST ************/

template <class H> class ListNode
{
	ListNode<H> *prev, *next;
	H *key;

public:
	ListNode(H *key = NULL)
	{
		this->key = key ? new H(*key) : NULL;
		prev = next = NULL;
	}	

	ListNode<H> *getPrev(){ return prev; }
	ListNode<H> *getNext(){ return next; }
	H *getKey(){ return key; }

	void setPrev(ListNode<H> *prev){ this->prev = prev; }
	void setNext(ListNode<H> *next){ this->next = next; }
};

template <class H> class DList
{
	ListNode<H> *header, *trailer, *current;
	int n;

	ListNode<H> *_search(H x)
	{
		ListNode<H> *tmp = header->getNext();
		while(tmp != trailer && *tmp->getKey() != x)
			tmp = tmp->getNext();
		return tmp != trailer ? tmp : NULL;
	}

public:
	DList()
	{
		header = new ListNode<H>();
		trailer = new ListNode<H>();
		header->setNext(trailer);
		trailer->setPrev(header);
		n = 0;
	}

	DList<H> *ins(H x)
	{
		ListNode<H> *nd = new ListNode<H>(&x),
					*tmp = header->getNext();

		while(tmp != trailer && *tmp->getKey() < x)
			tmp = tmp->getNext();

		nd->setNext(tmp);
		nd->setPrev(tmp->getPrev());

		tmp->getPrev()->setNext(nd);
		tmp->setPrev(nd);

		n++;
		return this;
	}

	DList<H> *headIns(H x)
   {
		ListNode<H> *nd = new ListNode<H>(&x);
		n++;
		nd->setPrev(header);
		nd->setNext(header->getNext());
		header->getNext()->setPrev(nd);
		header->setNext(nd);
		return this;
	}

	DList<H> *canc(H x)
	{
		if(n > 0){
			ListNode<H> *tmp = _search(x);
			if(tmp){
				tmp->getNext()->setPrev(tmp->getPrev());
				tmp->getPrev()->setNext(tmp->getNext());
				delete tmp;
				n--;
			}
		}
		return this;
	}

	H* search(H x)
	{
		ListNode<H> *tmp = _search(x);
		return tmp ? tmp->getKey() : NULL;
	}

	void print()
	{
		ListNode<H> *tmp = header->getNext();
		while(tmp != trailer){
			cout << *tmp->getKey() << " ";
			tmp = tmp->getNext();
		}
		cout << endl;
	}

	H* begin()
	{
		current = header;
		return next();
	}

	H* next()
    {
		if(current->getNext() == trailer) return NULL;
		current = current->getNext(); 
		return current->getKey();
	}

	int getSize(){ return n; }
};

/********** CLASSE BST ***********/

template <class H> class TreeNode
{
	TreeNode<H> *left, *right, *parent;
	H *key;

public:
	TreeNode(H *key = NULL)
	{
		this->key = key ? new H(*key) : NULL;
		left = right = parent = NULL;
	}	

	TreeNode<H> *getLeft(){ return left; }
	TreeNode<H> *getRight(){ return right; }
	TreeNode<H> *getParent(){ return parent; }
	H *getKey(){ if(key) return new H(*key); }

	void setLeft(TreeNode<H> *left){ this->left = left; }
	void setRight(TreeNode<H> *right){ this->right = right; }
	void setParent(TreeNode<H> *parent){ this->parent = parent; }
	void setKey(H *key){ this->key = key; }
};

template <class H> class BST
{
	TreeNode<H> *root, *current;
	int numElem, minValue;

	TreeNode<H> *_search(H x)
	{
		if(!root) return NULL;
		TreeNode<H> *tmp = root;
		while(tmp && *tmp->getKey() != x)
			tmp = x < *tmp->getKey() ? tmp->getLeft() : tmp->getRight();
		return tmp;
	}

	TreeNode<H> *_minimum(TreeNode<H> *x)
	{
		if(!x) return NULL;
		TreeNode<H> *tmp = x;
		while(tmp->getLeft()) tmp = tmp->getLeft();
		return tmp;
	}

	TreeNode<H> *_succ(TreeNode<H> *x)
	{
		if(!x) return NULL;
		if(x->getRight()) return _minimum(x->getRight());

		TreeNode<H> *tmp = x, *par = x->getParent();
		while(par && par->getRight() == tmp){
			tmp = par;
			par = par->getParent();
		}
		return par;
	}

	void _canc(TreeNode<H> *x)
	{
		numElem--;

		if(!x->getRight() && !x->getLeft()){
			TreeNode<H> *par = x->getParent();
			if(!par) root = NULL;
			else if(par->getRight() == x) par->setRight(NULL);
			else par->setLeft(NULL);
			delete x;
			return;
		}

		if(x->getRight() && x->getLeft()){
			TreeNode<H> *s = _succ(x);
			x->setKey(s->getKey());
			_canc(s);
			return;
		}

		TreeNode<H> *par = x->getParent(), *son = x->getRight();
		if(!son) son = x->getLeft();
		if(!par) root = son;
		else if(par->getRight() == x) par->setRight(son);
		else par->setLeft(son);
		son->setParent(par);
		delete x;
	}

public:
	BST() : root(NULL), numElem(0), minValue(-1) {}

	BST<H> *ins(H x)
	{
		TreeNode<H> *nd = new TreeNode<H>(&x);

		numElem++;

		if(!root){
			root = nd;
			minValue = x;
			return this;
		}

		if(x < minValue) minValue = x;

		TreeNode<H> *tmp = root, *par = NULL;
		while(tmp){
			par = tmp;
			tmp = x < *tmp->getKey() ? tmp->getLeft() : tmp->getRight();
		}

		x < *par->getKey() ? par->setLeft(nd) : par->setRight(nd);
		nd->setParent(par);
		return this; 
	}

	BST<H> *canc(H x)
	{
		if(numElem > 0){
			TreeNode<H> *tmp = _search(x);
			if(tmp){
				_canc(tmp);
				if(x == minValue)
					minValue = *_minimum(root)->getKey();
			}
		}
		return this;
	}

	H* minimum()
	{
		if(!root) return NULL;
		TreeNode<H> *tmp = _minimum(root);
		return tmp ? tmp->getKey() : NULL;
	}

	H* successor(H x)
	{
		if(!root) return NULL;
		TreeNode<H> *tmp = _search(x);
		if(tmp){
			tmp = _succ(tmp);
			if(tmp) return tmp->getKey();
		}
		return NULL;
	}

	H* begin()
	{
		current = _minimum(root);
		return current ? current->getKey() : NULL;
	}

	H* next()
	{
		current = _succ(current);
		return current ? current->getKey() : NULL;
	}

	void print()
	{
		for(H *it = begin(); it; it = next())
			cout << *it << " ";
		cout << endl;
	}

	int getMinValue(){ return minValue; }
	int getNumElem(){ return numElem; }
};

/*** OVERLOADING OPERATORI ***/

template <class H> int operator<(BST<H>& a, BST<H>& b)
{
	if(a.getNumElem() < b.getNumElem()) return 1;
	if(a.getNumElem() == b.getNumElem() 
	&& a.getMinValue() < b.getMinValue()) return 1;
	return 0;
}

template <class H> int operator!=(BST<H>& a, BST<H>& b)
{
	if(a.getNumElem() != b.getNumElem() 
	&& a.getMinValue() != b.getMinValue()) return 1;
	return 0;
}

template <class H> ostream& operator<<(ostream& out, DList<H>& a)
{
	for(H *it = a.begin(); it; it = a.next()){
		it->print();
	}
	return out;
}

/*** CLASSE COMPOSTA ***/

template <class H> class BSTList
{
	DList< BST<H> > *bl;
	int k;

public:
	BSTList(int k)
	{
		this->k = k;
		bl = new DList< BST<H> >();
	}

	BSTList<H> *ins(H x)
	{
		BST<H> *tmp = bl->begin();
		while(tmp && tmp->getNumElem() == k) tmp = bl->next();
		if(tmp){
			tmp->ins(x);
			if(tmp->getNumElem() == k){
				bl->canc(*tmp);
				bl->ins(*tmp);
			}
		}
		else{
			BST<H> *node = new BST<H>();
			node->ins(x);
			bl->ins(*node);
		}
		return this;
	}

	BSTList<H> *canc(H x)
	{
		BST<H> *tmp = bl->begin();
		while(tmp){
			tmp->canc(x);
			tmp = bl->next();
		}
		return this;
	}

	void print(){
		cout << *bl;
	}
};

int main()
{
	DList<int>* l = new DList<int>();
	l->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
	l->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
	if(l->search(5)) cout << "elemento 5 presente"; else cout << "elemento 5 non presente";
	cout << endl;
	if(l->search(3)) cout << "elemento 3 presente"; else cout << "elemento 3 non presente";
	cout << "\n\n";

	BST<int> *t = new BST<int>();
	t->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
	t->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
	if(l->search(5)) cout << "elemento 5 presente"; else cout << "elemento 5 non presente";
	cout << endl;
	if(l->search(3)) cout << "elemento 3 presente"; else cout << "elemento 3 non presente";
	cout << "\n\n";
	int *r = t->minimum();
	if(r) cout << "il valore piu' piccolo e' " << *r << endl;
	if(r=t->successor(5)) cout << "il successore di 5 e' " << *r << endl;
	if(r=t->successor(3)) cout << "il successore di 3 e' " << *r << endl;

	cout << endl;
	BSTList<int> *b = new BSTList<int>(4);
	b->ins(3)->ins(7)->ins(1)->ins(8)->ins(3)->ins(4)->print();
	cout << endl;
	b->ins(8)->ins(6)->ins(2)->ins(4)->ins(6)->ins(3)->print();
	cout << endl;
	b->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
}