#include"AllInitializers.h"

int main(int argc, char* argv[]) {
	int initializer_type = -1;
	std::string infile = "infile.txt";
	long long int n_bodies=100;
	if (argc > 1) {
		infile = argv[1];
	}
	else {
		std::cout << "Infile name not provided, using infile.txt";
	}
	if (argc > 2) {
		initializer_type = atoi(argv[2]);
	}
	else {
		std::cout << "No initializer type give, cannot initialize";
	}
	if (argc > 3) {
		n_bodies = atoll(argv[3]);
	}
	else {
		std::cout << "Number of bodies not provided, using default=100";
	}
	switch (initializer_type) {
		case 0:
			initialize_asteroids(infile,n_bodies);
			break;
		case 1:
			//gal_intializer(infile);
			break;
		default:
			break;
		}
	}