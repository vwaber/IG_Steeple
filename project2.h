#ifndef _PROJECT2_H_
#define _PROJECT2_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>

void calcCirclePos(float radius, float angle, float &X, float &Y);

void cube(
	float x,
	float y,
	float z,
	float sx,
	float sy,
	float sz,
	float r,
	float rx,
	float ry,
	float rz,
	const GLfloat* color
	);

void drawAxis(const GLfloat* xColor, const GLfloat* yColor, const GLfloat* zColor);
void polygon(int sides);
void unitCube();
void polygonPrism(int sides);
void calcNormal(float P1[3], float P2[3], float P3[3], float* N);
void polygonPyramid(int sides);
 
#endif
