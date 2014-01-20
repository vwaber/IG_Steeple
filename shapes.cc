#include"main.h"

//Draws X, Y, and Z axes for reference
void drawAxis(const GLfloat* xColor, const GLfloat* yColor, const GLfloat* zColor)
{
	glBegin(GL_LINES);
	glLineWidth(10.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, xColor );
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(20.0,0.0,0.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yColor );
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,20.0,0.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, zColor );
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.0,20.0);
	glEnd();
}

//Draws a simple flat square
//Lighting may not be correct
void square( )
{
   glBegin(GL_QUADS);
     glVertex3f(0,0,0);
     glVertex3f(1,0,0);
     glVertex3f(1,1,0);
     glVertex3f(0,1,0);
   glEnd( );
} // square( )

//Draws a simple flat triangle
//Lighting may not be correct
void triangle()
{
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
		glVertex3f(0.5,1,0.5);
	glEnd( );
}

//Draws a 1x1x1 cube
//Lighting may not be correct
void unitCube()
{  
	glPushMatrix();
		square();
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(0, 0, 1);
		square();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 1.0, 0.0, 0.0);
		square();
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(0, 1, 0);
		glRotatef(90, 1.0, 0.0, 0.0);
		square();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(-90, 0.0, 1.0, 0.0);
		square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1, 0, 0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		square();
	glPopMatrix();
}

//Draws a cube based on many parameters
//Lighting may not be correct
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
	)
{
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
		
		
		glTranslatef(x, y, z);
		glRotatef(r, rx, ry, rz);
		glScalef(sx, sy, sz);
		unitCube();
	glPopMatrix();
}

//Draws a 1x1x1 square pyramid
//Lighting may not be correct
void unitPyramid()
{

	glPushMatrix();
		glRotatef(90, 1.0, 0.0, 0.0);
		square();
	glPopMatrix();

	glPushMatrix();
		triangle();
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(0, 0, 1);
		glRotatef(90, 0.0, 1, 0.0);
		triangle();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1, 0, 1);
		glRotatef(180, 0.0, 1, 0.0);
		triangle();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1, 0, 0);
		glRotatef(270, 0.0, 1, 0.0);
		triangle();
	glPopMatrix();
	
}

//Draws a pyramid based on parameters
//Lighting may not be correct
void pyramid(float x, float y, float z, float s, float h)
{
	glPushMatrix();	
		glTranslatef(x, y, z);
		glScalef(s, h, s);
		unitPyramid();
	glPopMatrix();
}

//Draws a flat polygon with the specified number of sides
//Lighting IS correct
void polygon(int sides)
{
	float X=0, Y=0;
	float radius = 1;
	float angle = 0;
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	for(angle; angle < 360; angle += (360/sides))
	{
		calcCirclePos(radius, angle, X, Y);
		glVertex3f(X,Y,0);
	}
	glEnd( );   
}

//Draws a polygonal prism with the specified number of sides
//Lighting IS correct
void polygonPrism(int sides)
{
	float X, Y, angle;
	float radius = 1;
	float height = 1;
	float P1[3], P2[3], P3[3], P4[3], N[3];

	glBegin(GL_POLYGON);	
	glNormal3f(0.0, 0.0, 1.0);
	for(angle = 0; angle < 360; angle += (360/sides))
	{
		calcCirclePos(radius, angle, X, Y);
		glVertex3f(X, Y, 0);
	}
	glEnd( );
	
	glBegin(GL_POLYGON);	
	glNormal3f(0.0, 0.0, 1.0);
	for(angle = 0; angle < 360; angle += (360/sides))
	{
		calcCirclePos(radius, angle, X, Y);
		glVertex3f(X, Y, height);
	}
	glEnd( );
	
	for(angle = 0; angle < 360; angle += (360/sides))
	{
		calcCirclePos(radius, angle, X, Y);
		P1[0] = X;
		P1[1] = Y;
		P1[2] = 0;				
		P2[0] = X;
		P2[1] = Y;
		P2[2] = height;

		angle += (360/sides);
		calcCirclePos(radius, angle, X, Y);	
		P3[0] = X;
		P3[1] = Y;
		P3[2] = height;
		P4[0] = X;
		P4[1] = Y;
		P4[2] = 0;		
		angle -= (360/sides);	

		calcNormal(P1, P2, P3, N);
		
		glBegin(GL_QUADS);
			glNormal3fv(N);		
			glVertex3fv(P1);		
			glVertex3fv(P2);		
			glVertex3fv(P3);
			glVertex3fv(P4);		
		glEnd( );			
	}
}

//Draws a polygonal pyramid with the specified number of sides
//Lighting IS correct
void polygonPyramid(int sides)
{
	float X, Y, angle;
	float radius = 1;
	float height = 1;
	float P1[3], P2[3], P3[3], P4[3], N[3];

	glBegin(GL_POLYGON);	
	glNormal3f(0.0, 0.0, 1.0);
	for(angle = 0; angle < 360; angle += (360/sides))
	{
		calcCirclePos(radius, angle, X, Y);
		glVertex3f(X, Y, 0);
	}
	glEnd( );
	
	
	for(angle = 0; angle < 360; angle += (360/sides))
	{
		calcCirclePos(radius, angle, X, Y);
		P1[0] = X;
		P1[1] = Y;
		P1[2] = 0;				
		P2[0] = X;
		P2[1] = Y;
		P2[2] = height;

		angle += (360/sides);
		calcCirclePos(radius, angle, X, Y);	
		P3[0] = 0;
		P3[1] = 0;
		P3[2] = height;
		P4[0] = X;
		P4[1] = Y;
		P4[2] = 0;		
		angle -= (360/sides);	

		calcNormal(P1, P3, P4, N);
		
		glBegin(GL_TRIANGLES);
			glNormal3fv(N);		
			glVertex3fv(P1);		
			//glVertex3fv(P2);		
			glVertex3fv(P3);
			glVertex3fv(P4);		
		glEnd( );			
	}	
	
}



