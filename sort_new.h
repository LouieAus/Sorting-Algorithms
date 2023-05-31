namespace louie_sort {
  
  // =========== Сортировка обменом: O(n^2), неустойчивая ===========
	// type_A - тип элементов массива, arr - указатель на первый элемент массива, size - размер массива
	template <typename type_A>
	void exchangeSortArrs(type_A* arr, int size) {
		for (auto i = 0; i != size; ++i) {
			for (auto j = i + 1; j != size; ++j) {
				if (*(arr + i) > *(arr + j)) {
					type_A temp = *(arr + i);
					*(arr + i) = *(arr + j);
					*(arr + j) = temp;
				}
			}
		}
	}
  
}
