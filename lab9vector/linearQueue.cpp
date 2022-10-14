#include <iostream>
#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head == tail);   // queue is empty when head == tail
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (tail == N);     
}

template <typename T>
void DynamicQueue<T>::grow(){
    if(isFull()){
        T *A1;     // A1 is the new array with larger size 
        A1 = new T[nextSize()];
        for(int i = head; i < tail; i++){   // copying elements from A to A1
            A1[i] = A[i];
        }
        N = nextSize();    
        A = A1;      
    }
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        if(size() == N) grow();    // if queue size is full then only growing the array
        else{                      // else rearranging elements from last to top of same array
            for(int i = 0; i < size(); i++){
                A[i] = A[i+head];
            }
            tail = tail - head;
            head = 0;
        }
    }
    A[tail] = x;        // Inserting new element at tail
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head];
    A[head] = 0;    // deleting from the head
    head++;
    return true;
}

