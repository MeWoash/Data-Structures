#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <iomanip>

using namespace::std;

class Node {
    public:
    int data;
    Node(int d=0) :data(d) {};
};


class Hash_table {
public:
    int hash_function(int key) {
        return (((key % 1000) + int(pow(2, key % 10)) + 1) % 997);
    }
    int hash_function2(int key) {
        return ((3 * key) % 19 + 1);
    }

    int double_hash(int key,int i) {
        return (hash_function(key) + i * hash_function2(key)) % capacity;
    }
    int linear_hash(int key, int i=0) {
        return (hash_function(key) + i) % capacity;
    }

    void resize() {
        if (tab == nullptr) return;

        int old_capacity = capacity;
        int* tmp = new int[old_capacity];

        for (int i = 0; i < old_capacity; i++) {
            tmp[i] = tab[i]->data;
        }

        del_all();
        init_table(old_capacity*2);
        for (int i = 0; i < old_capacity; i++) {
            if(tmp[i]>0) add(tmp[i]);
        }
        delete[]tmp;

    }

    Node* add_linear(int value) {
        int i = 0, index;
        int looped = -2;

        while (true) {
            index = linear_hash(value, i);
            //cout << "liczba: " << value << ", index: " << index << endl;
            if (tab[index]->data <= 0) {
                tab[index]->data = value;
                size++;
                return tab[index];
            }
            else if (tab[index]->data == value) {
                return nullptr;
            }
            else if (index == looped) {
                //cout << "Brak miejsca w tablicy!" << endl;
                resize();
            }
            else if (i == 0) {
                looped = index;
            }
            i++;
        }
    }

    Node* add_double(int value) {
        int i = 0, index;
        int looped = -2;

        while (true) {
            index = double_hash(value, i);
            //cout << "liczba: " << value << ", index: " << index << endl;
            if (tab[index]->data <= 0) {
                tab[index]->data = value;
                size++;
                return tab[index];
            }
            else if (tab[index]->data == value) {
                return nullptr;
            }
            else if (index == looped) {
                //cout << "Brak miejsca w tablicy!" << endl;
                resize();
                i = 0;
            }
            else if (i == 0) {
                looped =index;
            }
            i++;
        }

    }

    Node* find_linear(int value) {
        int i = 0, index;
        int looped = -2;

        while (true) {
            index = linear_hash(value, i);
            if (tab[index]->data == value) {
                return tab[index];
            }
            else if (index == looped) {
                return nullptr;
            }
            else if (i == 0) {
                looped = index;
            }
            i++;
        }
    }

    Node* find_double(int value) {
        int i = 0, index;
        int looped = -2;

        while (true) {
            index = double_hash(value, i);
            if (tab[index]->data == value) {
                return tab[index];
            }
            else if (index == looped) {
                return nullptr;
            }
            else if (i == 0) {
                looped = index;
            }
            i++;
        }
    }


    int capacity;
    int size;
    Node** tab;
    char col_method;

public:
    Hash_table(){
        col_method = NULL;
        capacity = 0;
        size = 0;
        tab = nullptr;
    }

    void set_col_method(char ch='l') {
        if (tab != nullptr) {
            cout << "Aby wybrac metode rozwiazywania kolizji, tablica nie moze byc zainicjalizowana!\n";
            return;
        }
        switch (ch) {
        case 'l':
        case 'd':
            col_method = ch;
            break;
        default:
            cout << "Niepoprawna metoda rozwiazywania kolizji!\n";
        }
    }


