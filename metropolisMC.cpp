#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>

using namespace std;

double g(double x) { return exp(-1 * x * x ); }

double f1(double x) { return x*x; }
double f2(double x) { return cos(10*x*x); }


int main() {

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> acc_dist(0.0,1.0);
	uniform_real_distribution<> sampling_dist(-1.0,1.0);
	double pi = 3.14159265358979;
	cout << "Part a:" << endl;

	for (int p = 2; p<=8; p += 2) {

		double x = sampling_dist(gen);
		int i = 0;
		int steps = pow(10,p);
		double tot = 0.0;
		double acc = 0.0;
		double step = 2.08;

		while (i < steps) {
			double x1 = x + step * sampling_dist(gen);
			double u0 = g(x);
			double u1 = g(x1);
			double acceptance_crit = acc_dist(gen);
			if ( (u1 / u0) > acceptance_crit ) { 
				x = x1;
				acc++;
			}
			tot += f1(x);
			i++;
		}
 
		cout << "The integral is \t" << sqrt(pi) * tot / steps << endl;
		cout << "Acceptance ratio: \t" << acc / steps << endl;
		cout << "Nsteps: \t\t" << steps << endl << "---\n";
	}

	cout << "Part b:\n";


	for (int p = 2; p<=8; p += 2) {

		int i = 0;
		int steps = pow(10,p);
		double tot = 0.0;
		double acc = 0.0;
		double step = 2.08;
		double x = sampling_dist(gen);

		while (i < steps) {
			double x1 = x + step * sampling_dist(gen);
			double u0 = g(x);
			double u1 = g(x1);
			double acceptance_crit = acc_dist(gen);
			if ( (u1 / u0) > acceptance_crit ) { 
				x = x1;
				acc++;
			}
			tot += f2(x);
			i++;
		} 
		cout << "The integral is \t" << sqrt(pi) * tot / steps << endl;
		cout << "Acceptance ratio: \t" << acc / steps << endl;
		cout << "Nsteps: \t\t" << steps << endl << "---\n";
	}


	return 0;
}
