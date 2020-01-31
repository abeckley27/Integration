#include <iostream>
#include <fstream>
#include <omp.h>
#include <Eigen/Dense>
#include "basis.h"
#include "nquad.h"
#include "tensor.h"
#include "MC.h"

using namespace std;

double test_gaussian(double x, double y, double z) {
	double r2 = x * x + y * y + z * z;
	return exp(-0.4 * r2);
}

double phi(double* x, int nGF, double* c, double* a) {

}

int main(int argc, char* argv[]) {

	double t0 = omp_get_wtime();

	// load from basis set
	double coeff[3] = { 0.444635, 0.535328, 0.154329 };
	double alpha[3] = { 0.168856, 0.623913, 3.42525 };
	double zeta = 1.24;

	// load from coordinates
	double R1[3] = { 0.0, 0.0, 0.0 };
	double R2[3] = { 0.0, 0.0, 1.4 };

	double box[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
	const int num_intervals = 200;
	const int num_electrons = 2;
	int num_bf = 3;	
	int i, j, k;

	double rmin = 0.0;
	double rmax = 10.0;
	double b[6] = {-10.0, 10.0, -10.0, 10.0, -10.0, 10.0};
	int array_size = 100;

// radial-only calculation
	double* r = new double[array_size];
	for (i = 0; i < array_size; i++) { r[i] = rmin + i * ( (rmax - rmin) / (array_size - 1) ); }
	double* phi_1s = eval_lcgf(rmin, rmax, array_size, num_bf, coeff, alpha);

// test basis functions by writing to file
	ofstream f;
	f.open("test_basis.tsv");
	f << 'r' << '\t' << "phi" << endl;
	for (i = 0; i < array_size; i++) { f << r[i] << '\t' << phi_1s[i] << endl; }
	f << endl;
	f.close();

	// integrand arrays, including 4 pi r^2 volume element
	double* s11 = new double[array_size];
	double* s12 = new double[array_size];

	Eigen::MatrixXd S(num_electrons, num_electrons);
	Eigen::MatrixXd T(num_electrons, num_electrons);
	Eigen::MatrixXd V(num_electrons, num_electrons);
	Eigen::MatrixXd V1(num_electrons, num_electrons);
	Eigen::MatrixXd V2(num_electrons, num_electrons);
	Eigen::MatrixXd H(num_electrons, num_electrons);
	Eigen::MatrixXd F(num_electrons, num_electrons);

	for (i = 0; i < array_size; i++) { s11[i] = 4.0 * pi * pow(r[i] * phi_1s[i], 2); }
// ^easy one. 
// Now we have to do triple integrals.

	tensor3 phi1(array_size, array_size, array_size, lcgf_cart, 3, R1, b, coeff, alpha);
	tensor3 phi2(array_size, array_size, array_size, lcgf_cart, 3, R2, b, coeff, alpha);
	// maybe create another one for r^2 values.

	// test multiplying phi1 & phi2, then try integrating the product
	tensor3 phi11 = phi1 * phi1;
	tensor3 phi12 = phi1 * phi2;
	
	S(0, 0) = n_MCint(lcgf_mc, lcgf_mc, 3, 1000000, num_bf, coeff, alpha);
	S(0, 1) = n_MCint(lcgf_mc, lcgf_mc, 3, 1000000, num_bf, coeff, alpha);

	cout << S(0, 0) << endl;
	
	//S(1, 0) = triple_integrate(phi12, b, array_size);
	//S(1, 1) = triple_integrate(phi11, b, array_size);
	
	double t1 = omp_get_wtime();
	cout << "\nTime: " << t1 - t0 << " s\n";

}



