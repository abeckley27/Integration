#pragma once
#include <iostream>
#include <cmath>
#include <random>
#include <functional>

// sampling function
double g(double* x,int n) {
	double r = 0;
	for (int i = 0; i < n; i++) { r += pow(x[i],2); }
	return exp(-1*r);
}

double n_MCint(std::function<double(double*, int, double*, double*)> f, std::function<double(double*, int, double*, double*)> g, 
										int ndim, int steps, int nGF, double* c, double* a) {

	double pi = 3.141592653589793;
	int i, j, k;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> acc_dist(0.0, 1.0);
	std::uniform_real_distribution<> sampling_dist(-1.0, 1.0);

	double tot = 0.0;
	double acc = 0.0;
	double step = 2.0 / sqrt(ndim);

	double* x = new double[ndim];
	double* x1 = new double[ndim];
	double* xptr = NULL;

	for (i = 0; i < ndim; i++) { x[i] = sampling_dist(gen); }
	i = 0;

	//std::cout << "starting random walk\n";

	while (i < steps) {
		//std::cout << "i = " << i << std::endl;
		for (j = 0; j < ndim; j++) { x1[j] = x[j] + step * sampling_dist(gen); }
		double u0 = g(x, nGF, c, a);
		double u1 = g(x1, nGF, c, a);
		double acceptance_crit = acc_dist(gen);	
		
		if ( (u1 / u0) > acceptance_crit ) { 
			for (k = 0; k < ndim; k++) { x[k] = x1[k]; }
			acc++;
		}
		tot += f(x, ndim, c, a);
		i++;
	}

	delete[] x;
	delete[] x1;

	return sqrt(pow(pi,ndim)) * tot / steps;
}

