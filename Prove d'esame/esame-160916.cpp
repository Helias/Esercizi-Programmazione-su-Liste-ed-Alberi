// Coded by Alessio Sferro

#include <iostream>
using namespace std;

/* =========================================================== */
/* =================== CLASSE StackNode ====================== */
// Classe nodo relativa allo stack

template <class H> class StackNode
{
    StackNode<H> *prev, *next;
    H *key;

public:
    StackNode(H *key = NULL)
    {
        this->key = key ? new H(*key) : NULL;
        prev = next = NULL;
    }

    StackNode<H>* getPrev(){ return prev; }
    StackNode<H>* getNext(){ return next; }
    H* getKey(){ if(key) return new H(*key); }

    void setPrev(StackNode<H> *prev){ this->prev = prev; }
    void setNext(StackNode<H> *next){ this->next = next; }
};

/* =========================================================== */
/* ==================== CLASSE Stack ========================= */
/* Stack costruito mediante una lista doppiamente concatenata  */

template <class H> class Stack
{
    StackNode<H> *header, *trailer;
    int n;

public:
    Stack()
    {
        header = new StackNode<H>();
        trailer = new StackNode<H>();
        header->setNext(trailer);
        trailer->setPrev(header);
        n = 0;
    }

    Stack<H>* push(H x)
    {
        StackNode<H> *nd = new StackNode<H>(&x);
        nd->setPrev(header);
        nd->setNext(header->getNext());
        header->getNext()->setPrev(nd);
        header->setNext(nd);
        n++;
        return this;
    }

    H* pop()
    {
        H* key = NULL;
        if(n){
            StackNode<H> *tmp = header->getNext();
            tmp->getNext()->setPrev(header);
            header->setNext(tmp->getNext());
            key = new H(*tmp->getKey());
            delete tmp;
            n--;
        }
        return key;
    }

    void print()
    {
        if(n){
            StackNode<H> *tmp = header->getNext();
            while(tmp != trailer){
                cout << *tmp->getKey() << endl;
                tmp = tmp->getNext();
            }
            cout << endl;
        }
    }

    int isEmpty(){ return n == 0; }
};

/* =========================================================== */
/* ====================== CLASSE Matrix ====================== */

class Matrix
{
    int rows;
    int cols;

public:
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
    }

    int getRows(){ return rows; }
    int getCols(){ return cols; }
};

/* =========================================================== */
/* ===================== OVERLOADINGS ======================== */

ostream& operator<<(ostream &out, Matrix& obj)
{
    out << "[" << obj.getRows() << "x"
               << obj.getCols() << "]";
    return out;
}

/* =========================================================== */
/* ===================== CLASSE TreeNode ===================== */
// Classe nodo per il BSTree

template <class H> class TreeNode
{
    TreeNode<H> *left, *right, *parent;
    H *key;
    int color;

public:
    TreeNode(H *key = NULL)
    {
        this->key = key ? new H(*key) : NULL;
        left = right = parent = NULL;
        color = 0;
    }

    TreeNode<H>* getLeft(){ return left; }
    TreeNode<H>* getRight(){ return right; }
    TreeNode<H>* getParent(){ return parent; }
    H* getKey(){ if(key) return new H(*key); }
    int getColor(){ return color; }

    void setLeft(TreeNode<H> *left){ this->left = left; }
    void setRight(TreeNode<H> *right){ this->right = right; }
    void setParent(TreeNode<H> *parent){ this->parent = parent; }
    void setKey(H *key){ if(key) this->key = key; }
    void setColor(int color){ this->color = color; }
};

/* =========================================================== */
/* ====================== CLASSE BSTree ====================== */

