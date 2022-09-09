Roll Number : 210050026
Name        : Atishay Jain
Lab2        : Task 2

<!--The only files that I have modified and are to be evaluated are listed below--> 
<!--Rest are just test cases and the same files given as part of assignment-->
<!--The details of functions and variables used are explanied in comments as well in the code-->
 
# dictionary.h 
1. I have reused dictionary.h of task 1 and edited it for task 2. And So, I have not used planner.h 
   Basically dictionary.h is doing the task of planner.h , I guess this naming doesn't matter much.
2. I have changed a lot of implementation of this dictionary from task 1.
3. I have used TRAINS_SIZE as a constant which is the maximum number of trains starting from a 
   station.
4. I defined a new struct Train which stores start time, end time and destination of a train.
5. In struct Entry, the string station is being used as key with the value to which it is mapping
   being a array of struct Train.
   So, it is like a full information of all the trains that are starting from a station, with key as station
   name and values being all that information about all trains.
6. I have made a function for inserting a new train into these array of trains of a station.
   It stores the new array while keeping the list of trains sorted on the basis of start time of trains, as 
   this will help for searching for a train with least starting time.
7. The class Planner is basically the Dictionary with some of its functions same as task 1 while some
   other made by me for task 2. The tasks performed by those functions are commented in the file.


# planner.cpp
1. This file has all the fucntions implemented of dictionary.h
2. I am using linear Probing, Hashing using polynomial accumulation and compression using
   Fibonacci scheme for station keys.
3. Also, according to y implementation, if the station key is exact same and one train is inserted at that station,
   then if another train is being added it needs to go to next array location of Trains at the same array location of station.
   So, if the station is exactly same, then I am not doing linear probing for it.
   Otherwise, if two different station keys give same hash Value then I am gonna do linear probling on them.
4. The functionalities of all the functions are commented in this file as well as in dictionary.h
5. Note that the syntax of ADD function that I implemented is ADD(entry e), so do not pass each station details one by one
   as arguement to it. My ADD function will take a whole entry as its arguement.
6. I have displayed suitable error or display messages according to input asked.
7. Also, since We wanted to find journey with minimum start Time only in QUERY_JOURNEY, so it does not
   matter when will it leave the intermediate station. So different outputs for leave time and intermediate station are possible,
   and I was getting one such different output in a sample test case. So, please take care of this point. I hope that it does not matter
   according to requirements of the problem.


# plannerTest.cpp
1. It is the file which you can run to test my submission. 
2. It has the functions that I have implementated according to the syntax that I have used.
3. Running instructions -
   g++ plannerTest.cpp
   ./a.out < "input file" > "output file"       (for checking through input output files)
   			OR
   g++ plannerTest.cpp
   ./a.out                                      
   "Now type the queries manually one by one"   (for checking each query manually one by one)




