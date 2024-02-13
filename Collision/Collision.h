#pragma once
/*
 * COLLISION.H
 */
#ifndef COLLISION_H_
#define COLLISION_H_

#include "../Body/body.h"
#include "../ForceCalculators/BarnesHutForceCalculator.h"
#include "../Utils/utils.h"

class Collision{
    public:
        class BHTreeNew{
            public:  
                const valtype theta = 0;
                valtype mass; // total mass of node
                vector3 com;  // centre of mass of node

                GravitationalBody *particle; // NULL if not a leaf
                int nParticles;

                const vector3 centre; // centre of node
                const valtype s;      // side length

                BHTreeNew *children[2][2][2] = {{{NULL, NULL}, {NULL, NULL}}, {{NULL, NULL}, {NULL, NULL}}};

                static valtype i2sgn(const int i);
                static int sgn2i(const valtype v);

                void divide();
                BHTreeNew *getOctant(const GravitationalBody *body)const;
                BHTreeNew(const vector3 centre, const valtype s);
                ~BHTreeNew();
                void insertBody(GravitationalBody *body);
        };

        bool Intersect(vector3 cube, vector3 sphere, valtype r, valtype side);

        void Query(GravitationalBody *body, BHTreeNew* node, vector<GravitationalBody*>& neighbours);

        valtype MaxRadius = 0;   
        BHTreeNew* bhtree;
        valtype CoefficientOfRestitution;

        Collision(GravitationalSystem& s,valtype e);
        ~Collision();
        
        GravitationalSystem ResolveCollisions(GravitationalSystem s);
};

#endif
