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
	double x_l = (x - lower > sigma) ? x - sigma : upper;
	double x_r = (lower - x > sigma) ? x + sigma : upper;
	
	for(int i= 0;i < 10;i++)
	{
		while(true)
		{		
			if(f(x_r) >= y) 
			{
				double new_r = (x_l - x) * 2 + x;
				x_r = (new_r <= upper) ? new_r : upper;
				continue;
			}
			if(f(x_l) >= y)
			{
				double new_l = x - (x - x_l) * 2;
				x_l = (new_l >= lower) ? new_l : lower;
			} 
			break;
		}
		//cout << f(x_l) << " " << f(x_r) << " " << y << endl;
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
		x_l = (x - lower > sigma) ? x - sigma : upper;
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
	double sample[100];
	for(int i = 0;i < 100;i++)
	{
		sample[i] = slice_sampling(f, (-1) * (double) RAND_MAX / 10000, (double) RAND_MAX/ 10000, 100);
		cout << sample[i] << endl;
	}

	double avg = 0, var = 0;
	for(int i = 0;i < 100;i++)
		avg += sample[i];
	avg /= 100;
	for(int i = 0;i < 100;i++)
		var += (sample[i] - avg) * (sample[i] - avg);
	var /= 100;

	cout << "Mean: " << avg << ", Variance: " << var << endl;
}