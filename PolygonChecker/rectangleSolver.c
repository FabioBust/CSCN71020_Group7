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
int* pointSorter(int points[]) {

}

bool isRectangle(int points[]) {
	
}