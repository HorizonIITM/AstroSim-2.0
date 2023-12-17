#include "body.h"

// struct GravitationalBody{
//     int ID;
//     valtype mass;
//     vector3 position;
//     vector3 momentum;

//     GravitationalBody(const int, const valtype,const vector3,const vector3);
//     void writeCoords(ofstream&, const string&, const string&)const;
// };

GravitationalBody:: GravitationalBody(const int ID, const valtype mass,const vector3 position,const vector3 momentum): ID(ID), mass(mass), position(position), momentum(momentum){}

void GravitationalBody:: writeCoords(ofstream& outstream, const string& sep, const string& end)const {
    for(int i=0;i<3;i++){
        outstream<<position[i]<<sep;
    }
    outstream<<end;
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
    //expecting inputfile with format ID M X Y  Z VX VY VZ \N
    bodies = vector<GravitationalBody>();
    ifstream instream(infile);
    while(!instream.eof()){
        int ID;
        valtype m,x,y,z,vx,vy,vz;
        //std::cout<<"hello"<<std::endl;
        instream>>ID>>m>>x>>y>>z>>vx>>vy>>vz;
        std::cout<<" "<<ID<<" "<<m<<" "<<x<<" "<<y<<" "<<z<<" "<<vx<<" "<<vy<<" "<<vz<<std::endl;

        bodies.push_back(GravitationalBody(ID,m,{x,y,z},{vx*m,vy*m,vz*m}));
    }
}

GravitationalBody& GravitationalSystem:: operator[](const int i){
    return bodies[i];
}

int GravitationalSystem::size()const{
    return bodies.size();
}

void GravitationalSystem:: writeBodyCoords(ofstream& outstream, const string& coordSep, const string& bodySep, const string& end )const {
    for(auto& body:bodies){
        body.writeCoords(outstream, coordSep, bodySep);
    }
    outstream<<end;
}

