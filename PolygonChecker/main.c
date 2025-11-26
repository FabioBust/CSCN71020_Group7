#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "triangleSolver.h"
#include "rectangleSolver.h"



int main() { //main FUNCTION
	bool continueProgram = true;
	while (continueProgram) {
		printWelcome();

		int shapeChoice = printShapeMenu();

		switch (shapeChoice)
		{
		case 1:
			printf_s("Triangle selected.\n");
			float triangleSides[3] = { 0.0, 0.0, 0.0 };
			float* triangleSidesPtr = getTriangleSides(triangleSides);
			char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
			printf_s("%s\n", result);
			if (result != "Not a triangle") {
				angleCalculator(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
			}
			break;
		case 2:
			printf_s("Rectangle selected.\n");
			float points[4][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
			float* pointsPtr = getPoints(points);

			if (isRectangle(points[0], points[1], points[2], points[3] )) {  // pass the whole array
				printf("Yes, these 4 points form a rectangle!\n");
				float area = Area(points[0], points[1], points[2], points[3]);
				float perimeter = Perimeter(points[0], points[1], points[2], points[3]);
				printf("Area = %.2f\n", area);
				printf("Perimeter = %.2f\n", perimeter);
			}

			break;
		case 0:
			continueProgram = false;
			break;
		default:
			printf("This is not a triangle");
			break;
		}
	}
	return 0;
}

void printWelcome() {
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}

int printShapeMenu() {
	printf_s("2. Rectangle\n");
	printf_s("1. Triangle\n");
	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}

float* getTriangleSides(float* triangleSides) {
	printf_s("Enter the three sides of the triangle: ");
	for (int i = 0; i < 3; i++)
	{
		scanf_s("%f", &triangleSides[i]);
	}
	return triangleSides;
}

float* getPoints(float* points) {
	printf_s("Enter the four points for the rectangle: ");
	for (int i = 0; i < 4; i++)
	{
		printf("Enter the x value of point: ");
		scanf_s("%f", &points[i*2]);
		printf("Enter the y value of points: ");
		scanf_s("%f", &points[i*2+1]);
	}
	return points;
}