/*
* @Author: john
* @Date:   2016-05-22 10:44:22
* @Last Modified by:   john
* @Last Modified time: 2016-05-22 15:03:25
*/

#include <math.h>
//#include <cstdlib>
#include <vector>
#include "./Eigen/Dense"
#include "cell_operations.hpp"

#define NUMBER_OF_BEACONS 6
#define NUMBER_OF_DIMENSIONS 4

using namespace std;
using namespace Eigen;

// Global variables; all functions need to know this, because
// this is our base information

// These are the coordinates for each beacon. There are currently 6 beacons.
// They are organized in the four dimensions: x, y, z, and time.
// . . . . .
vector<float> x = 					{-45, -45,  45,  45,  0,  0  };
vector<float> y = 					{-25,  25, -25,  25, 25, -25 };
vector<float> z = 					{ 10,   0,   0,   5,  5,  15 };
vector<float> time_dimension = 		{  1,   1,   1,   1,  1,  1  };


bool adding_noise = true;

// This where we actually are in 3D space. It is ultimately the same value
// that we should receive at the end of all of these calculations.
int actual_position[] = { 25, 15, 5 };


// These variables should store where we think we currenly are, based off of
// the calculations.
// They are initialized to zero for the sake of the calculations.
float new_x_position, new_y_position, new_z_position;


// ======= BEGIN FUNCTIONS WE USE FOR THIS CODE ================

vector<float> get_beacon_ranges(){

	vector<float> beacon_ranges;


	for ( int i = 0; i < x.size(); i++ ){

		// These are the ranges that we pass in:
		// I don't actually set them because they don't really need to be
		// used as variables (no need to set the memory each time)
		//...
			// x_range = x[i] - actual_position[0];
			// y_range = y[i] - actual_position[1];
			// z_range = z[i] - actual_position[2];

		// Some 3D pythagorean theorem...
		beacon_ranges.push_back( sqrt( pow(x[i] - actual_position[0],2) + 
								 	   pow(y[i] - actual_position[1],2) + 
								       pow(z[i] - actual_position[2],2)
							   ));
	}

	return beacon_ranges;
}


vector<float> create_noise( vector<float> beacon_ranges ){

	/*//=====================================================================
	//
	// This function will return a new array with "noise" (just randomness)
	// added to the original beacon ranges. 
	//
	// NOTE: This function will only actually add randomness if a global 
	// boolean value "add_noise" is set to true.
	// If it is set to false, it will just return an array of the original
	// ranges because these variables is still used in calculations
	// in later function calls.
	//
	// The noise is within the range of +1 or -1.
	//  
	*///=====================================================================


	vector<float> PR;

	// Seed the random number generator
	srand(time(NULL));

	for ( int i = 0; i < x.size(); i++ ){

		if ( adding_noise ){
			PR.push_back( beacon_ranges[i] + 
						( ( rand() % 100 + 1 ) / 100.0) - 0.5 );
		}
		else{

			// If we are not adding noise, just use the original ranges
			PR.push_back(beacon_ranges[i]);
		}
	}

	return PR;
}


MatrixXf calculate_H_Matrix( vector<float> PR, float new_x_position, 
							 float new_y_position, float new_z_position ){


	MatrixXf H(NUMBER_OF_BEACONS, NUMBER_OF_DIMENSIONS);

	// Duplicate all of the current arrays...
	// I do this because the function we wrote to manipulate this data
	// work by "passing by reference", so we need copies of the
	// original arrays to work with.
	vector<float> new_x = x;
	vector<float> new_y = y;
	vector<float> new_z = z;

	// This sets up new_x to be (x-X)./PR
	array_subtract( new_x_position, new_x );
	array_divide( new_x, PR );
	
	// This sets up new_y to be (y-Y)./PR
	array_subtract( new_y_position, new_y );
	array_divide( new_y, PR );
	
	// This sets up new_x to be (z-Z)./PR
	array_subtract( new_z_position, new_z );
	array_divide( new_z, PR );
	
	// We have to add each dimension to the H matrix, now.
	for ( int i = 0; i < x.size(); i++ ){

		H(i,0) = (float)new_x[i];
	}

	for ( int i = 0; i < x.size(); i++ ){

		H(i,1) = (float)new_y[i];
	}

	for ( int i = 0; i < x.size(); i++ ){

		H(i,2) = (float)new_z[i];
	}

	for ( int i = 0; i < x.size(); i++ ){

		H(i,3) = (float)time_dimension[i];
	}

	return H;
}


