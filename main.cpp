#include <iostream>
#include <fstream>
#include <stdio.h>
#include "classes/Mgeometry.cpp"
#include "classes/Mflow.cpp"
#include "classes/EraseOutput.cpp"

using namespace std;

int main()
{
    EraseOutput reset;
    reset.resetFiles();

     Mgeometry geometry;
     geometry.results();
     Mflow flow;
     flow.results();
     system("mybatchfile.bat");
   
    return 0;
}
