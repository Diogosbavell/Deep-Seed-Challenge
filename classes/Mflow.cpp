#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "../headers/Mflow.h"
#include "../headers/split.h"

using namespace std;

vector<string> Mflow::matchTables(vector<string> table)
{
    string delimiter = ",";
    vector<string> matchTables;

    for (int i = 1; i < table.size(); i++)
    {
        if (serviceSplit.start(table[0], delimiter).size() == 4)
        {
            matchTables.push_back(serviceSplit.start(table[i], delimiter)[1] + "," + serviceSplit.start(table[i], delimiter)[2] + "," + serviceSplit.start(table[i], delimiter)[3]);
        }
        else if (serviceSplit.start(table[0], delimiter).size() == 3)
        {
            matchTables.push_back(serviceSplit.start(table[i], delimiter)[1] + "," + "0" + "," + serviceSplit.start(table[i], delimiter)[2]);
        }
    }
    sort(matchTables.begin(), matchTables.end());
    return matchTables;
}

void Mflow::setNWell()
{
    ifstream inputWell;
    string row;
    vector<string> lines;
    vector<string> diameters;
    vector<string> wellTempData;
    string delimiter = ",";
    const char delim[2] = "-";
    inputWell.open("inputData/well.csv");
    while (getline(inputWell, row, '\n'))
    {
        wellTempData.push_back({row});
    }

    this->nWell = wellTempData.size() - 1;
}

void Mflow::setSpoolDiameters()
{

    ifstream inputSpool;
    string row;
    vector<string> lines;
    vector<string> diameters;
    vector<string> tableAligned;
    string delimiter = ",";
    const char delim[2] = "-";
    inputSpool.open("inputData/spool.csv");
    while (getline(inputSpool, row, '\n'))
    {
        this->spoolData.push_back({row});
    }

    tableAligned = this->matchTables(spoolData);

    for (int i = 0; i < tableAligned.size(); i++)
    {
        this->diametersspool.push_back(stod(serviceSplit.start(tableAligned[i], delimiter)[2]));
    }
}

void Mflow::setWellDiameters()
{
    ifstream inputWell;
    string row;
    vector<string> lines;
    vector<string> diameters;
    vector<string> tableAligned;
    string delimiter = ",";
    const char delim[2] = "-";
    inputWell.open("inputData/well.csv");
    while (getline(inputWell, row, '\n'))
    {
        this->wellData.push_back({row});
    }

    tableAligned = this->matchTables(wellData);

    for (int i = 0; i < tableAligned.size(); i++)
    {
        this->diametersWell.push_back(stod(serviceSplit.start(tableAligned[i], delimiter)[2]));
    }
}

void Mflow::SubseaPipeline()
{
    float Paverage = 0;

    for (int i = 0; i < this->diametersspool.size(); i++)
    {
        Paverage += (this->diametersWell[i] + this->diametersspool[i]) / 2;
        cout<<this->diametersWell[i]<<" "<<this->diametersspool[i]<<" "<<Paverage<<"\n";
    }

    Paverage = Paverage / this->nWell;

    this->Dpipeline = floor((pow(this->nWell, 0.4) * Paverage));

}

void Mflow::results()
{
    ofstream mFlowData;
    mFlowData.open("outputData/Mflow1.txt");
    mFlowData << "Mflow1 Model"
              << "\n"
              << "------------"
              << "\n"
              << "There are " << fixed << setprecision(0) << this->nWell << " "
              << "Wells connected to the Manifold"
              << "\n"
              << "Subsea Pipeline Diameter (zero decimals precision) is: "
              << fixed << setprecision(0) << this->Dpipeline << " "
              << "inch";
    mFlowData.close();

    ofstream mFlowDataJs;
    mFlowDataJs.open("outputData/script.js", ios::app);
    mFlowDataJs << "document.getElementById(\"DpipelineMflow\").innerHTML= " 
                <<"\""<< fixed << setprecision(0) << this->Dpipeline <<"\""<< ";"
                << "\n"
                << "document.getElementById(\"NwellsMflow\").innerHTML= " 
                <<"\""<< fixed << setprecision(0) << this->nWell <<"\""<< ";"
                << "\n"
                << "document.getElementById(\"DminMflow\").innerHTML=\"--\";"
                << "\n";
    mFlowDataJs.close();
}

Mflow::Mflow()
{
    setNWell();
    setSpoolDiameters();
    setWellDiameters();
    SubseaPipeline();
}

Mflow::~Mflow()
{
    cout << "End class Mflow\n";
}
