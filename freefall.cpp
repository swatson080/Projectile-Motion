// Calculator for free fall motion problems (one dimensional)
// Input the initial velocity and the program will output:
// 	- Max. height
// 	- Distance flown
// 	- Flight time 
//
// Assumptions made:
// 	- No air resistance
// 	- Object lands at the same height from which it was launched
//
//
// TODO:
// 	- Support unit conversion..
// 	
// 	

#include <iostream>
#include <limits>
#include <climits>
#include <cmath>
#include <iomanip>

// Gravitational constant (metric)
const double GRAVITY_METRIC = -9.80665;
// Gravitation constant (imperial)
const double GRAVITY_IMPERIAL = -32.174;

// Calculations/Initial conditions 
double setLaunchAngle();
double maxHeight(double t, double v0, double g); 
double setInitialVelocity(double g);
double calculateTime(double v0,double g);
double calculateVX(double v0, double angle);
double calculateVY(double v0, double angle);
double calculateDisplacement(double vX, double t);
// User preference functions
bool runAgain();
bool useMetric();
bool useRadians();
// Utility functions
double convertToRads(double angle);
void clearInputStream();
void printResults(double t, double height, double displacement, double g);

int main() {

	while(true) {

		double g = GRAVITY_IMPERIAL;
		// Set units (metric/imperial) 
		if(useMetric()) {
			g = GRAVITY_METRIC;
		}

		// Launch angle
		double angle = setLaunchAngle();

		// Initial velocity
		double v0 = setInitialVelocity(g);
		double vX = calculateVX(v0,angle);
		double vY = calculateVY(v0,angle);
		
		// Calculate total flight time 
		double t = calculateTime(vY,g);

		// Calculate object's maximum height
		double height = maxHeight(0.5 * t,vY,g);

		// Calculate object's horizontal flight distance 
		double displacement = calculateDisplacement(vX,t);

		// Output the results
		printResults(t,height,displacement,g);

		if(runAgain()) {
			continue;
		}
		else {
			break;
		}
	}
	
	return 0;

}

// Calculates x component of velocity
double calculateVX(double v0, double angle) {
      double vX = v0 * cos(angle);
      return vX;
}       

// Calculates y component of velocity
double calculateVY(double v0, double angle) {
	double vY = v0 * sin(angle);
	return vY;
}

// Converts angle in degrees to angle in rads
double convertToRads(double angle) {
	angle = angle * (M_PI / 180.0);
	return angle;
}

// Sets the launch angle (calls functions for user preference rads/degrees, converts degrees to rads if necessary, returns angle in rads)
double setLaunchAngle() {

	double angle;
	if(useRadians()) {
		while(true) {
			std::cout << "Launch Angle(radians) >" << std::flush;
			if(std::cin >> angle && angle <= INT_MAX) {
				return angle;
			}
			else {
				clearInputStream();
				std::cout << "Invalid input" << std::endl;
			}
		}
	}
	else {
		while(true) {
			std::cout << "Launch Angle(degrees) >" << std::flush;
			if(std::cin >> angle && angle <= INT_MAX) {
				angle = convertToRads(angle);
				return angle;	
			}
			else {
				clearInputStream();
				std::cout << "Invalid input" << std::endl;
			}
		}
	}
}

// Sets user preference for degrees or rads
bool useRadians() {
	
	int inp;

	while(true){

		std::cout << "Indicate radians (1) or degrees (2) >" << std::flush;
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
		std::cout << "Continue? Yes(1) / No(2) >" << std::flush;
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



void printResults(double t,double height, double displacement, double g) {
	// Add newline before results
	std::cout << std::endl;

	// Output total flight time
	std::cout << "TOTAL FLIGHT TIME: " << std::setprecision(2) << std::fixed << t << " seconds" << std::endl;

	// Output height (in meters) with two decimal places after period
	if(g == GRAVITY_METRIC) {
		std::cout << "MAXIMUM HEIGHT: " << std::setprecision(2) << std::fixed << height << " meters" << std::endl;
		std::cout << "DISTANCE: " << std::setprecision(2) << std::fixed << displacement << " meters " << std::endl;
	}
	else {
		std::cout << "MAXIMUM HEIGHT: " << std::setprecision(2) << std::fixed << height << " feet" << std::endl;
		std::cout << "DISTANCE: " << std::setprecision(2) << std::fixed << displacement << " feet" << std::endl;
	}

	// Add newline after results
	std::cout << std::endl;
}

// Time when velocity equals 0 will be the intial velocity divided by the gravitational constant
double calculateTime(double v0,double g) {
	double t = -(v0 * 2.0) / g;
	return t;
}

// Set initial velocity and test input
double setInitialVelocity(double g) {

	double v0 = 0;
	while(true) {

		std::cout << "Initial Velocity " << std::flush;
		if(g == GRAVITY_METRIC) {
			std::cout << "(meters/second)>" << std::flush;
		}
		else if(g == GRAVITY_IMPERIAL) {
			std::cout << "(feet/second)>" << std::flush;
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

// Position function (determines displacement of the object)
double maxHeight(double t, double vY, double g) {
	double height = 0;
	height = vY*(t) + ((g/2.0)*pow(t,2.0));
	return height;

}	

// Displacement functions (determines object's horizontal displacement) 
double calculateDisplacement(double vX, double t) {
	double displacement = vX * t;
	return displacement;
}


