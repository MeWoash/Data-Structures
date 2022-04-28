#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;


template<typename T>
bool Greater(T a, T b) {
        return a > b;
    }
template<typename T>
bool Lesser(T a, T b) {
        return a < b;
    }

template<typename T>
class node {

public:

    T data;
    const int ID;
    node<T> *L, *R, *P;

    node(T value, int cnt):data(value),P(nullptr),L(nullptr),R(nullptr),ID(cnt){}


};


template<typename T>
class BST {
    
    int cnt;

    node<T>* max(node<T>* X) {
        node<T>* current=X;
        node<T>* prev=X;

        while (current != nullptr) {
            prev = current;
            current = current->R;
        }
        return prev;
    
    }

    node<T>* min(node<T>* X) {
        node<T>* current = X;
        node<T>* prev=X;

        while (current != nullptr) {
            prev = current;
            current = current->L;
        }
        return prev;

    }

    node<T>* predecessor(node<T>* X) {
        node<T>* current=X;
        bool found = false;

        if (current->L != nullptr) {
            current=max(current->L);
        }
        else {
            while (current != nullptr && !found && current!=root) {
                if (current->P->R == current) {
                    found = true;
                }
                current = current->P;
                
            }
        }
        if (current == root && found == false) return nullptr;
        return current;
    }

    node<T>* successor(node<T>* X) {
        node<T>* current = X;
        bool found = false;

        if (current->R != nullptr) {
            current = min(current->R);
        }
        else {
            while (current != nullptr && !found && current != root) {
                if (current->P->L == current) {
                    found = true;
                }
                current = current->P;

            }
        }
        if (current == root && found == false) return nullptr;
        return current;
    }

public:
    node<T>* root;
    int size;
    BST():root(nullptr),cnt(0),size(0){}

    template<typename S>
    void add(T value,S comp) {
        bool info = false;
        if (root == nullptr) {
            root = new node<T>(value,cnt);
            cnt++;
            size++;
            return;
        }
        node<T> *current = root;
        node<T>* prev = root;
        bool lflag;

        while (current != nullptr) {
            if(current->data == value) {
                if(info)cout << "Klucz: "<< value<<" juz istnieje!\n";
                return;
            }

            prev = current;
            lflag = false;

            if (comp(value,current->data)) {
                current=current->L;
                lflag = true;
            }
            else {
                current=current->R;
            }
        }
        current = new node<T>(value, cnt);
        cnt++;
        size++;
        current->P = prev;
        if (lflag) {
            prev->L = current; 
        }
        else {
            prev->R = current; 
        }

    }

