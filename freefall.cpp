// Calculator for free fall motion problems (one dimensional)
// Input the initial velocity and the program will output:
// 	- Max. height
// 	- Time when max height is reached

#include <iostream>
#include <iomanip>

int main() {

	// Initial velocity
	double v0 = 0;

	// Gravitational constant
	const double g = 9.8;

	// Set initial velocity and test input
	while(true) {

		std::cout << "Enter initial velocity>" << std::flush;
		if(std::cin >> v0) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(10000,'\n');
			std::cout << "Invalid input" << std::endl;
			
		}
	}

	// Test output
	std::cout << "Initial velocity set to " << v0 << std::endl;

	// Time when velocity equals 0 will be the intial velocity divided by the gravitational constant
	double t = v0 / g;

	std::cout << "The object reaches its maximum height at time t=" << std::setprecision(3) << t << std::endl;
	
	return 0;

}
