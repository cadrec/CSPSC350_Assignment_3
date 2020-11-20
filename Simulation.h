#include <iostream>
#include <fstream>
#include "Student.h"
#include "genQueue.h"


using namespace std;

class Simulation
{
  public:
    Simulation();
    Simulation(string fileName);
    ~Simulation();

    //variables
    int currentStudent;
    int total;
    int windowAmount;
    int ticker;
    int studentAmount;
    int counter;
    int medianWait;
    int longWait;
    int tenCount;
    int fiveCount;

    double meanWait;
    double meanIdle;
    double longestIdle;

    string fileName;
    string currentLine;

    ifstream inFile;

    //queues
    GenQueue<Student> start;
    GenQueue<Student> end;

    //storing students, recommended by Theo Balestra
    int *idleArray;
    int *waitArray;
    bool *windows;
    Student *personAtWindow;

    void fileReader();
    void toWindow();//called in main, used to move students to window
    void addToLine();
    void clearWindows();
    void statistics();

    double longestWait();
    double longestIdleWait();
    double overTen();
    double overFive();
    double median();

    bool windowsEmpty();

    int windowsOpen();
    int checkWindows();
};
