#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "triangleSolver.h"
double pi = 3.1415926535;

// Determine triangle type based on side lengths
char* analyzeTriangle(float side1, float side2, float side3) {
	char* result = ""; // Initialize result string

	// Check if the sides can form a triangle
	if (isTriangle(side1, side2, side3) == false) {
		result = "Not a triangle";
	}
	else if (side1 == side2 && side1 == side3) {  // All sides equal -> Equilateral
		result = "Equilateral triangle";
	}
	
	// Two sides equal -> Isosceles
	else if ((side1 == side2 && side1 != side3) || 
		(side1 == side3 && side1 != side2))
	{
		result = "Isosceles triangle";
	}
	else { //Otherwise -> Isosceles
		result = "Scalene triangle";
	}

	return result;
}

// Calculate the internal angles of a triangle using law of cosines
void angleCalculator(float side1, float side2, float side3) {
	double angle1 = acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3)); // angle1 opposite side1
	double angle2 = acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3)); // angle2 opposite side2
	double angle3 = pi - angle1 - angle2; // sum of angles in triangle = pi

	// Convert angles from radians to degreees
	angle1 = angle1 * 180 / pi;
	angle2 = angle2 * 180 / pi;
	angle3 = angle3 * 180 / pi;

	// Print anlges
	printf("The inside angles in the triangle are:\n");
	printf("Angle 1: %.2f\n", angle1);
	printf("Angle 2: %.2f\n", angle2);
	printf("Angle 3: %.2f\n", angle3);
}

// Checks if three sides can form a triangle
bool isTriangle(float side1, float side2, float side3) {
	float sides[] = { side1, side2, side3 }; // Store sides in array
	int max = 0; //get the max side length
 
	// Loop to find max side and check for non-positive sides
	for (int i = 0; i < 3; i++) {
		if (sides[i] > max) { // Find index of longest side
			max = i;
		}
		
		if (sides[i] <= 0.0) { // Sides must be positive
			return false;
		}
		
	}
	//now use triangle theorem to return if side lengths equal (max < side1 + side2)
	if (sides[max] < sides[(max - 1) % 3] + sides[(max + 1) % 3]) {
		return true;
	}

	return false;
}