#include "instructions.h"

int main(int argc, char* argv[]) {

	// TESTING
	std::clock_t start;
	Instructions I, J, K, L;

	// choose tests to run
	bool run_basic_test = 1;		// basic (instruct1.txt)
	bool run_advanced_test = 0;		// advanced (instruct2.txt)
	bool run_euler_test = 0;		// euler (euler.txt)
	bool run_performance_test = 0;		// performance of single instruction (instruct3.txt)

	if (run_basic_test) // Basic (instruct1.txt)
	{
		std::ifstream myfile("instruct1.txt");
		//start = std::clock();
		I.readFile(myfile);
		start = std::clock();
		I.run();
		std::cout << "Time to run: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / (1000)) << " milliseconds" << std::endl << std::endl; // time in milliseconds

	}

	if (run_advanced_test) // Advanced (instruct2.txt)
	{
		std::ifstream myfile2("instruct2.txt");
		//start = std::clock();
		J.readFile(myfile2);
		start = std::clock();
		J.run();
		std::cout << "Time to run: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / (1000)) << " milliseconds" << std::endl << std::endl; // time in milliseconds
		// Note: instruct2.txt asks for user input, and the time the user takes is included in the timing
	}

	if (run_euler_test) // Euler method damped projectile (euler.txt)
	{

		std::ifstream myfile3("euler.txt");
		//start = std::clock();
		K.readFile(myfile3);
		start = std::clock();
		K.run();
		std::cout << "Time to run: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / (1000)) << " milliseconds" << std::endl << std::endl; // time in milliseconds
	}

	if (run_performance_test) // performance testing (single operation and return) (instruct3.txt)
	{
		std::ifstream myfile4("instruct3.txt");
		bool print_return = true; // test performance with or without printing return value
		int iterations = 10000;
		//start = std::clock();
		L.readFile(myfile4);
		start = std::clock();
		for (int index = 0; index < iterations; ++index) // run number of iterations
			L.run(print_return);
		std::cout << "Time to run: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / (1000)) << " milliseconds" << std::endl << std::endl; // time in milliseconds
	}

	return 0;
}