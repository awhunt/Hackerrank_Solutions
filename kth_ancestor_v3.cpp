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
    vector<int> parents_for_child;
    vector<int> parents_ref;
    int children = 0;
    int num_parents = 0;
    

    Node(){}
    
    Node( const int c): num_parents(c) {}

};


class Tree {
    public:
    
    Tree() {
        tr[0] = new Node(0);
        tr[0]->parents_for_child.emplace_back(0);
    }
    
    void process_leaf(int leaf, int parent) {
        // if there is a new child, make its parents_ref vector
        if (tr[parent]->children == 1 && parent != 0) {
            int num_nodes_to_save = floor( log2(double(tr[leaf]->num_parents)) );
            int ancestor = tr[parent]->parents_for_child[1];
            // reserve space if needed
            if (num_nodes_to_save > 1) {
                tr[parent]->parents_for_child.reserve(num_nodes_to_save - 1);
            }
            // construct the parent's full parents for child vector
            for (int i = 1; i < num_nodes_to_save; i++) {
                ancestor = tr[ancestor]->parents_ref[i];
                tr[parent]->parents_for_child.emplace_back(ancestor);
            }   
        }
        tr[leaf]->parents_ref = tr[parent]->parents_for_child;
    }
    
    // O(log(n))
    void add_leaf(int child, int parent) {
        // existence check
        if (tr.find(child) != tr.end())  { return; }
        if (tr.find(parent) == tr.end()) { return; }
        
        // add child to the "tree"
        tr[child] = new Node(tr[parent]->num_parents + 1);
        tr[child]->parents_for_child.emplace_back(child);
        tr[child]->parents_for_child.emplace_back(parent);

        // update parents and process
        tr[parent]->children++;
        process_leaf(child, parent);
    }
    
    // O(1), 
    void remove_leaf(int victim) {
        // check if removal is valid
        if (tr.find(victim) == tr.end()) { return; }
        if (tr[victim]->children)         { return; }

        // decrement the parent's child count, remove victim
        tr[tr[victim]->parents_ref[0]]->children--;
        delete tr[victim];
        tr.erase(victim);
    }
    
    // O(log(n))
    int find_kth_parent(int child, int k) {
        if (tr.find(child) == tr.end()) { return 0; }
        if(tr[child]->num_parents < k)   { return 0; }
        
        int kth_parent = child;
        int current_k = 0;
        
        // loop to find the kth parent
        while(k != 0) {
            current_k = floor( log2(double(k)) );
            // "jump" up the tree
            auto par_node = tr.find(kth_parent);
            if (par_node != tr.end()) {
                kth_parent = par_node->second->parents_ref[current_k];
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
        unordered_map<int, Node*> tr;
        
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
    cout << out.str();
    
    return 0;
}
