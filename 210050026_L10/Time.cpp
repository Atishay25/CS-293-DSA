#include<iostream>
using namespace std;

int main(){
    int a = 1230;
    int b = 850;
    int newTrainDep = ((a)%100);
    newTrainDep = newTrainDep*100/60;
  int prevTrainArriv = ((b)%100)*(100/60);
  prevTrainArriv= prevTrainArriv*100/60;
  int firstTwoDep = (a)/100;
  firstTwoDep *= 100;
  int firstTwoArr = (b)/100;
  firstTwoArr *= 100;
  newTrainDep = firstTwoDep + newTrainDep;
  prevTrainArriv = firstTwoArr + prevTrainArriv;
  int v = newTrainDep - prevTrainArriv;
  int k = ((v*60)/100);
  int l = ((k)/60)*100 + k%60;
  cout << l << endl;
}