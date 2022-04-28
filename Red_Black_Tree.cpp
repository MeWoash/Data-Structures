#include <iostream>
#include <math.h>
#include <time.h>
#include <string>

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
    bool color_black;
    const int ID;
    node<T>* L, * R, * P;

    node(T value, int cnt,bool c=true) :data(value), P(nullptr), L(nullptr), R(nullptr), ID(cnt),color_black(c) {}


};


template<typename T>
class RBT {

    int cnt;

    node<T>* max(node<T>* X) {
        node<T>* current = X;
        node<T>* prev = X;

        while (current != nullptr) {
            prev = current;
            current = current->R;
        }
        return prev;

    }

    node<T>* min(node<T>* X) {
        node<T>* current = X;
        node<T>* prev = X;

        while (current != nullptr) {
            prev = current;
            current = current->L;
        }
        return prev;

    }

    node<T>* predecessor(node<T>* X) {
        node<T>* current = X;
        bool found = false;

        if (current->L != nullptr) {
            current = max(current->L);
        }
        else {
            while (current != nullptr && !found && current != root) {
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

    template<typename S>
    node<T>* insert_node(T value, S comp) {
        if (root == nullptr) {
            root = new node<T>(value, cnt);
            cnt++;
            size++;
            return root; //wstawienie korzenia
        }
        node<T>* current = root;
        node<T>* prev = root;
        bool lflag;

        while (current != nullptr) {
            if (current->data == value) {
                return nullptr;//wstawianie nie powiodlo sie - element juz istnieje
            }

            prev = current;
            lflag = false;

            if (comp(value, current->data)) {
                current = current->L;
                lflag = true;
            }
            else {
                current = current->R;
            }
        }
        current = new node<T>(value,cnt,false);
        cnt++;
        size++;
        current->P = prev;
        if (lflag) {
            prev->L = current;
        }
        else {
            prev->R = current;
        }
        return current; // zwrocenie adresu dodanego wezla
    }

public:
    node<T>* root;
    int size;
    RBT() :root(nullptr), cnt(0), size(0) {}

    void rotate_right(node<T>* pivot) {
        if (pivot == nullptr) {
            cout << "Blad rotacji! - nieprawidlowy adres\n";
        }
        else if (pivot->P == nullptr) {
            cout << "Blad rotacji! - wezel nie ma rodzica\n";
        }
        else if (pivot->P->L!=pivot) {
            cout <<"DATA: "<< pivot->P->data << endl;
            cout << "Blad rotacji! - wezel musi byc lewym potomkiem rodzica\n";
        }
        else {
            node<T>* parent = pivot->P;
            node<T>* grandparent = parent->P;

            if (parent == root) {//pivot nie ma dziadka, stanie sie nowym korzeniem
                root = pivot;
            }
            else{//pivot ma dziadka
                if (grandparent->L == parent) {
                    grandparent->L = pivot;
                }
                else {
                    grandparent->R = pivot;
                }
            }
            pivot->P = grandparent;
            
            //prawe dziecko pivota staje sie lewym dzieckiem rodzica
            if (pivot->R != nullptr) {
                pivot->R->P = parent;
            }
            parent->L = pivot->R;
            
            parent->P = pivot;
            pivot->R = parent;
        }
    }

    void rotate_left(node<T>* pivot) {
        if (pivot == nullptr) {
            cout << "Blad rotacji! - nieprawidlowy adres\n";
        }
        else if (pivot->P == nullptr) {
            cout << "Blad rotacji! - wezel nie ma rodzica\n";
        }
        else if (pivot->P->R != pivot) {
            cout << "Blad rotacji! - wezel musi byc prawym potomkiem rodzica\n";
        }
        else {
            node<T>* parent = pivot->P;
            node<T>* grandparent = parent->P;

            if (parent == root) {//pivot nie ma dziadka, stanie sie nowym korzeniem
                root = pivot;
            }
            else {//pivot ma dziadka
                if (grandparent->R == parent) {
                    grandparent->R = pivot;
                }
                else {
                    grandparent->L = pivot;
                }
            }
            pivot->P = grandparent;

            //lewe dziecko pivota staje sie prawym dzieckiem rodzica
            if (pivot->L != nullptr) {
                pivot->L->P = parent;
            }
            parent->R = pivot->L;

            parent->P = pivot;
            pivot->L = parent;
        }
    }

    void re_color(node<T>* inserted) {

        if (inserted == nullptr) {

        }
        else if (inserted == root){//1
            inserted->color_black = true;
        }
        else if (inserted->P->color_black == true) {

        }
        else if (inserted->P->P != nullptr) {
            node<T>* parent = inserted->P;
            node<T>* grandparent = parent->P;
            node<T>* uncle = (grandparent->L == parent ? grandparent->R : grandparent->L);
            bool uncle_color_black = true;
            if (uncle != nullptr) uncle_color_black = uncle->color_black;

            if (uncle_color_black == false) {//2
                parent->color_black = !parent->color_black;
                grandparent->color_black = !grandparent->color_black;
                if (uncle != nullptr) uncle->color_black = !uncle->color_black;
                re_color(grandparent);
            }

            if (uncle_color_black == true && grandparent->L==parent && parent->R==inserted) {
                rotate_left(inserted);
                
                auto tmp = inserted;
                inserted = parent;
                parent = tmp;
            }
            else if (uncle_color_black == true && grandparent->R == parent && parent->L == inserted) {
                rotate_right(inserted);

                auto tmp = inserted;
                inserted = parent;
                parent = tmp;
            }

            if (uncle_color_black == true && grandparent->L == parent && parent->L == inserted) {
                rotate_right(parent);
                parent->color_black = !parent->color_black;
                grandparent->color_black = !grandparent->color_black;
            }
            else if (uncle_color_black == true && grandparent->R == parent && parent->R == inserted) {
                rotate_left(parent);
                parent->color_black = !parent->color_black;
                grandparent->color_black = !grandparent->color_black;
            }
        }

        if (root->color_black==false) {
            root->color_black = true;
        }

    }

    template<typename S>
    void add(T value,S comp) {
        bool info = false;

        auto inserted=insert_node(value, comp);
        //cout << inserted <<", Data: "<<(inserted!=nullptr?inserted->data:-100)<< endl;
        re_color(inserted);
        
    }

    template<typename S>
    node<T>* find(T value, S comp) {
        bool info = false;
        node<T>* current = root;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            else if (comp(value, current->data)) {
                current = current->L;
            }
            else {
                current = current->R;
            }
        }
        if (info)cout << "Klucz nie istnieje!\n";
        return nullptr;

    }


    int pre_order(node<T>* nod, node<T>** tab, int i = 0)const {

        if (nod != nullptr) {
            tab[i++] = nod;
            i = pre_order(nod->L, tab, i);
            i = pre_order(nod->R, tab, i);

        }
        return i;
    }

    node<T>** pre_order_list(node<T>* nod)const {

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
        auto list = pre_order_list(root);
        int stop = size;
        for (int i = 0; i < stop; i++) {
            delete list[i];
            size--;
        }
        delete[] list;
        root = nullptr;
        cnt = 0;
    }

    int height(node<T>* nod) {
        if (nod == nullptr) return 0;

        int Lh = height(nod->L);
        int Rh = height(nod->R);
        int max;

        if (Lh > Rh) max = Lh;
        else max = Rh;

        return max + 1;
    }

    void to_string(int n = 10) {

        auto list = pre_order_list(root);
        int stop = size;
        if (n < size) stop = n;
        cout << "\n\t\t\t\tO-----(Red-Black Tree)-----O\n";
        cout << "Liczba elementow: " << size << endl;
        cout << "Liczba poziomow: " << height(root) << endl;

        for (int i = 0; i < stop; i++) {

            cout << "ID: " << list[i]->ID << ",\t Data: " << list[i]->data<<",\t Parent: ";


            if (list[i]->P != nullptr) cout << list[i]->P->data;
            else cout << "NULL";

            cout << ",\t Left: ";
            if (list[i]->L != nullptr)cout << list[i]->L->data;
            else cout << "NULL";

            cout << ",\t Right: ";
            if (list[i]->R != nullptr) cout << list[i]->R->data;
            else cout << "NULL";

            cout<<",\t Color: "<<(list[i]->color_black ? "BLACK" : "RED") << endl;
        }

    }

    void show_tree(node<T>* current,string str="") {//uzywac dla drzew z mala iloscia poziomow

        if (current != nullptr) {
            show_tree(current->R, str + "\t");
            cout << str << "[" << current->data << "|"<<(current->color_black?"BLACK":"RED")<< "]" << "======" << endl;
            show_tree(current->L, str + "\t");
        }
    }
};




int main()
{

    srand(time(NULL));
    RBT<int>* rbt = new RBT<int>;
    const int max_order = 7;
    unsigned long n, r, rr, hits;
    clock_t t1, t2;
    double time;
    int h;

    for (int i = 0; i <= max_order; i++) {
        int n = pow(10, i);

        t1 = clock();
        for (int i = 0; i < n; i++) {
            rr = rand();
            r = rand();
            rbt->add(r * rr % 10000000, Lesser<int>);
        }
        t2 = clock();
        time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        rbt->to_string(10);
        cout << endl << "Operacja dodawania 10^" << i << " elementow zajela: " << time << ", Czas sredni : " << (double)time / n << endl;
        h = rbt->height(rbt->root);
        cout << "Stosunek wysokosci drzewa do rozmiaru danych: " << (double)h / rbt->size << endl;
        cout << "Logartym (o podstawie 2) z rozmiaru danych: " << log2(rbt->size) << endl;
        cout << "Stosunek wysokosci drzewa do logarytmu z rozmiaru danych: " << (double)h / log2(rbt->size) << endl;


        t1 = clock();
        hits = 0;
        for (int i = 0; i < n; i++) {
            rr = rand();
            r = rand();
            if (rbt->find(r * rr % 10000000, Lesser<int>) != nullptr) hits++;
        }
        t2 = clock();
        time = (double)(t2 - t1) / CLOCKS_PER_SEC;


        cout << endl << "Operacja wyszukiwania 10^" << i << " elementow zajela: " << time << ", Czas sredni: " << (double)time / n << endl;
        cout << "Liczba trafien: " << hits << endl << endl;

        rbt->del_all();


    }

    delete rbt;


    return 0;
}