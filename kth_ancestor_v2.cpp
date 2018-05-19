#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;

// Code by Alex Hunt (5/9/2018 - 5/11/2018)

struct Node {
    int num_parents = 0;
    int position = 0;
    vector<int> children;
    vector<int> parents;
    
    Node(){}
    
    Node( const int c): num_parents(c) {}

};


class Tree {
    public:
    
    Tree() {
        tr[0] = Node(0);
    }
    
    void process_leaf(int leaf, int parent) {
        
        // if there is a sibling, copy the parents vector
        if (tr[parent].children.size() > 1) {
            int sibling = tr[parent].children[0];
            tr[leaf].parents.reserve(tr[sibling].parents.size());
            tr[leaf].parents.assign(tr[sibling].parents.begin(), 
                                    tr[sibling].parents.end());
        } 
        // if not construct a new parents vector
        else {
            int num_nodes_to_save = floor( log2(double(tr[leaf].num_parents)) );
            tr[leaf].parents.reserve(num_nodes_to_save + 1);
            tr[leaf].parents.emplace_back(parent);
            for (int i = 0; i < num_nodes_to_save; i++) {
                parent = tr[parent].parents[i];
                tr[leaf].parents.emplace_back(parent);
            }   
        }
    }
    
    // O(log(n))
    void add_leaf(int child, int parent) {
        // existence check
        if (tr.find(child) != tr.end())  { return; }
        if (tr.find(parent) == tr.end()) { return; }
        
        // add child to the "tree"
        tr[child] = Node(tr[parent].num_parents + 1);
        tr[child].position = tr[parent].children.size();
        tr[parent].children.emplace_back(child);
        process_leaf(child, parent);
    }
    
    // O(1), 
    void remove_leaf(int victim) {
        // check if removal is valid
        if (tr.find(victim) == tr.end()) { return; }
        if (tr[victim].children.size())  { return; }

        // remove from hash table
        int first_parent = tr[victim].parents[0];

        // swap to back if needed
        if (tr[first_parent].children.size() > 1) {
            int par_index = tr[victim].position;
            iter_swap(tr[first_parent].children.begin() + par_index, 
                      (tr[first_parent].children.begin() 
                       + (tr[first_parent].children.size() - 1) ));
            int affected_child = tr[first_parent].children[par_index];
            tr[affected_child].position = par_index;
        }

        // delete child from parent, 
        tr[first_parent].children.pop_back();
        tr.erase(victim);
    }
    
    // O(log(n))
    int find_kth_parent(int child, int k) {
        // existence checks
        if (tr.find(child) == tr.end()) { return 0; }
        if(tr[child].num_parents < k) { return 0; }
        
        int kth_parent = child;
        int current_k = 0;
        
        // loop to find the kth parent
        while(k != 0) {
            current_k = floor( log2(double(k)) );
            // "jump" up the tree
            auto par_node = tr.find(kth_parent);
            if (par_node != tr.end()) {
                kth_parent = par_node->second.parents[current_k];
                current_k = 1 << current_k;
            } else {
                return 0;
            }
            
            k -= current_k;
        }
        
        return kth_parent;
        
    }
    
    void clear() {
        tr.clear();
    }
    
    private:
        unordered_map<int, Node> tr;
        
};


int main() {
    // read in T
    int num_test_cases = 0;
    cin >> num_test_cases;
    stringstream out;
    
    // service tests
    for (int i = 0; i < num_test_cases; ++i) {

        // read in P
        int num_nodes = 0;
        cin >> num_nodes;
        
        // declare the tree and temp variables
        Tree tre;
        int child = 0;
        int parent = 0;

        // read in all nodes
        for(int i = 0; i < num_nodes; ++i){
            cin >> child >> parent;
            tre.add_leaf(child, parent);
        }
        
        int num_requests = 0;
        int type = 0;

        cin >> num_requests;

        for(int i = 0; i < num_requests; ++i) {
            cin >> type;
            switch (type){
                // add leaf node
                case 0:
                    cin >> parent >> child;
                    // cout << "adding child " << child << " to parent " << parent << endl;
                    tre.add_leaf(child, parent);
                    break;
                // remove leaf node
                case 1:
                    cin >> child;
                    // cout << "removing " << child << endl;
                    tre.remove_leaf(child);
                    break;
                // find the kth parent
                case 2: 
                    cin >> child >> parent;
                    // cout << "finding " << parent << "th parent of " << child << endl;
                    out << tre.find_kth_parent(child, parent) << endl;
                    break;
                default:
                    exit(1);
                    break;
            }
        }
    }
    // output the stringstream
    cout << out.str();
    
    return 0;
}
