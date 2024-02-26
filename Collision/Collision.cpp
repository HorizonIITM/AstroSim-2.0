#include "Collision.h"
#include <cassert>
#include <algorithm>
#include <vector>

valtype Collision::BHTreeNew::i2sgn(const int i)
{
    return i == 0 ? 1.0 : -1.0;
}
int Collision::BHTreeNew::sgn2i(const valtype v)
{
    return v >= 0 ? 0 : 1;
}

void Collision::BHTreeNew::divide()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                children[i][j][k] = new BHTreeNew(centre + s / 4 * vector3({i2sgn(i), i2sgn(j), i2sgn(k)}), s / 2);
            }
        }
    }
}

Collision::BHTreeNew* Collision::BHTreeNew::getOctant(const GravitationalBody *body) const
{
    vector3 r = body->position - centre;
    return children[sgn2i(r[0])][sgn2i(r[1])][sgn2i(r[2])];
}

Collision::BHTreeNew::BHTreeNew(const vector3 centre, const valtype s) : centre(centre), s(s)
{
    nParticles = 0;
    particle = NULL;
    mass = 0;
    com = vector3();
}

Collision::BHTreeNew::~BHTreeNew()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                delete children[i][j][k]; // delete checks if its NULL
            }
        }
    }
}

void Collision::BHTreeNew::insertBody(GravitationalBody *body)
{    
    if (nParticles >= 1)
    {
        if(nParticles==1){
            divide();
            getOctant(particle)->insertBody(particle); // handle NULL
            particle = NULL;
        }
        getOctant(body)->insertBody(body); // handle NULL
    }
    else
    {
        particle = body;
    }
    nParticles++;
    com = (mass * com + body->mass * body->position) / (mass + body->mass);
    mass += body->mass;
}

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

void Collision::Query(GravitationalBody *body, BHTreeNew* node, vector<GravitationalBody*>& neighbours)
{
    if (Intersect(node->centre,body->position,MaxRadius+body->radius,node->s)){
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
    bhtree = new BHTreeNew(s.middle(), s.maxSize());
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
            }
        }
    }
    return s;
}