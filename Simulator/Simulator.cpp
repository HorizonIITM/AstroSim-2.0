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

vector3 angularMomentum(GravitationalSystem& g) {
    vector3 L = {0 ,0, 0};
    for (auto& b : g.bodies) {
        L += b.momentum.cross_product(b.position);
    }
    return L;
}

void Simulator::solve(const valtype totalTime, const string filename){

    Integrator* integrator;
    switch(i_t){
        case Euler : integrator = new EulerIntegrator(f_t, step); break;
        case RK4 : integrator = new RK4Integrator(f_t, step); break;
        case Leapfrog : integrator = new LeapfrogIntegrator(f_t, step); break;
    }

    valtype progTime = 0;

    string energy_filename = "../Conserved/energy.txt";
    string linmom_filename= "../Conserved/linmom.txt";
    string angmom_filename = "../Conserved/angmom.txt";
    bool writeFlag = filename=="" ? false : true;
    bool energyFlag = energy_filename=="" ? false : true;
    bool linmomFlag = linmom_filename=="" ? false : true;
    bool angmomFlag = angmom_filename=="" ? false : true;
    ofstream my_file(filename); 
    ofstream energy_file(energy_filename);
    ofstream linmom_file(linmom_filename);
    ofstream angmom_file(angmom_filename);

    if(writeFlag) {
        for(int i=1;i<=(s.bodies).size();i++){
            my_file<<"x"<<i<<",y"<<i<<",z"<<i<<",";
        }
        my_file<<"\n";
    };

    if(energyFlag){
        energy_file<<"time,energy"<<endl;
    }

    if(linmomFlag){
        linmom_file<<"time,px,py,pz"<<endl;
    }

    if(angmomFlag){
        angmom_file<<"time,Lx,Ly,Lz"<<endl;
    }

    while(progTime<totalTime){
        if(writeFlag) s.writeBodyCoords(my_file, ",", ",", "\n");
        if(energyFlag) energy_file<<progTime<<","<<energy(s)<<endl;
        if(linmomFlag) linmom_file<<progTime<<","<<linearMomentum(s).to_string(",")<<endl;
        if(angmomFlag) angmom_file<<progTime<<","<<angularMomentum(s).to_string(",")<<endl;

        s = integrator->nextStep(s);

        Collision* collisionchecker = new Collision(s,0.8);
        s = collisionchecker->ResolveCollisions(false);

        progTime+=step;
    }



    if(writeFlag) s.writeBodyCoords(my_file, ",", ",", "\n");

    delete integrator;
}

