#ifndef RECTANGLE_SOLVER_H //proper include guard
#define RECTANGLE_SOLVER_H

bool isRectangle(float p1[2], float p2[2], float p3[2], float p4[2]);
float Area(float p1[2], float p2[2], float p3[2], float p4[2]);
float Perimeter(float p1[2], float p2[2], float p3[2], float p4[2]);
float(*pointSorter(float p1[2], float p2[2], float p3[2], float p4[2]))[2];

#endif