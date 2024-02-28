#include "body.h"
#include <stdlib.h>
// struct GravitationalBody{
//     int ID;
//     valtype mass;
//     vector3 position;
//     vector3 momentum;

//     GravitationalBody(const int, const valtype,const vector3,const vector3);
//     void writeCoords(ofstream&, const string&, const string&)const;
// };

GravitationalBody:: GravitationalBody(const int ID, const valtype mass, const valtype radius, const vector3 position,const vector3 momentum): ID(ID), mass(mass), radius(radius), position(position), momentum(momentum){}

void GravitationalBody:: writeCoords(ofstream& outstream, const string& sep, const string& end)const {
    outstream<<position.to_string(sep)<<end;
}

GravitationalBody GravitationalBody::fakeBody(const valtype mass, const vector3 position){
    return GravitationalBody(0, mass, 0, position, vector3());
}


// struct GravitationalSystem{
//     vector<GravitationalBody> bodies;

//     GravitationalSystem(const vector<GravitationalBody>&&);
//     GravitationalSystem(const string&&);

//     GravitationalBody& operator[](const int i);
//     int size() const;

//     void writeBodyCoords(std::ofstream& outstream, const string& coordSep, const string& bodySep, const string& end )const;
// };

GravitationalSystem::  GravitationalSystem(const vector<GravitationalBody>&& bodies): bodies(bodies){}

GravitationalSystem::  GravitationalSystem(const string&& infile){
    //expecting inputfile with format ID M R X Y Z VX VY VZ \N
    bodies = vector<GravitationalBody>();
    ifstream instream(infile);
    int ID;
    while(instream>>ID){
        valtype m,r,x,y,z,vx,vy,vz;
        instream>>m>>r>>x>>y>>z>>vx>>vy>>vz;
        std::cout<<" "<<ID<<" "<<m<<" "<<r<<" "<<x<<" "<<y<<" "<<z<<" "<<vx<<" "<<vy<<" "<<vz<<std::endl;

        bodies.push_back(GravitationalBody(ID,m,r,{x,y,z},{vx*m,vy*m,vz*m}));
    }
    
    //bodies.pop_back(); //Last body was being read twice in my system-Amogh
}

GravitationalBody& GravitationalSystem:: operator[](const int i){
    return bodies[i];
}

int GravitationalSystem::size()const{
    return bodies.size();
}

valtype GravitationalSystem::maxSize()
{
    valtype side = 0;
    for (int i = 0; i < size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            side = std::max(side, abs(operator[](i).position[j]));
        }
    }
    return 2*side;
}

vector3 GravitationalSystem::middle(){
    vector3 max = vector3();
    vector3 min = vector3();
    for (int i = 0; i < size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            max[j] = std::max(max[j], abs(operator[](i).position[j]));
            min[j] = std::min(min[j], abs(operator[](i).position[j]));
        }
    }
    return (max+min)/2;

}

void GravitationalSystem:: writeBodyCoords(ofstream& outstream, const string& coordSep, const string& bodySep, const string& end )const {
    for(auto& body:bodies){
        body.writeCoords(outstream, coordSep, bodySep);
    }
    outstream<<end;
}

