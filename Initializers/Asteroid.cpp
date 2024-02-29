#define _USE_MATH_DEFINES
#include "Asteroid.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cmath>
#include<random>
#include<string>
#include "../Utils/utils.h"
#include "../Utils/vector_n.h"
#include "../Utils/vector3.h"
#include "../defs.h"


void initialize_asteroids(std::string infile, long long int n_bodies) { //Produces n asteroids
	long long int n_ini_bodies = n_bodies;
	valtype G = 1.0;
	valtype max_mass = 100.0;
	valtype min_mass = 10.0;
	valtype power_law = -0.6;   // dN/dM proportional to M to the power this
	valtype mean_distance = 5000.0;
	valtype distance_deviation = 1000.0;
	valtype mean_velocity = 0.0;
	valtype velocity_deviation = 1.0;
	valtype mean_inclination = 0.0; //degrees
	valtype inclination_deviation = 40.0;
	valtype w_x = 0.01; //radians/sec
	valtype w_y = 0.01;
	valtype w_z = 0.01;
	vector3 angular_velocity({ w_x,w_y,w_z }); //Systematic anguolar velocity given to all particles, with gaussian "noise".
	valtype asteroid_radius = 0;
	std::ofstream input_conds(infile);


	std::random_device rd1;  // For generating power law distribution for mass
	std::mt19937 gen1(rd1());
	std::uniform_real_distribution<long double> dis1(0.0, 1.0);

	std::random_device rd2;  // For generating positions centered on the solar mass
	std::mt19937 gen2(rd2());
	std::normal_distribution<long double> dis2(mean_distance, distance_deviation);

	std::random_device rd3;  // For generating velocities 
	std::mt19937 gen3(rd3());
	std::normal_distribution<long double> dis3(mean_velocity, velocity_deviation);

	std::random_device rd4;  // For generating inclinations
	std::mt19937 gen4(rd4());
	std::normal_distribution<long double> dis4(mean_inclination * M_PI / 180.0, inclination_deviation * M_PI / 180.0);

	std::random_device rd5;  // For generating orbit angle in plane
	std::mt19937 gen5(rd5());
	std::uniform_real_distribution<long double> dis5(0.0, 2 * M_PI);


	std::vector<valtype>masses;
	std::vector<vector3>positions(n_ini_bodies);
	std::vector<vector3>velocities(n_ini_bodies);
	valtype T = 0.0;  //Kinetic energy	
	valtype V = 0.0;  //Potential energy
	long long int n_so_far = 0;   
	valtype ini_mass, x_vel, y_vel, inclination, orbit_angle, radius;

	masses.push_back(10 * max_mass);
	vector3 ini_pos({ 0.0,0.0,0.0 });
	vector3 ini_vel({ 0.0,0.0,0.0 });
	positions[0] = ini_pos;
	velocities[0]=ini_vel;
	input_conds << 0 << " ";
	input_conds << 10 * max_mass << " " <<asteroid_radius<<" ";
	input_conds << 0.0 << " " << 0.0 << " " << 0.0 << " ";
	input_conds << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
	n_so_far = 1;
	valtype characteristic_velocity;
	valtype virial_radius;
	valtype total_energy;
    valtype virial_ratio;
	valtype crossing_time;
	valtype mass_sum = 100 * max_mass;

	std::cout << "Initializing bodies;" << std::endl;

	while (true) {
		//Select mass per power law, then select radius and some x, y velocity in some plane. Select inclination, orbit argument and then rotate to solar system plane.
		ini_mass = pow(((pow(max_mass, power_law + 1) - pow(min_mass, power_law + 1)) * dis1(gen1) + pow(min_mass, power_law + 1)), 1.0 / (power_law + 1.0));
		radius = dis2(gen2);
		x_vel = dis3(gen3);
		y_vel = dis3(gen3);
		inclination = dis4(gen4);
		orbit_angle = dis5(gen5);
		vector3 ini_pos({ radius * cos(orbit_angle) * cos(inclination) ,radius * sin(orbit_angle) * cos(inclination) ,radius * sin(inclination) });
		vector3 ini_vel({ x_vel * cos(orbit_angle) * cos(inclination) - y_vel * cos(orbit_angle) * sin(inclination) ,x_vel * sin(orbit_angle) + y_vel * cos(orbit_angle) ,-x_vel * cos(orbit_angle) * sin(inclination) + y_vel * sin(orbit_angle) * sin(inclination) });
		ini_vel = ini_vel + angular_velocity.cross_product(ini_pos);
		for (long long int i = 0; i < n_so_far; i++) {
			vector_n diff = positions[i] - ini_pos;
			V = V - G * ini_mass * masses[i] / diff.mag() ;
		}
		T = T + 0.5 * ini_mass * pow(ini_vel.mag(), 2);
		masses.push_back(ini_mass);
		positions[n_so_far]=ini_pos;
		velocities[n_so_far]=ini_vel;
		mass_sum = mass_sum + ini_mass;
		input_conds << n_so_far << " ";
		input_conds << ini_mass << " ";
		input_conds << asteroid_radius << " ";
		input_conds << ini_pos[0] << " " << ini_pos[1] << " " << ini_pos[2] << " ";
		input_conds << ini_vel[0] << " " << ini_vel[1] << " " << ini_vel[2] << std::endl;
		n_so_far += 1;

		if (n_so_far < n_ini_bodies) {
			std::cout << "Working on body no: " << n_so_far << std::endl;
			continue;
		}
		else {
			break;
		}
	}

	input_conds.close();

	virial_ratio = fabs(T / V);
	characteristic_velocity = sqrtl(2 * T / (mass_sum));
	total_energy = T + V;
	virial_radius = -G * mass_sum * mass_sum / (2 * V);
	crossing_time = 2 * virial_radius / (characteristic_velocity);
	//For system in dynamic equilibrium ideally you want 2*T+V close to zero

	std::cout << "Virial ratio " << virial_ratio << std::endl;
	std::cout << "Characteristic velocity " << characteristic_velocity << std::endl;
	std::cout << "Total energy " << total_energy << std::endl;
	std::cout << "Virial Radius " << virial_radius << std::endl;
	std::cout << "Crossing time " << crossing_time << std::endl;

}
