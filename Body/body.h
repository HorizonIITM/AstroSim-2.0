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

#include "../Utils/vector3.h"

#include <vector>
using std::vector;

struct GravitationalBody{
    int ID;
    valtype mass;
    vector3 position;
    vector3 momentum;

    GravitationalBody(const int, const valtype,const vector3,const vector3);
    void writeCoords(ofstream&, const string&, const string&)const;
    static GravitationalBody fakeBody(const valtype, const vector3);
};

struct GravitationalSystem{
    vector<GravitationalBody> bodies;

    GravitationalSystem(const vector<GravitationalBody>&&);
    GravitationalSystem(const string&&);

    GravitationalBody& operator[](const int i);
    int size() const;
    valtype maxSize();
    vector3 middle();

    void writeBodyCoords(std::ofstream& outstream, const string& coordSep, const string& bodySep, const string& end )const;
};
