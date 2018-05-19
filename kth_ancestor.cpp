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
    int children = 0;
    vector<int> parents;
    
    Node(){}
    
    Node( const int c): num_parents(c) {}

};


class Tree {
    public:
    
    Tree() {
        tr[0] = Node(0);
    }
    
    // O(log (n))
    void process_leaf(int leaf, int parent) {
        int num_nodes_to_save = floor( log(double(tr[leaf].num_parents)) 
                                      / log(2.0) );
        // add first parent
        tr[leaf].parents.emplace_back(parent);

        // add all other needed parents 2nd, 4th, 8th etc
        for (int i = 0; i < num_nodes_to_save; i++) {
            parent = tr[parent].parents[i];
            tr[leaf].parents.emplace_back(parent);
        }
    }
    
    // O(log(n))
    void add_leaf(int child, int parent) {
        // existence check
        if (tr.find(child) != tr.end())  { return; }
        if (tr.find(parent) == tr.end()) { return; }
        
        // add child to the "tree"
        tr[child] = Node(tr[parent].num_parents + 1);
        tr[parent].children++;

        // make parent vector
        process_leaf(child, parent);
    }
    
    // O(1)
    void remove_leaf(int victim) {
        // check if removal is valid
        if (tr.find(victim) == tr.end()) { return; }
        if (tr[victim].children)        { return; }

        // remove from hash table
        tr[tr[victim].parents[0]].children--;
        tr.erase(victim);
    }
    
    // O(log(n))
    int find_kth_parent(int child, int k) {
        // existence checks
        if (tr.find(child) == tr.end()) { return 0; }
        if(tr[child].num_parents < k) { return 0; }
        
        int kth_parent = child;
        int current_k = 0;
        
        while(k != 0) {
            current_k = floor( log(double(k)) / log(2.0) );
            // go up the tree k levels
            if (tr.find(kth_parent) != tr.end()) {
                kth_parent = tr[kth_parent].parents[current_k];
                current_k = 1 << current_k;
            } else {
                return 0;
            }
            
            k -= current_k;

            if (k < 0) { exit(1); }
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

        
        // handle the requests associated with this tree
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
    cout << out.str();
    
    return 0;
}