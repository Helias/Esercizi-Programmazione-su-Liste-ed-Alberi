/* Coded by Alessio Sferro */

#include <iostream>
using namespace std;
 
/***** IMPLEMENTAZIONE LISTA *****/
 
// Classe Nodo
template <class H> class Nodo{
 
    /*
        key : chiave del nodo.
        prev : puntatore al nodo precedente.
        next : puntatore al nodo successivo.
    */
 
    H* key;
    Nodo<H> *prev, *next;
 
public:
    Nodo(H* key = NULL){
        this->key = key ? new H(*key) : NULL;
        prev = next = NULL;
    }
 
    Nodo<H>* getPrev(){ return prev; }
    Nodo<H>* getNext(){ return next; }
    H* getKey(){ return key; }
 
    void setPrev(Nodo<H>* prev){ this->prev = prev; }
    void setNext(Nodo<H>* next){ this->next = next; }
};
 
// Classe Lista
template <class H> class List{
protected:
 
    /*
        header : nodo sentinella iniziale.
        trailer : nodo sentinella finale.
        current : nodo utilizzato dall'iteratore.
    */
 
    Nodo<H> *header, *trailer, *current;
    int n;
 
    // Questo metodo ricerca un nodo, con chiave x, nella lista.
    Nodo<H>* _search(H x){
        Nodo<H>* tmp = header->getNext();
        while(tmp && *tmp->getKey() != x)
            tmp = tmp->getNext();
        return tmp;
    }
 
public:
    List(){
        header = new Nodo<H>();
        trailer = new Nodo<H>();
        header->setNext(trailer);
        trailer->setPrev(header);
        n = 0;
    }
 
    // Questo metodo inserisce un nodo, con chiave x, in ordine non decrescente, nella lista.
    void insert(H x){
        Nodo<H>* nd = new Nodo<H>(&x);
 
        Nodo<H>* tmp = header->getNext();
        while(tmp != trailer && x > *tmp->getKey())
            tmp = tmp->getNext();
 
        nd->setNext(tmp);
        nd->setPrev(tmp->getPrev());
 
        tmp->getPrev()->setNext(nd);
        tmp->setPrev(nd);
 
        n++;
    }  
 
    // Questo metodo elimina un nodo, con chiave x, dalla lista.
    void del(H x){
        Nodo<H>* tmp = _search(x);
        if(tmp){
            tmp->getNext()->setPrev(tmp->getPrev());
            tmp->getPrev()->setNext(tmp->getNext());
            delete tmp;
            n--;
        }
    }
 
    // Questo metodo restituisce la prima chiave della lista.
    H* begin(){
        current = header;
        return next();
    }
 
    // Questo metodo restituisce la chiave successiva.
    H* next(){
        if(current->getNext() == trailer) return NULL;
        current = current->getNext();
        return current->getKey();
    }
};
 
/***** IMPLEMENTAZIONE CODA *****/
 
// Classe coda (derivata dalla classe lista)
template <class H> class Queue : public List<H>{
 
    /*
        sumElem : somma degli elementi della coda.
        topElem : chiave in testa alla coda.
        numElem : numero degli elementi della coda.
    */
 
    H sumElem, topElem;
    int numElem;
 
public:
    Queue() : List<H>() {
        sumElem = topElem = H();
        numElem = 0;
    }
 
    // Questo metodo inserisce un nodo in coda.
    void enqueue(H x){
        Nodo<H>* nd = new Nodo<H>(&x);
 
        if(!List<H>::begin()) topElem = x;
 
        nd->setNext(List<H>::trailer);
        nd->setPrev(List<H>::trailer->getPrev());
 
        List<H>::trailer->getPrev()->setNext(nd);
        List<H>::trailer->setPrev(nd);
 
        sumElem += x;
        numElem += 1;
    }
 
    // Questo metodo elimina il nodo in testa alla coda e ne restituisce il puntatore alla chiave.
    H* dequeue(){
        if(numElem > 0){
            Nodo<H>* tmp = List<H>::header->getNext();
 
            if(tmp->getNext() != List<H>::trailer)
                topElem = *tmp->getNext()->getKey();
            else
                topElem = H();
 
            List<H>::header->setNext(tmp->getNext());
            tmp->getNext()->setPrev(List<H>::header);
 
            sumElem -= *tmp->getKey();
            numElem -= 1;
 
            return tmp->getKey();
        }
 
        return NULL;
    }  
 
    int getNumElem(){ return numElem; }
    int getSumElem(){ return sumElem; }
    int getTopElem(){ return topElem; }
};
 
