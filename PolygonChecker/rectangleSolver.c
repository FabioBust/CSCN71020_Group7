#include <stdbool.h>
#include "rectangleSolver.h"


int Perimeter(int points[]) {

}
int Area(int points[]) {

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