#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "triangleSolver.h"
double pi = 3.1415926535;

char* analyzeTriangle(float side1, float side2, float side3) {
	char* result = "";
	if (isTriangle(side1, side2, side3) == false) {
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

void angleCalculator(float side1, float side2, float side3) { //still needs testing
	double angle1 = acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3));
	double angle2 = acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3));
	double angle3 = pi - angle1 - angle2;

	angle1 = angle1 * 180 / pi;
	angle2 = angle2 * 180 / pi;
	angle3 = angle3 * 180 / pi;

	printf("The inside angles in the triangle are:\n");
	printf("Angle 1: %.2f\n", angle1);
	printf("Angle 2: %.2f\n", angle2);
	printf("Angle 3: %.2f\n", angle3);
  }

bool isTriangle(float side1, float side2, float side3) {
	float sides[] = { side1, side2, side3 };
	int max = 0; //get the max side length
 
	for (int i = 0; i < 3; i++) {
		if (sides[i] > max) {
			max = i;
		}
		
		if (sides[i] <= 0.0) {
			return false;
		}
		
	}
	//now use triangle theorem to return if side lengths equal (max < side1 + side2)
	if (sides[max] < sides[(max - 1) % 3] + sides[(max + 1) % 3]) {
		return true;
	}

	return false;
}