    template<typename S>
    node<T>* find(T value,S comp) {
        bool info = false;
        node<T>* current=root;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            else if (comp(value,current->data)) {
                current = current->L;
            }
            else {
                current = current->R;
            }
        }
        if(info)cout << "Klucz nie istnieje!\n";
        return nullptr;

    }

    void del(node<T>* X) {
        if (X == nullptr) {
            return;
        }

        int pnt = 0;
        if (X->L != nullptr) pnt++;
        if (X->R != nullptr) pnt++;



        if (pnt == 0) {
            if (X == root) {
                root = nullptr;
            }
            else{
                if (X->P->R == X) {
                    X->P->R = nullptr;
                }
                else {
                    X->P->L = nullptr;
                }

            }
            delete X;
            size--;
            
        }
        else if(pnt == 1) {
            if (X == root) {

                if (X->L != nullptr) {
                    root = X->L;
                    X->L->P = nullptr;
                }
                else {
                    root = X->R;
                    X->R->P = nullptr;
                }
            }
            else {
                if (X->P->L == X) {
                    if (X->L != nullptr) {
                        X->P->L = X->L;
                        X->L->P = X->P;
                    }
                    else {
                        X->P->L = X->R;
                        X->R->P = X->P;
                    }
                }
                else {
                    if (X->R != nullptr) {
                        X->P->R = X->R;
                        X->R->P = X->P;
                    }
                    else { 
                        X->P->R = X->L;
                        X->L->P = X->P;
                    }
                }
            }
            delete X;
            size--;
        }
        else if(pnt==2){
            node<T>* suc = successor(X);

            suc->L = X->L;

            if (suc->P == X) {
                suc->R = nullptr;
            }
            else {
                suc->P->L = suc->R;
                suc->R = X->R;
            }

            X->R->P = suc;
            X->L->P = suc;
            
            if (root == X) {
                root = suc;
                suc->P = nullptr;
            }
            delete X;
            size--;

        }
        

    }

    int pre_order(node<T>* nod, node<T> **tab,int i=0)const {
        
        if (nod != nullptr) {
            tab[i++] = nod;
            i=pre_order(nod->L,tab,i);
            i=pre_order(nod->R,tab,i);

        }
        return i;
    }

    node<T>** pre_order_list(node<T>* nod)const{

        node<int>** tab = new node<int>*[size];
        pre_order(root, tab);

        return tab;
    }

    int in_order(node<T>* nod, node<T>** tab, int i = 0)const {

        if (nod != nullptr) {
            i = in_order(nod->L, tab, i);
            tab[i++] = nod;
            i = in_order(nod->R, tab, i);

        }
        return i;
    }

    node<T>** in_order_list(node<T>* nod)const {


        node<int>** tab = new node<int>*[size];
        in_order(root, tab);

        return tab;
    }

    void del_all() {
        auto list=pre_order_list(root);
        int stop = size;
        for (int i = 0; i < stop; i++) {
            delete list[i];
            size--;
        }
        delete[] list;
        root = nullptr;
        cnt = 0;
    }

    int height(node<T> *nod) {
        if (nod == nullptr) return 0;

        int Lh=height(nod->L);
        int Rh=height(nod->R);
        int max;

        if (Lh > Rh) max=Lh;
        else max=Rh;

        return max + 1;
    }

    void to_string(int n=10) {

        auto list = pre_order_list(root);
        int stop = size;
        if (n < size) stop = n;

        cout << "Liczba elementow: " << size << endl;
        cout << "Liczba poziomow: " << height(root) << endl;

        for (int i = 0; i < stop; i++){
            cout << "ID: " << list[i]->ID << ",\t Parent: ";

            if (list[i]->P != nullptr) cout << list[i]->P->data;
            else cout << "NULL";

            cout << ", Left: ";
            if(list[i]->L!=nullptr)cout<< list[i]->L->data;
            else cout << "NULL";

            cout << ", Right: ";
            if (list[i]->R != nullptr) cout<< list[i]->R->data;
            else cout << "NULL";

            cout << ", Data: " << list[i]->data << endl;
        }

    }
};




int main()
{

    srand(time(NULL));
    BST<int> *bst=new BST<int>;
    const int max_order = 7;
    unsigned long n,r,rr,hits;
    clock_t t1, t2;
    double time;
    int h;

    for (int i = 0; i <= max_order; i++) {
        int n = pow(10, i);

        t1 = clock();
        for (int i = 0; i < n; i++) {
            rr = rand();
            r = rand();
            bst->add(r*rr%10000000, Lesser<int>);
        }
        t2 = clock();
        time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        bst->to_string(10);
        cout <<endl<< "Operacja dodawania 10^" << i << " elementow zajela: " << time << ", Czas sredni : "<<(double)time/n<< endl;
        h = bst->height(bst->root);
        cout << "Stosunek wysokosci drzewa do rozmiaru danych: " << (double)h / bst->size << endl;
        cout << "Logartym (o podstawie 2) z rozmiaru danych: " << log2(bst->size) << endl;
        cout << "Stosunek wysokosci drzewa do logarytmu z rozmiaru danych: " << (double)h / log2(bst->size) << endl;


        t1 = clock();
        hits = 0;
        for (int i = 0; i < n; i++) {
            rr = rand();
            r = rand();
            if(bst->find(r * rr % 10000000,Lesser<int>)!=nullptr) hits++;
        }
        t2 = clock();
        time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        

        cout <<endl<<"Operacja wyszukiwania 10^" << i << " elementow zajela: " << time <<", Czas sredni: "<<(double)time/n<< endl;
        cout <<"Liczba trafien: "<<hits<<endl<<endl;
        cout << "=================================================================" << endl;
        
        bst->del_all();


    }
    
    delete bst;
 

    return 0;
}