#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rectangleSolver.h"

// Calculates squared distance between 2 points
static float distanceSquared(float p1[2], float p2[2]) {
    float dx = p1[0] - p2[0];
    float dy = p1[1] - p2[1];
    return dx * dx + dy * dy;
}

// Swap two points, used when sorting points
static void swap(float a[2], float b[2]) {
    float temp[2] = { a[0], a[1] };
    a[0] = b[0]; a[1] = b[1];
    b[0] = temp[0]; b[1] = temp[1];
}

// Calculates perimeter of quadrilateral
float Perimeter(float p1[2], float p2[2], float p3[2], float p4[2]) {
    float* p[4] = { p1, p2, p3, p4 }; //Array of pointers for easy looping
    float perim = 0.0f;

    // Loop over each consecutive pair of points
    for (int i = 0; i < 4; i++) {
        perim += sqrtf(distanceSquared(p[i], p[(i + 1) % 4])); // Add distance to perimeter
    }
    return perim; // Return total perimeter
}

// Calculates area of a rectangle from 4 points
// Uses largest distance from first point as diagonal
float Area(float p1[2], float p2[2], float p3[2], float p4[2]) {
    float points[4][2] = { {p1[0],p1[1]}, {p2[0],p2[1]}, {p3[0],p3[1]}, {p4[0],p4[1]} };

    float d1 = distanceSquared(points[0], points[1]); // distance from p0 to p1 squared
    float d2 = distanceSquared(points[0], points[2]); // distance from p0 to p2 squared
    float d3 = distanceSquared(points[0], points[3]); // distance from p0 to p3 squared
  
    float maxD = fmaxf(fmaxf(d1, d2), d3); // Identify the diagonal (largest distance)

    float side1sq = 0, side2sq = 0; // To store squared lengths of sides
    if (maxD == d1) { side1sq = d2; side2sq = d3; } // If d1 is diagonal, sides are d2 & d3
    else if (maxD == d2) { side1sq = d1; side2sq = d3; }
    else { side1sq = d1; side2sq = d2; } // If d3 is diagonal, sides are d1 & d2

    return sqrtf(side1sq) * sqrtf(side2sq); // Multiply side lengths to get area
}

// Sorts points in clockwise order around centroid
// Returns dynamically allocated array of sorted points
float(*pointSorter(float p1[2], float p2[2], float p3[2], float p4[2]))[2] {
    // Copy points into local array for manipulation
    float points[4][2] = { {p1[0],p1[1]}, {p2[0],p2[1]}, {p3[0],p3[1]}, {p4[0],p4[1]} };

    // Calculate centroid (average x and y)
    float cx = (points[0][0] + points[1][0] + points[2][0] + points[3][0]) / 4.0f;
    float cy = (points[0][1] + points[1][1] + points[2][1] + points[3][1]) / 4.0f;

    // Shift points so that centroid is at origin (0,0)
    for (int i = 0; i < 4; i++) {
        points[i][0] -= cx;
        points[i][1] -= cy;
    }

    // Compute angles of points relative to origin using atan2
    float angles[4];
    for (int i = 0; i < 4; i++) {
        angles[i] = atan2f(points[i][1], points[i][0]); // Angle from centroid
    }

    // Sort points by angle using bubble sort
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (angles[j] > angles[j + 1]) { // Swap if out of order
                float temp = angles[j]; angles[j] = angles[j + 1]; angles[j + 1] = temp;
                swap(points[j], points[j + 1]); // Swap corresponding points
            }
        }
    }

    // Shift points back to original coordinates
    for (int i = 0; i < 4; i++) {
        points[i][0] += cx;
        points[i][1] += cy;
    }

    // Allocate dynamic array for result
    float(*result)[2] = malloc(4 * sizeof(float[2]));
    if (result == NULL) {
        // Allocation failed, return NULL to avoid dereferencing
        return NULL;
    }
    for (int i = 0; i < 4; i++) {
        result[i][0] = points[i][0];
        result[i][1] = points[i][1];
    }
    return result;
}

// Determines if 4 points form a rectangle
bool isRectangle(float p1[2], float p2[2], float p3[2], float p4[2]) {
    float points[4][2] = { {p1[0],p1[1]}, {p2[0],p2[1]}, {p3[0],p3[1]}, {p4[0],p4[1]} };

    for (int i = 0; i < 4; i++) {
        float a = distanceSquared(points[i], points[(i + 1) % 4]); // side1
        float b = distanceSquared(points[(i + 1) % 4], points[(i + 2) % 4]); // side 2
        float c = distanceSquared(points[i], points[(i + 2) % 4]); // diagonal

        if (c < a || c < b) continue;  // c must be diagonal

        if (fabsf(a + b - c) > 0.5f) return false;  // Pythagoras with tolerance
    }
    return true; // All vertices satisfy rectangle condition
}