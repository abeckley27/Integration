#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdint>
#include "nquad.h"
#include "MC.h"
#include "metropolisMC.h"

using namespace std;

// test (mathematical) functions
const double a1(double x) { return x*x; }
const double a2(double x) { return pow(x,3); }
const double a3(double x) { return sqrt(x); }
const double a4(double x) { return exp(x); }
const double a5(double x) { return -1.0 * cos(x); }
const double a6(double x) { return exp(-1.0 * x * x); }

const int64_t N = 2000000;

int main() {

	clock_t t0 = clock();

	// Monte Carlo integration (not metropolis)
	double x[5];
	cout << MCint_1d(&a1, 0.0, 1.0, N) << endl;
	cout << MCint_1d(&a2, 0.0, 1.0, N) << endl;
	cout << MCint_1d(&a3, 0.0, 1.0, N) << endl;
	cout << MCint_1d(&a3, 0.0, 2.0, N) << endl;
	cout << MCint_1d(&a5, 0.0, 3.14159265358979, N) << endl;
	cout << "MC integration time: " << (double(clock()) - double(t0)) / CLOCKS_PER_SEC << endl;

	clock_t t1 = clock();
	cout << mmc_1d(&a6, N) << endl;

	cout << "metropolis integration time: " << (double(clock()) - double(t1)) / CLOCKS_PER_SEC << endl;
}