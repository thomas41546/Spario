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
// Vector Class Methods
//==================================================================

//------------------------------------------------------------------
//  Unary Ops
//------------------------------------------------------------------

// Unary minus
Vector Vector::operator-() {
	Vector v;
	v.x = -x; v.y = -y;
	v.dimn = dimn;
	return v;
}

// Unary 2D perp operator
Vector Vector::operator~() {
	Vector v;
	v.x = -y; v.y = x;
	v.dimn = dimn;
	return v;
}

//------------------------------------------------------------------
//  Scalar Ops
//------------------------------------------------------------------

// Scalar multiplication
Vector operator*( int c, Vector w ) {
	Vector v;
	v.x = c * w.x;
	v.y = c * w.y;
	v.dimn = w.dim();
	return v;
}

Vector operator*( double c, Vector w ) {
	Vector v;
	v.x = c * w.x;
	v.y = c * w.y;
	v.dimn = w.dim();
	return v;
}

Vector operator*( Vector w, int c ) {
	Vector v;
	v.x = c * w.x;
	v.y = c * w.y;
	v.dimn = w.dim();
	return v;
}

Vector operator*( Vector w, double c ) {
	Vector v;
	v.x = c * w.x;
	v.y = c * w.y;
	v.dimn = w.dim();
	return v;
}

// Scalar division
Vector operator/( Vector w, int c ) {
	Vector v;
	v.x = w.x / c;
	v.y = w.y / c;
	v.dimn = w.dim();
	return v;
}

Vector operator/( Vector w, double c ) {
	Vector v;
	v.x = w.x / c;
	v.y = w.y / c;
	v.dimn = w.dim();
	return v;
}

//------------------------------------------------------------------
//  Arithmetic Ops
//------------------------------------------------------------------

Vector Vector::operator+( Vector w ) {
	Vector v;
	v.x = x + w.x;
	v.y = y + w.y;
	v.dimn = max_2( dimn, w.dim());
	return v;
}

Vector Vector::operator-( Vector w ) {
	Vector v;
	v.x = x - w.x;
	v.y = y - w.y;
	v.dimn = max_2( dimn, w.dim());
	return v;
}

//------------------------------------------------------------------
//  Products
//------------------------------------------------------------------

// Inner Dot Product
double Vector::operator*( Vector w ) {
	return (x * w.x + y * w.y);
}

// 2D Exterior Perp Product
double Vector::operator|( Vector w ) {
	return (x * w.y - y * w.x);
}

//------------------------------------------------------------------
//  Shorthand Ops
//------------------------------------------------------------------

Vector& Vector::operator*=( double c ) {        // vector scalar mult
	x *= c;
	y *= c;
	return *this;
}

Vector& Vector::operator/=( double c ) {        // vector scalar div
	x /= c;
	y /= c;
	return *this;
}

Vector& Vector::operator+=( Vector w ) {        // vector increment
	x += w.x;
	y += w.y;
	dimn = max_2(dimn, w.dim());
	return *this;
}

Vector& Vector::operator-=( Vector w ) {        // vector decrement
	x -= w.x;
	y -= w.y;
	dimn = max_2(dimn, w.dim());
	return *this;
}

//------------------------------------------------------------------
//  Special Operations
//------------------------------------------------------------------
double Vector::dot(Vector w){
       return x*w.x + y*w.y;
}
double Vector::length(){
       return sqrt(x*x + y*y);
}

double Vector::lengthSquared(){
       return (x*x + y*y);
}
Vector Vector::setLength(double a){
        Vector v;
        v.x = x;
        v.y = y;
        v *= a / sqrt(x*x + y*y);
        return v;
}
bool Vector::inside(Vector c1,Vector c2){
     if ((x >= c1.x and x <= c2.x) || (x >= c2.x and x <= c1.x)){
            if((y >= c1.y and y <= c2.y)||(y >= c2.y and y <= c1.y)){
                return true;
            }
     }
     return false;
}

void Vector::normalize() {                      // convert to unit length
	double ln = sqrt( x*x + y*y );
	if (ln == 0) return;                    // do nothing for nothing
	x /= ln;
	y /= ln;
}

void Vector::concate(Vector lower, Vector upper){ //inclusive
       x = (lower.x < x) ? lower.x  : x;
       y = (lower.y < y) ? lower.y  : y;
       
       x = (x > upper.x) ? upper.x : x;
       y = (y > upper.x) ? upper.y : y;
}

void Vector::apply_ceil(){
       x = ceil(x);
       y = ceil(y);
}
void Vector::apply_abs(){
       x = abs_2(x);
       y = abs_2(y);
}


Vector sum( int n, int c[], Vector w[] ) {     // vector sum
	int     maxd = 0;
	Vector  v;

	for (int i=0; i<n; i++) {
		if (w[i].dim() > maxd)
			maxd = w[i].dim();
	}
	v.dimn = maxd;

	for (int i=0; i<n; i++) {
		v.x += c[i] * w[i].x;
		v.y += c[i] * w[i].y;
	}
	return v;
}

Vector sum( int n, double c[], Vector w[] ) {  // vector sum
	int     maxd = 0;
	Vector  v;

	for (int i=0; i<n; i++) {
		if (w[i].dim() > maxd)
			maxd = w[i].dim();
	}
	v.dimn = maxd;

	for (int i=0; i<n; i++) {
		v.x += c[i] * w[i].x;
		v.y += c[i] * w[i].y;
	}
	return v;
}
