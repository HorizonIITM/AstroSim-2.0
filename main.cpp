#include "everything.h"

//make a custom datastructure which is vector of size 3
//move gravitational integrator to a separate file

int main(int argc, char *argv[]) {
    string outfile = "nbodyoutput.txt";
    string infile = "";
    valtype totalProgTime = 20000;
    valtype step = 0.01;
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
    cout<<"Taking total time = "<<totalProgTime<<endl;
    cout<<"Taking step time = "<<step<<endl;
    
    Simulator my_solver(std::move(infile), RK4, Direct, step);
    my_solver.solve(totalProgTime, outfile);
    return 0;
}
