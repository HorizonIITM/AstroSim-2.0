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

void Collision::Query(GravitationalBody& body, BHTree* node, vector<GravitationalBody*>& neighbours)
{
    if (Intersect(node->centre,body.position,MaxRadius+body.radius,node->side)){
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
            valtype d2 = (node->particle->position-body.position).mag_square();
            if (d2 <= pow(body.radius+node->particle->radius,2)){
                neighbours.push_back(node->particle);
            }
        }
    }
}


Collision::Collision(GravitationalSystem& s,valtype e): s(s)
{
    CoefficientOfRestitution = e;
    for (int i = 0; i < s.size(); i++)
    {
        MaxRadius = std::max(MaxRadius,s[i].radius);
    }
    bhtree = new BHTree(s.middle(), s.maxSize());
    for (int i = 0; i < s.size(); i++)
    {
        bhtree->insertBody(&s[i]);
    }
}

Collision::~Collision()
{
    delete bhtree;
}

GravitationalSystem Collision::ResolveCollisions(bool printCollisions)
{   
    int CollisionCount = 0;
    
    for (int i = 0; i < s.size(); i++)
    {
        vector<GravitationalBody*> neighbours;
        Query(s[i],bhtree,neighbours);
        for (int j=0;j<neighbours.size();j++){
            if (neighbours[j]->ID != s[i].ID){
                CollisionCount+=1;
                vector3 del = neighbours[j]->position - s[i].position;
                valtype r = del.mag();
                valtype k = s[i].radius+neighbours[j]->radius-r;
                vector3 n = del/r;
                valtype v_impact = n.dot_product(s[i].momentum/s[i].mass - neighbours[j]->momentum/neighbours[j]->mass);
                valtype reduced_mass = (s[i].mass*neighbours[j]->mass)/(s[i].mass+neighbours[j]->mass);
                valtype impulse = (1+CoefficientOfRestitution)*reduced_mass*v_impact;
                s[i].momentum -= impulse*n;
                neighbours[j]->momentum += impulse*n;
                s[i].position -= 0.51*k*n;
                neighbours[j]->position += 0.51*k*n;

                if(printCollisions)
                    cout<<"Collision"<<" "<<i<<" "<<j<<endl;  
            }
        }
    }
    if (printCollisions && CollisionCount > 0)
        cout<<CollisionCount<<endl;
    return s;
}