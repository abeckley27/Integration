#pragma once

#include <cmath>
#include <functional>

double integrate(double* y, double a, double b, int n) {
	double output = 0.0;
	double dx = (b - a) / (n - 1);
	
	for (int i = 0; i < n; i++) { output += ((y[i] + y[i + 1]) * dx) / 2.0; }
	return output;
}
/*
 double*** create(std::function<double(double, double, double)> f, double* bounds, int num_intervals) {
	int i, j, k;
	double dx[3];
	for (i = 0; i < 3; i++) { dx[i] = (bounds[2 * i + 1] - bounds[2 * i]) / (num_intervals - 1); }

	double** x = new double*[3];
	for (i = 0; i < 3; i++) { x[i] = new double[num_intervals + 1]; }
	for (i = 0; i < 3; i++) {
		for (j = 0; j <= num_intervals; j++) { x[i][j] = bounds[i / 2] + dx[i] * j; }
	}

	double*** f_vals = new double**[num_intervals + 1];
	for (i = 0; i <= num_intervals; i++) {
		f_vals[i] = new double*[num_intervals + 1];
		for (j = 0; j <= num_intervals; j++) {
			f_vals[i][j] = new double[num_intervals + 1];
		}
	}

	for (i = 0; i <= num_intervals; i++) {
		for (j = 0; j <= num_intervals; j++) {
			for (k = 0; k <= num_intervals; k++) {
				f_vals[i][j][k] = f(x[0][i], x[1][j], x[2][k]);
			}
		}
	}

	for (i = 0; i < 3; i++) { delete[] x[i]; }
	delete[] x;

	return f_vals;
}
*/

double triple_integrate(double*** f_vals, double* bounds, int num_intervals) {
	double output = 0.0;
	double dx[3];
	int i, j, k, l;
	for (i = 0; i < 3; i++) { dx[i] = (bounds[2 * i + 1] - bounds[2 * i]) / (num_intervals - 1); }

	for (i = 0; i < num_intervals; i++) {
		for (j = 0; j < num_intervals; j++) {
			for (k = 0; k < num_intervals; k++) {
				double corners = 0.0;
				for (l = 0; l < 8; l++) {
					corners += f_vals[i + (l / 4)][j + ((l % 4) / 2)][k + (l % 2)];
				}
				output +=  (corners * dx[0] * dx[1] * dx[2] / 8.0);
			}
		}
	}

	return output;
}

double n_quad(std::function<double(double*)> f, double* bounds, int ndim, int num_intervals) {
	double output = 0.0;
	double* dx = new double[ndim];
	int i;

	for (i = 0; i < ndim; i++) { dx[i] = (bounds[2 * i + 1] - bounds[2 * i]) / (num_intervals - 1); }

	return 0.0;

}