vector<float> calculate_assumedPR(  float new_x_position, 
									float new_y_position, 
									float new_z_position 
								){

		// Duplicate all of the current arrays...
		// I do this because the function we wrote to manipulate this data
		// work by "passing by reference", so we need copies of the
		// original arrays to work with.
		// (I do this same thing in the `calculate_H_matrix` function)
		vector<float> new_x = x;	
		vector<float> new_y = y;
		vector<float> new_z = z;

		// For X...
		array_subtract( new_x_position, new_x );
		array_exponent( new_x, 2 );

		// For Y...
		array_subtract( new_y_position, new_y );
		array_exponent( new_y, 2 );

		// For Z...
		array_subtract( new_z_position, new_z );
		array_exponent( new_z, 2 );


		// Now add these all together and 
		array_add( new_x, new_y );
		// Now `new_x` is (x-X).^2+(y-Y).^2
		array_add( new_x, new_z );

		// Now we just take the square root of each element and we have the
		// value of assumedPR
		array_exponent( new_x, 0.5 );

		// Declare this variable so it has a proper name
		vector<float> assumedPR;
		assumedPR = new_x;
		// == This completes the building of assumedPR

		return assumedPR;
}


VectorXf calculate_deltaPR( vector<float> assumedPR, vector<float> PR ){

	// Declare this as position PR change, used to calculate our total change
	VectorXf deltaPR_vector(NUMBER_OF_BEACONS);

	array_subtract( assumedPR, PR );

	// Now deltaPR should be completed

	for ( int i = 0; i < assumedPR.size(); i++ ){
	
		deltaPR_vector(i) = (float)assumedPR[i];
	}
	// Now it is in Vector Form, which we can use to calculate posChange

	return deltaPR_vector;
}

VectorXf calculate_position_change( MatrixXf H_matrix, 
									VectorXf deltaPR_vector ){

	VectorXf posChange(NUMBER_OF_DIMENSIONS);
	posChange = H_matrix.colPivHouseholderQr().solve(deltaPR_vector);

	return posChange;

}

void calculate_new_position( VectorXf position_change ){

	new_x_position -= position_change(0);
 	new_y_position -= position_change(1);
 	new_z_position -= position_change(2);

}

void setup(){
	Serial.begin(9600);
}

void loop() {

	
	vector<float> beacon_ranges;
	beacon_ranges = get_beacon_ranges();

	// Note that you MUST run this function, even if you do not add noise,
	// just so the PR variable is filled with values.
	vector<float> PR;
	PR = create_noise( beacon_ranges );




	// I declare these variables before the for loop so they aren't remade
	// Declare this variable to hold the entire position change
	VectorXf position_change(NUMBER_OF_DIMENSIONS);

	// Declare this as our H-Matrix
	MatrixXf H(NUMBER_OF_BEACONS, NUMBER_OF_DIMENSIONS);
	
	// Declare this as our PR array, used to base our calculations off of
	vector<float> assumedPR;
	
	// Declare this as position PR change, used to calculate our total change
	VectorXf deltaPR_vector(NUMBER_OF_BEACONS);

	// Now we have to determine our position based off of the beacon ranges.
	// We do this calculation seven times. 
	for ( int counter = 0; counter < 7; counter ++ ){


		H = calculate_H_Matrix( PR, new_x_position, 
									new_y_position, new_z_position );

		assumedPR = calculate_assumedPR( new_x_position, new_y_position, 
										 new_z_position );

		deltaPR_vector = calculate_deltaPR( assumedPR, PR );
		
	 	position_change = calculate_position_change(H, deltaPR_vector);

	 	calculate_new_position( position_change );

	}

	// cout << "x position " << new_x_position << "\n";
	// cout << "y position " << new_y_position << "\n";
	// cout << "z position " << new_z_position << "\n";

    return 0;
}
