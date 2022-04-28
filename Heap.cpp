#include <iostream>
#include <time.h>
using namespace std;

template<typename T>
bool Greater(T a, T b) {
	return a > b;
}

template<typename T>
class dynamic_array {
	size_t size, capacity;
	T* arr;

public:
	dynamic_array() {
		capacity = 1;
		size = 0;
		arr = new T[capacity];

	}
	~dynamic_array() {
		if (arr != nullptr) {
			delete[] arr;
		}
	}
	void resize() {
		capacity *= 2;
		T* tmp = new T[capacity];
		for (int i = 0; i < size; i++) {
			tmp[i] = arr[i];
		};
		delete[] arr;
		arr = tmp;
	}

	int swap(int i, int j) {
		if (i >= size || i < 0 || j >= size || j < 0)
			return -1;
		T tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		return 0;
	}

	int add(T val) {
		int tmp = size;
		if (size >= capacity) {
			resize();
		}
		arr[size] = val;
		size++;
		return tmp;
	}

	T& at(int i) {
		if (i >= size || i < 0) {
			cout << "Wyszedles poza zakres tablicy!!!\n";
			return nullptr;
		}
		else {
			return arr[i];
		}
	}

	void set(int i, T val) {
		if (i >= size || i < 0) {
			cout << "Wyszedles poza zakres tablicy!!!\n";
		}
		else {
			arr[i] = val;
		}
	}
	void clear() {
		delete[] arr;
		capacity = 1;
		arr = new T[capacity];
		size = 0;
	}

	void to_string(int first = 5, int last = 5) {
		cout << "Adres tablicy: " << arr << ", rozmiar: " << size << ", pojemnosc: " << capacity << endl;
		cout << "Wartosci tablicy:\n";
		if (first + last > size) {
			first = size / 2;
			last = size - first;
		}

		for (int i = 0; i < first; i++) {
			cout << i << ". \t" << arr[i] << endl;
		}
		if (first + last != size) cout << ".\n.\n.\n";
		for (int i = size - last; i < size; i++) {
			cout << i << ". \t" << arr[i] << endl;
		}

	}
	T get_val(int i) {
		if (i >= size || i < 0) {
			cout << "Wyszedles poza zakres tablicy!!!\n";
			return NULL;
		}
		return arr[i];
	}
	void decr_size() {
		size--;
	}

	int get_size()const {
		return size;
	}
	int get_capacity()const {
		return capacity;
	}
};

template<typename T>
class Heap {
public:
	dynamic_array<T>* tab;
	

	int get_parent(int i) {
		if (i <= 0 || i >= get_heap_size()) {
			return -1;
		}
		return (i - 1)/2;
	}

	int get_left_child(int i) {
		int size = get_heap_size();
		if (i < 0 || i >=size ) {
			return -1;
		}
		int index = 2 * i + 1;
		if (index >= size) {
			return -1;
		}
		return index;
	}

	int get_right_child(int i) {
		int size = get_heap_size();
		if (i < 0 || i >= size) {
			return -1;
		}
		int index = 2 * i + 2;
		if (index >= size) {
			return -1;
		}
		return index;
	}

	template <typename S>
	void rebuild_heap_up(int i,S func) {
		if (i <= 0 || i>=get_heap_size()) {
			return;
		}
		else {
			int parent_id = get_parent(i);
			if ( func(tab->get_val(i), tab->get_val(parent_id)) ) {
				tab->swap(i, parent_id);
				rebuild_heap_up(parent_id,func);
			}
			else {
				return;
			}
		}
	}

	template <typename S>
	void rebuild_heap_down(int i,S func) {
		if (i < 0 || i >= get_heap_size()) {
			return;
		}
		else {
			int lchild = get_left_child(i);
			int rchild = get_right_child(i);
			int to_swap;

			if(lchild !=-1 && rchild!=-1){
				if (func(tab->get_val(lchild), tab->get_val(rchild))) {
					to_swap = lchild;
				}
				else {
					to_swap = rchild;
				}
			}
			else if (lchild != -1 && rchild == -1) {
				to_swap = lchild;
			}
			else {
				return;
			}

			if ( func( tab->get_val(to_swap), tab->get_val(i) )) {
				tab->swap(to_swap,i);
				rebuild_heap_down(to_swap, func);
			}
			else {
				return;
			}
		}
	}

public:

	Heap(){
		tab = new dynamic_array<T>;
	}

	template <typename S>
	void add(T val,S func) {
		int index=tab->add(val);
		rebuild_heap_up(index,func);
	}

	template <typename S>
	T pop_max(S func) {
		if (get_heap_size() <= 0) {
			cout << "Kopiec jest pusty!\n";
			return NULL;
		}

		T tmp = tab->get_val(0);
		tab->set(0, NULL);
		tab->decr_size();
		if (get_heap_size() >= 2) {
			tab->swap(0, tab->get_size() - 1);
			rebuild_heap_down(0,func);
		}
		return tmp;
	}

	void del_all() {
		tab->clear();
	}

	void to_string() {
		tab->to_string();
	}

	int get_heap_size() {
		return tab->get_size();
	}

	int get_heap_capacity() {
		return tab->get_capacity();
	}

};



int main()
{
	srand(time(NULL));
	Heap<int>* heap = new Heap<int>;

	const int max_order = 7;
	unsigned long n, r, rr;
	clock_t t1, t2;
	double time;
	int h;


	for (int i = 0; i <= max_order; i++) {
		int n = pow(10, i);

		t1 = clock();
		for (int i = 0; i < n; i++) {
			r = rand();
			heap->add(r, Greater<int>);
		}
		t2 = clock();
		time = (double)(t2 - t1) / CLOCKS_PER_SEC;
		heap->to_string();
		cout << endl << "Operacja dodawania 10^" << i << " elementow zajela: " << time << ", Czas sredni : " << (double)time / n << endl;


		t1 = clock();
		for (int i = 0; i < n; i++) {
			heap->pop_max(Greater<int>);
		}
		t2 = clock();
		time = (double)(t2 - t1) / CLOCKS_PER_SEC;

		cout<< "Operacja Usuwania maximum 10^" << i << " elementow zajela: " << time << ", Czas sredni: " << (double)time / n << endl<<endl;
		heap->to_string();

		cout << "\n================================================================================================================\n\n";
		heap->del_all();
	}

	delete heap;


	return 0;
}

