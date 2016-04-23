#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <cassert>
#include <limits.h>
#include <conio.h>

using namespace std;

mt19937_64 gen;

inline double uniform(double a, double b)
{
	uniform_real_distribution<double> ug(a, b);
	return ug(gen);
}

double slice_sampling(double(*f)(double), double lower, double upper, double sigma)
{
	double x, y = 0;
	while(y == 0)
	{
		x = uniform(lower, upper);	
		y = uniform(0, f(x));
		//cout << y << endl;
	}
	double x_l = (x - lower > sigma) ? x - sigma : lower;
	double x_r = (lower - x > sigma) ? x + sigma : upper;
	
	for(int i= 0;i < 10;i++)
	{

		for (int i = 0; i < 10; i++)
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
			while (f(x_r) >= y)
			{
				double new_r = (x_r - x) * 2 + x;
				if (new_r > upper)
				{
					x_r = upper;
					break;
				}
				x_r = new_r;
			}
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

	assert(gen.min() == 0);
	int n = 10000;
	vector<double> sample(n);
	for(int i = 0;i < n;i++)
	{
		sample[i] = slice_sampling(f, -1e2, 1e2, 100);
		cout << sample[i] << endl;
	}

	auto &v = sample;
	double sum = accumulate(v.begin(), v.end(), 0.0);
	double mean = sum / v.size();

	vector<double> diff(v.size());
	transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / v.size());
	cout << "mean: " << mean << ", stdev: " << stdev << endl;
	//_getch();
	return 0;
}