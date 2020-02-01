#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <random>
#include <cstdint>

double MCint_1d(const std::function<double(double)>& f, double a, double b, int64_t n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0.0,1.0);
	double width = b - a;
	double height = -0.1;
	double dx = width / n;
	int64_t n_included = 0;
	int64_t i, j;

	for (i = 0; i < n; i++) {
		double x = b + i * dx;
		if (f(x) > height) height = f(x);
	}

	if (height < 0.0) {

	}

	for (i = 0; i < n; i++) {
		double x = width * dist(gen) - b;
		double y = height * dist(gen);
		if (y > height) height = y;
		n_included += (y < height);
	}
	
	return double(n_included) * width * height / double(n);
}



