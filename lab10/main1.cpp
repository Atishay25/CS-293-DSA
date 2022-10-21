#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_CPP
#include "dictionary.cpp"
#endif

#ifndef TRIE_CPP
#include "Trie.cpp"
#endif

#ifndef KMP_CPP
#include "kmp.cpp"
#endif

#ifndef PLANNER_CPP
#include "planner.cpp"
#endif

#ifndef QUICKSORT_CPP
#include "quicksort.cpp"
#endif

#ifndef HEAP_CPP
#include "Heap.cpp"
#endif

#ifndef PRINT_JOURNEY_CPP
#include "printJourney.cpp"
#endif

using namespace std;

int main(int argc, char **argv) {

  Planner *myPlanner = new Planner("log.txt");
  if (myPlanner == nullptr) {
    cerr << "Memory allocation failure." << endl;
    return -1;
  }
  
  myPlanner->displayWelcomeMessage();

  do {
    bool continueMenu = myPlanner->displayMenuAndAct();

    if (!continueMenu) {
      delete myPlanner;
      return 0;
    }
    else {
      continue;
    }
  } while (true);
}

