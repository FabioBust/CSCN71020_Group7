#include <stdbool.h>
#include "rectangleSolver.h"
#include <math.h>


float Perimeter(float p1[2], float p2[2], float p3[2], float p4[2]) {
	float perim = 0.0f;
	perim += (float)sqrt(distanceSquared(p1, p2));
	perim += (float)sqrt(distanceSquared(p2, p3));
	perim += (float)sqrt(distanceSquared(p3, p4));
	perim += (float)sqrt(distanceSquared(p4, p1));
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

 void pointSorter(float points[4][2]) { 
	 float centroid[2] = { 0 };

	 for (int i = 0; i < 4; i++)
	 {
		 centroid[0] += points[i][0];
		 centroid[1] += points[i][1];
	 }
	 centroid[0] /= 4.0f;
	 centroid[1] /= 4.0f;
	 //get one point (0) and sort based off of angle to that point
	 //center points around centroid
	 float angles[4];
	 for (int i = 0; i < 4; i++) {
		 points[i][0] -= centroid[0];
		 points[i][1] -= centroid[1];
		 angles[i] = (float)atan2(points[i][1], points[i][0]);
	 }


	 //bubble sort
	 for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) {
			if (angles[j] > angles[j + 1]) {
				float tempAngle = angles[j];
				angles[j] = angles[j + 1];
				angles[j + 1] = tempAngle;

				float tempPoint[2] = { points[j][0], points[j][1] };
				points[j][0] = points[j + 1][0];
				points[j][1] = points[j + 1][1];
				points[j + 1][0] = tempPoint[0];
				points[j + 1][1] = tempPoint[1];
			}
		}
	 }

	 for (int i = 0; i < 4; i++) {
		 points[i][0] += centroid[0];
		 points[i][1] += centroid[1];
	 }
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