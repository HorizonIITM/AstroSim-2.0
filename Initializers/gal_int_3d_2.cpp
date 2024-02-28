#pragma once
#include "gal_init.h"



using namespace std;

double generateRandomGaussian(double mean, double stddev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(mean, stddev);

    return distribution(gen);
}

struct Star {
    double mass;
    double x, y, z;
    double vx, vy, vz;
    double potential;
};

class Grid {
public:
    int rows, cols;
    double cellWidth, cellHeight;

public:
    Grid(int rows, int cols, double width, double height)
        : rows(rows), cols(cols), cellWidth(width / cols), cellHeight(height / rows) {}

    // to generate position coordinates based on grid location
    tuple<double, double, double> generatePosition(int row, int col) const {
        double x = col * cellWidth - (cellWidth * cols) / 2.0 + cellWidth / 2.0 + generateRandomGaussian(0, 3);
        double y = row * cellHeight - (cellHeight * rows) / 2.0 + cellHeight / 2.0 + generateRandomGaussian(0, 3);
        double z = 0;

        return make_tuple(x, y, z);
    }
};

class SpiralGalaxyPotential {
public:
    int G = 1;

    double gravitationalPotential(double x, double y, double z, double time) const {
        double arms = 4.0; // Number of spiral arms
        double scale = 2.0; // Scale factor for the spiral arms(how strongly they affect stuff)
        double bulgeMass = 1e11; // Mass of the bulge(in place of the blackhole)
        double bulgeScaleRadius = 1e-1; // Scale radius of the bulge
        double diskMass = 1e10; // Mass of the disk(to keep it flat)
        double diskScaleRadius = 5e-1; // Scale radius of the disk
        double diskScaleHeight = 1e-2; // Scale height of the disk

        double angle = atan2(y, x) + time; // Angle in polar coordinates

        // Extra term '0.5' to improve symmetry
        double potential = cos(arms * angle) * exp(-sqrt(x * x + y * y) / scale) + 0.5;

        // Bulge potential
        potential += -G * bulgeMass / (sqrt(x * x + y * y + z * z) * sqrt(x * x + y * y + z * z) + bulgeScaleRadius * bulgeScaleRadius);

        // Disk potential
        potential += -G * diskMass / ((x * x + y * y) * (x * x + y * y) + diskScaleRadius * diskScaleRadius) /
                      ((z * z) + diskScaleHeight * diskScaleHeight);

        return potential;
    }
};

void gal_intializer(std::string input_file) {
    SpiralGalaxyPotential spiralGalaxy;
    int counter = 0;

    // Defining grid---need to adjust values to match repo
    Grid myGrid(100, 100, 50.0, 50.0);

    std::ofstream outputFile(input_file);
    float max_potential = 0;
    float min_potential = 0;
    for (int row = 0; row < myGrid.rows; ++row) {
        for (int col = 0; col < myGrid.cols; ++col) {
            tuple<double, double, double> position = myGrid.generatePosition(row, col);

            double time = 2.0;
            double gravitationalPotential = spiralGalaxy.gravitationalPotential(get<0>(position), get<1>(position), get<2>(position), time);
            get<2>(position) += generateRandomGaussian(0, 1);
            double m = generateRandomGaussian(100, 10);  
            Star star;
            star.mass = m;
            star.potential = gravitationalPotential;
            star.x = get<0>(position);
            star.y = get<1>(position);
            star.z = get<2>(position);

            // Calculating velocity components using potential and distance from centre
            double angle = atan2(star.y, star.x);
            double vel = sqrt(fabs(star.potential) / m);
            star.vx = vel * cos(angle);
            star.vy = vel * sin(angle);
            star.vz = generateRandomGaussian(0, 0.1);  // Small random velocity in z-direction
        
            max_potential +=star.potential;
            min_potential +=1;

            // Writing data to the output file--threshold needed
            if (star.mass >0 && star.potential < -3.1002e+9){
                counter +=1;
            outputFile<<counter<< star.mass << " 0 " <<star.x << " " << star.y << " " << star.z << " "
                        << star.vx << " " << star.vy << " " << star.vz <<"\n";};
            
        }
    }

    outputFile.close();
    
}
