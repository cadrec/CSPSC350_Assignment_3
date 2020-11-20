#include <iostream>
#include <fstream>
#include "GenQueue.h"
#include "Simulation.h"


int main(int argc, char** argv){
  string fileName;

  fileName = argv[1];

  Simulation registrar(fileName);
  registrar.toWindow();

}

//old idea
//int main(int argc, char** argv) {
//  string fileName;
//  if(argc > 1) {
//    fileName = argv[1];
//    ifstream myfile (fileName);
//    Simulation* r1;
//    r1.Simulation();
//  }
//  else {
//    cout << "No file entered on command line!" << endl;
//  }


//}
