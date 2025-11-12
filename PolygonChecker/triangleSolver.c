#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "triangleSolver.h"

char* analyzeTriangle(int side1, int side2, int side3) {
	char* result = "";
	if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
		result = "Not a triangle";
	}
	else if (side1 == side2 && side1 == side3) {
		result = "Equilateral triangle";
	}
	else if ((side1 == side2 && side1 != side3) || 
		(side1 == side3 && side1 != side2))
	{
		result = "Isosceles triangle";
	}
	else {
		result = "Scalene triangle";
	}

	return result;
}

void angleCalculator(float side1, float side2, float side3) {
	float angle1 = acos((side2 * side2 + side3 * side3 - side1 * side1) / 2 * side2 * side3);
	float angle2 = acos((side1 * side1 + side3 * side3 - side2 * side2) / 2 * side1 * side3);
	float angle3 = 180 - angle1 - angle2;

	printf("The inside angles in the triangle are:\n");
	printf("Angle 1: %lf", angle1);
	printf("Angle 2: %lf", angle2);
	printf("Angle 3: %lf", angle3);
}