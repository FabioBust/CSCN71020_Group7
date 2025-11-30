#ifndef TRIANGLE_SOLVER_H
#define TRIANGLE_SOLVER_H

#include <stdbool.h>

// Struct to hold the three internal angles of a triangle
typedef struct {
	double a1;
	double a2;
	double a3;
} TriangleAngles;

// Functions declarations
char* analyzeTriangle(float side1, float side2, float side3);
TriangleAngles angleCalculator(float side1, float side2, float side3);
bool isTriangle(float side1, float side2, float side3); 

#endif