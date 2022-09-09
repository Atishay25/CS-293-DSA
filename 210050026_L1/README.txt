Name        : Atishay Jain
Roll Number : 210050026
CS293 Lab1

# linearQueue.cpp :
1. A Linear Queue is a general queue which follows FIFO (First In First Out). I have 
   implemented the various member functions required in queue.h in the file linearQueue.cpp
   The idea used in implementing the member functions are also commented in the code.
2. The member functions are implemented as follows:
(1) isEmpty()     : queue is empty whenever head is equal to tail.
(2) isFull()      : A Linear queue is full when the tail is N, as the last slot of array (at index N-1) gets occupied.
                    Note that the array may or may not be full always when the queue is full. 
(3) grow()        : Whenever queue is full and also size is N (that is array is also full), grow the array to a larger size.
                    This is done by creating a temporary array and copying elements of A to it, and then setting A = that temporary array.
                    Also, N is incremented to the nextSize here.
(4) size()        : size is (tail - head)
(5) QInsert(T x)  : When queue is Full -
                    (a) is array is also full - grow the array
                    (b) if there is space behind - rearrange the elements from end of array to start of it 
                                                   (This ensures that elements of array are not wasted)
                    Then, insert new element at tail and increment tail.
(6) QDelete(T *x) : copy the element to be deleted at the value to which x points to. Then, delete the element at head and increment head.

# circularQueue.cpp :
1. In circular queue, the front and end are connected to each other in a circular way to optimize the space 
   wastage that happens in linear queue. So, it has some advantages over linear queue :
   (1) Easier insertion and deletion if the vacant positions of array are not occupied fully. As in linear queue,
       insertion is not possible when the tail reaches the end even if some space is left empty at other indices at start of array.
   (2) So, in circular queue there is efficient utilization of memory as it can use those unoccupied spaces properly and efficiently.
   Beacuse of these advantages, the running time taken by circular was lesser than linear, i.e, it was more efficient. 
3. Member functions are implemented as follows :
(1) isEmpty()     : queue is Empty when head == tail
(2) isFull()      : queue is full when every slot of array is occupied, that is size == N
(3) grow()        : when size is full, then grow the array to a larger size by copying elements from previous array.
                    The head and tail have to changed now to head = 0 and tail to be the current size of queue accordingly.
                    Also, For ensuring that no element of array is left unused when growing, that is the array is grown only when size == N,
                    I have implemented in such a way that head and tail keep on increasing and they are not used as index for operations.
                    Instead of this, (head%N) and (tail%N) are being used as index wherever required.
                    This ensures that head == tail becomes the condition only for empty queue, not for full queue.
                    The condition for a full queue now becomes that head - tail == N or size() == N.
                    And, thus the array can hold full N elements at max and will grow only if all the N elements are occupied.
                    So, I am using head and tail as just numbers for keeping track whereas there%N as indices while operating on queue.
                    This is kind off similar to hashing with hash function as key%N and key being head or tail accordingly.
(4) size()        : size in a circular queue is tail - head
(5) QInsert(T x)  : If queue is full, then grow it.
                    And then insert new element at tail. Also increment tail and use index as (tail%N) wherever required to keep the queue circular
(6) QDelete(T *x) : Delete element at front (that is, at head) and increment head and use index as (head%N) wherever required to keep the queue circular

# Makefile :
1. No change was required in this file. This is submitted as it is.

# queue.h :
1. It was instructed to not to modify this file. So, it is submitted as it is.

# test.cpp :
1. It was instructed to not to modify this file. So, it is submitted as it is, as this file would be modified by TAs to check the code accordingly.