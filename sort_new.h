#pragma once
namespace louie_sort {
  
  // =========== Сортировка обменом: O(n^2), неустойчивая ===========
	template <typename T>
		void exchangeSortArr2(T iter_begin, T iter_end) {
			for (T i = iter_begin; i != iter_end; ++i) {
				if (i != iter_end) {
					T temp_i = i;
					T j = ++i;
					i = temp_i;
					for (; j != iter_end; ++j) {
						if (*i > *j) {
							auto temp = *i;
							*i = *j;
							*j = temp;
						}	
					}
				}
			}
		}
}
