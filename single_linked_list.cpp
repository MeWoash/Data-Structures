#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

class node {

    int key;
    double _double;
    char _char;
    node* next;
    
public:
    node() :key(NULL), _double(NULL), _char(NULL), next(nullptr) {}
    node(int x, double y, char z,node* t=nullptr) :key(x), _double(y), _char(z), next(t) {}

    int get_key()const {
         return key;
    }
    double get_double()const {
        return _double;
    }
    char get_char()const {
        return _char;
    }
    node* get_next()const {
        return next;
    }


    void set_key(int x) {
        key = x;
    }
    void set_double(double x){
        _double = x;
    }
    void set_char(char x) {
        _char = x;
    }
    void set_next(node* x) {
        next = x;
    }
    
};

class single_linked_list {
    node* head;
    int node_number;
public:
    single_linked_list():head(nullptr),node_number(0){}
    
    void add(int key) {
        bool info = true;
        int max = 100;
        int min = 0;
        char ch = 'T';
        double d = (rand() % (max + 1 - min)) + min;

        if (head == nullptr) {
            head = new node(key,d,ch);
            incr_node_number();
            return;
        }
        
        node* current = head;
        while (current->get_next() != nullptr) {
            if (current->get_next()->get_key() < key) {
                current = current->get_next();
            }
            else if (current->get_next()->get_key() == key) {// czy sie powtarza z prawej
                if(info) cout << "Ten Klucz = "<<key<<" juz istnieje!\n";
                return;
            }
            else {
                break;
            }
        }

        if (current->get_key() == key) {// czy sie powtarza z lewej
            if (info) cout << "Ten Klucz juz istnieje!\n";
            return;
        }
        else if (current == head && current->get_key() > key) {// na poczatek
            head = new node(key,d,ch,current);
            incr_node_number();
        }
        else if (current->get_next() == nullptr) {//na koniec
            current->set_next(new node(key, d, ch));
            incr_node_number();
        }
        else{// w srodku
            node* tmp = new node(key, d, ch, current->get_next());
            current->set_next(tmp);
            incr_node_number();
        }
           
        

    }

    void add_n(int x) {
        bool unique = true;
        int max_k = 99999;
        int min_k = 99;
        int k,r;
        bool flag;
        int* tab = new int[x];

        for (int i = 0; i < x; i++) {
            do {
                flag = false;
                r=(rand() % (max_k + 1 - min_k)) + min_k;

                if (unique){
                    for (int j = 0; j < i; j++) {
                        if (tab[j] == r) {
                            flag = true;
                            break;
                        }
                    }
                }
            } while (flag);
            tab[i] = r;
        }

        for (int i = 0; i < x; i++) {
            add(tab[i]);
        }
        delete[] tab;
    }

    node* find(int x) {
        bool info = true;
        node* current = head;
        while (current != nullptr) {
            if (current->get_key()==x) {
                if(info) cout << "Klucz: " << current->get_key() << ", double: " << current->get_double() << ", char: " << current->get_char() << endl;
                return(current);
            }
            current = current->get_next();
        }
        if (info) cout << "Nie znaleziono klucza!\n";
        return(current);
    }

    void del(int x) {
        node* current = head;
        

        if (head == nullptr) {//pusta lista
            cout << "Lista jest pusta!\n";
            return;
        }

        if (head->get_key() == x) {//klucz w head
            node* tmp = head->get_next();
            delete head;
            head = tmp;
            incr_node_number(-1);
            return;
        }
        current = current->get_next();
        node* prev = head;
        while(current!=nullptr){
            if (current->get_key() == x) {
                prev->set_next(current->get_next());
                delete current;
                incr_node_number(-1);
                return;
            }
            prev = prev->get_next();
            current = current->get_next();
        }
        if (current == nullptr) {
            cout << "Nie znaleziono klucza!\n";
        }

        
    }

    void show_first(int x=5) {
        if (head == nullptr) {
            cout << "Lista jest pusta!\n";
            return;
        }
        node* current = head;
        cout << "Lista, adres head: 0x" << head << endl;
        for (int i = 0; i < x; i++) {
            if (current != nullptr) {
                cout <<i<< ". key = "<<current->get_key()<<", double = "<<current->get_double();
                cout << ", char = '" << current->get_char()<<"'" << endl;
                current = current->get_next();
            }
            else {
                break;
            }
        }

    }

    void show_last(int x = 5) {
        if (head == nullptr) {
            cout << "Lista jest pusta!\n";
            return;
        }
        if (x <= 0) return;
        node* beg=head, * end=head;
        int cnt = 0;

        for (int i = 0; i < x; i++) {
            if (end == nullptr) break;
            end = end->get_next();
        }
        while (end != nullptr) {
            end = end->get_next();
            beg = beg->get_next();
            cnt++;
        }

        do{
            cout << cnt << ". key = " << beg->get_key() << ", double = " << beg->get_double();
            cout << ", char = '" << beg->get_char() << "'" << endl;
            beg = beg->get_next();
            cnt++;
        } while (beg != end);

    }
    void show_node_number() {
        cout << "Liczba wezlow: " << get_node_number() << endl;
    }

    void del_all() {
        node* current = head,*next;
        while (current != nullptr) {
            next = current->get_next();
            delete current;
            current = next;
            incr_node_number(-1);
        }
        head = nullptr;
    }


    int set_node_number(int x){
        node_number=x;
    }
    int get_node_number()const {
        return node_number;
    }
    void incr_node_number(int x = 1) {
        node_number = node_number + x;
    }

};


int main()
{
    srand(time(NULL));
    int X, k1, k2, k3, k4, k5;
    
    fstream plik;
    plik.open("inlab02.txt", ios::in);
    if (!plik.is_open()) {
        cout << "Nie znaleziono pliku \"inlab02.txt\"\n";
        return 0;
    }
    plik >> X >> k1 >> k2 >> k3 >> k4 >> k5;
    plik.close();

    clock_t begin, end;
    double time;

    begin = clock();
    single_linked_list lista;
    lista.find(k1);
    cout << "\n";

    lista.add_n(X);
    lista.show_node_number();
    cout << "\n";

    lista.show_first(20);
    cout << "\n";

    lista.add(k2);
    lista.show_first(20);
    cout << "\n";

    lista.add(k3);
    lista.show_first(20);
    cout << "\n";

    lista.add(k4);
    lista.show_first(20);
    cout << "\n";

    lista.add(k5);
    lista.del(k3);
    lista.show_first(20);
    cout << "\n";

    lista.del(k2);
    lista.show_first(20);
    cout << "\n";

    lista.del(k5);
    lista.show_node_number();
    cout << "\n";

    lista.find(k5);
    lista.show_last(11);
    cout << "\n";

    lista.show_node_number();
    lista.del_all();

    end = clock();

    time = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "Zadanie wykonywalo sie: " << time << endl;
}
