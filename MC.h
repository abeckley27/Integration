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
	int64_t i;

	for (i = 0; i < n; i++) {
		double x = a + i * dx;
		if (f(x) > height) height = f(x);
	}

	if (height < 0.0) {
		
	}

	for (i = 0; i < n; i++) {
		double x = width * dist(gen) - a;
		double y = height * dist(gen);
		n_included += (y < f(x));
		if (y > height) height = y;
	}
	
	return double(n_included) * width * height / double(n);
}

double MCint_2d(const std::function<double(double, double)>& f, double a, double b, double c, double d, int64_t n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0.0,1.0);
	double width = b - a;
	double length = d - c;
	double height = -0.1;
	double dx = width / n;
	double dy = length / n;
	int64_t n_included = 0;
	int64_t i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			double x = a + i * dx;
			double y = c + j * dy;
			if (f(x, y) > height) height = f(x, y);
		}
	}

	if (height < 0.0) {
		
	}

	for (i = 0; i < n; i++) {
		double x = width * dist(gen) - a;
		double y = length * dist(gen) - c;
		double z = height * dist(gen);
		n_included += (y < f(x, y));
		if (y > height) height = y;
	}
	
	return double(n_included) * width * height / double(n);
}

