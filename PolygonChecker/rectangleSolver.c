#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "rectangleSolver.h"

float distanceSquared(float p1[2], float p2[2]) {
    float dx = p1[0] - p2[0];
    float dy = p1[1] - p2[1];
    return dx * dx + dy * dy;
}

// Fixed swap: now correctly swaps two float[2] points
void swap(float p1[2], float p2[2]) {
    float temp[2] = { p1[0], p1[1] };
    p1[0] = p2[0]; p1[1] = p2[1];
    p2[0] = temp[0]; p2[1] = temp[1];
}

float Perimeter(float p1[2], float p2[2], float p3[2], float p4[2]) {
    float points[4][2] = {
        { p1[0], p1[1] },
        { p2[0], p2[1] },
        { p3[0], p3[1] },
        { p4[0], p4[1] }
    };
    float perim = 0.0f;
    for (int i = 0; i < 4; i++) {
        perim += sqrtf(distanceSquared(points[i], points[(i + 1) % 4]));
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

    // Use your original smart method: find two sides from one point
    float d1 = distanceSquared(points[0], points[1]);
    float d2 = distanceSquared(points[0], points[2]);
    float d3 = distanceSquared(points[0], points[3]);

    float distances[3] = { d1, d2, d3 };
    int maxIdx = 0;
    if (distances[1] > distances[maxIdx]) maxIdx = 1;
    if (distances[2] > distances[maxIdx]) maxIdx = 2;

    // The two non-diagonal sides
    float side1sq = 0, side2sq = 0;
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (i != maxIdx) {
            if (count == 0) side1sq = distances[i];
            else side2sq = distances[i];
            count++;
        }
    }
    return sqrtf(side1sq) * sqrtf(side2sq);  // length × width
}

// Your original brilliant centroid + atan2 sorting — now fixed!
float(*pointSorter(float p1[2], float p2[2], float p3[2], float p4[2]))[2] {
    float points[4][2] = {
        { p1[0], p1[1] },
        { p2[0], p2[1] },
        { p3[0], p3[1] },
        { p4[0], p4[1] }
    };

    // Calculate centroid
    float centroid[2] = { 0 };
    for (int i = 0; i < 4; i++) {
        centroid[0] += points[i][0];
        centroid[1] += points[i][1];
    }
    centroid[0] /= 4.0f;
    centroid[1] /= 4.0f;

    // Center points
    for (int i = 0; i < 4; i++) {
        points[i][0] -= centroid[0];
        points[i][1] -= centroid[1];
    }

    // Calculate angle and store index
    float angles[4];
    for (int i = 0; i < 4; i++) {
        angles[i] = atan2f(points[i][1], points[i][0]);
    }

    // Bubble sort by angle (your style!)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (angles[j] > angles[j + 1]) {
                // Swap angles
                float tempAngle = angles[j];
                angles[j] = angles[j + 1];
                angles[j + 1] = tempAngle;
                // Swap points
                swap(points[j], points[j + 1]);
            }
        }
    }

    // Restore original position (add centroid back)
    for (int i = 0; i < 4; i++) {
        points[i][0] += centroid[0];
        points[i][1] += centroid[1];
    }

    // Allocate and return sorted points
    float(*result)[2] = malloc(4 * sizeof(float[2]));
    for (int i = 0; i < 4; i++) {
        result[i][0] = points[i][0];
        result[i][1] = points[i][1];
    }
    return result;
}

bool isRectangle(float p1[2], float p2[2], float p3[2], float p4[2]) {
    float points[4][2] = {
        { p1[0], p1[1] },
        { p2[0], p2[1] },
        { p3[0], p3[1] },
        { p4[0], p4[1] }
    };

    // Check all 4 corners using your original Pythagoras method
    for (int i = 0; i < 4; i++) {
        float a = distanceSquared(points[i], points[(i + 1) % 4]);
        float b = distanceSquared(points[(i + 1) % 4], points[(i + 2) % 4]);
        float c = distanceSquared(points[i], points[(i + 2) % 4]);  // diagonal

        // Find longest (should be diagonal)
        if (c < a || c < b) continue;  // diagonal must be longest

        if (fabs(a + b - c) > 0.1f) {  // allow small error
            return false;
        }
    }
    return true;
}