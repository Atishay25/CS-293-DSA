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
    //A[head];    // deleting from the head
    head++;
    return true;
}

template <typename T>
T DynamicQueue<T>::getHead(){
  T x = A[head];
  QDelete();
  return x;
}

TrainInfoPerStation* find(int jrnyCode ,listOfObjects<TrainInfoPerStation *> *trains){
  listOfObjects<TrainInfoPerStation *> *listOfTrains = trains;
  while(listOfTrains != nullptr){
    if(listOfTrains->object->journeyCode == jrnyCode) return listOfTrains->object;
  }
  return nullptr;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
  StationAdjacencyList srcStn = adjacency[stnNameToIndex.get(srcStnName)->value];
  StationAdjacencyList destStn = adjacency[stnNameToIndex.get(destStnName)->value];
  listOfObjects<StationConnectionInfo *> *adj = srcStn.toStations;
  //DynamicQueue<StationAdjacencyList> q;
  TrainInfoPerStation * t = new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation *> *directTrains = new listOfObjects<TrainInfoPerStation *>(t);
  listOfObjects<TrainInfoPerStation *> *answerTrains = directTrains;
  vector<int> trainJourneyCode;
  while(adj != nullptr){
    //cout << "station index " << adj->object->adjacentStnIndex << endl;
    listOfObjects<TrainInfoPerStation *> *Trains = adj->object->trains;
    while(Trains != nullptr){
      //cout << Trains->object->journeyCode << "TRAIN JC \n";
      trainJourneyCode.push_back(Trains->object->journeyCode);
      Trains = Trains->next;
    }
    adj = adj->next;
  }
  for(int i = 0; i < trainJourneyCode.size(); i++){
    cout << "JC : " << trainJourneyCode[i] << endl;
    queue<int> q;
    //queue<int> jrnyCodes;
    q.push(stnNameToIndex.get(srcStnName)->value);
    while(!q.empty()){
      int stn = q.front();
      q.pop();
      cout << "oops\n";
      listOfObjects<StationConnectionInfo *> *stnAdj = adjacency[stn].toStations;
      while(stnAdj != nullptr){
        cout << "Station " << stnAdj->object->adjacentStnIndex << endl;
        listOfObjects<TrainInfoPerStation *> *trains = stnAdj->object->trains;
        bool found = false;
        TrainInfoPerStation *newDirectTrain = nullptr;
        while(trains != nullptr){
          cout << "yeah\n";
          newDirectTrain = find(trainJourneyCode[i],trains);
          if(newDirectTrain != nullptr){
            found = true;
            break;
          }
                        cout << "hoi\n";
          trains = trains->next;
        }
        if(!found){
          stnAdj = stnAdj->next;
          continue;
        }
        if(stnAdj->object->adjacentStnIndex == stnNameToIndex.get(destStnName)->value){
          directTrains->object = newDirectTrain;
          directTrains = directTrains->next;
          break;
        }
        q.push(stnAdj->object->adjacentStnIndex);
        stnAdj = stnAdj->next;
      }
      //q.QDelete();
    }
  }
  while(answerTrains != nullptr){
    cout << answerTrains->object->journeyCode << endl;
    answerTrains = answerTrains->next;
  }
  printStationInfo(answerTrains);
  return;
}
