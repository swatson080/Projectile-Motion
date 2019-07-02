// Calculator for free fall motion problems (one dimensional)
// Input the initial velocity and the program will output:
// 	- Max. height
// 	- Time when max height is reached
//
//
// TODO:
// 	- Allow multiple runs in the same program
// 	- Break into discrete functions
// 	- Allow for change of units (e.g. ft/sec)
// 	

#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>

double maxHeight(double t, double v0, double g); 

int main() {

	// Initial velocity
	double v0 = 0;

	// Gravitational constant
	const double g = 9.80665;

	// Set initial velocity and test input
	while(true) {

		std::cout << "Enter initial velocity in meters/second>" << std::flush;
		if(std::cin >> v0) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Invalid input" << std::endl;
			
		}
	}

	// Test output
	//std::cout << "Initial velocity set to " << v0 << std::endl;

	// Time when velocity equals 0 will be the intial velocity divided by the gravitational constant
	double t = v0 / g;

	// Maximum height that object reaches can now be determined with the following calculation
	// (v0*t) - ((g/2.0)*pow(t,2.0));
	double p = maxHeight(t,v0,g);

	// Output time (in seconds) with two decimal places after period
	std::cout << "The object reaches its maximum height at time t=" << std::setprecision(2) << std::fixed << t << " seconds" << std::endl;

	// Output height (in meters) with two decimal places after period
	std::cout << "The maximum height reached by the object is " << std::setprecision(2) << std::fixed << p << " meters" << std::endl;
	
	return 0;

}

// Position function
double maxHeight(double t, double v0, double g) {

	double p = 0;
	p = v0*t - ((g/2.0)*pow(t,2.0));
	return p;

}	
