#include "Collision.h"
#include <cassert>
#include <algorithm>
#include <vector>


bool Collision::Intersect(vector3 cube, vector3 sphere, valtype r, valtype side)
{
    vector3 C1 = {cube[0]-side/2,cube[1]-side/2,cube[2]-side/2};
    vector3 C2 = {cube[0]+side/2,cube[1]+side/2,cube[2]+side/2};
    valtype dist_squared = r * r;
    if (sphere[0] < C1[0]){
        dist_squared -= (sphere[0] - C1[0])*(sphere[0] - C1[0]);
    } 
    else if (sphere[0] > C2[0]){
        dist_squared -= (sphere[0] - C2[0])*(sphere[0] - C2[0]);
    } 
    if (sphere[1] < C1[1]){
        dist_squared -= (sphere[1] - C1[1])*(sphere[1] - C1[1]);
    } 
    else if (sphere[1] > C2[1]){
        dist_squared -= (sphere[1] - C2[1])*(sphere[1] - C2[1]);
    } 
    if (sphere[2] < C1[2]){
        dist_squared -= (sphere[2] - C1[2])*(sphere[2] - C1[2]);
    } 
    else if (sphere[2] > C2[2]){
        dist_squared -= (sphere[2] - C2[2])*(sphere[2] - C2[2]);
    } 
    return dist_squared > 0;
}

void Collision::Query(GravitationalBody *body, BHTree* node, vector<GravitationalBody*>& neighbours)
{
    if (Intersect(node->centre,body->position,MaxRadius+body->radius,node->side)){
        if (node->nParticles>1){
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        if (node->children[i][j][k])
                        {
                            Query(body,node->children[i][j][k],neighbours);
                        }
                    }
                }
            }
        }
        else if (node->nParticles==1)
        {
            valtype d2 = pow((node->particle->position[0]-body->position[0]),2)+pow((node->particle->position[1]-body->position[1]),2)+pow((node->particle->position[2]-body->position[2]),2);
            if (d2 <= pow(body->radius+node->particle->radius,2)){
                neighbours.push_back(node->particle);
            }
        }
    }
}


Collision::Collision(GravitationalSystem& s,valtype e)
{
    CoefficientOfRestitution = e;
    for (int i = 0; i < s.size(); i++)
    {
        MaxRadius = std::max(MaxRadius,s[i].radius);
    }
}

Collision::~Collision()
{
    delete bhtree;
}

GravitationalSystem Collision::ResolveCollisions(GravitationalSystem s)
{   
    int CollisionCount = 0;
    bhtree = new BHTree(s.middle(), s.maxSize());
    for (int i = 0; i < s.size(); i++)
    {
        bhtree->insertBody(&s[i]);
    }
    for (int i = 0; i < s.size(); i++)
    {
        vector<GravitationalBody*> neighbours;
        Query(&s[i],bhtree,neighbours);
        for (int j=0;j<neighbours.size();j++){
            if (neighbours[j] != &s[i]){
                CollisionCount+=1;
                valtype delx = neighbours[j]->position[0] - s[i].position[0];
                valtype dely = neighbours[j]->position[1] - s[i].position[1];
                valtype delz = neighbours[j]->position[2] - s[i].position[2];
                valtype r = sqrt(delx*delx+dely*dely+delz*delz);
                valtype k = s[i].radius+neighbours[j]->radius-r;
                valtype nx = delx/r;
                valtype ny = dely/r;
                valtype nz = delz/r;
                valtype v_impact = nx*(s[i].momentum[0]/s[i].mass-neighbours[j]->momentum[0]/neighbours[j]->mass) + ny*(s[i].momentum[1]/s[i].mass-neighbours[j]->momentum[1]/neighbours[j]->mass) + nz*(s[i].momentum[2]/s[i].mass-neighbours[j]->momentum[2]/neighbours[j]->mass);
                valtype reduced_mass = (s[i].mass*neighbours[j]->mass)/(s[i].mass+neighbours[j]->mass);
                valtype impulse = (1+CoefficientOfRestitution)*reduced_mass*v_impact;
                s[i].momentum[0] -= impulse*nx;
                s[i].momentum[1] -= impulse*ny;
                s[i].momentum[2] -= impulse*nz;
                neighbours[j]->momentum[0] += impulse*nx;
                neighbours[j]->momentum[1] += impulse*ny;
                neighbours[j]->momentum[2] += impulse*nz;
                s[i].position[0] -= 0.51*k*nx;
                s[i].position[1] -= 0.51*k*ny;
                s[i].position[2] -= 0.51*k*nz;
                neighbours[j]->position[0] += 0.51*k*nx;
                neighbours[j]->position[1] += 0.51*k*ny;
                neighbours[j]->position[2] += 0.51*k*nz;
                std::cout<<"Collision"<<" "<<i<<" "<<j<<endl;  
            }
        }
    }
    cout<<CollisionCount<<endl;
    return s;
}