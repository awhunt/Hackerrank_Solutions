#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check_sort(vector<int> v, vector<int> v2) {
	for(size_t i = 0; i < v.size(); i++) {
		if (v[i] != v2[i]) { return false; }
	}
	return true;
}

void print_vector(vector<int>& print_me){
	for(size_t i = 0; i < print_me.size(); ++i) {
		cout << print_me[i] << " ";
	}
	cout << '\n';
}

void add_rest(vector<int>& v, vector<int>::iterator start, 
			  vector<int>::iterator end) {
	while(start != end) {
		v.emplace_back(*start);
		start++;
	}
}

void merge(vector<int>::iterator start, 
	       vector<int>::iterator middle, 
	       vector<int>::iterator end) {
	vector<int> sorted_copy;
	size_t total_dist = distance(start, end);
	sorted_copy.reserve(total_dist);
	auto first_end = middle;
	auto begin = start;

	for (size_t i = 0; i < total_dist; ++i) {
		// base cases
		if (middle == end) { 
			add_rest(sorted_copy, start, first_end); 
			break;
		}
		if (start == first_end) {
			add_rest(sorted_copy, middle, end); 
			break;
		}

		// add lower elt
		if (*start < *middle) {
			sorted_copy.emplace_back(*start);
			start++;
		} else {
			sorted_copy.emplace_back(*middle);
			middle++;
		}
	}
	// copy over sorted vals
	for(size_t i = 0; i < sorted_copy.size(); ++i) {
		*begin = sorted_copy[i];
		begin++; 
	}

}

void merge_sort(vector<int>::iterator start, 
				vector<int>::iterator end, size_t n) {
	if (n < 2) { return; }
	
	size_t middle = n / 2;
	merge_sort(start, start + middle, middle);
	merge_sort(start + middle, end, n - middle);
	merge(start, (start + middle), end);
}

void quick_sort(vector<int>::iterator begin, 
				vector<int>::iterator end, size_t n){
	// base case
	if (n <= 1) { return; }

	size_t pivot = n - 1;
	int pivot_val = *(begin + n - 1);
	size_t left  = 0;
	size_t right = n - 2;

	// search for values to swap
	while (left < right) {
		// find a higher value on the left
		while ( (*(begin + left) < pivot_val) && 
				left < right) {
			left++;
		}
		// find a lesser value on right 
		while ( (*(begin + right) > pivot_val) && 
				right > left) {
			right--;
		}
		// swap values on either side of pivot
		if (left < right && 
			*(begin + left) >= pivot_val &&
			*(begin + right) <= pivot_val){
			// cout << "swapping " << *(begin + left) << " and ";
			// cout << *(begin + right) << '\n';
			iter_swap(begin + left, begin + right);
			right--;
			left++;
		}
	}

	// if(*(begin + right) > pivot_val) {
		// cout << "after\n";
		// cout << "swapping " << *(begin + right) << " and ";
		// cout << *(begin + pivot) << '\n';
	// 


	// split list and make recursive call
	quick_sort(begin, begin + pivot, pivot);
	quick_sort(begin + pivot + 1, end, (n - pivot));

}

int main(){
	vector<int> test1;
	vector<int> test2;
	int size1 = 0;
	int input;
	int num_tests = 100;
	int range = 10;
	int num_range = 100;


	// test1.push_back(1);
	// test1.push_back(2);
	// test1.push_back(7);
	// test1.push_back(0);
	// quick_sort(test1.begin(), test1.end(), test1.size());
	// print_vector(test1);
	// exit(1);

	for(int tests = 0; tests < num_tests; ++tests) {
		size1 = rand() % range;
		for (int i = 0; i < size1; i++) {
			input = rand() % num_range;
			test1.push_back(input);
		}

		for (int i = 0; i < int(test1.size()); i++) {
			test2.push_back(test1[i]);
		}
		cout << "Input: \n";
		print_vector(test1);
		print_vector(test2);

		sort(test2.begin(), test2.end());
		quick_sort(test1.begin(), test1.end(), test1.size());
		if (!check_sort(test1, test2)) {
			cout << "Error: \n";
			print_vector(test1);
			cout << "should be \n";
			print_vector(test2);
		} 
		else {
			cout << "correct!\n";
		}
		
		test1.clear();
		test2.clear();
	}

	

	cout << "PASSED!!!" << endl;

}