#pragma once
/*
 * COLLISION.H
 */
#ifndef COLLISION_H_
#define COLLISION_H_

#include "../Body/body.h"
#include "../ForceCalculators/BarnesHutForceCalculator.h"
#include "../Utils/utils.h"
#include "../Utils/BarnesHutTree.h"

class Collision{
    public:

        bool Intersect(vector3 cube, vector3 sphere, valtype r, valtype side);

        void Query(GravitationalBody *body, BHTree* node, vector<GravitationalBody*>& neighbours);

        valtype MaxRadius = 0;   
        BHTree* bhtree;
        valtype CoefficientOfRestitution;

        Collision(GravitationalSystem& s,valtype e);
        ~Collision();
        
        GravitationalSystem ResolveCollisions(GravitationalSystem s);
};

#endif
