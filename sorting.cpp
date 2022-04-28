#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

template<typename T>
bool Greater(T a, T b) {
	return a > b;
}

template<typename T>
class dynamic_array {
	size_t size, capacity;
	

public:
	T* arr;
	dynamic_array(T* array=nullptr, int s = 0, int c=1) : arr(array), capacity(c), size(s){

		if (!array) {
			arr = new T[capacity];
		}
	}

	~dynamic_array() {
		if (arr != nullptr) {
			delete[] arr;
		}
	}
	
	void insert(T val, int index) {
		if (size >= capacity) {
			resize();
		}
		//memmove(arr + index + 1, arr + index, (size - index)*sizeof(T));
		for (int i = size - 1; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = val;
		size++;
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

	T& operator[](int i) {
		return at(i);
	}

	T& at(int i) {
		if (i >= size || i < 0) {
			cout << "Wyszedles poza zakres tablicy!!!\n";
			return arr[0];
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
class Heap:public dynamic_array<T> {

	int get_parent(int i) {
		if (i <= 0 || i >= dynamic_array<T>::get_size()) {
			return -1;
		}
		return (i - 1) / 2;
	}

	int get_left_child(int i) {
		int size = dynamic_array<T>::get_size();
		if (i < 0 || i >= size) {
			return -1;
		}
		int index = 2 * i + 1;
		if (index >= size) {
			return -1;
		}
		return index;
	}

	int get_right_child(int i) {
		int size = dynamic_array<T>::get_size();
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
	void heap_up(int i, S func) {
		if (i <= 0 || i >= dynamic_array<T>::get_size()) {
			return;
		}
		else {
			int parent_id = get_parent(i);
			if (func(dynamic_array<T>::get_val(i), dynamic_array<T>::get_val(parent_id))) {
				dynamic_array<T>::swap(i, parent_id);
				heap_up(parent_id, func);
			}
			else {
				return;
			}
		}
	}

	template <typename S>
	void heap_down(int i, S func,int end) {
		int size = dynamic_array<T>::get_size();
		if (i < 0 || i >= size || i>=end) {
			return;
		}

		else {
			int lchild = get_left_child(i);
			if (lchild >= end)lchild = -1;
			int rchild = get_right_child(i);
			if (rchild >= end)rchild = -1;
			int to_swap;

			if (lchild != -1 && rchild != -1) {
				if (func(dynamic_array<T>::get_val(lchild), dynamic_array<T>::get_val(rchild))) {
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

			if (func(dynamic_array<T>::get_val(to_swap), dynamic_array<T>::get_val(i))) {
				dynamic_array<T>::swap(to_swap, i);
				heap_down(to_swap, func,end);
			}
			else {
				return;
			}
		}
	}

	template <typename S>
	void reheap_down(S func) {
		int size = dynamic_array<T>::get_size();
		for (int i = size - 1; i >= 0; i--) {
			heap_down(i, Greater<int>,size);
		}
	}

	template <typename S>
	void reheap_up(S func) {
		for (int i = 0; i < dynamic_array<T>::get_size(); i++) {
			heap_up(i, Greater<int>);
		}
	}

public:

	Heap():dynamic_array<T>() {
	}

	template<typename S>
	Heap(T* array,S func, size_t s, bool down=true): dynamic_array<T>(array, s, s){
		if (down) {
			reheap_down(func);
		}
		else {
			reheap_up(func);
		}
	}
	~Heap() {}

	template <typename S>
	void add(T val, S func) {
		int index = dynamic_array<T>::add(val);
		heap_up(index, func);
	}

	template <typename S>
	T pop_max(S func) {
		if (dynamic_array<T>::get_size() <= 0) {
			cout << "Kopiec jest pusty!\n";
			return NULL;
		}

		T tmp = dynamic_array<T>::get_val(0);
		dynamic_array<T>::set(0, NULL);
		dynamic_array<T>::decr_size();
		if (dynamic_array<T>::get_size() >= 2) {
			dynamic_array<T>::swap(0, dynamic_array<T>::get_size() - 1);
			heap_down(0, func,dynamic_array<T>::get_size());
		}
		return tmp;
	}

	void del_all() {
		dynamic_array<T>::clear();
	}

	template <typename S>
	void sort(S func) {
		int size = dynamic_array<T>::get_size();
		if (size <= 1) {
			return;
		}
		
		for (int i = 1; i<=size; i++) {
			dynamic_array<T>::swap(0, size - i);
			heap_down(0, func,size-i);
		}

	}

};

template <typename T>
void to_string(T* arr,int size, int first = 5, int last = 5) {
	cout << "Adres tablicy: " << arr << ", rozmiar: " << size << endl;
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

template<typename T>
void counting_sort(T* arr, int size) {

	long long min=arr[0], max=arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	long long m = max - min + 1;
	int* counts = new int[m]{};


	for (int i = 0; i < size; i++) {
		counts[arr[i] - min]++;
	}


	int k = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < counts[i]; j++) {
			arr[k] = min + i;
			k++;
		}
	}


	delete[]counts;
}

template<typename T>
void bucket_sort(T* arr, int size) {

	float min = arr[0], max = arr[0];

	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}

		if (arr[i] > max) {
			max = arr[i];
		}
	}
	float m = max - min + 1;
	float w = max/(float)size+1;

	dynamic_array<T>* buckets = new dynamic_array<T>[size];

	for (int i = 0; i <size; i++) {
		int bucket_index = arr[i] / w;
		int bucket_size = buckets[bucket_index].get_size();

		if (bucket_size <= 0) { 
			buckets[bucket_index].add(arr[i]);
		}
		else if (buckets[bucket_index][bucket_size - 1] <= arr[i]) {
			buckets[bucket_index].add(arr[i]);
		}
		else {
			int p = 0;
			int prev=0;
			while (p < bucket_size && arr[i] < buckets[bucket_index][p]) {
				prev = p;
				p++;
			}
			buckets[bucket_index].insert(arr[i], prev);
		}
	}

	int k = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < buckets[i].get_size(); j++) {
			arr[k] = buckets[i][j];
			k++;
		}
	}


}



int main()
{
	srand(time(NULL));

	int first = 5;
	int last = 5;

	const int max_order = 7;
	unsigned long n, r, rr;
	clock_t t1, t2;
	double time;


	for (int i = 1; i <= max_order; i++) {
		int n = pow(10, i);

		int* arr1 = new int[n];
		int* arr2 = new int[n];
		int* arr3 = new int[n];

		for (int i = 0; i < n; i++) {
			r =((rand() << 15) + rand())%1000000;
			arr1[i] = r;
		}
		memcpy(arr2, arr1,n * sizeof(int));
		memcpy(arr3, arr1,n * sizeof(int));

		cout << "==========================================================================" << endl;
		cout << "\t\t\t=== Tablica do posortowania === " << endl;
		to_string(arr1, n,first,last);

		////////////////////////////////////////////////////////////////////////////////////////////////////////Heap sort

		t1 = clock();
		Heap<int>* heap = new Heap<int>(arr1,Greater<int>, n, true);
		heap->sort(Greater<int>);
		t2 = clock();

		time = (double)(t2 - t1) / CLOCKS_PER_SEC;

		cout << "\t\t\t=== HEAP SORT ===" << endl;
		to_string(arr1, n, first, last);
		cout << endl << "Sortowanie 10^" << i << " elementow zajelo: " << time << endl;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////Counting sort

		t1 = clock();
		counting_sort<int>(arr2,n);
		t2 = clock();

		time = (double)(t2 - t1) / CLOCKS_PER_SEC;

		cout << "\t\t\t=== COUNTING SORT ===" << endl;
		to_string(arr2, n, first, last);
		cout << endl << "Sortowanie 10^" << i << " elementow zajelo: " << time << endl;


		////////////////////////////////////////////////////////////////////////////////////////////////////////Bucket sort

		t1 = clock();
		bucket_sort<int>(arr3, n);
		t2 = clock();

		time = (double)(t2 - t1) / CLOCKS_PER_SEC;

		cout << "\t\t\t=== BUCKET SORT ===" << endl;
		to_string(arr3, n, first, last);
		cout << endl << "Sortowanie 10^" << i << " elementow zajelo: " << time << endl;


		///////////////////////////////////////////////////////////////////////////////////////////////////////////delete
		
		delete heap;
		delete[]arr2;
		delete[]arr3;
		
	}

	

	return 0;
}