#ifndef RANDUTILS
#define RANDUTILS
#include "mex.h"
#include <math.h>
#ifdef _WIN32

#define _CRT_RAND_S
#include <stdlib.h>

double drand48()
{
	/*
	 Returns a random number in [0.0, 1.0)
	 http://man7.org/linux/man-pages/man3/drand48.3.html
	 */
	return (double)rand() / (RAND_MAX + 1);
	//unsigned ui;
	//rand_s(&ui);
	//return (double)ui / ((double)UINT_MAX + 1);
}

#else

#include <stdlib.h>

#endif

double max_element(const double * x, int n, int* argmax)
{
	*argmax = 0;
	double max_val = x[0];
	for (int i = 1; i < n; i++)
		if (x[i] > max_val)
		{
			max_val = x[i];
			*argmax = i;
		}
	return max_val;
}

/**
 * given log(a) and log(b), return log(a + b)
 *
 */

double log_sum(double log_a, double log_b)
{
	double v;

	if (log_a < log_b)
		v = log_b + log(1 + exp(log_a - log_b));
	else
		v = log_a + log(1 + exp(log_b - log_a));
	return v;
}


// give a_1, ..., a_n,
// return log(exp(a_1)+...+exp(a_n))
double log_normalize(double * array, int nlen)
{
	const double log_max = 100.0; // the log(maximum in double precision), make sure it is large enough.
	int argmax;
	double max_val = max_element(array, nlen, &argmax); //get the maximum value in the array to avoid overflow
	double log_shift = log_max - log(nlen + 1.0) - max_val;
	double sum = 0.0;
	for (int i = 0; i < nlen; i++)
		sum += exp(array[i] + log_shift); //shift it

	double log_norm = log(sum) - log_shift;
	for (int i = 0; i < nlen; i++)
		array[i] -= log_norm; //shift it back

	return log_norm;
}


/**
 * given log(a) and log(b), return log(a - b) a>b
 *
 */

double log_subtract(double log_a, double log_b)
{
	if (log_a < log_b) return -1000.0;

	double v;
	v = log_a + log(1 - exp(log_b - log_a));
	return v;
}


double randgamma(double rr)
{
	double aa, bb, cc, dd;
	double uu, vv, ww, xx, yy, zz;

	if (rr <= 0.0)
	{
		/* Not well defined, set to zero and skip. */
		return 0.0;
	}
	else if (rr == 1.0)
	{
		/* Exponential */
		return -log(drand48());
	}
	else if (rr < 1.0)
	{
		/* Use Johnks generator */
		cc = 1.0 / rr;
		dd = 1.0 / (1.0 - rr);
		while (1)
		{
			xx = pow(drand48(), cc);
			yy = xx + pow(drand48(), dd);
			if (yy != 0 && !isnormal(yy))
				yy = yy;
			if (yy <= 1.0)
			{
				return -log(drand48()) * xx / yy;
			}
		}
	}
	else
	{ /* rr > 1.0 */
		/* Use bests algorithm */
		bb = rr - 1.0;
		cc = 3.0 * rr - 0.75;
		while (1)
		{
			uu = drand48();
			vv = drand48();
			ww = uu * (1.0 - uu);
			yy = sqrt(cc / ww) * (uu - 0.5);
			xx = bb + yy;
			if (xx >= 0)
			{
				zz = 64.0 * ww * ww * ww * vv * vv;
				if (zz != 0 && !isnormal(zz))
					zz = zz;
				if ((zz <= (1.0 - 2.0 * yy * yy / xx)) ||
					(log(zz) <= 2.0 * (bb * log(xx / bb) - yy)))
				{
					return xx;
				}
			}
		}
	}
}

int randnumtable(double alpha, int numdata)
{
	int ii, numtable;

	if (numdata == 0)
	{
		return 0;
	}
	else
	{
		numtable = 1;
		for (ii = 1; ii < numdata; ii++)
		{
			if (drand48() < alpha / (ii + alpha)) numtable++;
		}
		return numtable;
	}
}

void randdir(double *pi, double *alpha, int veclength, int skip)
{
	double *pi2, *piend;
	double sum;

	sum = 0.0;
	piend = pi + veclength*skip;
	for (pi2 = pi; pi2 < piend; pi2 += skip)
	{
		sum += *pi2 = randgamma(*alpha);
		alpha += skip;
	}
	for (pi2 = pi; pi2 < piend; pi2 += skip)
	{
		*pi2 /= sum;
	}
}

double randbeta(double aa, double bb)
{
	aa = randgamma(aa);
	bb = randgamma(bb);
	return aa / (aa + bb);
}

int randmult(double *pi, int veclength, int skip)
{
	double *pi2, *piend;
	double sum = 0.0, mass;
	int cc = 0;

	piend = pi + veclength*skip;
	for (pi2 = pi; pi2 < piend; pi2 += skip)
		sum += *pi2;
	if (sum != 0 && !isnormal(sum))
		sum = sum;
	mass = drand48() * sum;
	while (pi < piend)
	{
		mass -= *pi;
		if (mass <= 0.0) break;
		pi += skip;
		cc++;
	}
	return cc;
}

int randuniform(int numvalue)
{
	return floor(drand48() * numvalue);
}

double randconparam(double alpha, int numgroup, int *numdata, int *numtable,
	double alphaa, double alphab, int numiter)
{
	int iter, jj, nd, zz;
	double aa, bb, xx;
	for (iter = 0; iter < numiter; iter++)
	{
		aa = alphaa;
		bb = alphab;
		for (jj = 0; jj < numgroup; jj++)
		{
			nd = numdata[jj];
			xx = randbeta(alpha + 1.0, nd);
			zz = (drand48() * (alpha + nd) < nd);

			aa += numtable[jj] - zz;
			bb -= log(xx);
		}
		alpha = randgamma(aa) / bb;
	}
	return alpha;
}

#endif
