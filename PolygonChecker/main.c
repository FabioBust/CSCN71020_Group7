#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void printWelcome();
int printShapeMenu();
float* getTriangleSides(float* triangleSides);
void getPoints(float points[4][2]);

#include "triangleSolver.h"
#include "rectangleSolver.h"

int main() {
    bool continueProgram = true;
    while (continueProgram) {
        printWelcome();
        int shapeChoice = printShapeMenu();

        switch (shapeChoice) {
        case 1: {
            printf_s("Triangle selected.\n");
            float triangleSides[3] = { 0.0f };
            float* triangleSidesPtr = getTriangleSides(triangleSides);

            char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
            printf_s("%s\n", result);

            if (strcmp(result, "Not a triangle") != 0) {
                angleCalculator(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
            }
            break;
        }

        case 2: {
            printf_s("Rectangle selected.\n");
            float points[4][2] = { {0} };  // zero-init
            getPoints(points);  // now void, modifies directly

            if (isRectangle(points[0], points[1], points[2], points[3])) {
                printf_s("Yes, these 4 points form a rectangle!\n");

                float(*sorted)[2] = pointSorter(points[0], points[1], points[2], points[3]);
                float area = Area(sorted[0], sorted[1], sorted[2], sorted[3]);
                float perimeter = Perimeter(sorted[0], sorted[1], sorted[2], sorted[3]);

                printf_s("Area = %.2f\n", area);
                printf_s("Perimeter = %.2f\n", perimeter);

                free(sorted);
            }
            else {
                printf_s("No, these points do not form a rectangle.\n");
            }
            break;
        }

        case 0:
            continueProgram = false;
            printf_s("Goodbye!\n");
            break;

        default:
            printf_s("Invalid choice.\n");
            break;
        }
    }
    return 0;
}

void printWelcome() {
    printf_s("\n **********************\n");
    printf_s("**   Polygon Checker  **\n");
    printf_s(" **********************\n\n");
}

int printShapeMenu() {
    printf_s("1. Triangle\n2. Rectangle\n0. Exit\n");
    printf_s("Enter choice: ");
    int choice;
    scanf_s("%d", &choice);
    return choice;
}

float* getTriangleSides(float* sides) {
    printf_s("Enter three sides: ");
    for (int i = 0; i < 3; i++) {
        scanf_s("%f", &sides[i]);
    }
    return sides;
}

void getPoints(float points[4][2]) {
    printf_s("Enter 4 points (x y):\n");
    for (int i = 0; i < 4; i++) {
        printf_s("Point %d: ", i + 1);
        scanf_s("%f %f", &points[i][0], &points[i][1]);
    }
}