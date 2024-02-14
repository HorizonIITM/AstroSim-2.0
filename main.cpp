#include "Integrators/AllIntegrators.h"
#include "ForceCalculators/AllForceCalculators.h"
#include "Simulator/Simulator.h"
#include "Body/body.h"
#include "defs.h"
#include "Initializers/AllInitializers.h"


int main(int argc, char *argv[]) {

    string outfile = "nbodyoutput.txt";
    string infile = "";
    valtype totalProgTime = 20000;
    valtype step = 0.01;
    int init_type = 0;
    if(argc>1){
        outfile = argv[1];
    }
    if(argc>2){
        infile = argv[2];
    }else{
        cout<<"NO INPUT FILE PROVIDED"<<endl;
        exit(1);
    }
    if(argc>3){
        totalProgTime = atof(argv[3]);
    }
    if(argc>4){
        step = atof(argv[4]);
    }
    if (argc>5) {
        init_type = atoi(argv[5]);
        switch (init_type){
        case 1:
            initialize_asteroids(infile);
            break;
            //Add other initializers here
        default:
            break;
        }
    }
    cout<<"Taking total time = "<<totalProgTime<<endl;
    cout<<"Taking step time = "<<step<<endl;
    
    Simulator my_solver(std::move(infile), Euler, BarnesHut, step);
    my_solver.solve(totalProgTime, outfile);
    return 0;
}
