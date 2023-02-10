#pragma once

#include <iostream>
#include <vector>
#include "../headers/split.h"

using namespace std;

class Mflow
{
private:
    Split serviceSplit;
    int nWell;
    float Dwi;
    float Dsi;
    float Dpipeline;
    vector<float> diametersspool;
    vector<float> diametersWell;
    vector<string> wellData;
    vector<string> spoolData;

    vector<string> matchTables(vector<string>);
    void setNWell();
    void setSpoolDiameters();
    void setWellDiameters();
    void SubseaPipeline();

public:
    void results();
    Mflow();
    ~Mflow();
};
