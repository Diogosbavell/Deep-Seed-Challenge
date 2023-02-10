#include <iostream>
#include <fstream>
#include "../headers/EraseOutput.h"

using namespace std;

void EraseOutput::resetFiles()
{
    ifstream srcHtml {"outputData/container/output.html"};
    ofstream dsHtml {"outputData/output.html"};
    string line;
    if(srcHtml && dsHtml){
 
        while(getline(srcHtml,line)){
            dsHtml << line << "\n";
        }
    }

    ofstream js;
    js.open("outputData/script.js");

    js.close();
    srcHtml.close();
    dsHtml.close();
}
