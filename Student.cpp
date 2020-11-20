#include <iostream>
#include "Student.h"

using namespace std;

Student::Student()
{
  timeNeeded = 0; 
  timeSpent = 0;
  timeWaited = 0;
  timeArrived = 0;
}

Student::Student(int needs, int arrived)
{
  timeNeeded = needs;
  timeArrived = arrived;
  timeSpent = 0;
  timeWaited = 0;
}

Student::~Student()//destructor
{

}


//int Student::getVisitTime()
//{
//	return visitTime;
//}

//int Student::getArrive()
//{
//	return ArrivalTime;
//}

//int Student::getWaitTime()
//{
//	return waitTime;
//}

//void Student::setWaitTime(int minuteIn)
//{
//	waitTime = minuteIn - ArrivalTime;
//}

//void Student::toString()
//{
//	cout << "Student arrived at " << ArrivalTime << " and needs " << visitTime << endl;
//}
