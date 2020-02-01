#include <iostream>
#include <fstream>
#include <cmath>
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

const int64_t N = 1000000;

int main() {

	// Monte Carlo integration (not metropolis)
	double x[5];
	cout << MCint_1d(&a1, 0.0, 1.0, N) << endl;
	cout << MCint_1d(&a2, 0.0, 1.0, N) << endl;
	cout << MCint_1d(&a3, 0.0, 1.0, N) << endl;
	cout << MCint_1d(&a3, 0.0, 2.0, N) << endl;
	cout << MCint_1d(&a5, 0.0, 3.14159265358979, N) << endl;


	
}