template <class H> class BSTree
{
    TreeNode<H> *root, *current;
    int n, mulC;


    // Procedura di stampa postorder.
    void _printTree(TreeNode<H> *x)
    {
        if(x != NULL){
            _printTree(x->getLeft());
            _printTree(x->getRight());
            cout << *(x->getKey()) << " " << endl;
        }
    }

    TreeNode<H>* _getRoot(){ return root; }

    // Questo metodo stampa la sequenza di matrici compl. parentesizzate.
    void _printSeq(TreeNode<H> *tmp)
    {
        if(tmp != NULL){
            if(tmp->getRight() && tmp->getLeft())
                cout << "(";

            tmp->setColor(1);

            _printSeq(tmp->getLeft());
            _printSeq(tmp->getRight());

            if(!tmp->getRight() && !tmp->getLeft()){
                cout << *tmp->getKey();
                if(tmp == tmp->getParent()->getLeft())
                    cout << "x";
            }

            if(tmp->getRight() && tmp->getLeft()){
                cout << ")";
                if(_getRoot()->getRight()->getColor() == 0){
                    cout << "x";
                }
            }
        }
    }

    void _resetColors(TreeNode<H> *tmp){
        if(tmp != NULL){
            tmp->setColor(0);
            _resetColors(tmp->getLeft());
            _resetColors(tmp->getRight());
        }
    }

    // Questo metodo ricerca un possibile padre dell'oggetto da inserire
    // nell'albero.
    TreeNode<H>* _searchIns(TreeNode<H> *tmp, H x)
    {
        if(tmp != NULL){
            if( (x.getRows() == tmp->getKey()->getRows()
                             && !tmp->getLeft() ) ||
                (x.getCols() == tmp->getKey()->getCols()
                             && !tmp->getRight() )) return tmp;

            TreeNode<H> *leftNode = _searchIns(tmp->getLeft(), x);
            TreeNode<H> *rightNode = _searchIns(tmp->getRight(), x);

            return leftNode ? leftNode : rightNode;
        }
        return NULL;
    }

    void _incMult(int mulC){
        this->mulC += mulC;
    }

    void _resetMult(){ mulC = 0; }

    Matrix* _multiplyCalc(TreeNode<H> *tmp)
    {
        if(tmp != NULL){
            tmp->setColor(1);

            Matrix* a = _multiplyCalc(tmp->getLeft());
            Matrix* b = _multiplyCalc(tmp->getRight());

            if(!tmp->getLeft() && !tmp->getRight())
                return tmp->getKey();

            _incMult(a->getRows()*b->getRows()*b->getCols());

            if(tmp->getLeft()->getColor() == 1)
                return tmp->getKey();
        }
    }

public:
    BSTree() : root(NULL), n(0), mulC(0) {}

    BSTree<H>* ins(H x)
    {
        TreeNode<H> *nd = new TreeNode<H>(&x);

        n++;
        if(!root){
            root = nd;
            return this;
        }

        TreeNode<H> *tmp = _searchIns(root, x);
        if(x.getRows() == tmp->getKey()->getRows()) tmp->setLeft(nd);
        else if(x.getCols() == tmp->getKey()->getCols()) tmp->setRight(nd);

        nd->setParent(tmp);
        return this;
    }

    void printTree()
    {
        cout << "\nStampa postOrder dell'albero:\n";
        _printTree(root);
        cout << endl;
    }

    void printSeq()
    {
        cout << "Stampa sequenza matrici completamente parentesizzata:\n";
        _printSeq(root);
        _resetColors(root);
        cout << endl;
    }

    int multiplyCalc()
    {
        cout << "\nNumero di moltiplicazioni elementari: ";
        _multiplyCalc(root);
        int tmp = mulC;
        _resetMult();
        return tmp;
    }

};

/* ========================================================= */
/* ==================== Classe MMultiply =================== */

template <class H> class MMultiply
{
    string s; // stringa di default (accettata dopo il parse)
    Stack< Matrix > *matParsed; // stack di matrici di una stringa accettata
    BSTree< Matrix > *bt; // albero delle matrici

    int checkMatrices(Matrix& a, Matrix& b)
    {
        return a.getCols() == b.getRows() ? 1 : 0;
    }

public:
    MMultiply(){
        s = "NULL";
        matParsed = new Stack< Matrix >();
        bt = new BSTree< Matrix >();
    }

    void parse(string s)
    {
        cout << "Eseguo il parsing di: " << s << "\n\n";
        Stack<H> *l = new Stack<H>();
        for(int i = s.length()-1; i >= 0; i--){
            l->push(s[i]);
        }

        bool wellformed = true,
             popped = false;

        H *ch = NULL,
          *pre = NULL;

        int openBr = 0,
            closedBr = 0,
            rows, cols;

        Stack< Matrix > *mat = new Stack< Matrix >();

        while(!l->isEmpty() && wellformed){
            if(!popped) ch = l->pop();
            else popped = false;

            switch(*ch){
            case '(':
                openBr++;
                ch = l->pop();
                popped = true;
                if(*ch != '[' && *ch != '(') wellformed = false;
                break;

            case ')':
                closedBr++;
                if(*pre != ']' && *pre != ')')
                    wellformed = false;

                {
                    Matrix *b = mat->pop();
                    Matrix *a = mat->pop();

                    matParsed->push(*b);
                    matParsed->push(*a);

                    cout << *a << " x " << *b << endl;

                    if(checkMatrices(*a, *b)){
                        Matrix *tmp = new Matrix(a->getRows(), b->getCols());
                        mat->push(*tmp);
                        if(l->isEmpty())
                            matParsed->push(*tmp);
                    }else wellformed = false;
                }
                break;

            case '[':
                ch = l->pop();
                if(*ch >= 48 && *ch <= 57){
                    rows = *ch - 48;
                    ch = l->pop();
                    if(*ch == 'x'){
                        ch = l->pop();
                        if(*ch >= 48 && *ch <= 57){
                            cols = *ch - 48;
                            ch = l->pop();
                            if(*ch == ']'){
                                mat->push(Matrix(rows, cols));
                            }
                            else wellformed = false;
                        }else wellformed = false;
                    }else wellformed = false;
                }else wellformed = false;
                pre = ch;
                break;

            case 'x':
                if(*pre == ']' || *pre == ')'){
                    ch = l->pop();
                    popped = true;
                    if(*ch != '[' && *ch != '(') wellformed = false;
                }else wellformed = false;
                break;

            default:
                wellformed = false;
            }
        }

        if(wellformed && openBr == closedBr){
            this->s = s;
            cout << "\nStringa accettata." << endl;
        }else{
            cout << "\nStringa NON accettata." << endl;
        }
    }

    void makeTree()
    {
        while(!matParsed->isEmpty()){
            bt->ins(*matParsed->pop());
        }

        bt->printTree();
        bt->printSeq();
        cout << bt->multiplyCalc() << endl;
    }
};

/* ========================================================= */
/* ======================== MAIN =========================== */

int main()
{
    MMultiply<char> *m = new MMultiply<char>();
    m->parse("(([3x9]x[9x5])x([5x7]x([7x2]x[2x3])))");

    m->makeTree();
}
