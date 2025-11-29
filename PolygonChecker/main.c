#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "triangleSolver.h"
#include "rectangleSolver.h"

int main() {
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
            if (strcmp(result, "Not a triangle") != 0) {
                angleCalculator(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
            }
            break;

        case 2:
            printf_s("Rectangle selected.\n");
            float points[4][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
            float* pointsPtr = getPoints(points);  // Now matches exactly

            if (isRectangle(points[0], points[1], points[2], points[3])) {
                printf_s("Yes, these 4 points form a rectangle!\n");

                // Sort points properly before calculating area/perimeter
                float(*sortedPoints)[2] = pointSorter(points[0], points[1], points[2], points[3]);

                float area = Area(sortedPoints[0], sortedPoints[1], sortedPoints[2], sortedPoints[3]);
                float perimeter = Perimeter(sortedPoints[0], sortedPoints[1], sortedPoints[2], sortedPoints[3]);

                printf_s("Area = %.2f\n", area);
                printf_s("Perimeter = %.2f\n", perimeter);

                free(sortedPoints);  // Clean up
            }
            else {
                printf_s("No, these points do not form a rectangle.\n");
                float(*sortedPoints)[2] = pointSorter(points[0], points[1], points[2], points[3]);
                float perimeter = Perimeter(sortedPoints[0], sortedPoints[1], sortedPoints[2], sortedPoints[3]);
                printf_s("Perimeter = %.2f\n", perimeter);
                free(sortedPoints);
            }
            break;

        case 0:
            continueProgram = false;
            printf_s("Goodbye!\n");
            break;

        default:
            printf_s("Invalid choice. Please try again.\n");
            break;
        }
    }
    return 0;
}

void printWelcome() {
    printf_s("\n");
    printf_s(" **********************\n");
    printf_s("**   Polygon Checker  **\n");
    printf_s(" **********************\n");
}

int printShapeMenu() {
    printf_s("1. Triangle\n");
    printf_s("2. Rectangle\n");
    printf_s("0. Exit\n");
    int choice;
    printf_s("Enter number: ");
    scanf_s("%d", &choice);  // Fixed: was %1o wrong!
    return choice;
}

float* getTriangleSides(float* triangleSides) {
    printf_s("Enter the three sides of the triangle: ");
    for (int i = 0; i < 3; i++) {
        scanf_s("%f", &triangleSides[i]);
    }
    return triangleSides;
}

float* getPoints(float points[4][2]) {  // Keep return type float* like you had
    printf_s("Enter the four points (x and y for each):\n");
    for (int i = 0; i < 4; i++) {
        printf_s("Point %d - x: ", i + 1);
        scanf_s("%f", &points[i][0]);
        printf_s("       y: ");
        scanf_s("%f", &points[i][1]);
    }
    return &points[0][0];  // Return pointer to first element (safe in this context)
}