/***** OVERLOADING DEGLI OPERATORI *****/
 
// Questo overloading del != confronta il numero degli elementi di due code a e b.
template <class H> int operator!=(Queue<H>& a, Queue<H>& b){
    if(a.getNumElem() != b.getNumElem()) return 1;
    return 0;
}
 
// Questo overloading del == confronta gli elementi di una coda a con un valore x.
template <class H> int operator==(Queue<H>& a, H x){
    for(H* it = a.begin(); it; it = a.next())
        if(*it == x) return 1;
    return 0;
}
 
// Questo overloading del > confronta le code in base agli attributi privati delle stesse e secondo le modalità indicate.
template <class H> int operator>(Queue<H>& a, Queue<H>& b){
    if(a.getSumElem() > b.getSumElem()) return 1;
    if(a.getSumElem() == b.getSumElem() && a.getNumElem() > b.getNumElem()) return 1;
    if(a.getSumElem() == b.getSumElem() && a.getNumElem() == b.getNumElem() && a.getTopElem() > b.getTopElem()) return 1;
   
    return 0;
}
 
// Questo overloading stampa in ordine FIFO gli elementi della coda.
template <class H> ostream& operator<<(ostream& out, Queue<H>& obj){
    for(H* it = obj.begin(); it; it = obj.next())
        out << *it << " ";
    return out;
}
 
/***** IMPLEMENTAZIONE DELLA BRIKLIST *****/
 
// Interfaccia della BrikList
template <class H> class BrikList{
public:
    virtual BrikList<H>* ins(H x) = 0;
    virtual BrikList<H>* push(H x) = 0;
    virtual H* pop() = 0;
    virtual int search(H x) = 0;
    virtual void print() = 0;
};
 
// Classe MyBrikList
template <class H> class MyBrikList : public BrikList<H>{
 
    /*
        MBL : Lista di code.
        n : numero di elementi (code) nella lista.
    */
 
    List< Queue<H> >* MBL;
    int n;
 
public:
    MyBrikList(){
        MBL = new List< Queue<H> >();
        n = 0;
    }
 
    // Questo metodo aggiunge una coda alla BrikList.
    BrikList<H>* ins(H x){
        Queue<H>* tmp = new Queue<H>();
        tmp->enqueue(x);
        MBL->insert(*tmp);
        n++;
        return this;
    }
 
    // Questo metodo aggiunge un valore alla più piccola coda della BrikList e riordina le code all'interno della stessa
    // per mantenerne l'ordine non decrescente.
    BrikList<H>* push(H x){
        Queue<H>* tmp = MBL->begin();
        tmp->enqueue(x);
        MBL->del(*tmp);
        MBL->insert(*tmp);
        return this;
    }
 
    // Questo metodo ritorna la chiave della coda più piccola della BrikList e la elimina se svuotata.
    H* pop(){
        Queue<H>* tmp = MBL->begin();
        H* value = tmp->dequeue();
        if(!tmp->begin()) MBL->del(*tmp);
        return value;
    }
 
    // Questo metodo ricerca un elemento x all'interno della BrikList.
    int search(H x){
        for(Queue<H>* it = MBL->begin(); it; it = MBL->next()){
            if(*it == x) return 1;
        }
        return 0;
    }
 
    // Questo metodo stampa le code della BrikList.
    void print(){
        for(Queue<H>* it = MBL->begin(); it; it = MBL->next())
            cout << *it << endl;
    }
};
 
 
int main(){
    MyBrikList<int>* MBL = new MyBrikList<int>();
   
    MBL->ins(15)->ins(12)->ins(6)->ins(9)->ins(10)
       ->ins(4)->ins(2)->ins(30)->ins(23)->ins(11);
 
    for(int i = 0; i < 4; i++){
        int x = *MBL->pop();
        MBL->push(x);
    }
 
    MBL->print();
}