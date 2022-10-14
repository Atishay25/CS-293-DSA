#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<queue>
#include<vector>

using namespace std;

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(T x); // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  T getHead();
};

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
bool DynamicQueue<T>::QDelete(){
    if(isEmpty()) return false;
    //*x = A[head];
    A[head] = 0;    // deleting from the head
    head++;
    return true;
}

template <typename T>
T DynamicQueue<T>::getHead(){
  T x = A[head];
  QDelete();
  return x;
}

// Finds the train with a given Journey Code from list of Trains
TrainInfoPerStation* find(int jrnyCode ,listOfObjects<TrainInfoPerStation *> *listOfTrains){
  while(listOfTrains != nullptr){
    if(listOfTrains->object->journeyCode == jrnyCode) return listOfTrains->object;
    listOfTrains = listOfTrains->next;
  }
  return nullptr;
}

// Prints all Direct Journeys from given source station to destination
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  
  //StationAdjacencyList srcStn = adjacency[stnNameToIndex.get(srcStnName)->value];
  //StationAdjacencyList destStn = adjacency[stnNameToIndex.get(destStnName)->value];

  listOfObjects<StationConnectionInfo *> *adj = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;

  vector<TrainInfoPerStation *> directTrains;
  vector<int> trainJourneyCode;

  while(adj != nullptr){
    listOfObjects<TrainInfoPerStation *> *Trains = adj->object->trains;
    while(Trains != nullptr){
      trainJourneyCode.push_back(Trains->object->journeyCode);
      Trains = Trains->next;
    }
    adj = adj->next;
  }

  for(int i = 0; i < trainJourneyCode.size(); i++){
    //queue<int> q;
    DynamicQueue<int> q;
    q.QInsert(stnNameToIndex.get(srcStnName)->value);
    while(!q.isEmpty()){
      int stn = q.getHead();
      //q.pop();
      listOfObjects<StationConnectionInfo *> *stnAdj = adjacency[stn].toStations;
      listOfObjects<StationConnectionInfo *> *search = stnAdj;
      while(stnAdj != nullptr){

        listOfObjects<TrainInfoPerStation *> *totrains = stnAdj->object->trains;
        listOfObjects<StationConnectionInfo *> *Adj = adjacency[stnAdj->object->adjacentStnIndex].fromStations;
        listOfObjects<TrainInfoPerStation *> *fromtrains = Adj->object->trains;
        bool foundinTo = false, foundinFrom = false;
        TrainInfoPerStation *newDirectTrain = nullptr;
        TrainInfoPerStation *sameTrain = nullptr;

        while(Adj != nullptr){
          fromtrains = Adj->object->trains;
          sameTrain = find(trainJourneyCode[i],fromtrains);
          if(sameTrain != nullptr){
            foundinFrom = true;
            break;
          }
          Adj = Adj->next;
        }

        while(search != nullptr){
          totrains = search->object->trains;
          newDirectTrain = find(trainJourneyCode[i],totrains);
          if(newDirectTrain != nullptr){
            foundinTo = true;
            break;
          }
          search = search->next;
        }
        
        if(!foundinTo || !foundinFrom){
          stnAdj = stnAdj->next;
          continue;
        }

        if(stnAdj->object->adjacentStnIndex == stnNameToIndex.get(destStnName)->value){
          directTrains.push_back(newDirectTrain);
          break;
        }

        q.QInsert(stnAdj->object->adjacentStnIndex);
        stnAdj = stnAdj->next;

      }
    }
  }

  listOfObjects<TrainInfoPerStation *> *DirectTrains = nullptr;
  for(int i=0; i<directTrains.size(); i++){
    if(DirectTrains == nullptr){
      DirectTrains = new listOfObjects<TrainInfoPerStation *>(directTrains[i]);
    }
    else{
      listOfObjects<TrainInfoPerStation *> *newDirectTrain = new listOfObjects<TrainInfoPerStation *>(directTrains[i]);
      listOfObjects<TrainInfoPerStation *> *temp = DirectTrains;
      while(temp->next != nullptr){
        temp = temp->next;
      }
      temp->next = newDirectTrain;
    }
  }
  if(DirectTrains != nullptr){
    //while(DirectTrains->prev != nullptr){
    //  DirectTrains = DirectTrains->prev;
    //}
    printStationInfo(DirectTrains);
  }
  else{
    cout << "No direct journeys available\n";
  }
  return;
}
