#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.


// Function to do comparison amonf the Objects of TrainsInfoPreStation
// Returns true if stn1 < stn2
// Comparing them on following priority order -
// Day of week -> arrival time -> departure time
bool compare(TrainInfoPerStation *stn1,TrainInfoPerStation *stn2){
  for(int i = 0; i < 7; i++){     // First sort on basis of Days of Week
    if(stn1->daysOfWeek[i] == true && stn2->daysOfWeek[i] == false){
      return true;
    }
    else if(stn1->daysOfWeek[i] == false && stn2->daysOfWeek[i] == true){
      return false;
    }
  }

  // Then if days of week are same, check arrival time
  if(stn1->arrTime < stn2->arrTime) return true;
  else if(stn1->arrTime == stn2->arrTime){
    // If arrival time is same, check departure time
    if(stn1->depTime == -1 && stn2->depTime != -1) return false;
    else if(stn1->depTime != -1 && stn2->depTime == -1) return true;
    else if(stn1->depTime < stn2->depTime) return true;
    else return false;
  }
  else return false;
}

// Swap two Nodes of Linked List
void swapStnInfo(TrainInfoPerStation *&stn1, TrainInfoPerStation *&stn2){
  TrainInfoPerStation *temp = stn1;
  stn1 = stn2;
  stn2 = temp;
}

// QuickSort the Linked List
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start = 0;           // starting index of Linked List
  static int end = 0;             // Last index of Linked List
  static listOfObjects<TrainInfoPerStation *> **stnArray;   // Array of size n/K to store some elements
                                                            // inorder to find a random pivot

  // If stnInfoList is NULL, return as there is nothing left to sort
  if(stnInfoList == nullptr){
    return;
  }

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.

  listOfObjects<TrainInfoPerStation *> *firstStnInfo = stnInfoList;   // First Element of Linked list

  // Calculating first Node of linked list
  for(int i = 0; i < start; i++){
    firstStnInfo = firstStnInfo->next;
  }

  // Calculating value of end, which denotes last Element of Linked List
  if(recursionLevel == 0){
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
    while(temp->next != nullptr){
      temp = temp->next;
      end++;
    }
  }

  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    int arrSize = (end-start+1)/K + 1;    // Size of Array to be formed
    if((end-start+1)%K == 0) arrSize = (end-start+1)/K;

    listOfObjects<TrainInfoPerStation *> *tempStnInfo = stnInfoList;      // Temporary station list
    stnArray = new listOfObjects<TrainInfoPerStation *> *(stnInfoList);   // Allocating memory to array formed once

    // Storing Values in Array
    for(int i = 0; i < arrSize; i++){
      stnArray[i] = tempStnInfo;
      for(int j = 0; j < K; j++){
        if(tempStnInfo == nullptr) break;
        tempStnInfo = tempStnInfo->next;
      }
    }

  }

  listOfObjects<TrainInfoPerStation *> *lastStnInfo = stnArray[end/K];    // Last Node of Linked List
  for(int i = 0; i < end%K; i++){
    lastStnInfo = lastStnInfo->next;
  }

  int tempStart = start, tempEnd = end;                 // Temporary copies of start and end
  
  int randomNumber = start + (rand()%(end-start+1));    // Random Number to find random pivot

  // Pivot Node for partitioning the linked list
  listOfObjects<TrainInfoPerStation *> *pivot = stnArray[randomNumber/K];
  for(int j = 0; j < randomNumber%K; j++){
    pivot = pivot->next;
  }
  TrainInfoPerStation *pivot_object = pivot->object;    // Storing object at Pivot Node

  // Partitioning the Linked List
  int i = tempStart, j = tempEnd;
  while(i <= j){
    while(compare(pivot_object,lastStnInfo->object)){
      j--;
      lastStnInfo = lastStnInfo->prev;
    }
    while(compare(firstStnInfo->object,pivot_object)){
      i++;
      firstStnInfo = firstStnInfo->next;
    }
    if(i <= j){
      swapStnInfo(firstStnInfo->object,lastStnInfo->object);
      firstStnInfo = firstStnInfo->next;
      lastStnInfo = lastStnInfo->prev;
      i++;
      j--;
    }
  }

  // Recursive calls to partitioned parts of Linked List
  if(tempStart < j){
    end = j;
    start = tempStart;
    Quicksort(stnInfoList);
  }
  if(i < tempEnd){
    start = i;
    end = tempEnd;
    Quicksort(stnInfoList);
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

// QuickSort with helping arguements of starting and ending values of Linked List to be sorted 
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  static listOfObjects<TrainInfoPerStation *> **stnArray; // Array of size n/K to store some elements 
                                                          // inorder to find pivot

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained

  // Base Case for recursion
  if(start >= end && recursionLevel != -1) return;

  listOfObjects<TrainInfoPerStation *> *firstStnInfo = stnInfoList;   // First Element of Linked List

  for(int i = 0; i < start; i++){     // Calculating first Node of linked list
    firstStnInfo = firstStnInfo->next;
  }

  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    int arrSize = (end-start+1)/K + 1;        // Size of Array to be formed
    if((end-start+1)%K == 0) arrSize = (end-start+1)/K;

    listOfObjects<TrainInfoPerStation *> *tempStnInfo = stnInfoList;    // Temporary Station list
    stnArray = new listOfObjects<TrainInfoPerStation *> *(stnInfoList); // Allocating memory to Array only once

    // Storing values in Array
    for(int i = 0; i < arrSize; i++){
      stnArray[i] = tempStnInfo;
      for(int j = 0; j < K; j++){
        if(tempStnInfo == nullptr) break;
        tempStnInfo = tempStnInfo->next;
      }
    } 

  }

  listOfObjects<TrainInfoPerStation *> *lastStnInfo = stnArray[end/K];    // Last element of Linked List
  for(int i = 0; i < end%K; i++){
    lastStnInfo = lastStnInfo->next;
  }

  int randomNumber = start + (rand()%(end-start+1));    // Random Number to find random pivot

  listOfObjects<TrainInfoPerStation *> *pivot = stnArray[randomNumber/K]; // Pivot Node

  for(int j = 0; j < randomNumber%K; j++){
    if(pivot->next == nullptr) break;
    pivot = pivot->next;
  }
  TrainInfoPerStation *pivot_object = pivot->object;    // Storing object at pivot

  int i = start, j = end;

  // Partitioning of QuickSort
  while(i <= j){
    while(compare(pivot_object,lastStnInfo->object)){
      j--;
      lastStnInfo = lastStnInfo->prev;
    }
    while(compare(firstStnInfo->object,pivot_object)){
      i++;
      firstStnInfo = firstStnInfo->next;
    }
    if(i <= j){
      swapStnInfo(firstStnInfo->object,lastStnInfo->object);
      firstStnInfo = firstStnInfo->next;
      lastStnInfo = lastStnInfo->prev;
      i++;
      j--;
    }
  }

  // Recursive Calls to Partitioned Linked List
  if(start < j) QuicksortSimple(stnInfoList,start,j);
  if(i < end) QuicksortSimple(stnInfoList,i,end);

  recursionLevel--;
  return;
}

#endif
