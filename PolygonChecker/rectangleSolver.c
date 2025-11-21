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
void pointSorter(int points[], int out[]) { //matthew

	struct Point { float x, y; } c[4]; //create array for each corner
	for (int i = 0; i < 4; i++) { //put inputs into struct point
		c[i].x = points[i * 2];
		c[i].y = points[i + 2 + 1];
	}
	int tl = 0, tr = 0, br = 0, bl = 0; //create ints for each corner (top left, top right, bottom right, bottom left)

	for (int i = 1; i < 4; i++) { //top left, min y, min x
		if (c[i].y < c[tl].y || (c[i].y == c[tl].y && c[i].x < c[tl].x))
			tl = i;
	}
	for (int i = 1; i < 4; i++) { //top right, min y, max x
		if (c[i].y < c[tr].y || (c[i].y == c[tr].y && c[i].x > c[tr].x))
			tr = i;
	}
	for (int i = 1; i < 4; i++) { //bottom right, max y, max x
		if (c[i].y > c[br].y || (c[i].y == c[br].y && c[i].x > c[br].x))
			br = i;
	}
	for (int i = 1; i < 4; i++) { //bottom left, max y, min x
		if (c[i].y > c[bl].y || (c[i].y == c[bl].y && c[i].x < c[bl].x))
			bl = i;
	}
	struct Point order[4] = { c[tl], c[tr], c[br], c[bl] };

	for (int i = 0; i < 4; i++) { //copy points into array when called
		out[i * 2] = order[i].x;
		out[i * 2 + 1] = order[i].y;
	}

	/*
	* call for function
	int sorted[8];
	pointSorter(points, sorted);*/
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