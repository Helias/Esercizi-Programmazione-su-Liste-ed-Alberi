// Coded by Alessio Sferro

#include <iostream>
#include <typeinfo>
using namespace std;

template <class H> class Node
{
    Node<H> *prev, *next;
    H *key;

public:
    Node(H *key = NULL)
    {
        this->key = key ? new H(*key) : NULL;
        prev = next = NULL;
    }

    Node<H>* getPrev(){ return prev; }
    Node<H>* getNext(){ return next; }
    H* getKey(){ if(key) return new H(*key); }

    void setPrev(Node<H> *prev){ this->prev = prev; }
    void setNext(Node<H> *next){ this->next = next; }
};

template <class H> class Stack
{
    Node<H> *header, *trailer;
    int n;

public:
    Stack()
    {
        header = new Node<H>();
        trailer = new Node<H>();
        header->setNext(trailer);
        trailer->setPrev(header);
        n = 0;
    }

    Stack<H>* push(H x)
    {
        Node<H> *nd = new Node<H>(&x);
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
            Node<H> *tmp = header->getNext();
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
            Node<H> *tmp = header->getNext();
            while(tmp != trailer){
                cout << *tmp->getKey();
                tmp = tmp->getNext();
            }
            cout << endl;
        }
    }

    int isEmpty(){ return n == 0; }
};

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

template <class H> class MMultiply
{
    string s;

    int checkMatrices(Matrix& a, Matrix& b)
    {
        return a->getCols() == b->getRows() ? 1 : 0;
    }

public:
    MMultiply(){
        s = "vuoto";
    }

    void parse(string s)
    {
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
            rows,
            cols,
            matrices;

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

                if(matrices > 1){
                    Matrix b = mat->pop();
                    Matrix a = mat->pop();
                    if (!checkMatrices(a, b))
                        wellformed = false;
                }

                break;

            case '[':
                matrices++;
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
            cout << "Stringa accettata" << endl;
        }else{
            cout << "Stringa NON accettata" << endl;
        }
    }

    void print(){
        cout << s << endl;
    }
};

int main()
{
    MMultiply<char> *m = new MMultiply<char>();
    m->parse("([3x9]x[9x5])x([5x7]x([7x2]x[2x3]))");

    m->print();

}
