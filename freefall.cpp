// Calculator for free fall motion problems (one dimensional)
// Input the initial velocity and the program will output:
// 	- Max. height
// 	- Time when max height is reached
//
//
// TODO:
// 	- Allow other types of kinematics calculations
// 	

#include <iostream>
#include <limits>
#include <climits>
#include <cmath>
#include <iomanip>

// Gravitational constant (metric)
const double gM = 9.80665;

// Gravitation constant (imperial)
const double gI = 32.174;

double maxHeight(double t, double v0, double g); 
double setInitialVelocity(double g);
double calculateTime(double v0,double g);
void printResults(double t,double p, double g);
bool runAgain();
bool useMetric();
void clearInputStream();

int main() {

	while(true) {

		double g = gI;
		// Set units (metric/imperial) 
		if(useMetric()) {
			g = gM;
		}

		// Initial velocity
		double v0 = setInitialVelocity(g);

		// Calculate time when object's velocity = 0
		double t = calculateTime(v0,g);

		// Calculate object's maximum height
		double p = maxHeight(t,v0,g);

		// Output the results
		printResults(t,p,g);

		if(runAgain()) {
			continue;
		}
		else {
			break;
		}
	}
	
	return 0;

}

// Clears the input stream
void clearInputStream() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}


// Checks what unit system user wants
bool useMetric() {

	int inp;

	while(true){

		std::cout << "Indicate metric (1) or imperial (2) >" << std::flush;
		if(std::cin >> inp && inp <= INT_MAX && (inp == 1 || inp == 2)) {
			if(inp == 1) {
				return true;
			}
			else if(inp == 2) {
				return false;
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else{
			clearInputStream();
			std::cout << "Invalid input" << std::endl;
		}

	}
			
}	


// Checks if user wants to run another calculation
bool runAgain() {

	int inp;
	while(true) {
		std::cout << "Continue? Enter Yes(1) or No(2)>" << std::flush;
		if(std::cin >> inp && inp <= INT_MAX && (inp == 1 || inp == 2)) {
			if(inp == 1) {
				return true;
			}
			else if(inp == 2) {
				return false;
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else {
			clearInputStream();
			std::cout << "Invalid input" << std::endl;
		}
	}
}



void printResults(double t,double p, double g) {
	// Output time (in seconds) with two decimal places after period
	std::cout << "The object reaches its maximum height at time t=" << std::setprecision(2) << std::fixed << t << " seconds" << std::endl;

	// Output height (in meters) with two decimal places after period
	if(g == gM) {
		std::cout << "The maximum height reached by the object is " << std::setprecision(2) << std::fixed << p << " meters" << std::endl;
	}
	else {
		std::cout << "The maximum height reached by the object is " << std::setprecision(2) << std::fixed << p << " feet" << std::endl;
	}
}

// Time when velocity equals 0 will be the intial velocity divided by the gravitational constant
double calculateTime(double v0,double g) {
	double t = v0 / g;
	return t;
}

// Set initial velocity and test input
double setInitialVelocity(double g) {

	double v0 = 0;
	while(true) {

		std::cout << "Enter initial velocity " << std::flush;
		if(g == gM) {
			std::cout << "in meters/second>" << std::flush;
		}
		else if(g == gI) {
			std::cout << "in feet/second>" << std::flush;
		}
		if(std::cin >> v0 && v0 <= INT_MAX) {
			break;
		}
		else {
			clearInputStream();
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
