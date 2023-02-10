#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "../headers/split.h"
#include "../headers/mgeometry.h"

using namespace std;

string Mgeometry::getNWellDMin()
{
    return to_string(this->nWell) + "-" + to_string(this->dMin);
}

void Mgeometry::setNWellAndDmin()
{
    ifstream inputWell;
    string row;
    vector<string> lines;
    vector<string> diameters;
    vector<string> wellData;
    string delimiter = ",";
    inputWell.open("inputData/well.csv");
    while (getline(inputWell, row, '\n'))
    {
        wellData.push_back({row});
    }

    this->nWell = wellData.size() - 1;

    for (int i = 1; i < wellData.size(); i++)
    {
        diameters.push_back(serviceSplit.start(wellData[i], delimiter)[2]);
    }
    sort(diameters.begin(), diameters.end());
   diametersWellandspool.push_back(stod(diameters[0]));
}

void Mgeometry::setspoolDmin()
{
    ifstream inputspool;
    string row;
    vector<string> lines;
    vector<string> diameters;
    diameters.clear();
    vector<string> spoolData;
    string delimiter = ",";
    const char delim[2] = "-";
    inputspool.open("inputData/spool.csv");
    while (getline(inputspool, row, '\n'))
    {
        spoolData.push_back({row});
    }

    for (int i = 0; i < spoolData.size(); i++)
    {
        diameters.push_back(serviceSplit.start(spoolData[i], delimiter)[3]);
    }
    sort(diameters.begin(), diameters.end());

    this->diametersWellandspool.push_back(stod(diameters[0]));

    sort(this->diametersWellandspool.begin(), this->diametersWellandspool.end());

    this->dMin = this->diametersWellandspool[0];
}

void Mgeometry::subSeaPipeline()
{
    this->Dpipeline = pow(this->nWell, 0.5) * this->dMin;
}

void Mgeometry::results()
{
    ofstream mGeometryData;
    mGeometryData.open("outputData/Mgeometry1.txt");
    mGeometryData << "Mgeometry1 Model"
                  << "\n"
                  << "----------------"
                  << "\n"
                  << "There are " << fixed << setprecision(0) << this->nWell << " "
                  << "Wells connected to the Manifold"
                  << "\n"
                  << "The smallest Diameter (3 decimals precision) from all Wells and Spools "
                  << "connected to the Manifold is: "
                  << fixed << setprecision(3) << this->dMin << " "
                  << "inch"
                  << "\n"
                  << "Subsea Pipeline Diameter (3 decimals precision) is: "
                  << fixed << setprecision(3) << this->Dpipeline << " "
                  << "inch";
    mGeometryData.close();

    ofstream mGeometyDataJs;
    mGeometyDataJs.open("outputData/script.js", ios::app);
    mGeometyDataJs << "document.getElementById(\"DpipelineMgeometry\").innerHTML= "
                   <<"\""<< fixed << setprecision(3) << this->Dpipeline <<"\""<< ";"
                   << "\n"
                   << "document.getElementById(\"NwellsMgeometry\").innerHTML= "
                   <<"\""<< fixed << setprecision(0) << this->nWell <<"\""<< ";"
                   << "\n"
                   << "document.getElementById(\"DminMgeometry\").innerHTML= "
                   <<"\""<< fixed << setprecision(3) << this->dMin <<"\""<< ";"
                   << "\n";
    mGeometyDataJs.close();
}

Mgeometry::Mgeometry()
{
    setNWellAndDmin();
    setspoolDmin();
    subSeaPipeline();
}

Mgeometry::~Mgeometry()
{
    cout << "End class Mgeometry\n";
}
