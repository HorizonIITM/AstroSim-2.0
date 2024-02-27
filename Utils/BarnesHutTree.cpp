#include "BarnesHutTree.h"

valtype BHTree::i2sgn(const int i)
{
    return i == 0 ? 1.0 : -1.0;
}


int BHTree::sgn2i(const valtype v)
{
    return v >= 0 ? 0 : 1;
}



void BHTree::divide()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                children[i][j][k] = new BHTree(centre + side / 4 * vector3({i2sgn(i), i2sgn(j), i2sgn(k)}), side / 2);
            }
        }
    }
}



BHTree *BHTree::getOctant(const GravitationalBody *body) const
{
    vector3 r = body->position - centre;
    return children[sgn2i(r[0])][sgn2i(r[1])][sgn2i(r[2])];
}



BHTree::BHTree(const vector3 centre, const valtype side) : centre(centre), side(side)
{
    nParticles = 0;
    particle = NULL;
    mass = 0;
    com = vector3();
}



BHTree::~BHTree()
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



void BHTree::insertBody(GravitationalBody *body)
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



vector3 BHTree::getForce(const GravitationalBody *body) const
{
    vector3 force = vector3();
    valtype r = (com - body->position).mag();
    if (nParticles == 1)
    {
        if (particle->ID != body->ID)
            force = ForceCalculator::Force(*body, GravitationalBody::fakeBody(mass, com));
    }
    else if (nParticles > 1)
    {
        if (side / r < theta)
        {
            force = ForceCalculator::Force(*body, GravitationalBody::fakeBody(mass, com));
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


// void BHTree::deleteEmpty()
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