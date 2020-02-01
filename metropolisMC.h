#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

// Sampling functions
// 1D
double g(double x) { return exp(-1 * x * x ); }
double f1(double x) { return x*x; }
double f2(double x) { return cos(10*x*x); }

// 2D
double g(double x, double y) { return exp(-1 * x * x - y * y ) ; }
double f1(double x, double y) { return x * x * y * y; }

// 3D

//Integrating functions

double mmc_1d(const std::function<double(double)>& f, int n) {	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> acc_dist(0.0,1.0);
	std::uniform_real_distribution<> sampling_dist(-1.0,1.0);
	double pi = 3.14159265358979;
	double result = 0.0;
	double x = sampling_dist(gen);
	int i = 0;
	double tot = 0.0;
	double acc = 0.0;
	double step = 2.08;

	while (i < n) {
		double x1 = x + step * sampling_dist(gen);
		double u0 = g(x);
		double u1 = g(x1);
		double acceptance_crit = acc_dist(gen);
		if ( (u1 / u0) > acceptance_crit ) { 
			x = x1;
			acc++;
		}
		tot += f(x);
		i++;
	}

	result = sqrt(pi) * tot / n;
	//std::cout << "The integral is \t" << result << std::endl;
	//std::cout << "Acceptance ratio: \t" << acc / n << std::endl;
	//std::cout << "n: \t\t" << n << std::endl << "---\n";
	return result;
}

double mmc_2d() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> acc_dist(0.0,1.0);
	std::uniform_real_distribution<> sampling_dist(-1.0,1.0);
	double pi = 3.14159265358979;

	double x = sampling_dist(gen);
	double y = sampling_dist(gen);
	int i = 0;
	int p = 7;
	int n = pow(10,p);
	double tot = 0.0;
	double acc = 0.0;
	double step = 1.0;

	while (i < n) {
		double x1 = x + step * sampling_dist(gen);
		double y1 = y + step * sampling_dist(gen);
		double u0 = g(x,y);
		double u1 = g(x1,y1);
		double acceptance_crit = acc_dist(gen);
		if ( (u1 / u0) > acceptance_crit ) { 
			x = x1;
			y = y1;
			acc++;
		}
		tot += f1(x,y);
		i++;
	}
 
	std::cout << "The integral is \t" << pi * tot / n << std::endl;
	std::cout << "Acceptance ratio: \t" << acc / n << std::endl;
	std::cout << "Nn: \t\t" << n << std::endl << "---\n";

	return 0;
}
