#include "Mat.h"

void main()
{
	Mat m1(INIT_ZERO,3,4); 
	Mat m2(INIT_DIST_MASK);
	Mat* corrMat;

	corrMat = m1.corr(m2);

	cout << "matrix m1:" << endl;
	m1.printMat();
	cout << "matrix m2:" << endl;
	m2.printMat();
	cout << "corr matrix:" << endl;
	corrMat->printMat();
	corrMat->occupiedSpots(m1);
	cout << "corr matrix with 0 at occupoed spots: " << endl;
	corrMat->printMat();
	cout << "corr max = " << corrMat->findMax();
}