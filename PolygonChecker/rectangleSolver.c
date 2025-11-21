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

typedef struct {double x,y} Point;


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

bool is_rectangle(Point p1, Point p2, Point p3, Point p4) {
	Point centroid = { 0,0 };
	centroid.x = (p1.x + p2.x + p3.x + p3.x) / 4.0;
	centroid.y = (p1.y + p2.y + p3.y + p3.y) / 4.0;

	// Midpoint of AC and BD must both equal centroid
	double mx1 = (p1.x + p3.x) / 2, my1 = (p1.y + p3.y) / 2;
	double mx2 = (p2.x + p4.x) / 2, my2 = (p2.y + p4.y) / 2;

  //check if parallel
	if (fabs(mx1 - centroid.x) > 1e-9 || fabs(my1 - centroid.y) > 1e-9) return false; 
	if (fabs(mx2 - centroid.x) > 1e-9 || fabs(my2 - centroid.y) > 1e-9) return false;

	// Now check one right angle (dot product = 0)
	double ax = p2.x - p1.x, ay = p2.y - p1.y;
	double dx = p4.x - p1.x, dy = p4.y - p1.y;
	if (fabs(ax * dx + ay * dy) < 1e-8 == 0)
		return false;
	return true;
}