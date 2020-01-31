#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <pthread.h>
#include <random>

using namespace std;

#define NUM_THREADS 4

struct thread_data { // For passing argument to and from threads
	int thread_id;
	int pn_steps;
	double out;
	double acc_ratio;
};

void *partition_function(void *threadarg) {

// Initialize thread data
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
	long psteps = my_data->pn_steps;
	
// Initialize other variables
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> acc_dist(0.0,1.0);
	uniform_real_distribution<> sampling_dist(-1.0,1.0);
	double pi = 3.14159265358979;
	double x = sampling_dist(gen);
	double p = sampling_dist(gen);
	int i = 0;
	long steps = pow(10,psteps);
	double tot = 0.0;
	long accepted_moves = 0.0;
	double step = 1.5;

// metropolis MC
	while (i < steps) {
		double x1 = x + step * sampling_dist(gen);
		double p1 = p + step * sampling_dist(gen);
		double u0 = exp( -0.5 * p * p - 0.5 * x * x );
		double u1 = exp( -0.5 * p1 * p1 - 0.5 * x1 * x1 );
		double acceptance_crit = acc_dist(gen);
		if ( (u1 / u0) > acceptance_crit ) { 
			x = x1;
			p = p1;
			accepted_moves++;
		} 

		tot += 1.0; 
		i++;
	}

	double s = static_cast<double>(steps);
	double acc = static_cast<double>(accepted_moves);
	my_data->acc_ratio = acc / s;
	my_data->out = (2 * pi * tot / s); 	// Return the result of integration
	pthread_exit(NULL);
}

void *energy_distribution(void *threadarg) {

// Initialize thread data
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
	long psteps = my_data->pn_steps;
	
// Initialize other variables
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> acc_dist(0.0,1.0);
	uniform_real_distribution<> sampling_dist(-1.0,1.0);
	double pi = 3.14159265358979;
	double x = sampling_dist(gen);
	double p = sampling_dist(gen);
	int i = 0;
	long steps = pow(10,psteps);
	double tot = 0.0;
	long accepted_moves = 0.0;
	double step = 1.5;

// metropolis MC
	while (i < steps) {
		double x1 = x + step * sampling_dist(gen);
		double p1 = p + step * sampling_dist(gen);
		double u0 = exp( -0.5 * p * p - 0.5 * x * x );
		double u1 = exp( -0.5 * p1 * p1 - 0.5 * x1 * x1 );
		double acceptance_crit = acc_dist(gen);
		if ( (u1 / u0) > acceptance_crit ) { 
			x = x1;
			p = p1;
			accepted_moves++;
		} 
		tot += 0.5 * ( p * p + x * x ); 
		i++;
	}

	double s = static_cast<double>(steps);
	double acc = static_cast<double>(accepted_moves);
	my_data->acc_ratio = acc / s;
	my_data->out = (2 * pi * tot / s); 	// Return the result of integration
	pthread_exit(NULL);
}

int main () {

	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	int rc;
	int i;
	double numerator = 0.0;
	double denominator = 0.0;
	double pi = 3.14159265358979;

// Calculate the partition function

	for( i = 0; i < NUM_THREADS; i++ ) {
		td[i].thread_id = i;
		td[i].pn_steps = 7;
		rc = pthread_create(&threads[i], NULL, partition_function, (void *)&td[i]);
		
		if (rc) {
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
	
	for (int i = 0; i < NUM_THREADS; i++) { 
		pthread_join(threads[i], NULL);	
		denominator += td[i].out;
	}

	cout << "Total steps = " << NUM_THREADS * pow(10,td[0].pn_steps) << endl;

	denominator = denominator / NUM_THREADS;
	cout << "Z = " << denominator << endl;


// Calculate \int \int H exp(-beta H) dx dp
	for( i = 0; i < NUM_THREADS; i++ ) {
		td[i].thread_id = i;
		td[i].pn_steps = 7;
		rc = pthread_create(&threads[i], NULL, energy_distribution, (void *)&td[i]);
		
		if (rc) {
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
	
	for (int i = 0; i < NUM_THREADS; i++) { 
		pthread_join(threads[i], NULL);	
		numerator += td[i].out;
	}

	numerator = numerator / NUM_THREADS;
	cout << "<E> = " << numerator / denominator << endl;

	pthread_exit(NULL);
	return 0;
}




