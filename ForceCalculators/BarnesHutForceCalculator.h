#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef BARNES_HUT_H_
#define BARNES_HUT_H_

#include "ForceCalculator.h"
#include "../Utils/BarnesHutTree.h"


class BarnesHutForceCalculator : public ForceCalculator{
    private:
        // class BHTree{
        //     private:    
        //         const valtype theta = 0;
        //         valtype mass; // total mass of node
        //         vector3 com;  // centre of mass of node

        //         GravitationalBody *particle; // NULL if not a leaf
        //         int nParticles;

        //         const vector3 centre; // centre of node
        //         const valtype s;      // side length

        //         BHTree *children[2][2][2] = {{{NULL, NULL}, {NULL, NULL}}, {{NULL, NULL}, {NULL, NULL}}};

        //         static valtype i2sgn(const int i);
        //         static int sgn2i(const valtype v);

        //         void divide();
        //         BHTree *getOctant(const GravitationalBody *body)const;
        //     public:
        //         BHTree(const vector3 centre, const valtype s);
        //         ~BHTree();
        //         void insertBody(GravitationalBody *body);
        //         vector3 getForce(const GravitationalBody *body)const;

        //         /*it was useful in the old implementation, but i found the new one easier, and this slows it down
        //         but i implemented it just in case*/
        //         //void deleteEmpty();
        // };

        BHTree* bhtree;
    public:
        BarnesHutForceCalculator(GravitationalSystem& s);
        ~BarnesHutForceCalculator();
        vector3 getForce (const int i) override;
};




#endif