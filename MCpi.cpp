#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>

using namespace std;

int main() {

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dist(0.0,0.999999);

	for (int pn = 2; pn <= 8; pn += 2) {
		long double count = 0.0;
		long i = 0;	
		long double n = pow(10,pn);

		while ( i < n ) {
			double x = dist(gen);
			double y = dist(gen);
			if (x*x + y*y < 1) { count++; }
			i++;
		}
	cout << "N = \t10^" << pn << endl;
	cout << "Pi = \t" << setprecision(6) << (4 * count / n) << endl << "---" << endl;
	}

	return 0;
}
