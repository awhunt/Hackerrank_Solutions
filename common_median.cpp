#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void print_vector(vector<int>& print_me){
	for(size_t i = 0; i < print_me.size(); ++i) {
		cout << print_me[i] << " ";
	}
	cout << '\n';
}


double median(vector<int>& med) {
	// if empty return -1
	if (med.size() == 0) { return -1.0; }
	// return median
	int mid = med.size() / 2;
	if ( (med.size() % 2) == 0) {
		return (double(med[mid] + med[mid - 1]) / 2.0);
	} else {
		return double(med[mid]);
	}
}


double common_median(vector<int>& nums1, vector<int>& nums2) {
	// two empty vectors
	if (!nums1.size() && !nums2.size()) { return -1.0; }

	// one empty vector
	if (!nums1.size()) { return median(nums2); }
	if (!nums2.size()) { return median(nums1); }
	if (nums1.size() == 1 && nums2.size() == 1) {
		return double(nums1[0] + nums2[0]) / 2.0;
	}

	bool is_even = false;
    is_even = ((nums1.size() + nums2.size()) % 2 == 0);
    
    size_t ind1 = 0;
    size_t ind2 = 0;
    size_t used1 = 0;
    size_t used2 = 0;
    size_t end_ind = ((nums1.size() + nums2.size()) / 2) + 1;

    // bounds
    size_t upper1 = nums1.size();
    size_t upper2 = nums2.size();
    size_t lower1 = 0;
    size_t lower2 = 0; 
    
    while( (used1 + used2) != end_ind) {
        // continue upward
        if ( (used1 + used2) < end_ind) {

            // first elt less than second, jump up on first
            if (nums1[ind1] < nums2[ind2]) {
            	if (!ind1) {
	        		used1++;
	        		continue;
	        	} else if (ind1 == nums1.size() - 1) {
	        		lower2 = ind2;
	                ind2 += (upper2 - ind2) / 2;
	                used2 = ind2 + 1;
	                continue;
	        	}
            	lower1 = ind1;
                ind1 += (upper1 - ind1) / 2;
                used1 = ind1 + 1;
            }
            // second elt less than eq to, jump up on second
            else{
            	if (!ind2) {
	        		used2++;
	        		continue;
	        	} else if (ind2 == nums2.size() - 1) {
        			lower1 = ind1;
                	ind1 += (upper1 - ind1) / 2;
                	used1 = ind1 + 1;
                	continue;
        		} 
            	lower2 = ind2;
                ind2 += (upper2 - ind2) / 2;
                used2 = ind2 + 1;
            }
        } 
        // need to backtrack
        else {
        	if (ind1 == nums1.size() - 1) {
        		upper2 = ind2;
                ind2 -= (ind2 - lower2) / 2;
                used2 = ind2 + 1;
                continue;
        	}

        	if (ind2 == nums2.size() - 1) {
        		upper1 = ind1;
                ind1 -= (ind1 - lower1) / 2;
                used1 = ind1 + 1;
                continue;
        	}
            // second elt greater than, jump back on second
            if (nums1[ind1] < nums2[ind2]) {
            	upper2 = ind2;
                ind2 -= (ind2 - lower2) / 2;
                used2 = ind2 + 1;
            }
            // first elt greater than, jump back on first
            else{
            	upper1 = ind1;
                ind1 -= (ind1 - lower1) / 2;
                used1 = ind1 + 1;
            }
        }
    } // while
    
    double return_me = 0.0;

    if(!used1) {
    	if (is_even) {
    		return double(nums2[ind2] + nums2[ind2 - 1]) / 2.0;
    	} else {
    		return nums2[ind2];
    	}
    }

    if(!used2) {
    	if (is_even) {
    		return double(nums1[ind1] + nums1[ind1 - 1]) / 2.0;
    	} else {
    		return nums1[ind1];
    	}
    }

    
    // return middle number 
    if (nums1[ind1] > nums2[ind2])
        return_me += nums1[ind1--];
    else 
        return_me += nums2[ind2--];

    if(is_even) {  
        if (nums1[ind1] > nums2[ind2])
            return_me += nums1[ind1];
        else 
            return_me += nums2[ind2];

        return_me /= 2;
    }
    return return_me;
}


double solve_median_slow(vector<int>& nums1, vector<int>& nums2) {
	// if either vectors are empty
	if (nums1.size() == 0) {
		return median(nums2);
	} else if (nums2.size() == 0) {
		return median(nums1);
	}

	vector<int> total;
	for (size_t i = 0; i < nums1.size(); i++) {
		total.push_back(nums1[i]);
	}

	for (size_t i = 0; i < nums2.size(); i++) {
		total.push_back(nums2[i]);
	}

	sort(total.begin(), total.end());

	return median(total);
}

bool check_median(vector<int>& nums1, vector<int>& nums2) {
	double test    = common_median(nums1, nums2);
	double correct = solve_median_slow(nums1, nums2);
	return ((test - correct) < 0.001);
}


int main(){
	vector<int> test1;
	vector<int> test2;
	int size1 = 0;
	int size2 = 0;
	int input;
	int num_tests = 100;
	int range = 5;
	int num_range = 5;

	test1.push_back(1);
	test1.push_back(3);
	test2.push_back(2);
	cout << common_median(test1, test2)<< '\n';
	test1.clear();
	test2.clear();
	for(int tests = 0; tests < num_tests; ++tests) {
		size1 = rand() % range;
		for (int i = 0; i < size1; i++) {
			input = rand() % num_range;
			test1.push_back(input);
		}
		size2 = rand() % range;
		for (int i = 0; i < size2; i++) {
			input = rand() % num_range;
			test2.push_back(input);
		}

		sort(test1.begin(), test1.end());
		sort(test2.begin(), test2.end());
		if (!check_median(test1, test2)) {
			cout << "vector 1: ";
			print_vector(test1);
			cout << "vector 2: ";
			print_vector(test2);
			cout << "Correct Answer: " << solve_median_slow(test1, test2) << '\n';
			cout << "Your    Answer: " << common_median(test1, test2) << '\n';
		} 
		// else {
		// 	cout << "correct\n";
		// }

		test1.clear();
		test2.clear();
	}

	

	cout << "PASSED!!!" << endl;

}
