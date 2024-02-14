#include "Simulator.h"

// class Simulator{
//     private:
//         const integrator_t i_t;
//         const force_calulator_t f_t;
//         GravitationalSystem s;
//         const valtype step;
    
//     public:
//         Simulator(GravitationalSystem s, const integrator_t i_t, const force_calulator_t f_t, const valtype step);
//         Simulator(std:: string&& infile, const integrator_t i_t, const force_calulator_t f_t, const valtype step);

//         void solve(const valtype totaltime, const string filename);
// };

Simulator::Simulator(GravitationalSystem s, const integrator_t i_t, const force_calulator_t f_t, const valtype step)
     :s(s), i_t(i_t), f_t(f_t), step(step){}

Simulator::Simulator(std::string&& infile,  const integrator_t i_t, const force_calulator_t f_t, const valtype step)
    :s(GravitationalSystem(std::move(infile))),
     i_t(i_t), f_t(f_t), step(step){}

valtype energy(GravitationalSystem& g){
    valtype e = 0;
    for(auto&b : g.bodies){
        e+= 0.5*b.momentum.mag_square()/b.mass;
    }
    for(auto&b1 : g.bodies){
        for(auto&b2: g.bodies){
            if(b1.ID!=b2.ID){
                e+=-G*b1.mass*b2.mass/(b1.position-b2.position).mag();
            }
        }
    }
    return e;
}

vector3 linearMomentum(GravitationalSystem& g) {
    vector3 totalMomentum = {0, 0, 0};

    for (const auto& body : g.bodies) {
        totalMomentum += body.momentum;
    }

    return totalMomentum;
}

// valtype angular_momentum(GravitationalSystem& g) {
//     valtype L = 0;
//     for (auto& b : g.bodies) {
//         L += b.momentum.cross(b.position);
//     }
//     return L;
// }

void Simulator::solve(const valtype totalTime, const string filename){

    Integrator* integrator;
    switch(i_t){
        case Euler : integrator = new EulerIntegrator(f_t, step); break;
        case RK4 : integrator = new RK4Integrator(f_t, step); break;
        case Leapfrog : integrator = new LeapfrogIntegrator(f_t, step); break;
    }

    valtype progTime = 0;

    bool writeFlag = filename=="" ? false : true;
    ofstream my_file(filename); 

    if(writeFlag) {
        //my_file<<"x1,y1,z1,,,x2,y2,z2,,,x3,y3,z3,,,"<<endl; //scam
        for(int i=1;i<=(s.bodies).size();i++){
            my_file<<"x"<<i<<",y"<<i<<",z"<<i<<",";
        }
        my_file<<"\n";
    }

    while(progTime<totalTime){
        if(writeFlag) s.writeBodyCoords(my_file, ",", ",", "\n");
        s = integrator->nextStep(s);
        cout<<energy(s)<<endl;
        progTime+=step;
    }

    if(writeFlag) s.writeBodyCoords(my_file, ",", ",", "\n");

    delete integrator;
}

