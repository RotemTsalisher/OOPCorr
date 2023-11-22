#pragma once
#include <iostream>
#include "math.h"
using namespace std;

#define MAX_MAT_SIZE    1000
#define DIM_ARRAY_SIZE  2

typedef enum {
	INIT_DEMO       = 0x00,
	INIT_ZERO       = 0x01,
	INIT_VALS       = 0x02,
	INIT_DIST_MASK  = 0x03,

	INIT_NONE       = 0xFF
}initMat;

class Mat {
private:
	int n, m;
	int mat[MAX_MAT_SIZE];

	void initDemo();
	void initZero(const int n, const int m);
	void initVals(const int n, const int m);
	void initDistMask(const int k);
	const float calcDist(const int a, const int b, const int c, const int d);

public:
	void set_dim(const int n, const int m);
	void printMat();
	const int get_n() { return this->n; };
	const int get_m() { return this->m; };
	Mat(const initMat init = INIT_DEMO, const int n = 0, const int m = 0);
	Mat(const Mat& other, const int xpad = 0, const int ypad = 0);
	int wSum(const Mat& other, int xOffset = 0, int yOffset = 0);
	void setVal(int val, int j, int i) { *(mat + m * i + j) = val; };
	Mat* corr(const Mat& other);
	void occupiedSpots(const Mat& other);
	const int findMax();
};