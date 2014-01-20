#include"main.h"

#define PI 3.14159265358979323846

//Calculates positions on a circle based on a radius and angle
void calcCirclePos(float radius, float angle, float &X, float &Y)
{
	float radians = angle * (PI/180.0);
	X = radius * cos(radians);
	Y = radius * sin(radians);
}

//Calculates a normalized cross-product given 3 points
void calcNormal(float P1[3], float P2[3], float P3[3], float* N)
{
    float magnitude = 0.0;
	
	N[0] = (P2[1]-P1[1])*(P3[2]-P1[2]) - (P3[1]-P1[1])*(P2[2]-P1[2]);
	N[1] = (P2[2]-P1[2])*(P3[0]-P1[0]) - (P3[2]-P1[2])*(P2[0]-P1[0]);
	N[2] = (P2[0]-P1[0])*(P3[1]-P1[1]) - (P3[0]-P1[0])*(P2[1]-P1[1]);

    magnitude = sqrt(N[0]*N[0] + N[1]*N[1] + N[2]*N[2]);

	N[0] /= magnitude;
	N[1] /= magnitude;
	N[2] /= magnitude;

}
