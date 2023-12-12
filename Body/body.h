#pragma once

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

// #include "simulator.h"
#include "../defs.h"

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

struct GravitationalBody{
    int ID;
    valtype mass;
    vector<valtype> position;
    vector<valtype> momentum;

    GravitationalBody(const int, const valtype,const vector<valtype>,const vector<valtype>);
    void writeCoords(ofstream&, const string&, const string&)const;
};

struct GravitationalSystem{
    vector<GravitationalBody> bodies;

    GravitationalSystem(const vector<GravitationalBody>&&);
    GravitationalSystem(const string&&);

    GravitationalBody& operator[](const int i);
    int size() const;

    void writeBodyCoords(std::ofstream& outstream, const string& coordSep, const string& bodySep, const string& end )const;
};
