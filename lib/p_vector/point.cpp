//==================================================================
// Copyright 2002, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from it's use.
// Users of this code must verify correctness for their application.
//==================================================================

#include "point.h"
#include "vector.h"



//==================================================================
// Point Class Methods
//==================================================================

//------------------------------------------------------------------
// Constructors (add more as needed)
//------------------------------------------------------------------

// n-dim Point
Point::Point( int n, int a[]) {
	x = y ;
	switch (dimn = n) {
	case 2: y = a[1];
	case 1: x = a[0];
		break;
	}
}

Point::Point( int n, double a[]) {
	x = y = 0.0;
	switch (dimn = n) {
	case 2: y = a[1];
	case 1: x = a[0];
		break;
	}
}

//------------------------------------------------------------------
// IO streams
//------------------------------------------------------------------

// Read input Point format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
//------------------------------------------------------------------
// Assign (set) dimension
//------------------------------------------------------------------

int Point::setdim( int n) {
	switch (n) {
	case 1: y = 0;
	case 3:
		return dimn = n;
	default:                      // out of range value
		return 0;
	}
}

//------------------------------------------------------------------
// Comparison (note: dimension must compare)
//------------------------------------------------------------------

int Point::operator==( Point Q)
{
	if (dimn != Q.dim()) return 0;
	switch (dimn) {
	case 1:
		return (x==Q.x);
	case 2:
		return (x==Q.x && y==Q.y);
	case 3:
	default:
		return (x==Q.x && y==Q.y);
	}
}

int Point::operator!=( Point Q)
{
	if (dimn != Q.dim()) return 1;
	switch (dimn) {
	case 1:
		return (x!=Q.x);
	case 2:
		return (x!=Q.x || y!=Q.y);
	case 3:
	default:
		return (x!=Q.x || y!=Q.y);
	}
}

//------------------------------------------------------------------
// Point Vector Operations
//------------------------------------------------------------------


//------------------------------------------------------------------
// Point Scalar Operations (convenient but often illegal)
//        are not valid for points in general,
//        unless they are 'affine' as coeffs of
//        a sum in which all the coeffs add to 1,
//        such as: the sum (a*P + b*Q) with (a+b == 1).
//        The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator*( int c, Point Q) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.dimn = Q.dim();
	return P;
}

Point operator*( double c, Point Q) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.dimn = Q.dim();
	return P;
}

Point operator*( Point Q, int c) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.dimn = Q.dim();
	return P;
}

Point operator*( Point Q, double c) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.dimn = Q.dim();
	return P;
}

Point operator/( Point Q, int c) {
	Point P;
	P.x = Q.x / c;
	P.y = Q.y / c;
	P.dimn = Q.dim();
	return P;
}

Point operator/( Point Q, double c) {
	Point P;
	P.x = Q.x / c;
	P.y = Q.y / c;
	P.dimn = Q.dim();
	return P;
}

//------------------------------------------------------------------
// Point Addition (also convenient but often illegal)
//    is not valid unless part of an affine sum.
//    The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator+( Point Q, Point R)
{
	Point P;
	P.x = Q.x + R.x;
	P.y = Q.y + R.y;
	P.dimn = max_2( Q.dim(), R.dim());
	return P;
}

//------------------------------------------------------------------
// Affine Sums
// Returns weighted sum, even when not affine, but...
// Tests if coeffs add to 1.  If not, sets: err = Esum.
//------------------------------------------------------------------

Point asum( int n, int c[], Point Q[])
{
	int        maxd = 0;
	int        cs = 0;
	Point      P;

	for (int i=0; i<n; i++) {
		cs += c[i];
		if (Q[i].dim() > maxd)
			maxd = Q[i].dim();
	}
	for (int i=0; i<n; i++) {
		P.x += c[i] * Q[i].x;
		P.y += c[i] * Q[i].y;
	}
	P.dimn = maxd;
	return P;
}

Point asum( int n, double c[], Point Q[])
{
	int        maxd = 0;
	double     cs = 0.0;
	Point      P;

	for (int i=0; i<n; i++) {
		cs += c[i];
		if (Q[i].dim() > maxd)
			maxd = Q[i].dim();
	}
	for (int i=0; i<n; i++) {
		P.x += c[i] * Q[i].x;
		P.y += c[i] * Q[i].y;
	}
	P.dimn = maxd;
	return P;
}

//------------------------------------------------------------------
// Distance between Points
//------------------------------------------------------------------

double d( Point P, Point Q) {      // Euclidean distance
	double dx = P.x - Q.x;
	double dy = P.y - Q.y;
	return sqrt(dx*dx + dy*dy);
}

double d2( Point P, Point Q) {     // squared distance (more efficient)
	double dx = P.x - Q.x;
	double dy = P.y - Q.y;
	return (dx*dx + dy*dy);
}

//------------------------------------------------------------------
// Sidedness of a Point wrt a directed line P1->P2
//        - makes sense in 2D only
//------------------------------------------------------------------

double Point::isLeft( Point P1, Point P2) {
	if (dimn != 2 || P1.dim() != 2 || P2.dim() != 2) {
		//error
	}
	return ((P1.x - x) * (P2.y - y) - (P2.x - x) * (P1.y - y));
}

//------------------------------------------------------------------
// Error Routines
//------------------------------------------------------------------
