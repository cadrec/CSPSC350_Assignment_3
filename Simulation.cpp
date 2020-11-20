#include <iostream>
#include <fstream>
#include "Simulation.h"
#include "GenQueue.h"
#include <algorithm>

using namespace std;

Simulation::Simulation()//constructor
{

}

Simulation::Simulation(string file)//constructor
{
  studentAmount = 0;
  counter = 0;
  fileName = file;
  longWait = 0;
  longestIdle = 0;
  meanWait = 0;
  medianWait = 0;
  meanIdle = 0;
  currentStudent = 0;
  ticker = 0;
  total = 0;
  tenCount = 0;
  fiveCount = 0;
  fileReader();
}

Simulation::~Simulation()//destructor
{

}

void Simulation::statistics() //calculation of data
{
  for(int j = 0; j < windowAmount; j++)
  {
    meanIdle = meanIdle + idleArray[j];
  }

  for(int i = 0; i < total; i++)
  {
    meanWait = meanWait + waitArray[i];
  }

  longestWait();
  overTen();
  longestIdleWait();
  overFive();

  meanWait = meanWait/total;
  medianWait = median();
  meanIdle = meanIdle/windowAmount;

  cout << "Mean wait time is: " << meanWait << endl;
  cout << "Median wait time is: " << medianWait << endl;
  cout << "Longest wait time is: " << longWait << endl;
  cout << "Mean window idle time is:  " << meanIdle << endl;
  cout << "Longest window idle time is: " << longestIdle << endl;
  cout << "Windows idle for over 5 minutes: "<< fiveCount << endl;
  cout << "Students waiting over 10 minutes is: "<< tenCount << endl;


}

void Simulation::fileReader()//file reader plus assigning
{

  //  string line;
  //  ifstream UserIn(fileName);
  //  int check = 0;

  //  if(!UserIn) {
  //    check = 1;
  //    cout << "No file was available with the name " << fileName << endl;

  //    UserIn.close();

  //  }

  inFile.open(fileName); //opens the file
  inFile >> currentLine;
  windowAmount = stoi(currentLine);
  personAtWindow = new Student[windowAmount];
  windows = new bool[windowAmount];
  idleArray = new int[windowAmount];
  int peopleArriving;

  while(!inFile.eof())
  {
    inFile >> currentLine;
    studentAmount = stoi(currentLine);

    inFile >> currentLine;
    peopleArriving = stoi(currentLine);

    for(int i = 0; i < peopleArriving; i++)
    {
      inFile >> currentLine;
      Student curr(stoi(currentLine), studentAmount);
      total++;
      start.enqueue(curr);
    }
  }
  waitArray = new int[total];
}


void Simulation::toWindow() //move student to window
{
    while(!start.isEmpty()|| !end.isEmpty() || !windowsEmpty())
    {
      if(!start.isEmpty())
      {
        addToLine();
      }

      clearWindows();

      while(checkWindows() != -1 && !end.isEmpty())
      {
        Student temp = end.vFront();
        int openWindow = checkWindows();
        windows[openWindow] = true;
        personAtWindow[openWindow] = temp;
        end.dequeue();
      }

      for(int i = 0; i < windowAmount; i++)
      {
        personAtWindow[i].timeSpent++;
      }

      GenQueue<Student> studentTwo;
      while(!end.isEmpty())
      {
        Student temp1 = end.vFront();
        end.dequeue();
        studentTwo.enqueue(temp1);
      }

      while(!studentTwo.isEmpty())
      {
        Student temp = studentTwo.vFront();
        studentTwo.dequeue();
        temp.timeWaited++;
        end.enqueue(temp);
      }

      for(int i = 0; i < windowAmount; i++)
      {
        if(windows[i] == false)
        {
          idleArray[i]++;
        }
      }

      if(ticker == 5)
      {
        Student test = end.vFront();
      }
      ticker++;
    }


    statistics();

}

