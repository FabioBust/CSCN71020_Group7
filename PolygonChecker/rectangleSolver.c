#include <stdbool.h>
#include "rectangleSolver.h"


int Perimeter(int points[]) {
	float a = points[1 * 2] - points[0 * 2];
	float b = points[2 * 2 + 1] - points[0 * 2 + 1];
	float perimeter = 2 * (a + b);
	
	return perimeter;
}
int Area(int points[]) {
	float a = points[1 * 2] - points[0 * 2];
	float b = points[2 * 2 + 1] - points[0 * 2 + 1];
	float area = a * b;

	return area; 
}
int* pointSorter(int points[]) { //matthew

}

bool isRectangle(int points[]) { //me //point order, topleft(0) to bottom right(3), max point is (1) min point is (2)
	float max = points[1];
	float min = points[2];

	float checkP1 = points[0];
	float checkP2 = points[3];

	if (checkP1[1] != max[1] || checkP1[0] != min[0]) { //point to check is invalid
		return false;
	}
	if (checkP2[0] != max[0] || checkP2[1] != min[1]) { //point to check is invalid
		return false;
	}

	return true;
}