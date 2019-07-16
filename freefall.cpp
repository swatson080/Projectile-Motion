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
// 	- Allow additional values of G
// 	
// 	

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <climits>
#include <cmath>

// Gravitational constant (metric)
const double GRAVITY_METRIC = -9.80665;
// Gravitation constant (imperial)
const double GRAVITY_IMPERIAL = -32.174;

// Initial conditions 
double setLaunchAngle(bool radians);
double setInitialVelocity(bool metric);
// Input functions
double getFloatInput(std::string message);
int getIntInput(std::string message); 
std::string getStringInput();
// Calculations
double calculateVX(double v0, double angle);
double calculateVY(double v0, double angle);
double calculateTime(double v0,double g);
double maxHeight(double t, double v0, double g); 
double calculateDisplacement(double vX, double t);
// User preference functions
bool runAgain();
bool useMetric();
bool useRadians();
// Utility functions
void runSimulation(double g, bool metric, bool radians);
int menuChoice();
double convertToRads(double angle);
void clearInputStream();
void printResults(double t, double height, double displacement, bool metric, bool radians, double v0, double angle);

int main() {

	bool exit = false;
	bool metric = true; // Defaults to metric 
	bool radians = false; // Defaults to degrees
	double g;

	do {
		if(metric) {
			g = GRAVITY_METRIC;
		}
		else {
			g = GRAVITY_IMPERIAL;
		}

		int selection = menuChoice();
		switch(selection) {
			case 1: 
				runSimulation(g, metric, radians);
				break;
			case 2:
				metric = useMetric();
				radians = useRadians();
				break;
			case 3:
				exit = true;
				break;
		}
	} while(!exit);
	
	return 0;
}

// Sets the launch angle (returns angle in rads)
double setLaunchAngle(bool radians) {

	double angle;
	if(radians) {
		angle = getFloatInput("Input Launch Angle (radians) >");
		return angle;
	}
	else {
		angle = getFloatInput("Input Launch Angle (degrees) >");
		angle = convertToRads(angle);
		return angle;	
	}
}

// Set initial velocity and test input
double setInitialVelocity(bool metric) {
	double v0;
	if(metric) {
		v0 = getFloatInput("Enter initial velocity (meters/second)>");
		return v0;
	}
	else {
		v0 = getFloatInput("Enter initial velocity (feet/second) >");
		return v0;	
	}
}

// Gets float input
double getFloatInput(std::string message) {
	std::string rawInput;
	while(true) {
		std::cout << message;
		rawInput = getStringInput();
		std::stringstream stream(rawInput);

		double value;
		char temp;
		stream >> value;
		if(stream && !(stream >> temp) && value >= 0 && value <= INT_MAX) {
			return value;
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}
	}
}

// Gets integer input
int getIntInput(std::string message) {
	std::string rawInput;
	while(true) {
		std::cout << message;
		rawInput = getStringInput();
		std::stringstream stream(rawInput);

		int value;
		char temp;
		stream >> value;
		if(stream && !(stream >> temp) && value >= 0 && value <= INT_MAX) {
			return value;
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}
	}
}

// Gets string input
std::string getStringInput() {
	std::string input;
	std::getline(std::cin,input);
	return input;
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

// Time when velocity equals 0 will be the intial velocity divided by the gravitational constant
double calculateTime(double v0,double g) {
	double t = -(v0 * 2.0) / g;
	return t;
}

// Position function (determines displacement of the object)
double maxHeight(double t, double vY, double g) {
	double height = 0;
	height = vY*(t) + ((g/2.0)*pow(t,2.0));
	return height;

}	

// Displacement function (determines object's horizontal displacement) 
double calculateDisplacement(double vX, double t) {
	double displacement = vX * t;
	return displacement;
}

// Checks if user wants to run another calculation
bool runAgain() {

	while(true) {
		int inp = getIntInput("Continue? Enter 1 (Yes) or 2 (No) >");
		switch(inp) {
			case 1:
				return true;
			case 2:
				return false;
			default:
				std::cout << "Invalid input" << std::endl;
				continue;
		}
	}
}

// Checks what unit system user wants
bool useMetric() {

	while(true) {
		int inp = getIntInput("Indicate metric (1) or imperial (2) >");
		switch(inp) {
			case 1:
				return true;
			case 2:
				return false;
			default:
				std::cout << "Invalid input" << std::endl;
		}
	}
}	

// Sets user preference for degrees or rads
bool useRadians() {
	while(true) {	
		int inp = getIntInput("Indicate radians (1) or degrees (2) >");
		switch(inp) {
			case 1:
				return true;
			case 2:
				return false;
			default:
				std::cout << "Invalid input" << std::endl;
				continue;
		}
	}
}

// Loop for running projectile motion simulations
void runSimulation(double g, bool metric, bool radians) {
	while(true) {

		// Launch angle
		double angle = setLaunchAngle(radians);
		// Initial velocity
		double v0 = setInitialVelocity(metric);
		double vX = calculateVX(v0,angle);
		double vY = calculateVY(v0,angle);
		
		// Calculate total flight time 
		double t = calculateTime(vY,g);

		// Calculate object's maximum height
		double height = maxHeight(0.5 * t,vY,g);

		// Calculate object's horizontal flight distance 
		double displacement = calculateDisplacement(vX,t);

		// Output the results
		printResults(t,height,displacement,metric,radians,v0,angle);

		if(runAgain()) {
			continue;
		}
		else {
			break;
		}
	}
}

// Gets users choice for next action
int menuChoice() {
	std::string menuMessage = "\nMake a selection\n1. Run simulations\n2. Set unit preferences\n3. Exit\n>";
	while(true) {
		int selection = getIntInput(menuMessage);
		switch(selection) {
			case 1: 
				return selection;
			case 2:
				return selection;
			case 3:
				return selection;
			default:
				std::cout << "Invalid Input" << std::endl;
		}
	}
}


// Converts angle in degrees to angle in rads
double convertToRads(double angle) {
	angle = angle * (M_PI / 180.0);
	return angle;
}

// Converts angle in rads to angle in degrees
double convertToDegrees(double angle) {
	angle = angle * (180.0 / M_PI);
	return angle;
}

// Clears the input stream
void clearInputStream() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

// Outputs results
void printResults(double t,double height, double displacement, bool metric, bool radians, double v0, double angle) {
	// Add newline before results
	std::cout << std::endl;

	// Output initial conditions
	std::cout << "INITIAL VELOCITY: " << v0;
	if(metric) {
		std::cout << " meters/second | " << std::flush;
	}
	else {
		std::cout << " feet/second | " << std::flush;
	}
	std::cout << "LAUNCH ANGLE: ";
	if(radians) {
		std::cout << angle << " radians" << std::endl;
	}
	else {
		std::cout << convertToDegrees(angle) << " degrees" << std::endl;
	}
	
	// Output total flight time
	std::cout << "TOTAL FLIGHT TIME: " << std::setprecision(2) << std::fixed << t << " seconds" << std::endl;

	// Output height (in meters) with two decimal places after period
	if(metric) {
		std::cout << "DISTANCE: " << std::setprecision(2) << std::fixed << displacement << " meters " << std::endl;
		std::cout << "MAXIMUM HEIGHT: " << std::setprecision(2) << std::fixed << height << " meters" << std::endl;
		}
	else {
		std::cout << "DISTANCE: " << std::setprecision(2) << std::fixed << displacement << " feet" << std::endl;
		std::cout << "MAXIMUM HEIGHT: " << std::setprecision(2) << std::fixed << height << " feet" << std::endl;
		}

	// Add newline after results
	std::cout << std::endl;
}
