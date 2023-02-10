#pragma once

#include <iostream>
#include <vector>
#include "split.h"

using namespace std;

class Mgeometry
{
private:
    Split serviceSplit;
    int nWell;
    float dMin;
    float Dpipeline;

    vector<float> diametersWellandspool;

    string getNWellDMin();
    void setNWellAndDmin();
    void setspoolDmin();
    void subSeaPipeline();

public:
    void results();
    Mgeometry();
    ~Mgeometry();
};
