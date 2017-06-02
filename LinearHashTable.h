#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

/*****************************************
 * UW User ID:  m258zhan
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

using namespace std;

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
    int index;
    int collisions = 0;
		int count;                      //number of elements in hash table
		int power;
    int initialCapacity;
		int array_size;                 //capacity of hash table
        	int mod;
		T *array;                       //hash table
    T *tempArray;
		state *occupied;                //state of bins in hash table
        state *tempOccupied;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
array_size( 1 << m ){
    
	// enter your implemetation here
    initialCapacity = array_size;
    
    array = new T [array_size];                     //create new hash table
    occupied = new state[array_size];
    
    for (int i = 0; i < array_size; i++) {          //set every state in hash table to EMPTY
        occupied[i] = EMPTY;
    }
    
    count = 0;                                      //initial number of elements is 0
    
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
    delete [] array;                                //delete memory allocated for hash table
    delete [] occupied;
}

template<typename T >
int LinearHashTable<T >::size() const {
    // enter your implemetation here                //return number of elements in hash table
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
    // enter your implemetation here                //return number of bins in hash table
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
    // enter your implemetation here
    
    double loadFactor = (double)count / array_size;         //load factor = number of elements / slots of hash table
    
	return loadFactor;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
    // enter your implemetation here 
	return (count==0)? true:false;                  //if count = 0, array is empty, return true
                                                    //else, return false
}


template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
	// enter your implemetation here
    //calculate index of obj
    //loop through array, starting at array[index], increase

    int start = (int)obj % array_size;              //calculate hash value for obj
    
    //cout<<start<<endl;
    if (array[start] == obj && occupied[start] != DELETED) {                      //if array element at that bin is obj, return true
        return true;
    }
    else{
        for (int i = start; i < (array_size + start); i++) {          //check collision by looping through array starting at calculated hash value
            i = i % array_size;
            //cout<<i<<endl;
            
            if(occupied[i] == EMPTY){               //if we reached an empty bin, obj does not exist
                return false;
            }
            
            if (array[i] == obj && occupied[i] != DELETED){                   //check if array at index equals obj, if equal return true, if not equal, go to next index
                return true;
            }
            
        }
    }
    return false;
}


template<typename T >
T LinearHashTable<T >::bin( int n ) const {
    // enter your implemetation here
	return array[n];
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	 // enter your implemetation here
    
    mod = array_size;
    
    index = (int)obj % mod;
    
    if (load_factor() <= 0.75){
        if (occupied[index] == EMPTY || occupied[index] == DELETED){
            array[index] = obj;
            occupied[index] = OCCUPIED;
        }
        else if (occupied[index] == OCCUPIED){
            
            int h1k = index;
            
            while (occupied[index] == OCCUPIED) {
                collisions++;
                index = (h1k + collisions) % mod;
            }
            
            array[index] = obj;
            occupied[index] = OCCUPIED;
        }
    }
    
    if (load_factor() > 0.75){
        array_size = 2 * array_size;
        
        tempArray = new T [array_size];                     //create new temperary hash table
        tempOccupied = new state[array_size];
        
        for (int i = 0; i < array_size; i++) {          //set every state in hash table to EMPTY
            tempOccupied[i] = EMPTY;
        }
        
        for (int j = 0; j < array_size / 2 ; j++) {
            if (occupied[j] == OCCUPIED){
            
                index = (int) array[j] % array_size;
            
            
                if (tempOccupied[index] == EMPTY || tempOccupied[index] == DELETED){
                    tempArray[index] = array[j];
                    tempOccupied[index] = OCCUPIED;
                }
                else if (tempOccupied[index] == OCCUPIED){
                
                    int h1k = index;
                
                    while (tempOccupied[index] == OCCUPIED) {
                        collisions++;
                        index = (h1k + collisions) % array_size;
                    }
                
                    tempArray[index] = array[j];
                    tempOccupied[index] = OCCUPIED;
                }
            }
            
        }
        
        
        index = (int)obj % array_size;
        
        if (tempOccupied[index] == EMPTY || tempOccupied[index] == DELETED){
            tempArray[index] = obj;
            tempOccupied[index] = OCCUPIED;
        }
        else if (tempOccupied[index] == OCCUPIED){
            
            int h1k = index;
            
            while (tempOccupied[index] == OCCUPIED) {
                collisions++;
                index = (h1k + collisions) % mod;
            }
            
            tempArray[index] = obj;
            tempOccupied[index] = OCCUPIED;
        }
        delete [] array;
        delete [] occupied;
        array = tempArray;
        occupied = tempOccupied;
    }

    collisions = 0;
    count++;
    //print();
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	// enter your implemetation here
    
    if (member(obj) == false){
        return false;
    }
    
    if (member(obj) == true) {
        if (load_factor() > 0.25) {
            index = (int) obj % array_size;
            
            if (array[index] == obj) {
                occupied[index] = DELETED;

            }else{
                
                int h1k = index;
                while (array[index] != obj) {
                    collisions++;
                    index = (h1k + collisions) % array_size;
                    
                }
                occupied[index] = DELETED;
                
            
            }
            
        }
        
        if (load_factor() <= 0.25 && array_size != initialCapacity) {
            index = (int) obj % array_size;
            
            if (array[index] == obj) {
                occupied[index] = DELETED;
                
            }else{
                
                int h1k = index;
                while (array[index] != obj) {
                    collisions++;
                    index = (h1k + collisions) % array_size;
                    
                }
                occupied[index] = DELETED;

            }
            
            array_size = array_size / 2;                    //resize hash table
            
            //cout<<array_size<<endl;
            
            tempArray = new T [array_size];
            tempOccupied = new state[array_size];
            
            for (int i = 0; i < array_size; i++) {
                tempOccupied[i] = EMPTY;
            }
            
            for (int j = 0; j < (array_size*2); j++) {
                if (occupied[j] == OCCUPIED){
                    
                    index = (int) array[j] % array_size;
                    
                    
                    if (tempOccupied[index] == EMPTY || tempOccupied[index] == DELETED){
                        tempArray[index] = array[j];
                        tempOccupied[index] = OCCUPIED;
                    }
                    else if (tempOccupied[index] == OCCUPIED){
                        
                        int h1k = index;
                        
                        while (tempOccupied[index] == OCCUPIED) {
                            collisions++;
                            index = (h1k + collisions) % array_size;
                        }
                        
                        tempArray[index] = array[j];
                        tempOccupied[index] = OCCUPIED;
                    }
                }
                
            }
            
            delete [] array;
            delete [] occupied;
            array = tempArray;
            occupied = tempOccupied;
            
        }
        
        count--;
        collisions = 0;
        //print();
        return true;
    }
    
    count--;
    collisions = 0;
    //print();
    return false;
}

template<typename T >
void LinearHashTable<T >::clear() {
	// enter your implemetation here
    
    for (int i = 0; i < array_size; i++) {          //set every state in hash table to EMPTY
        occupied[i] = EMPTY;
    }
    
    count = 0;
}

template<typename T >
void LinearHashTable<T >::print() const{
	// enter your implemetation here
    for (int i = 0; i < array_size; i++) {                           //print elements of array, used for testing
        cout << array[i] << endl;
    }
}

#endif
