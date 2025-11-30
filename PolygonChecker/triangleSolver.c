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
		(side1 == side3 && side1 != side2) ||
		(side2 == side3 && side2 != side1))
	{
		result = "Isosceles triangle";
	}
	else { //Otherwise -> Scalene
		result = "Scalene triangle";
	}

	return result;
}

// Calculate the internal angles of a triangle using law of cosines
TriangleAngles angleCalculator(float side1, float side2, float side3) {
	TriangleAngles t; //Create a struct variable to store the three angles

	t.a1 = acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3)); // angle1 opposite side1
	t.a2 = acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3)); // angle2 opposite side2
	t.a3 = pi - t.a1 - t.a2; // sum of angles in triangle = pi

	// Convert angles from radians to degreees
	t.a1 = t.a1 * 180 / pi;
	t.a2 = t.a2 * 180 / pi;
	t.a3 = t.a3 * 180 / pi;

	return t; //Return the struct containing all three angles
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