#include <stdbool.h>
#include "rectangleSolver.h"
#include <math.h>


float Perimeter(float p1[2], float p2[2], float p3[2], float p4[2]) {
	float points[4][2] = {
		{ p1[0], p1[1] },
		{ p2[0], p2[1] },
		{ p3[0], p3[1] },
		{ p4[0], p4[1] }
	};

	float perim = 0.0f;

	for (int i = 1; i <= 4; i++) {
		perim += sqrt(distanceSquared(points[i - 1], points[i % 4]));
	}
	return perim;
}
float Area(float p1[2], float p2[2], float p3[2], float p4[2]) {
	float points[4][2] = {
		{ p1[0], p1[1] },
		{ p2[0], p2[1] },
		{ p3[0], p3[1] },
		{ p4[0], p4[1] }
	};

	float d1 = distanceSquared(points[0], points[(1) % 4]);  // side
	float d2 = distanceSquared(points[0], points[(2) % 4]);  // diagonal
	float d3 = distanceSquared(points[0], points[(3) % 4]);  // other side

	float distances[3] = { d1, d2, d3 };

	int maxIdx = 0;
	if (distances[1] > distances[maxIdx]) maxIdx = 1;
	if (distances[2] > distances[maxIdx]) maxIdx = 2;

	return sqrt(distances[(maxIdx + 1) % 3]) * sqrt(distances[(maxIdx + 2) % 3]);

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

float distanceSquared(float p1[2], float p2[2])  
{
	float dx = p1[0] - p2[0];
	float dy = p1[1] - p2[1];
	return dx * dx + dy * dy;          
}

bool isRectangle(float p1[2], float p2[2], float p3[2], float p4[2]) //returns area or -1
{
	float points[4][2] = {
		{ p1[0], p1[1] },
		{ p2[0], p2[1] },
		{ p3[0], p3[1] },
		{ p4[0], p4[1] }
	};


	for (int i = 0; i < 4; i++)
	{
		float d1 = distanceSquared(points[i], points[(i + 1) % 4]);  // side
		float d2 = distanceSquared(points[i], points[(i + 2) % 4]);  // diagonal
		float d3 = distanceSquared(points[i], points[(i + 3) % 4]);  // other side

		float distances[3] = { d1, d2, d3 };

		int maxIdx = 0;
		if (distances[1] > distances[maxIdx]) maxIdx = 1;
		if (distances[2] > distances[maxIdx]) maxIdx = 2;

		float sumOfSquares = 0;
		for (int j = 0; j < 3; j++)
			if (j != maxIdx)
				sumOfSquares += distances[j];

		if (fabs(distances[maxIdx] - sumOfSquares) > 0.01f)
			return false;

	}

	return true;   
}