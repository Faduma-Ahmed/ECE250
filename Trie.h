/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  m258zhan @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Trie {
	private:
        // Member Variables
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators
    
		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
    clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
    if (trie_size == 0) {
        return true;
    }
    
	return false;
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
    
    if (empty()) {
        return false;
    }
    
    for (int i = 0; i < str.length(); i++) {                                //check if all characters in string are alphabets
        if(isalpha(str[i]) == 0){
            throw illegal_argument();
        }
    }
    
    if (root_node->member(str, 0)){
        return true;
    }
    
	return false;
}


bool Trie::insert( std::string const &str ) {
    
    for (int i = 0; i < str.length(); i++) {                                //check if all characters in string are alphabets
        if(isalpha(str[i]) == 0){
            throw illegal_argument();
        }
    }
    
    if(member(str)){                                                        //return false if string is already in the tree
        return false;
    }
    
    if (root_node == nullptr) {
        root_node = new Trie_node;
    }
    
    root_node->insert(str, 0);
    trie_size++;
	return true;
}

bool Trie::erase( std::string const &str ) {
    for (int i = 0; i < str.length(); i++) {                                //check if all characters in string are alphabets
        if(isalpha(str[i]) == 0){
            throw illegal_argument();
        }
    }
    
    if(member(str)==false || empty()==true){
        return false;
    }
    else if (trie_size == 1){
        root_node->clear();
        delete root_node;
        trie_size = 0;
        root_node = nullptr;        //only line added to fix errors.
    }
    else{
        root_node->erase(str, 0, root_node);
        trie_size--;
    }
    
    return true;
}

void Trie::clear() {
    if (trie_size!=0) {
        
        root_node->clear();
    
        delete root_node;
        root_node = nullptr;
        trie_size = 0;
    }
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
