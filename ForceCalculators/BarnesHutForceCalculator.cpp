#include "BarnesHutForceCalculator.h"
#include <cassert>
#include <algorithm>
#include <vector>

// class BarnesHutForceCalculator : public ForceCalculator{
//     private:
//         class BHTree{
//             private:    
//                 const valtype theta = 0;
//                 valtype mass; // total mass of node
//                 vector3 com;  // centre of mass of node

//                 GravitationalBody *particle; // NULL if not a leaf
//                 int nParticles;

//                 const vector3 centre; // centre of node
//                 const valtype s;      // side length

//                 BHTree *children[2][2][2] = {{{NULL, NULL}, {NULL, NULL}}, {{NULL, NULL}, {NULL, NULL}}};

//                 static valtype i2sgn(const int i);
//                 static int sgn2i(const valtype v);

//                 void divide();
//                 BHTree *getOctant(const GravitationalBody *body)const;
//             public:
//                 BHTree(const vector3 centre, const valtype s);
//                 ~BHTree();
//                 void insertBody(GravitationalBody *body);
//                 vector3 getForce(const GravitationalBody *body)const;

//                 /*it was useful in the old implementation, but i found the new one easier, and this slows it down
//                 but i implemented it just in case*/
//                 //void deleteEmpty();
//         };

//         BHTree* bhtree;
//     public:
//         BarnesHutForceCalculator(GravitationalSystem& s);
//         ~BarnesHutForceCalculator();
//         vector3 getForce (const int i) override;
// };

valtype BarnesHutForceCalculator::BHTree::i2sgn(const int i)
{
    return i == 0 ? 1.0 : -1.0;
}
int BarnesHutForceCalculator::BHTree::sgn2i(const valtype v)
{
    return v >= 0 ? 0 : 1;
}

void BarnesHutForceCalculator::BHTree::divide()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                children[i][j][k] = new BHTree(centre + s / 4 * vector3({i2sgn(i), i2sgn(j), i2sgn(k)}), s / 2);
            }
        }
    }
}

BarnesHutForceCalculator::BHTree *BarnesHutForceCalculator::BHTree::getOctant(const GravitationalBody *body) const
{
    vector3 r = body->position - centre;
    return children[sgn2i(r[0])][sgn2i(r[1])][sgn2i(r[2])];
}

BarnesHutForceCalculator::BHTree::BHTree(const vector3 centre, const valtype s) : centre(centre), s(s)
{
    nParticles = 0;
    particle = NULL;
    mass = 0;
    com = vector3();
}

BarnesHutForceCalculator::BHTree::~BHTree()
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

void BarnesHutForceCalculator::BHTree::insertBody(GravitationalBody *body)
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

vector3 BarnesHutForceCalculator::BHTree::getForce(const GravitationalBody *body) const
{
    vector3 force = vector3();
    valtype r = invsqrt((com - body->position).mag_square());
    if (nParticles == 1)
    {
        if (particle->ID != body->ID)
            force = Force(*body, GravitationalBody::fakeBody(mass, com));
    }
    else if (nParticles > 1)
    {
        if (s / r < theta)
        {
            force = Force(*body, GravitationalBody::fakeBody(mass, com));
        }

        else
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        if (children[i][j][k])
                        {
                            force += children[i][j][k]->getForce(body);
                        }
                    }
                }
            }
        }
    }
    return force;
}

/*it was useful in the old implementation, but i found the new one easier, and this slows it down
but i implemented it just in case*/
// void BarnesHutForceCalculator::BHTree::deleteEmpty()
// {
//     for (int i = 0; i < 2; i++)
//     {
//         for (int j = 0; j < 2; j++)
//         {
//             for (int k = 0; k < 2; k++)
//             {
//                 auto child = children[i][j][k];
//                 if (!child)
//                     ;
//                 else if (child->nParticles == 0)
//                 {
//                     delete child;
//                     child = NULL;
//                 }
//                 else
//                 {
//                     child->deleteEmpty();
//                 }
//             }
//         }
//     }
// }

BarnesHutForceCalculator::BarnesHutForceCalculator(GravitationalSystem &s) : ForceCalculator(s)
{
    bhtree = new BHTree(s.middle(), s.maxSize());
    // bhtree = new BHTree({0, 0, 0}, s.maxSize());
    for (int i = 0; i < s.size(); i++)
    {
        bhtree->insertBody(&s[i]);
    }
    //bhtree->deleteEmpty();
}

vector3 BarnesHutForceCalculator::getForce(const int i)
{
    GravitationalBody *body = &s[i];
    return bhtree->getForce(body);
}

BarnesHutForceCalculator::~BarnesHutForceCalculator()
{
    delete bhtree;
}