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

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <climits>
#include <cmath>

// Number of celestial bodies
const int NUM_LOCATIONS = 10;
// Gravitation constants for solar system bodies (metric)
const double GRAVITY_METRIC[NUM_LOCATIONS] = { -3.70, -8.87, -9.80665, -1.62, -3.71, -24.79, -10.44, -8.69, -11.15, -0.66 };
// Gravitation constants for solar system bodies (imperial)
const double GRAVITY_IMPERIAL[NUM_LOCATIONS] = { -12.1391, -29.10, -32.174, -5.31496, -12.1719, -81.332, -34.252, -28.5105, -36.5814, -2.1654 };
// Names of solar system bodies
const std::string PLANETS[10] = { "Mercury", "Venus", "Earth", "The moon", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto" };
// Planet enum
enum planets{mercury, venus, earth, moon, mars, jupiter, saturn, uranus, neptune, pluto};

// Gravitational constant (metric)
//const double GRAVITY_METRIC = -9.80665;
// Gravitation constant (imperial)
//const double GRAVITY_IMPERIAL = -32.174;

// Initial conditions 
double setLaunchAngle(bool radians);
double setInitialVelocity(bool metric);
double setGravity(bool metric, int currentPlanet);
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
int setPlanet();
// Utility functions
void runSimulation(double g, bool metric, bool radians);
int menuChoice();
double convertToRads(double angle);
void clearInputStream();
void printInfo(int currentPlanet, double g, bool metric, bool radians);
void printResults(double t, double height, double displacement, bool metric, bool radians, double v0, double angle);

int main() {

	bool exit = false;
	bool metric = true; // Defaults to metric 
	bool radians = false; // Defaults to degrees
	double g;
	int currentPlanet = earth; 

	do {
		g = setGravity(metric,currentPlanet);
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
				currentPlanet = setPlanet();
				break;
			case 4:
				printInfo(currentPlanet,g,metric,radians);
				break;
			case 5:
				exit = true;
				break;
		}
	} while(!exit);
	
	return 0;
}

// Sets gravity value based on metric/imperial and current planet
double setGravity(bool metric, int currentPlanet) {
	double g;
	if(metric) {
		g = GRAVITY_METRIC[currentPlanet];
	}
	else {
		g = GRAVITY_IMPERIAL[currentPlanet];
	}
	return g;
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

// Sets the users location
int setPlanet() {
	int currentPlanet;
	// Build message for planet menu
	std::string planetMessage = "\nSelect the planet you would like to run simulations for\n"; 
	for(int i = 0; i < 10; i++) {
		std::stringstream stream;
		std::string num;
		stream << i+1;
		num = stream.str();
		planetMessage += num + ". " + PLANETS[i] + "\n";
	}
	planetMessage += ">";
	// Get user input for planet selection
	while(true) {	
		int currentPlanet = getIntInput(planetMessage);
		if(currentPlanet >= 1 && currentPlanet <= 10) {
			return currentPlanet - 1;
		}
		else {
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
	std::string menuMessage = "\nMain Menu\n1. Simulations\n2. Units\n3. Location\n4. Current Settings\n5. Exit\n>";
	while(true) {
		int selection = getIntInput(menuMessage);
		if(selection > 0 && selection < 6) {
			return selection;
		}
		else {
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

// Prints the Current Planet, the value of gravity, and measurement settings (metric/imperial and degrees/radians)
void printInfo(int currentPlanet, double g, bool metric, bool radians) {
	std::cout << "\nLOCATION: " << PLANETS[currentPlanet] << std::endl;
	std::cout << "GRAVITY: " << g << std::endl;
	if(metric) {
		std::cout << "UNITS: METRIC" << std::flush;
	}
	else {
		std::cout << "UNITS: IMPERIAL" << std::flush;
	}
	if(radians) {
		std::cout << ", RADIANS\n" << std::endl;
	}
	else {
		std::cout << ", DEGREES\n" << std::endl;
	}
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
