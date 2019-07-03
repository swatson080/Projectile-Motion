// Calculator for free fall motion problems (one dimensional)
// Input the initial velocity and the program will output:
// 	- Max. height
// 	- Time when max height is reached
//
//
// TODO:
// 	- Allow multiple runs in the same program
// 	- Allow for change of units (e.g. ft/sec)
// 	

#include <iostream>
#include <limits>
#include <climits>
#include <cmath>
#include <iomanip>

double maxHeight(double t, double v0, double g); 
double setInitialVelocity();
double calculateTime(double v0,double g);
void printResults(double t,double p);
bool runAgain();

int main() {

	while(true) {

		// Gravitational constant
		const double g = 9.80665;

		// Initial velocity
		double v0 = setInitialVelocity();

		// Calculate time when object's velocity = 0
		double t = calculateTime(v0,g);

		// Calculate object's maximum height
		double p = maxHeight(t,v0,g);

		// Output the results
		printResults(t,p);

		if(runAgain()) {
			continue;
		}
		else {
			break;
		}
	}
	
	return 0;

}

// Checks if user wants to run another calculation
bool runAgain() {
	char inp;
	while(true) {
		std::cout << "Continue? (Y/N)>" << std::flush;
		if(std::cin >> inp && (inp == 'y' || inp == 'Y' || inp == 'n' || inp == 'N') ) {
			switch(inp)
			{
				case 'y':
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
					return true;
				case 'Y':
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
					return true;
				case 'n':
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
					return false;
				case 'N':
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
					return false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Invalid input" << std::endl;
			
		}
	}
}



void printResults(double t,double p) {
	// Output time (in seconds) with two decimal places after period
	std::cout << "The object reaches its maximum height at time t=" << std::setprecision(2) << std::fixed << t << " seconds" << std::endl;

	// Output height (in meters) with two decimal places after period
	std::cout << "The maximum height reached by the object is " << std::setprecision(2) << std::fixed << p << " meters" << std::endl;
}

// Time when velocity equals 0 will be the intial velocity divided by the gravitational constant
double calculateTime(double v0,double g) {
	double t = v0 / g;
	return t;
}

// Set initial velocity and test input
double setInitialVelocity() {
	double v0 = 0;
	while(true) {

		std::cout << "Enter initial velocity in meters/second>" << std::flush;
		if(std::cin >> v0 && v0 <= INT_MAX) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Invalid input" << std::endl;
			
		}
	}

	return v0;

}

// Position function (determines maximum height that object reaches)
double maxHeight(double t, double v0, double g) {
	double p = 0;
	p = v0*t - ((g/2.0)*pow(t,2.0));
	return p;

}	
