#include <iostream>
#include <math.h>
#include <time.h>
#include <float.h>
#include <stdlib.h>
using namespace std;

double uniform(double lower, double upper)
{
	//srand (time(NULL));
	double x = rand();
	x = x * (upper - lower) / RAND_MAX + lower;
	//cout << x << endl;
	return x;
}

double slice_sampling(double (*f)(double), double lower, double upper, double sigma)
{
	double x, y = 0;
	while(y == 0)
	{
		x = uniform(lower, upper);	
		y = uniform(0, f(x));
	}
	double x_l = (x - lower > sigma) ? x - sigma : lower;
	double x_r = (lower - x > sigma) ? x + sigma : upper;
	
	int burnin = 5 + rand() % 10;
	for(int i = 0;i < burnin;i++)
	{		
		while (f(x_l) >= y)
		{
			double new_l = x - (x - x_l) * 2;
			if (new_l < lower)
			{
				x_l = lower;
				break;
			}
			x_l = new_l;
		} 
		while(f(x_r) >= y) 
		{
			double new_r = (x_r - x) * 2 + x;
			if (new_r > upper)
			{
				x_r = upper;
				break;
			}
			x_r = new_r;
		}
		while(true)
		{
			double new_x = uniform(x_l, x_r);
			if(f(new_x) > y)
			{
				x = new_x;
				break;
			}
		}
		y = uniform(0, f(x));	
		x_l = (x - lower > sigma) ? x - sigma : lower;
		x_r = (lower - x > sigma) ? x + sigma : upper;	
	}
	return x;
}

double f(double x)
{
	return exp((-0.5) * x * x);
}

int main()
{
	const int SIZE = 10000;
	double sample[SIZE];
	for(int i = 0;i < SIZE;i++)
	{
		sample[i] = slice_sampling(f, (-1) * (double) RAND_MAX / 10000, (double) RAND_MAX/ 10000, 10);
		//cout << sample[i] << endl;
	}

	double avg = 0, var = 0;
	for(int i = 0;i < SIZE;i++)
		avg += sample[i];
	avg /= SIZE;
	for(int i = 0;i < SIZE;i++)
		var += (sample[i] - avg) * (sample[i] - avg);
	var /= SIZE;

	cout << "Mean: " << avg << ", Variance: " << var << endl;
	cout << f(RAND_MAX) << endl;
}