    void init_table(int s = 997) {

        if (col_method == NULL) {
            cout << "Najpierw wyznacz metode rozwiazywanie kolizji!\n";
            return;
        }
        else if (tab != nullptr) {
            cout << "Najpierw usun poprzednia tablice!\n";
            return;
        }

        capacity = s;
        tab = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            tab[i] = new Node(0);
        }

    }

    void del(int value) {
        auto to_delete = find(value);
        if (to_delete == nullptr) {
            return;
        }
        
        to_delete->data = -1;
        size--;

    }
    Node* add(int value) {
        Node* added = nullptr;

        switch (col_method) {
        case 'l': {
            added=add_linear(value);
            break;
        }
        case 'd': {
            added=add_double(value);
            break;
        }
        default:
            //cout << "Blad!\n";
            break;
        }
        return added;
    }
    void add_n(int N) {
        srand(time(NULL));
        int min = 20000;
        int max = 40000;
        Node* added;
        int r;

        for (int i = 0; i < N; i++) {
            added = nullptr;
            while(added==nullptr) {
                r = rand() % (max - min + 1) + min;
                added=add(r);
                //if (added == nullptr) cout << r << endl;
            }

        }

    }

    Node* find(int value) {
        Node* found = nullptr;
        switch (col_method) {
        case 'l': {
            found=find_linear(value);
            break;
        }
        case 'd': {
            found = find_double(value);
            break;
        }
        default:
            cout << "Blad!\n";
        }
        if (found == nullptr) cout << "Brak klucza: "<<value<< " w tablicy!" << endl;
        return found;
    }


    void del_all() {
        for (int i = 0; i < capacity; i++) {
            delete tab[i];
        }
        delete[]tab;
        tab = nullptr;
        size = 0;
        capacity = 0;
    }
    void show() {
        show(0, capacity);
    }
    void show(int begin,int end) {
        cout << "====================================\nTablica Mieszajaca:\n";
        for (int i = begin; i < end; i++) {
            //if (tab[i]->data > 0)
            cout << "tab[" << i << "] = " << tab[i]->data << endl;
        }
        cout << "====================================\n";
    }

    int get_capacity() {
        return capacity;
    }
    int get_size() {
        return size;
    }


};


int main()
{
    int X, k1, k2, k3, k4;

    fstream plik;
    plik.open("inlab07.txt", ios::in);
    if (!plik.is_open()) {
        cout << "Nie znaleziono pliku \"inlab07.txt\"\n";
        return 0;
    }

    plik >> X>>k1>>k2>>k3>>k4;
    plik.close();

    Hash_table obj;

    clock_t begin, end;
    double time;
    
    begin = clock();

    obj.set_col_method('l'); //adresowanie liniowe
    obj.init_table();
    cout << "Usuwanie: " << k1 << endl;
    obj.del(k1);
    cout << "Dodawanie: " << k1 << endl;
    obj.add(k1);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    cout << "Wstawianie " << X << ". elementow" << endl;
    obj.add_n(X);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    cout << "Dodawanie: " << k2 << endl;
    obj.add(k2);
    cout << "Dodawanie: " << k3 << endl;
    obj.add(k3);
    cout << "Dodawanie: " << k4 << endl;
    obj.add(k4);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(500, 600);
    cout << "Usuwanie: " << k3 << endl;
    obj.del(k3);
    cout << "Usuwanie: " << k4 << endl;
    obj.del(k4);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    obj.show(500, 600);

    end = clock();
    time = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Czas wykonywania tej fazy programu: "<< time << endl;
    
    obj.del_all();
    //FAZA 2

    begin = clock();
    obj.set_col_method('d'); // mieszanie podwojne
    obj.init_table();

    cout << "Usuwanie: " << k1 << endl;
    obj.del(k1);
    cout << "Dodawanie: " << k1 << endl;
    obj.add(k1);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    cout << "Wstawianie " << X << ". elementow" << endl;
    obj.add_n(X);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    cout << "Dodawanie: " << k2 << endl;
    obj.add(k2);
    cout << "Dodawanie: " << k3 << endl;
    obj.add(k3);
    cout << "Dodawanie: " << k4 << endl;
    obj.add(k4);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(500, 600);
    cout << "Usuwanie: " << k3 << endl;
    obj.del(k3);
    cout << "Usuwanie: " << k4 << endl;
    obj.del(k4);
    cout << "Wyswietlanie tablicy: " << endl;
    obj.show(0, 100);
    obj.show(500, 600);


    end = clock();
    time = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Czas wykonywania tej fazy programu: " << time << endl;;


    obj.del_all();


}
