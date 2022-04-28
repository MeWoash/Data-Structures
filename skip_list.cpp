#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

class node {

    int key;
    int levels;
    double _double;
    char _char;
    node** next;
    

public:
    node() :key(NULL), levels(NULL), _double(NULL), _char(NULL), next(nullptr) {}
    node(int x, double y, char z, node** t = nullptr) :key(x), _double(y), _char(z), next(t) {}

    int get_key()const {
        return key;
    }
    double get_double()const {
        return _double;
    }
    char get_char()const {
        return _char;
    }
    node* get_next(int level)const {
        return next[level];
    }
    node** get_next_array() {
        return next;
    }
    int get_max_lvl()const {
        return levels;
    }


    void set_key(int x) {
        key = x;
    }
    void set_double(double x) {
        _double = x;
    }
    void set_char(char x) {
        _char = x;
    }
    void set_next_size(int lvl=11) {
        levels = lvl;
        if (next != nullptr) {
            delete [] next;
        }
        next = new node * [levels];

        for (int i = 0; i < levels; i++) {
            next[i] = nullptr;
        };
    }

    void set_next(node* x,int level) {
        next[level] = x;
    }

};

class skip_list {
    node* head;
    int lmax;
    int node_number;

    int set_node_number(int x) {
        node_number = x;
    }

    void incr_node_number(int x = 1) {
        node_number = node_number + x;
    }

public:
    skip_list(int l=10) :head(nullptr),lmax(l), node_number(0) {}


    int get_node_number()const {
        return node_number;
    }
    int get_lmax()const {
        return lmax;
    }

    void add(int key) {
        bool info = true;

        char ch = 'T';
        double db = rand() % 100 + 1;
        int lvl = rand() % (get_lmax() + 1) + 1;

        if (head == nullptr) {
            head = new node(key,db,ch);
            incr_node_number();
            head->set_next_size(get_lmax()+1);
            return;
       }

        if (head->get_key() > key) {
            node* tmp = new node(key, db, ch);
            incr_node_number();
            tmp->set_next_size(get_lmax() + 1);
            for (int i = 0; i < get_lmax() + 1; i++) {
                tmp->set_next(head, i);
            }
            head = tmp;
            return;
        }
        else if (head->get_key() == key) {
            head->set_char('D');
            if(info)cout << "Klucz juz istnieje!\n";
            return;
        }

        
        node** current = new node* [get_lmax() + 1];
        for (int i = 0; i <= get_lmax();i++) {
            current[i] = head;
        }
        node* searching = head;
        
        int current_lvl = get_lmax();

        while (current_lvl >= 0) {

            if (searching == nullptr) {
                current_lvl--;
                searching = current[current_lvl];
                continue;
            }
            else if (searching->get_key() > key) {
                current_lvl--;
                searching = current[current_lvl];
                continue;
            }
            else if (searching->get_key() == key){
                searching->set_char('D');
                if (info)cout << "Klucz juz istnieje!\n";
                return;
            }
            else if (searching->get_key() < key) {
                current[current_lvl] = searching;
            }

            if (current_lvl >= 0) {
                searching = searching->get_next(current_lvl);
            }
            else break;
        }

            node* tmp = new node(key, db, ch);
            incr_node_number();
            tmp->set_next_size(lvl);

            for (int i = lvl-1; i >= 0; i--) {

                tmp->set_next(current[i]->get_next(i), i);
                current[i]->set_next(tmp, i);
            }
        delete[] current;

    }

