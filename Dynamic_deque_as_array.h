#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_deque_as_array
{

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();


		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;
    
    int* array;             //declare the member variables in the class
    int* newArray;          //use this when doubling the array size
    int arraySize;          //capacity of the array
    int counter;            //counts the size of the array
    int headIndex;          //index of the head of the array
    int tailIndex;          //index of the tail of the array
    

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
    
    void print();
};


Dynamic_deque_as_array::Dynamic_deque_as_array( int n) {
    
    if (n < 1){                     //if capacity is less than 1, use array size of 1
        array  = new int [1];
        arraySize = 1;
        
    }else{
        array = new int [n];        //constructs array of size n
        arraySize = n;
        
    }
    
    headIndex = 0;                  //set head index to 0 when array is empty
    tailIndex = 0;                  //set tail index to 0 when array is empty
    counter = 0;                    //size is 0 when array is empty
    
}




Dynamic_deque_as_array::~Dynamic_deque_as_array() {
    delete[] array;                 //deletes the memory allocated for the array, deconstructs the array
}





int Dynamic_deque_as_array::size() const {
	return counter;                 // returns the size of the array
}


int Dynamic_deque_as_array::capacity() const {
	return arraySize;               //returns the capacity of the array
}


bool Dynamic_deque_as_array::empty() const {
    
    return (counter==0)? true:false;        //if counter is 0, array is empty, else, array is not empty
}


int Dynamic_deque_as_array::head() const {
    if (empty())
        throw underflow();                  //if array is empty, no head, throw underflow
    else
        return array[headIndex];            //use head index to return head
}


int Dynamic_deque_as_array::tail() const {
    if (empty())
        throw underflow();                  //if array is empty, no tail, throw underflow
    else
        return array[tailIndex];            //use tail index to return tail

}



void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
    
    if (counter == 0){
        
        array[headIndex] = obj;                                 //if array is empty, add the element
        
    }
    else if (counter < arraySize){                              //if array is not full, add element
        
        if ((headIndex) - 1 < 0){                               //if head index is zero, go to back of the array and add
            
            headIndex = arraySize - 1;
            array[headIndex] = obj;
        }else{
            
            array[(headIndex - 1) % arraySize] = obj;           //if head index is not zero, add to the space to the left of current head
            headIndex --;                                       //move the head index left, to point to the new head
        
        }
    }
    
    else if (counter == arraySize){                             //if array is full
        
        arraySize = 2 * arraySize;                              //double the array size
        
        newArray = new int [arraySize];                         //make a new array
        
        int count = 0;
        
        if (counter == 1){                                      //if there was only one element in the array
            
            newArray[0] = array[0];                             //copy it to index 0 of the new array
            
            headIndex = arraySize - 1;                          //the old head is the new tail, and add new element at the end of array
            tailIndex = 0;
            newArray[headIndex] = obj;
        
        }

        if(headIndex > tailIndex){
            
            while (count != (arraySize/2)) {                                        //when head is to the right of the tail
                                                                                    //copy head to index 0 of new array
                newArray[count] = array[(headIndex+count) % (arraySize/2)];         //copy the other elements in order and make tail the right most element of the array
                                                                                    //for example, if the previous array is 1 4 3 2, 1 is tail and 4 is head
                                                                                    //copying to the new array will be 4 3 2 1, 1 is still tail and 4 is still head
                count++;
            }
            
            headIndex = arraySize - 1;
            tailIndex = arraySize/2 - 1;                                            //point head and tail indexes to the correct locations
            newArray[headIndex] = obj;                                              //add the new element to the head

        }
        else if (tailIndex > headIndex){
            
            while (count != (arraySize/2)) {                                        //when tail is to the right of head
                newArray[count] = array[count];                                     //copy the old array to the new array directly
                                                                                    //for example, old array is 1 2 3 4, 1 is head and 4 is tail
                count++;                                                            //new array is still 1 2 3 4, 1 is still head, 4 is still tail
            }
            
            headIndex = (arraySize - 1);                                            //point head and tail to the correct locations
            tailIndex = (arraySize/2) - 1;
            
            newArray[headIndex] = obj;                                              //add new element to head
        
        }
        delete[] array;                                                             //delete memeory of old array

        
        array = newArray;                                                           //point the new array to old array
        
    }
    
    
    counter++;                                                                      //increase size of array
    
    //print();
    return;
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {

    if (counter == 0){
        
        array[tailIndex] = obj;                                                 //if array is empty, add the element
        
    }
    else if (counter < arraySize){
        
        array[(tailIndex + 1) % arraySize] = obj;                               //if array is not full, add element
        tailIndex++;                                                            //point to the new tail
        
    }
    else if(counter == arraySize){                                              //if array is full, make new array double the capacity
        
        int count = 0;
        
        arraySize = 2 * arraySize;
        
        newArray = new int [arraySize];
        
        if (counter == 1){                                                      //if there was only one element in the old array
            
            newArray[0] = array[0];                                             //copy it to index 0 of new array, make it head
            
            tailIndex = 1;                                                      //make the tail index to the right of head
            headIndex = 0;
            newArray[tailIndex] = obj;                                          //add element to tail
            
        }

        
        if(headIndex > tailIndex){                                                  //when head is to the right of tail
                                                                                    //copy head to index 0 of new array, other elements from left to right starting from head
            while (count != (arraySize/2)) {                                        //end at tail, tail is at the right most index
                                                                                    //for example, old array is 1 4 3 2, 4 is head and 1 is tail
                newArray[count] = array[(headIndex+count) % (arraySize/2)];         //new array is 4 3 2 1, 4 is still head and 1 is still tail
                
                count++;
            }
            
            headIndex = 0;                                                          //set head and tail pointers to correct place
            tailIndex = arraySize/2;
            newArray[tailIndex] = obj;                                              //add element at tail
            
        }
        else if (tailIndex > headIndex){                                            //when tail is to the right of head
                                                                                    //copy old array directly
            while (count != (arraySize/2)) {                                        //for example, old array is 1 2 3 4, 1 is head, 4 is tail
                newArray[count] = array[count];                                     //new array is still 1 2 3 4, 1 is head, 4 is tail
                
                count++;
            }
            
            headIndex = 0;                                                          //set head and tail pointers to correct locations
            tailIndex = (arraySize / 2);
            
            newArray[tailIndex] = obj;                                              //add element at tail
            
        }

        delete[] array;                                                             //deallocate memory for old array

        array = newArray;                                                           //point new array to old array
        
    }
    
    counter++;                                                                      //increase size counter
    
    //print();
    
	return;
}


