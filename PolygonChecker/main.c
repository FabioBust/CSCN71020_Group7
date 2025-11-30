#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void printWelcome();
int printShapeMenu();
float* getTriangleSides(float* triangleSides);
void getPoints(float points[4][2]);

#include "triangleSolver.h"
#include "rectangleSolver.h"

int main() {
    bool continueProgram = true;

    while (continueProgram) { // Program continues until user selects 0
        printWelcome();
        int shapeChoice = printShapeMenu(); // Reads user's selection

        switch (shapeChoice) {

        case 1: { // Triangle processing
            printf_s("Triangle selected.\n");

            float triangleSides[3] = { 0.0f };
            
            float* triangleSidesPtr = getTriangleSides(triangleSides);  // getTriangleSides fills the array and returns the same pointer

            // analyzeTriangle returns a char* describing triangle type
            char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);

            printf_s("%s\n", result);

            // Only calculate angles if sides form a valid triangle
            if (strcmp(result, "Not a triangle") != 0) {

                TriangleAngles angles = angleCalculator(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);

                // Access each angle from the struct and display it
                printf("The inside angles in the triangle are:\n");
                printf("Angle 1: %2.f\n", angles.a1);
                printf("Angle 2: %2.f\n", angles.a2);
                printf("Angle 3: %2.f\n", angles.a3);
            }
            break;
        }

        case 2: {   // Rectangle and quadrilateral processing
            printf_s("Rectangle selected.\n");
           
            float points[4][2] = { {0} };  // zero-init
            getPoints(points);  // Writes directly into the 2D array

            // Check if the input points form a rectangle
            if (isRectangle(points[0], points[1], points[2], points[3])) {
                printf_s("Yes, these 4 points form a rectangle!\n");
                
                float(*sorted)[2] = pointSorter(points[0], points[1], points[2], points[3]); //Allocates and returns a new 4x2 arra, sorted clockwise
                float area = Area(sorted[0], sorted[1], sorted[2], sorted[3]);  
                float perimeter = Perimeter(sorted[0], sorted[1], sorted[2], sorted[3]);

                printf_s("Area = %.2f\n", area);
                printf_s("Perimeter = %.2f\n", perimeter);

                free(sorted); // Free allocated memory
            }
            else {
                printf_s("No, these points do not form a rectangle.\n");

                float(*sorted)[2] = pointSorter(points[0], points[1], points[2], points[3]); // Sorting still required for correct perimeter calculation
                float perimeter = Perimeter(sorted[0], sorted[1], sorted[2], sorted[3]);
                
                printf_s("Perimeter = %.2f\n", perimeter);
                
                free(sorted);
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

// Displays program header
void printWelcome() {
    printf_s("\n **********************\n");
    printf_s("**   Polygon Checker  **\n");
    printf_s(" **********************\n\n");
}

// Prints menu and returns user selection
int printShapeMenu() {
    printf_s("1. Triangle\n2. Rectangle\n0. Exit\n");
    printf_s("Enter choice: ");
    int choice;
    scanf_s("%d", &choice);
    return choice;
}

// Reads three triangle side lengths into the provided array
float* getTriangleSides(float* sides) {
    printf_s("Enter three sides: ");
    for (int i = 0; i < 3; i++) {
        scanf_s("%f", &sides[i]);
    }
    return sides; // Return pointer to caller-owned memory
}

// Reads four points (x, y) into a 4x2 array
void getPoints(float points[4][2]) {
    printf_s("Enter 4 points (x y):\n");

    for (int i = 0; i < 4; i++) {
        printf_s("Point %d: ", i + 1);
        scanf_s("%f %f", &points[i][0], &points[i][1]);
    }
}