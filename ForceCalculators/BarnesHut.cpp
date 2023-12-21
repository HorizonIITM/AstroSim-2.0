#include "BarnesHut.h"
#include <cassert>
#include <algorithm>
#include <vector>
class Node{
            public:
                valtype mass = 0; // total mass of node
                vector3 com; // centre of mass of node
                vector<GravitationalBody*> particles; //ptrs to particles inside the node
                vector3 centre; // centre of node
                valtype s; // side length
                vector<Node*> child; // ptrs to child nodes
                Node(valtype x, valtype y, valtype z, valtype side){
                    centre = {x,y,z};
                    s = side;
                }
};

class BarnesHutMethods {
    private:
        void Divide(Node* node){
            valtype x = node->centre[0];
            valtype y = node->centre[1];
            valtype z = node->centre[2];
            valtype s = node->s;
            Node* btr = new Node(x+s/4,y+s/4,z-s/4,s/2); // b-bottom t-top l-left r-right
            Node* btl = new Node(x-s/4,y+s/4,z-s/4,s/2);
            Node* bbl = new Node(x-s/4,y-s/4,z-s/4,s/2);
            Node* bbr = new Node(x+s/4,y-s/4,z-s/4,s/2);
            Node* ttr = new Node(x+s/4,y+s/4,z+s/4,s/2);
            Node* ttl = new Node(x-s/4,y+s/4,z+s/4,s/2);
            Node* tbl = new Node(x-s/4,y-s/4,z+s/4,s/2);
            Node* tbr = new Node(x+s/4,y-s/4,z+s/4,s/2);
            node->child = {btr,btl,bbl,bbr,ttr,ttl,tbl,tbr};
        }

        int whichOctant(Node* node, GravitationalBody& body){
            valtype xr = body.position[0] - node->centre[0];
            valtype yr = body.position[1] - node->centre[1];
            valtype zr = body.position[2] - node->centre[2];
            if (xr>0 && yr>0 && zr<0){return 0;}
            else if (xr<0 && yr>0 && zr<0){return 1;}
            else if (xr<0 && yr<0 && zr<0){return 2;}
            else if (xr>0 && yr<0 && zr<0){return 3;}
            else if (xr>0 && yr>0 && zr>0){return 4;}
            else if (xr<0 && yr>0 && zr>0){return 5;}
            else if (xr<0 && yr<0 && zr>0){return 6;}
            else {return 7;}
        }

        void Octinsert(Node* node, GravitationalBody& body){
            if (node->particles.size()>1){
                node->com[0] = (node->mass*node->com[0] + body.mass*body.position[0])/(node->mass+body.mass);
                node->com[1] = (node->mass*node->com[1] + body.mass*body.position[1])/(node->mass+body.mass);
                node->com[2] = (node->mass*node->com[2] + body.mass*body.position[2])/(node->mass+body.mass);
                node->mass += body.mass;
                node->particles.push_back(&body);
                Octinsert(node->child[whichOctant(node,body)],body);
            }
            else if (node->particles.size()==1){
                Divide(node);
                Octinsert(node->child[whichOctant(node,*(node->particles[0]))],*(node->particles[0]));
                node->com[0] = (node->mass*node->com[0] + body.mass*body.position[0])/(node->mass+body.mass);
                node->com[1] = (node->mass*node->com[1] + body.mass*body.position[1])/(node->mass+body.mass);
                node->com[2] = (node->mass*node->com[2] + body.mass*body.position[2])/(node->mass+body.mass);
                node->mass += body.mass;
                node->particles.push_back(&body);
                Octinsert(node->child[whichOctant(node,body)],body);
            }
            else {
                node->com = body.position;
                node->mass = body.mass;
                node->particles = {&body};
            }
        }

        void DeleteUnusedNodes(Node* root){
            for (auto it=root->child.begin();it!=root->child.end();){
                if ((*it)->particles.size()==0){
                    delete *it;
                    it = root->child.erase(it);
                }
                else if ((*it)->particles.size()==1){
                    it++;
                }
                else {
                    DeleteUnusedNodes(*it);
                    it++;
                }
            }
        }

        void OcttreeBuild(Node* root, vector<GravitationalBody>& o){
            for (int i=0;i<o.size();i++){
                Octinsert(root,o[i]);
            }
            DeleteUnusedNodes(root);
        }

        void DeleteOcttree(Node* root){
            for (auto it=root->child.begin();it!=root->child.end();it++){
                if ((*it)->particles.size()==1){
                    delete *it;
                }
                else {
                    DeleteOcttree(*it);
                }
            }
            delete root;
        }

        vector3 TreeForce(Node* node, GravitationalBody& body){                 //G needs to be 6.67*10-34
            valtype fx=0, fy=0, fz=0;
            if (node->particles.size()==1){
                if (node->particles[0]!=&body){
                    valtype r = Q_rsqrt(((node->com[0]-body.position[0]),2)+pow((node->com[1]-body.position[1]),2)+pow((node->com[2]-body.position[2]),2));
                    fx = G*body.mass*node->mass*(node->com[0]-body.position[0])/pow(r,3);
                    fy = G*body.mass*node->mass*(node->com[1]-body.position[1])/pow(r,3);
                    fz = G*body.mass*node->mass*(node->com[2]-body.position[2])/pow(r,3);                   
                }
            }
            else {
                valtype r = Q_rsqrt(pow((node->com[0]-body.position[0]),2)+pow((node->com[1]-body.position[1]),2)+pow((node->com[2]-body.position[2]),2));
                valtype theta = 0.5;
                if (node->s/r <theta){
                    fx = G*body.mass*node->mass*(node->com[0]-body.position[0])/pow(r,3);
                    fy = G*body.mass*node->mass*(node->com[1]-body.position[1])/pow(r,3);
                    fz = G*body.mass*node->mass*(node->com[2]-body.position[2])/pow(r,3);
                }
                else {
                    for (auto it=node->child.begin();it!=node->child.end();it++){
                        vector3 ChildForce = TreeForce(*it,body);
                        fx+=ChildForce[0];
                        fy+=ChildForce[1];
                        fz+=ChildForce[2];
                    }
                }
            }
            return {fx,fy,fz};
        }

    public:
        vector3 RootCenter;
        valtype RootSide;
        valtype ComputeRootSide(vector<GravitationalBody>& o){
            valtype side = 0;
            for (int i=0;i<o.size();i++){
                for(int j = 0; j < 3; j++){
                    if(side < 2*abs(o[i].position[j])){
                        side = 2*abs(o[i].position[j]);
                    }
                }
            }
            return side;
        }
        BarnesHutMethods(vector3 center, vector<GravitationalBody>& o){
            RootCenter = center;
            RootSide = ComputeRootSide(o);
        }
        vector<vector3> BarnesHutForces(vector<GravitationalBody>& o){
            Node* root = new Node(RootCenter[0],RootCenter[1],RootCenter[2],RootSide);
            OcttreeBuild(root,o);
            vector<vector3> f(o.size());
            for (int i=0;i<o.size();i++){
                vector3 ForceOnBody = TreeForce(root,o[i]);
                f[i] = ForceOnBody;
            }

            DeleteOcttree(root);
            return f;
        }
};

BarnesHut::BarnesHut(GravitationalSystem& s):ForceCalculator(s){
    BarnesHutMethods TreeObj({0, 0, 0}, s.bodies);                         //need to change based on length scale of the problem(rename later)
    forces = TreeObj.BarnesHutForces(s.bodies);
}

vector3 BarnesHut::getForce(const int i){
    return forces[i];
}