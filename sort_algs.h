#pragma once
#include <vector>

namespace louie_sort {
	template <typename T>
	void swap(std::vector<T>& arr, unsigned int A, unsigned int B) {
		T temp = arr[A];
		arr[A] = arr[B];
		arr[B] = temp;
	}


	// =========== Сортировка обменом: O(n^2), неустойчивая ===========
	template <typename T>
	void exchangeSort(std::vector<T>& arr) {
		for (unsigned int i = 0; i < arr.size() - 1; i++) {
			for (unsigned int j = i + 1; j < arr.size(); j++) {
				if (arr[i] > arr[j])
					swap(arr, i, j);
			}
		}
	}


	// =========== Сортировка выбором: O(n^2), неустойчивая ===========
	template <typename T>
	void selectionSort(std::vector<T>& arr) {
		for (unsigned int i = 0; i < arr.size(); i++) {
			unsigned int j_min = i;
			unsigned int j = i + 1;
			for (; j < arr.size(); j++) {
				if (arr[j] < arr[j_min])
					j_min = j;
			}
			if (j_min != j)
				swap(arr, i, j_min);
		}
	}


	// =========== Сортировка пузырьком: O(n), O(n^2), устойчивая ===========
	template <typename T>
	void bubbleSort(std::vector<T>& arr) {
		bool swapped = false;
		do {
			swapped = false;
			for (unsigned int i = 0; i < arr.size() - 1; i++) {
				if (arr[i] > arr[i + 1]) {
					swap(arr, i, i + 1);
					swapped = true;
				}
			}
		} while (swapped);
	}


	// =========== Сортировка вставками: O(n), O(n^2), устойчивая ===========
	template <typename T>
	void insertionSort(std::vector<T>& arr) {
		for (unsigned int i = 1; i < arr.size(); i++) {
			if (arr[i] < arr[i - 1]) {
				int j = i;
				while ((j > 0) && (arr[j] < arr[j - 1])) {
					swap(arr, j, j - 1);
					j--;
				}
			}
		}
	}


	// =========== Сортировка Шелла: неустойчивая ===========
	enum h_type { SIMPLE, SEJVIG, HIBBARD, PRATT, CIURA, FIBONACHI, KNUT };

		// Функция реверса массива
	template <typename T>
	void inverseArray(std::vector<T>& arr) {
		for (unsigned int i = 0; i < arr.size() / 2; i++) {
			swap(arr, i, arr.size() - 1 - i);
		}
	}

		// Функция создания массива промежутков для соритровки Шелла
	void getIntervals(std::vector<unsigned int>& intervals, h_type interval, unsigned int elements_amount) {
			// Обычный вариант выбора промежутков: O(n^2)
		if (interval == SIMPLE) {
			intervals.push_back(elements_amount / 2);
			while (intervals[intervals.size() - 1] != 1) {
				intervals.push_back(intervals[intervals.size() - 1] / 2);
			}
		}

			// Вариант Седжвика выбора промежутков: O(n^(7/6)), O(n^(4/3))
		else if (interval == SEJVIG) {
			int i = 1;
			unsigned int k = 1;
			do {
				intervals.push_back(k);
				if (i % 2 == 0) {
					k = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
				}
				else {
					k = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;
				}
				i++;
			} while (k * 3 <= elements_amount);
			inverseArray(intervals);
		}

			// Вариант Хиббарда выбора промежутков: O(n^(3/2))
		else if (interval == HIBBARD) {
			int i = 2;
			unsigned int k = 1;
			do {
				intervals.push_back(k);
				k = pow(2, i) - 1;
				i++;
			} while (k <= elements_amount);
			inverseArray(intervals);
		}
		
		// Вариант Пратта выбора промежутков: O(n*(log n)^2)
		else if (interval == PRATT) {
			int a = 0;
			int k = 1;
			bool out = false;
			do {
				for (int i = 0; i <= a; i++) {
					int j = a - i;
					k = pow(2, j) * pow(3, i);
					if (k <= elements_amount / 2) {
						intervals.push_back(k);
					}
					else {
						out = true;
						break;
					}
				}
				a++;
			} while (!out);
			inverseArray(intervals);
		}

			// Вариант в виде последовательности Циура для выбора промежутков
		else if (interval == CIURA) {
			std::vector<short int> knut = { 1, 4, 10, 23, 57, 132, 301, 701, 1750 };
			for (short int& num : knut) {
				if (num > elements_amount / 2)
					break;
				intervals.push_back(num);
			}
			inverseArray(intervals);
		}

			// Вариант в виде последовательности Фибоначчи для выбора промежутков
		else if (interval == FIBONACHI) {
			std::vector<short int> knut = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597 };
			for (short int& num : knut) {
				if (num > elements_amount / 2)
					break;
				intervals.push_back(num);
			}
			inverseArray(intervals);
		}

			// Вариант Кнута выбора промежутков: O(n^(5/4)), O(n^(3/2))
		else if (interval == KNUT) {
			int i = 2;
			unsigned int k = 1;
			do {
				intervals.push_back(k);
				k = 0.5 * (pow(3, i) - 1);
				i++;
			} while (k <= elements_amount / 2);
			inverseArray(intervals);
		}
	}

		// Основной алгоритм сортировки Шелла
	template <typename T>
	void shellSort(std::vector<T>& arr, h_type interval) {
		std::vector<unsigned int> vecs;
		getIntervals(vecs, interval, arr.size());
		int curr = 0;
		unsigned int h;
		do {
			h = vecs[curr];
			for (int q = 0; q < h; q++) {
				for (unsigned int i = q + h; i < arr.size(); i = i + h) {
					if (arr[i] < arr[i - h]) {
						int j = i;
						while ((j > q) && (arr[j] < arr[j - h])) {
							swap(arr, j, j - h);
							j = j - h;
						}
					}
				}

			}
			curr++;
		} while (h != 1);
	}


	// =========== Быстрая сортировка: O(n*log(2, n)), O(n*log(n)), O(n^2), неустойчивая ===========

		// Функция разбиения массива методом Хоара
	template <typename T>
	unsigned int partition(std::vector<T>& arr, unsigned int low, unsigned int high) {
		T v = arr[(high + low) / 2];
		unsigned int i = low;
		unsigned int j = high;
		while (true) {
			while (arr[i] < v) {
				i++;
			}
			while (arr[j] > v) {
				j--;
			}
			if (i >= j) break;
			swap(arr, i, j);
			if (arr[i] == arr[j]) {
				i++;
				j--;
			}
		}
		return j;
	}

		// Основная функция сортировки
	template <typename T>
	void quickSort(std::vector<T>& arr, int high = 0, int low = 0, bool user = true) {
		if (user) {
			high = arr.size() - 1;
		}
		if (low < high) {
			unsigned int a = partition(arr, low, high);
			quickSort(arr, a, low, false);
			quickSort(arr, high, a + 1, false);
		}
	}
}