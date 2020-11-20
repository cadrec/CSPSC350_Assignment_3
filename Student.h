#include <iostream>
using namespace std;

class Student
{
  public:
    Student();
    Student(int needs, int arrived);
		~Student();

    int timeNeeded;
    int timeSpent;
    int timeWaited;
    int timeArrived;

//		int getVisitTime();
//		int getArrive();
//		int getWaitTime();
//		int getTimeArrived();
};
