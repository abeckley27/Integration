#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <random>

using namespace std;

// Sampling distribution
double g(double x, double y) { return exp(-1 * x * x - y * y ) ; }

double f1(double x, double y) { return x * x * y * y; }


// Todo: extend to n-dimensional integrals
int main() {

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> acc_dist(0.0,1.0);
	uniform_real_distribution<> sampling_dist(-1.0,1.0);
	double pi = 3.14159265358979;

	double x = sampling_dist(gen);
	double y = sampling_dist(gen);
	int i = 0;
	int p = 7;
	int steps = pow(10,p);
	double tot = 0.0;
	double acc = 0.0;
	double step = 1.0;

	while (i < steps) {
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
 
	cout << "The integral is \t" << pi * tot / steps << endl;
	cout << "Acceptance ratio: \t" << acc / steps << endl;
	cout << "Nsteps: \t\t" << steps << endl << "---\n";

	return 0;
}