bool Simulation::windowsEmpty()//if all windows are empty, returns true
{

  for(int i = 0; i < windowAmount; i++)
  {
    if(windows[i] == true)
    {
      return false;
    }
  }
  return true;
}

int Simulation::checkWindows()//checks to see how many windows are being used
{

  for(int i = 0; i < windowAmount; i++)
  {
    if(windows[i] == false)
    {
      return i;
    }
  }
  return -1;
}

void Simulation::clearWindows()//clears person from window when done and replaces with new person
{

  for(int i = 0; i < windowAmount; i++)
  {
    if(windows[i] == true)
    {
      if (personAtWindow[i].timeSpent == personAtWindow[i].timeNeeded)
      {
        windows[i] = false;
        Student temp = personAtWindow[i];
        if(temp.timeWaited == 0)
        {
          waitArray[currentStudent] = 0;
        }
        else
        {
          waitArray[currentStudent] =  temp.timeWaited - 1;
        }
        currentStudent++;
      }
    }
  }
}

void Simulation::addToLine()//add to queue
{

  Student curr = start.vFront();
  while(curr.timeArrived == ticker)
  {
    end.enqueue(curr);
    start.dequeue();
    curr = start.vFront();
  }
}

double Simulation::median()//median value
{

  sort(waitArray, waitArray + total - 1);
  if((total % 2) == 1)
  {
    return waitArray[(total/2)];
  }
  else
  {
    return ((waitArray[total/2]+waitArray[(total/2)-1]));
  }
}

double Simulation::longestIdleWait()//finds longest idle time
{

  for(int j = 0; j < windowAmount; j++)
  {
    if(longestIdle < idleArray[j])
    {
      longestIdle = idleArray[j];
    }
  }
}

double Simulation::longestWait()//finds longest wait time
{

  for(int i = 0; i < total; i++)
  {
    if(longWait < waitArray[i])
    {
      longWait = waitArray[i];
    }
  }
}

double Simulation::overTen()//total students waiting over 10 min
{

  for(int i = 0; i < total; i++)
  {
    if(waitArray[i] > 10)
    {
      tenCount++;
    }
  }
}

double Simulation::overFive()//total windows idle for more than 5 minutes
{

  for(int j = 0; j < windowAmount; j++)
  {
    if(idleArray[j] > 5)
    {
      fiveCount++;
    }
  }
}


//void simulation::newSim()
//{
//	if(file->isValid())
//	{
//		cout << "Starting simulation..." << endl;
//		while(stillPatients()) runAMinute();//fix variable

//		cout << "Simulation done" << endl;

//		for(int i = 0; i < totalWindows; i++)
//		{
//			if(windows[i].getMaxIdleTime() > longestIdleTime) longestIdleTime = windows[i].getLongestIdleTime();
//			if(windows[i].getMaxIdleTime() > 5) idleTimeOverFive++;
//			if(windows[i].getIdleTime() > 0)
//			{
//				idleWindowCounter++;
//				meanIdleTime += windows[i].getIdleTime();
//			}
//		}

//		medianWaitTime = median();
//		meanStudentWaitTime = mean();
//		meanIdleTime /= idleWindowCounter;

//		for(int i = 0; i < patientsPassed.size(); i++)
//		{
//			if(patientsPassed[i]->getWaitTime() > longestWaitTime) longestWaitTime = patientsPassed[i]->getWaitTime();
//			if(patientsPassed[i]->getWaitTime() > 10) studentWaitingOverTen++;
//		}

//		cout << "The mean student wait time is: " << meanStudentWaitTime << endl;
//		cout << "The median student wait time is: " << medianWaitTime << endl;
//		cout << "The longest student wait time is: " << longestWaitTime << endl;
//		cout << "The number of students who waited over 10 minutes is: " << studentWaitingOverTen << endl;
//		cout << "The mean window idle time is: " << meanIdleTime << endl;
//		cout << "The longest window idle time is: " << longestIdleTime << endl;
//		cout << "The number of windows with an idle time of more than five is: " << idleTimeOverFive << endl;

//	}else cout << "Simulation closing" << endl;
//}
