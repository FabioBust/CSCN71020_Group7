#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "triangleSolver.h"

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

void angleCalculator(float side1, float side2, float side3) {
	double angle1 = acos((side2 * side2 + side3 * side3 - side1 * side1) / 2 * side2 * side3);
	double angle2 = acos((side1 * side1 + side3 * side3 - side2 * side2) / 2 * side1 * side3);
	double angle3 = 180 - angle1 - angle2;

	printf("The inside angles in the triangle are:\n");
	printf("Angle 1: %lf", angle1);
	printf("Angle 2: %lf", angle2);
	printf("Angle 3: %lf", angle3);
  }

bool isTriangle(float side1, float side2, float side3) {
	int sides[] = { side1, side2, side3 };
	int max = 0; //get the max side length
 
	for (int i = 0; i < 3; i++) {
		if (sides[i] > max) {
			max = i;
		}
		if (sides[i] <= 0) {
			return false;
		}
	}
	//now use triangle theorem to return if side lengths equal (max < side1 + side2)
	if (sides[max] < sides[(max - 1) % 3] + sides[(max + 1) % 3]) {
		return true;
	}
	return false;
}