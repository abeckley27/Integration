#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <random>
#include <cstdint>

double MCint_1d(std::function<double(double)> f, double a, double b, int64_t n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0.0,1.0);
	double width = b - a;
	double height = 0.0;
	int64_t n_included = 0;
	int64_t i, j;

	for (i = 0; )

	for (i = 0; i < n; i++) {
		double x = width * dist(gen) - b;
		double y = f(x);
		if (y > height) height = y;
		n_included += ()
	}
}



