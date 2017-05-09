#include "cell_operations.hpp"
#include <vector>

using namespace std;

// Overload the crap out of this function so we can use it easily
void array_subtract( vector<float> &array, float number ){


	
	for ( int i = 0; i < array.size(); i++ ){

		array[i] = array[i] - number;
	}

	
}

void array_subtract( vector<float> &array, int number ){


	
	for ( int i = 0; i < array.size(); i++ ){

		array[i] = array[i] - number;
	}

	
}

void array_subtract( float number, vector<float> &array ){


	
	for ( int i = 0; i < array.size(); i++ ){

		array[i] = number - array[i];
	}
	
}

void array_subtract( int number, vector<float> &array ){

	
	for ( int i = 0; i < array.size(); i++ ){

		array[i] = number - array[i];

	}

}

void array_subtract( vector<float> &array_one, vector<float> array_two ){

	for ( int i = 0; i < array_one.size(); i++ ){

		array_one[i] = array_one[i] - array_two[i];
	}

}
//**************************************************************************

void array_divide( vector<float> &array_one, vector<float> array_two ){

	for ( int i = 0; i < array_one.size(); i++ ){

		array_one[i] = array_one[i] / array_two[i];
	}	
}



void array_exponent( vector<float> &array_one, float exponent ){

	for ( int i = 0; i < array_one.size(); i++ ){

		array_one[i] = pow(array_one[i], exponent);
	}	
}


void array_add( vector<float> &array_one, vector<float> array_two ){

	for ( int i = 0; i < array_one.size(); i++ ){

		array_one[i] = array_one[i] + array_two[i];
	}
}
