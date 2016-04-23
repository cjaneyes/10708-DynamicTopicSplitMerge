#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <random>

using namespace std;

mt19937_64 gen;
inline double uniform(double a, double b)
{
	uniform_real_distribution<double> ug(a, b);
	return ug(gen);
}

double slice_sampling(double(*f)(double, int, double, double *, double, double, double *, int), double lower, double upper, double sigma, int index, double sum, double * lambda_k, double alphak, double beta_k, double *old_beta, int old_numclass)
{
	double x, y = 0;
	while(y == 0)
	{
		x = uniform(lower, upper);	
		y = uniform(0, f(x, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass));
		cout << y << endl;
	}
	double x_l = (x - lower > sigma) ? x - sigma : lower;
	double x_r = (lower - x > sigma) ? x + sigma : upper;
	
	for(int i= 0;i < 10;i++)
	{

		for (int i = 0; i < 10; i++)
		{
			while (f(x_l, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass) >= y)
			{
				double new_l = x - (x - x_l) * 2;
				if (new_l < lower)
				{
					x_l = lower;
					break;
				}
				x_l = new_l;
			}
			while (f(x_r, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass) >= y)
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
		//cout << f(x_l, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass) << " " << f(x_r, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass) << " " << y << endl;
		while(true)
		{
			double new_x = uniform(x_l, x_r);
			if(f(new_x, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass) > y)
			{
				x = new_x;
				break;
			}
		}
		y = uniform(0, f(x, index, sum, lambda_k, alphak, beta_k, old_beta, old_numclass));	
		x_l = (x - lower > sigma) ? x - sigma : lower;
		x_r = (lower - x > sigma) ? x + sigma : upper;	
	}
	return x;
}

/***************************************************************************/
double f(double sample, int index, double sum, double * lambda_k, double alphak, double beta_k, double *old_beta, int old_numclass)
{
    double res = 1;
    for(int kk = 0;kk < old_numclass;kk++)
    {
        if(kk == index) res *= pow((sample/(sample + sum)), (alphak-1)) * pow(beta_k, (old_beta[kk]*(sample/(sample + sum))));
        else res *= pow((lambda_k[kk]/(sample + sum)), (alphak-1)) * pow(beta_k, (old_beta[kk]*(lambda_k[kk]/(sample + sum))));
    }
    return res;
}