    void add_n(int x) {
        bool unique = true;
        int max_k = 99999;
        int min_k = 99;
        int k, r;
        bool flag;
        int* tab = new int[x];

        for (int i = 0; i < x; i++) {
            do {
                flag = false;
                r = (rand() % (max_k + 1 - min_k)) + min_k;

                if (unique) {
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

    node* find(int key) {
        bool info = true;
        bool debug = false;

        node* current = head,*prev=head;
        int lvl_counter = get_lmax();
        
        while (lvl_counter >= 0) {

            if(current!=nullptr && debug)cout << current->get_key() << " -> ";

            if (current == nullptr) {
                lvl_counter--;
                current = prev;
                if (debug) cout << "\n";
                continue;
            }
            else if (current->get_key() > key) {
                lvl_counter--;
                current = prev;
                if (debug) cout << "\n";
                continue;
            }
            else if (current->get_key() == key) {
                if (info) cout << "Znaleziono klucz!\n";
                return current;
            }
            else if (current->get_key() < key) {
                prev = current;
            }

            if (lvl_counter >= 0) {
                current = current->get_next(lvl_counter);
            }
            else break;
        }

        if (info) cout << "Nie znaleziono klucza!\n";
        return(current);
    }

    void del(int key) {

        node** current = new node * [get_lmax()+1];
        for (int i = 0; i <= get_lmax(); i++) {
            current[i] = head;
        }
        node* searching = head;
        node* found=nullptr;

        int current_lvl = get_lmax();

        while (current_lvl >= 0) {

            if (searching == nullptr) {
                current_lvl--;
                searching = current[current_lvl];
                continue;
            }
            else if (searching->get_key() > key) {
                current_lvl--;
                searching = current[current_lvl];
                continue;
            }
            else if (searching->get_key() == key) {
                found = searching;
            }
            else if (searching->get_key() < key) {
                current[current_lvl] = searching;
            }

            if (current_lvl >= 0) {
                searching = searching->get_next(current_lvl);
            }
            else break;
        }

        if (found == nullptr) {
            cout << "Nie znaleziono klucza!\n";
        }
        else {
            if (found != head)
            {
                for (int i = found->get_max_lvl() - 1; i >= 0; i--) {
                    current[i]->set_next(found->get_next(i), i);
                }
                delete found;
                incr_node_number(-1);
            }
            else if(found==head && found->get_next(0)!=0){
                node** tmp = new node * [get_lmax() + 1];

                for (int i = get_lmax(); i > found->get_next(0)->get_max_lvl()-1; i--) {
                    tmp[i] = found->get_next(i);
                }
                for (int i = found->get_next(0)->get_max_lvl()-1; i >= 0; i--) {
                    tmp[i] = found->get_next(0)->get_next(i);
                }
                found = found->get_next(0);
                found->set_next_size(get_lmax() + 1);
                for (int i = 0; i <= get_lmax(); i++) {
                    found->set_next(tmp[i], i);
                }
                delete head;
                incr_node_number(-1);
                head = found;
                delete[]tmp;
            }
            else {
                delete found;
                incr_node_number(-1);
            }

        }

        delete[]current;
    }

    void show_first(int x = 5, int lvl=0) {

        if (lvl > get_lmax()) {
            cout << "Nie ma takiego poziomu!\n";
            return;
        }

        if (head == nullptr) {
            cout << "Lista jest pusta!\n";
            return;
        }
        node* current = head;
        cout << "\nPoziom: " << lvl << endl;
        cout << "Lista, adres head: 0x" << head << endl;
        for (int i = 0; i < x; i++) {
            if (current != nullptr) {
                cout << i << ". key = " << current->get_key() << ", double = " << current->get_double();
                cout << ", char = '" << current->get_char() << "'" << endl;
                current = current->get_next(lvl);
            }
            else {
                break;
            }
        }

    }

    void show_last(int x = 5,int lvl=0) {
        if (lvl > get_lmax()) {
            cout << "Nie ma takiego poziomu!\n";
            return;
        }
        if (head == nullptr) {
            cout << "Lista jest pusta!\n";
            return;
        }
        if (x <= 0) return;
        node* beg = head, * end = head;
        int cnt = 0;

        for (int i = 0; i < x; i++) {
            if (end == nullptr) break;
            end = end->get_next(lvl);
        }
        while (end != nullptr) {
            end = end->get_next(lvl);
            beg = beg->get_next(lvl);
            cnt++;
        }

        do {
            cout << cnt << ". key = " << beg->get_key() << ", double = " << beg->get_double();
            cout << ", char = '" << beg->get_char() << "'" << endl;
            beg = beg->get_next(lvl);
            cnt++;
        } while (beg != end);

    }
    void show_node_number() {
        cout << "Liczba wezlow: " << get_node_number() << endl;
    }

    void show_node_number(int lvl) {
        if (lvl > get_lmax()) {
            cout << "Brak takiego poziomu!\n";
            return;
        }
        if (head == nullptr) {
            cout << "Lista jest pusta!\n";
            return;
        }
        int cnt = 0;
        node* current = head;
        while (true) {
            if (current != nullptr) {
                cnt++;
                current = current->get_next(lvl);
            }
            else {
                cout << "Liczba wezlow widocznych na " << lvl << ". poziomie: " << cnt << endl;
                break;
            }
        }
    }


    void del_all() {
        node* current = head, * next;
        while (current != nullptr) {
            next = current->get_next(0);
            delete [] current->get_next_array();
            delete current;
            current = next;
            incr_node_number(-1);
        }
        head = nullptr;
    }

    void debug(int x = 5) {
        if (head == nullptr) {
            cout << "Lista jest pusta!\n";
            return;
        }
        node* tmp = head;
        int cnt = 0;
        while (tmp != nullptr && cnt<x) {
            cout << tmp->get_key() << " : " << tmp->get_max_lvl() << " levels\n";
            tmp = tmp->get_next(0);
            cnt++;
        }
        cout << "\n";

        for (int k = get_lmax(); k >= 0; k--) {
            node* current = head;
            cout << "\nPoziom: "<<k<<endl;
            for (int i = 0; i < x; i++) {
                if (current != nullptr) {
                    cout << current->get_key() << " -> ";
                    current = current->get_next(k);
                }
                else {
                    cout << "\n";
                    break;
                }
            }
        }

    }

};


int main()
{
    srand(time(NULL));

    int X, k1, k2, k3, k4, k5,LMAX;
    clock_t begin, end;
    double time;

    fstream plik;
    plik.open("inlab03.txt", ios::in);
    if (!plik.is_open()) {
        cout << "Nie znaleziono pliku \"inlab03.txt\"\n";
        return 0;
    }
    plik >> X >>LMAX>> k1 >> k2 >> k3 >> k4 >> k5;
    plik.close();

    begin = clock();
    skip_list* obj=new skip_list(LMAX);

    obj->find(k1);
    obj->add_n(X);
    for (int i = 0; i <= LMAX; i++) {
        obj->show_node_number(i);
    }
    for (int i = 0; i <= LMAX; i++) {
        obj->show_first(20,i);
    }
    obj->add(k2);
    for (int i = 0; i <= LMAX; i++) {
        obj->show_first(20, i);
    }
    obj->add(k3);
    for (int i = 0; i <= LMAX; i++) {
        obj->show_first(20, i);
    }
    obj->add(k4);
    for (int i = 0; i <= LMAX; i++) {
        obj->show_first(20, i);
    }
    obj->add(k5);
    for (int i = 0; i <= LMAX; i++) {
        obj->show_node_number(i);
    }
    for (int i = 0; i <= LMAX; i++) {
        obj->show_first(20, i);
    }
    obj->del(k3);
    obj->del(k2);
    obj->del(k5);
    for (int i = 0; i <= LMAX; i++) {
        obj->show_node_number(i);
    }
    for (int i = 0; i <= LMAX; i++) {
        obj->show_first(20, i);
    }

    end = clock();
    time = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Zadanie wykonywalo sie: " << time << endl;

    obj->del_all();
    delete obj;
}
