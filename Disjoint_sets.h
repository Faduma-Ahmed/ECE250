
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	// initialize the sets
    
    for (int i = 0; i < n; i++) {
        nodes[i] = new ll_entry;
        nodes[i] -> content = i;
        nodes[i] -> next = nullptr;
        
        sets[i] = new set_info;
        sets[i] -> size = 1;
        
        nodes[i] -> ptr_to_info = sets[i];
        
        sets[i] -> head = nodes[i];
        sets[i] -> tail = nodes[i];
    }
    
    set_counter = n;
    initial_num_sets = n;
}

Disjoint_set::~Disjoint_set() {
    for (int i = 0; i < initial_num_sets; i++) {
        delete nodes[i];
        delete sets[i];
    }
    
    delete [] nodes;
    delete [] sets;
	// deallocate memory
}
int Disjoint_set::find_set(int item) const{
	// should it be? return nodes[item]->ptr_to_info->head->content 
	return nodes[item] -> ptr_to_info -> head -> content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;
    
    if (si1 -> head -> content == si2 -> head -> content) {             //if they are in the same set
        return;
    }

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;
    
    
    nodes[ni1] -> ptr_to_info -> tail -> next = nodes[ni2] -> ptr_to_info -> head;
    nodes[ni1] -> ptr_to_info -> tail = nodes[ni2] -> ptr_to_info -> tail;
    nodes[ni1] -> ptr_to_info -> size = nodes[ni1] -> ptr_to_info -> size + nodes[ni2] -> ptr_to_info -> size;
    
    ll_entry * currNode = nodes[ni2] -> ptr_to_info -> head;
    
	/* iterate through the shorter list and modify the pointers
	while (has not reached the end of set) {
		....
	}*/
    while (currNode != nullptr) {
        currNode -> ptr_to_info = nodes[ni1] -> ptr_to_info;
        currNode = currNode -> next;
    }

	// do we need to modify anything else?
    set_counter--;


	// delete the set_info entry that no longer exists
    //delete nodes[ni2] -> ptr_to_info;
    //delete sets[ni2];
}


#endif