int Dynamic_deque_as_array::dequeue_head() {
	
    int removedHead = head();                                                       //save current head into a variable
    
    if (empty())
        throw underflow();                                                          //if array is empty, no head, throw exception
    
    if (counter == 1){
        
        headIndex = 0;                                                              //if only one element in array, remove head
        tailIndex = 0;                                                              //point head and tail to index 0, no array
    
    }else{
        
        headIndex = (headIndex + 1) % arraySize;                                    //move head index to the new head
    }
    
    
    counter--;                                                                      //decrease size counter
    
    //print();
    
    return removedHead;                                                             //return head
}

int Dynamic_deque_as_array::dequeue_tail() {
    
    int removedTail = tail();                                                       //save current tail into a variable
    
    if (empty())
        throw underflow();                                                          //if array is empty, no tail, throw exception
    
    if (counter == 1){                                                              //if only 1 element in array, remove tail
        
        headIndex = 0;                                                              //point head and tail index to 0, no array
        tailIndex = 0;
        
    }else{
        
        if (tailIndex - 1 < 0) {                                                    //if tail is at index 0 of array
            tailIndex = arraySize - 1;                                              //point tail to end of array
            counter--;                                                              //decrease size counter
            return removedTail;                                                     //return the previous saved tail
            
        }
        else{
            
            tailIndex = (tailIndex - 1) % arraySize;                                //move tail pointer to the left
        }
    }
    
    //print();

    counter--;                                                                      //decrease size counter
    
    return removedTail;
}


void Dynamic_deque_as_array::clear() {
	
    headIndex = 0;                                                  //clear the array, let head = tail = array index 0
    tailIndex = 0;
    counter = 0;                                                    //change array size to 0
    return;
}

/*
void Dynamic_deque_as_array::print(){
    for (int i = 0; i < arraySize; i++) {                           //print elements of array, used for testing
        cout << array[i] << endl;
    }
    
}
*/
#endif
