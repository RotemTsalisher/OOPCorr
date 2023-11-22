#include "Mat.h"

void Mat::initDemo()
{
	n = 4;
	m = 4;

	mat[ 0] = 1;
	mat[ 1] = 0;
	mat[ 2] = 0;
	mat[ 3] = 0;
	mat[ 4] = 0;
	mat[ 5] = 1;
	mat[ 6] = 1;
	mat[ 7] = 0;
	mat[ 8] = 1;
	mat[ 9] = 0;
	mat[10] = 0;
	mat[11] = 1;
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1;
}
void Mat::initZero(const int n, const int m)
{
	memset(mat, 0, sizeof(int) * (n * m));
}
void Mat::initDistMask(const int k)
{
	int i, j;
	n = (k << 1) + 1;
	m = (k << 1) + 1;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (k >= calcDist(j, i, k, k))
			{
				*(mat + m * i + j) = 1;
			}
			else
			{
				*(mat + m * i + j) = 0;
			}
		}
	}
}
const float Mat::calcDist(const int a, const int b, const int c, const int d)
{
	return (sqrt(pow((c - a), 2) + pow((d - b), 2)));
}
void Mat::initVals(const int n, const int m)
{
	int i, j;

	cout << "Enter valse for " << n << "x" << m << " matrix:" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << "enter val for (" << j << "," << i << "} = ";
			cin >> *(mat + m * i + j);
		}
	}
}
void Mat::set_dim(const int n, const int m)
{
	this->n = n;
	this->m = m;
}
void Mat::printMat()
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << "[" << *(mat + m * i + j) << "]";
		}
		cout << endl;
	}
}
Mat::Mat(const initMat init, const int n, const int m)
{
	this->n = n;
	this->m = m;

	switch (init)
	{
		case INIT_DEMO:
			initDemo();
			break;
		case INIT_DIST_MASK:
			int k;
			cout << "Enter k = ";
			cin >> k;
			initDistMask(k);
			break;
		case INIT_VALS:
			initVals(n, m);
			break;
		case INIT_ZERO:
			initZero(n, m);
			break;
		case INIT_NONE:
		default:
			break;
	}
}
Mat::Mat(const Mat& other, const int xpad, const int ypad)
{
	int i, j;
	this->n = (other.n + (ypad<<1));
	this->m = (other.m + (xpad<<1));

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if ((i<ypad) || (j < xpad) || (i > (other.n - 1) + ypad) || (j > (other.m - 1) + xpad))
			{
				*(this->mat + this->m * i + j) = 0;
			}
			else
			{
				*(this->mat + this->m * i + j) = *(other.mat + other.m * (i - ypad) + (j - xpad));
			}

		}
	}
}
int Mat::wSum(const Mat& other, int xOffset, int yOffset) 
{
	int sum, i, j, xdim, ydim;

	ydim = (other.n < this->n) ? other.n : this->n;
	xdim = (other.m < this->m) ? other.m : this->m;

	sum = 0;
	for (i = 0; i < ydim; i++)
	{
		for (j = 0; j < xdim; j++)
		{
			sum += ((*(this->mat + this->m * (i + yOffset) + (j + xOffset))) * (*(other.mat + other.m * i + j)));
		}
	}

	return sum;
}
Mat* Mat::corr(const Mat& other)
{
	int i, j, xpad,ypad;
	xpad = (other.m - 1) >> 1;
	ypad = (other.n - 1) >> 1;
	Mat paddedMat(*this, xpad, ypad);
	Mat corrMat(INIT_NONE, this->n, this->m);
	
	for (i = 0; i < this->n; i++)
	{
		for (j = 0; j < this->m; j++)
		{
			corrMat.setVal(paddedMat.wSum(other,j,i), j, i);
		}
	} 
	return &corrMat;

}
void Mat::occupiedSpots(const Mat& other)
{
	int i, j, xdim, ydim;

	ydim = (this->n <= other.n) ? this->n : other.n;
	xdim = (this->m <= other.m) ? this->m : other.m;

	for (i = 0; i < ydim; i++)
	{
		for (j = 0; j < xdim; j++)
		{
			if (1 == *(other.mat + other.m * i + j))
			{
				*(this->mat + this->m * i + j) = 0;
			}
		}
	}
}
const int Mat::findMax()
{
	int max, i, j;
	max = *mat;
	for (i = 0; i < n; i++)
	{
		for (j = 1; j < m; j++)
		{
			if (*(mat + m * i + j) > max)
			{
				max = *(mat + m * i + j);
			}
		}
	}
	return max;
}