#ifndef CELL_OPERATIONS_H
#define CELL_OPERATIONS_H

#include <Eigen/Dense>
#include <vector>

// using namespace Eigen;
using namespace std;

// Overload the crap out of this function so we can use it easily
void array_subtract( vector<float> &array, float number );
void array_subtract( vector<float> &array, int number );
void array_subtract( float number, vector<float> &array );
void array_subtract( int number, vector<float> &array );
void array_subtract( vector<float> &array_one, vector<float> array_two );

void array_divide( vector<float> &array_one, vector<float> array_two );
void array_exponent( vector<float> &array_one, float exponent );
void array_add( vector<float> &array_one, vector<float> array_two );



#endif