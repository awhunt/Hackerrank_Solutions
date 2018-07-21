#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <chrono> 

using namespace std;


string correct_parenth(string input) {
	vector<int> v;

	for(size_t i = 0 ; i < input.size(); ++i) {
		if (input[i] == '(') {
			v.push_back(i);
		} else if (input[i] == ')') {
			if (v.size() == 0)
				input[i] = '*';
			else 
				v.pop_back();
		}
	}

	for(auto num : v){
		input[num] = '*';
	}

	string ret = "";
	for(size_t i = 0 ; i < input.size(); ++i) {
		if (input[i] != '*') {
			ret += input[i];
		}

	}

	return ret;
}

string correct_parenth_reuse_mem(string input) {
	vector<int> v;

	for(size_t i = 0 ; i < input.size(); ++i) {
		if (input[i] == '(') {
			v.push_back(i);
		} else if (input[i] == ')') {
			if (v.size() == 0)
				input[i] = '*';
			else 
				v.pop_back();
		}
	}

	for(auto num : v){
		input[num] = '*';
	}

	// reuses input string for less memory
	int offset = 0;
	for(size_t i = 0 ; i < input.size() && (i + offset) < input.size(); ++i) {
		while (input[i + offset] == '*') {
			offset++;
		}
		input[i] = input[i + offset];
	}

	for(int i = 0 ; i < offset; ++i) {
		input.pop_back();
	}
           
	return input;
}


int main() {

	vector<string> v;
	v.push_back(")))))3((((((");  		// 3
	v.push_back("((5)(4)((((");   		// (5)(4)
	v.push_back("(((3)))");      		// (((3)))
	v.push_back("(3))((5)(((("); 		// (3)(5)
	v.push_back("((5)((4)44(55(66))");  // (5)(4)44(55(66))

	for(auto it: v) {
		cout << correct_parenth_reuse_mem(it) << " " << correct_parenth(it) <<  endl;
		assert(correct_parenth(it) == correct_parenth_reuse_mem(it));
	}

	// randomized load testing
	int iteration = 0;
	int total_tests = 100000;
	int num_chars = 0;
	int max_chars = 1000;
	vector<char> char_set = {'(', ')', '0'};
	string test_string = "";

	// auto tim = chrono::system_clock::now();

	while(iteration < total_tests) {
		num_chars = rand() % max_chars;
		for (int i = 0; i < num_chars; ++i) {
			test_string += char_set[rand() % char_set.size()];		
		}
		// correct_parenth(test_string);
		// correct_parenth_reuse_mem(test_string);
		assert(correct_parenth(test_string) == correct_parenth_reuse_mem(test_string));
		test_string = "";
		iteration++;
	}

	// cout << (chrono::system_clock::now()) << " "  << (tim) << endl;
}