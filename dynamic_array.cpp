#include <iostream>
#include <time.h>

using namespace std;

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

	void add(T val) {

		if (size >= capacity) {
			capacity *= 2;
			T* tmp = new T[capacity];
			for (int i = 0; i < size; i++) {
				tmp[i] = arr[i];
			};
			delete [] arr;
			arr = tmp;
		}
		arr[size] = val;
		size++;
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
		delete [] arr;
		capacity = 1;
		arr = new T[capacity];
		size = 0;
	}

	void to_string(int first=5, int last=5) {
		cout << "Adres tablicy: " << arr << ", rozmiar: " << size << ", pojemnosc: " << capacity << endl;
		cout << "Wartosci tablicy:\n";
		if (first + last > size) {
			first = size / 2;
			last = size - first;
		}

		for (int i = 0; i < first; i++) {
			cout << i << ". \t" << arr[i] << endl;
		}
		if(first+last!=size) cout << ".\n.\n.\n";
		for (int i = size-last; i < size; i++) {
			cout << i << ". \t" << arr[i] << endl;
		}

	}

	int get_size()const {
		return size;
	}
	int get_capacity()const {
		return capacity;
	}

	template<typename func>
	void sort(func fun) {

		for (int i = 0; i < size; i++) {
			bool flag = false;
			for (int j = 0; j < size - i - 1; j++) {
				if (fun(arr[j], arr[j + 1])) {

					T tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
					flag = true;
				}
			}
			if (!flag) break;
		}

	}

};

template<typename T>
bool lesser_(T a, T b){
	return (a < b);
}
template<typename T>
bool greater_(T a, T b) {
	return (a > b);
}

int main()
{

	long int n = pow(10, 7);
	dynamic_array <int>* tablica = new dynamic_array<int>;

	clock_t time_all_b = clock();
	clock_t time_all_e, time_el_b, time_el_e;
	double max_time_element = 0, time_el, time_all;
	


	srand(time(NULL));
	for (long int i = 0; i < n;i++) {

		time_el_b = clock();
		tablica->add(rand()%100001);
		time_el_e = clock();
		time_el = (double)(time_el_e - time_el_b) / CLOCKS_PER_SEC;
		if (time_el > max_time_element) {
			max_time_element = time_el;
			cout << "Uzyskano nowy maksymalny czas dodawania elementu!\n";
			cout << "Czas: " << max_time_element << ", rozmiar: " << tablica->get_size();
			cout << ", pojemnosc: " << tablica->get_capacity() << "\n\n";
		}
	}
	time_all_e = clock();
	time_all= (double)(time_all_e - time_all_b) / CLOCKS_PER_SEC;
	cout << "=========================================================================\n";
	cout << "Calkowity czas dodawaia: " << time_all << ",\n";
	cout<< "Najdluzszy czas dodawania elementu: "<<max_time_element<<",\n\n";
	tablica->to_string();

	tablica->clear();
	delete tablica;
	return 0;
};