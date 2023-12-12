#include "Simulator.h"

Simulator::Simulator(GravitationalSystem s, const integrator_t i_t, const force_calulator_t f_t, const valtype step)
     :s(s), i_t(i_t), f_t(f_t), step(step){}

Simulator::Simulator(std::string&& infile,  const integrator_t i_t, const force_calulator_t f_t, const valtype step)
    :s(GravitationalSystem(std::move(infile))),
     i_t(i_t), f_t(f_t), step(step){}

void Simulator::solve(const valtype totalTime, const string filename){

    Integrator* integrator;
    switch(i_t){
        case Euler : integrator = new EulerIntegrator(f_t, step); break;
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
        if(writeFlag) s.writeBodyCoords(my_file, ",", "", "\n");
        s = integrator->nextStep(s);
        progTime+=step;
    }

    if(writeFlag) s.writeBodyCoords(my_file, ",", "", "\n");

    delete integrator;
}

