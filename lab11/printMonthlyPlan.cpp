#ifndef PRINT_MONTHLY_PLAN_CPP
#define PRINT_MONTHLY_PLAN_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
/*
class TrainStnInfo
{
public:
  int journeyCode;        // same as train number
  unsigned short stopSeq; // sequence of this station's stop in
                          // itinerary of train, i.e. 1st stop in journey
                          // or 2nd stop in journey or ...
  bool daysOfWeek[7];     // Days of week when this train travels
                          // to/from this station
  int arrTime;            // Arrival time at station; -1 if train starts from here
  int depTime;            // Departure time from station; -1 if train ends here
  string departureStn;    // Station Name from which this train departs
  string arrivalStn;      // Station Name at which this train arrives
  int depIndex;           // Departure Station Index
  int arrIndex;           // Arrival Station Index

public:
  TrainStnInfo(int jCode, unsigned short stpSq, int aTm, int dTm, string dStn, string arrStn, int depID, int arrID)
  {
    journeyCode = jCode;
    stopSeq = stpSq;
    arrTime = aTm;
    depTime = dTm;
    departureStn = dStn;
    arrivalStn = arrStn;
    depIndex = depID;
    arrIndex = arrID;
    for (int i = 0; i < 7; i++)
    {
      daysOfWeek[i] = false;
    }
  }

  ~TrainStnInfo() { ; }

  void setDayOfWeek(int i)
  {
    if ((0 <= i) && (i < 7))
      daysOfWeek[i] = true;
  }
  void resetDayOfWeek(int i)
  {
    if ((0 <= i) && (i < 7))
      daysOfWeek[i] = false;
  }
};

TrainStnInfo *findTrain(int jrnyCode, listOfObjects<TrainStnInfo *> *listOfTrains)
{
  while (listOfTrains != nullptr)
  {
    if (listOfTrains->object->journeyCode == jrnyCode)
      return listOfTrains->object;
    listOfTrains = listOfTrains->next;
  }
  return nullptr;
}

TrainInfoPerStation *findTrain2(int jrnyCode, listOfObjects<TrainInfoPerStation *> *listOfTrains)
{
  while (listOfTrains != nullptr)
  {
    if (listOfTrains->object->journeyCode == jrnyCode)
      return listOfTrains->object;
    listOfTrains = listOfTrains->next;
  }
  return nullptr;
}

int findTransitTime(TrainStnInfo *train2, TrainStnInfo *train1, int maxTime, listOfObjects<TrainInfoPerStation *> **tempStnInfo)
{
  int train2Day, train1Day;
  for (int i = 0; i < 7; i++)
  {
    if (train1->daysOfWeek[i])
      train1Day = i;
    if (train2->daysOfWeek[i])
      train2Day = i;
  }
  int dayDiff;
  if (train2Day >= train1Day)
    dayDiff = train2Day - train1Day;
  else
    dayDiff = 7 + train2Day - train1Day;
  listOfObjects<TrainInfoPerStation *> *arrTrain = nullptr;
  for (int i = 0; i < DICT_SIZE; i++)
  {
    if (i == train2->depIndex)
    {
      arrTrain = tempStnInfo[i];
      break;
    }
  }
  TrainInfoPerStation *temp = findTrain2(train1->journeyCode, tempStnInfo[train2->depIndex]);
  int newTrainDep = ((train2->depTime) % 100);
  newTrainDep = newTrainDep * 100 / 60;
  int prevTrainArriv = ((temp->arrTime) % 100) * (100 / 60);
  prevTrainArriv = prevTrainArriv * 100 / 60;
  int firstTwoDep = (train2->depTime) / 100;
  firstTwoDep *= 100;
  int firstTwoArr = (temp->arrTime) / 100;
  firstTwoArr *= 100;
  newTrainDep = firstTwoDep + newTrainDep;
  prevTrainArriv = firstTwoArr + prevTrainArriv;
  int v = newTrainDep - prevTrainArriv;
  int k = ((v * 60) / 100);
  int l = ((k) / 60) * 100 + k % 60;
  int transitTime = l + 2400 * (dayDiff);
  return transitTime;
}*/
void Planner::printMonthlyPlan(string srcStnName, listOfObjects<string> *destStnNameList){
	// while(destStnNameList != nullptr){
	//   printPlanJourneys(srcStnName,destStnNameList->object,512,2400*7);
	//   destStnNameList = destStnNameList->next;
	// }
	StationAdjacencyList srcNode = adjacency[stnNameToIndex.get(srcStnName)->value];
	StationAdjacencyList *srcStn = &srcNode;
	listOfObjects<StationAdjacencyList *> *MST = new listOfObjects<StationAdjacencyList *>(srcStn);
	listOfObjects<StationConnectionInfo *> *srcAdj = MST->object->toStations;
	listOfObjects<int> *edgeCost = nullptr; 
	while (srcAdj != NULL){
		if(edgeCost == nullptr){

			edgeCost = new listOfObjects<int>(DIRECT_JOURNEY_RATE);
		}
		srcAdj = srcAdj->next;
	}
	return;
}

#endif
