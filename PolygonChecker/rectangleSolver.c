#include <stdbool.h>
#include "rectangleSolver.h"
#include <math.h>


float Perimeter(float points[]) {
	float a = points[1 * 2] - points[0 * 2];
	float b = points[2 * 2 + 1] - points[0 * 2 + 1];
	float perimeter = 2 * (a + b);

	
	return perimeter;
}
float Area(float points[]) {
	float a = points[1 * 2] - points[0 * 2];
	float b = points[2 * 2 + 1] - points[0 * 2 + 1];
	float area = a * b;

	return area;
}

void pointSorter(float points[], float out[]) { //matthew

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

bool is_rectangle(float p1[], float p2[], float p3[], float p4[]) {

	float size = 4.0;
	float centroid[] = { (p1[0] + p2[0] + p3[0] + p3[0]) / size, (p1[1] + p2[1] + p3[1] + p3[1]) / size };

	float mx1 = (p1[0] + p3[0]) / 2, my1 = (p1[1] + p3[1]) / 2;
	float mx2 = (p2[0] + p4[0]) / 2, my2 = (p2[1] + p4[1]) / 2;


	if (fabs(mx1 - centroid[0]) > 1e-9 || fabs(my1 - centroid[1]) > 1e-9) return false;
	if (fabs(mx2 - centroid[0]) > 1e-9 || fabs(my2 - centroid[1]) > 1e-9) return false;

	// Now check one right angle (dot product = 0)
	float ax = p2[0] - p1[0], ay = p2[1] - p1[1];
	float dx = p4[0] - p1[0], dy = p4[1] - p1[1];
	if (fabs(ax * dx + ay * dy) < 1e-8 == 0)
		return false;
	return true;
}