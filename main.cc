/*
 	Interactive Graphics - Project 2
	Vaan W. Waber
	10-19-11
*/

/*
	Camera Controls:

	Arrow Keys:
		L and R: Pan around focus point
		U and D: Zoom in and out of focus point
	Other:
		+ and -: Move the Eye position straight up and down. Advanced Use.
*/

//Header file for the project.
#include"main.h"

//Screen size constants
#define SCREENSIZE_X 512
#define SCREENSIZE_Y 512

/* Viewing defaults */
#define EYEX 0.0
#define EYEY 0.0
#define EYEZ 0.0
#define LOOKATX 0.0
#define LOOKATY 15.0
#define LOOKATZ 0.0

/* Initial eye position */
float eye[3] = {EYEX, EYEY, EYEZ};
float lookat[3] = {LOOKATX, LOOKATY, LOOKATZ};

//Use to calculate the eye position when panning
float eyePosDegree = 0;
float eyePosRadius = 36;

//Use to manipulate eye Height position
float eyeOffset = 0.0;



/* Some colors and positions */
GLfloat position[ ] = {0.0, 10.0, 0.0, 1.0}; /* Directional light */
GLfloat white[ ] = {1.0, 1.0, 1.0, 1.0};    /* White */
GLfloat red[ ] = {1.0, 0.0, 0.0, 1.0};    /* Red */
GLfloat blue[ ] = {0.0, 0.0, 1.0, 1.0};    /* Blue */
GLfloat green[ ] = {0.0, 1.0, 0.0, 1.0};    /* Green */
GLfloat purple[ ] = {0.5, 0.0, 0.5, 1.0};    /* Purple */
GLfloat ambient[ ] = {0.2, 0.2, 0.2, 1.0};

GLfloat dirtyWhite[ ] = {1.5, 1.4, 1.3, 1.0};
GLfloat black[ ] = {0.0, 0.0, 0.0, 0.0};

// init( )
// set the modeling parameters
//   and default lighting
void init( )
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* Set global ambient and two-squared model */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	/* Set up light #0 */
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Enable smooth shading and zbuffering */
	glEnable(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);


} // init( )

/* Reshape callback */
void Reshape(int width, int height)
{
   float aspect;

   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   // Maintain the aspect ratio
   aspect = (float)width/(float)height;
   gluPerspective(60.0, aspect, 10.0, 1000.0);
   glMatrixMode(GL_MODELVIEW);

} // Reshape( )

// Arrow key callback
void specialKeys(int key, int x, int y)
{

	switch(key)
	{
	case GLUT_KEY_UP:
		eyePosRadius --;
		break;
	case GLUT_KEY_DOWN:
		eyePosRadius ++;
		break;
	case GLUT_KEY_LEFT:
		eyePosDegree += 2;
		break;
	case GLUT_KEY_RIGHT:	
		eyePosDegree -= 2;
		break;
	}	

	// Redraw the window
	glutPostRedisplay( );
} // specialKeys( )

/* Key press callback */
void Key(unsigned char key, int x, int y)
{
	switch(key)
	{
		/* Escape => quit */
	case 27:
		exit(0);
		break;

	case '=':
	case '+':
		eyeOffset ++;
		break;
	

	case '-':
	case '_':
		eyeOffset --;
		break;
	} // switch

	glutPostRedisplay( );

} // Key( )

//Black pseudo-windows
void archWindow()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

	glPushMatrix();

	glTranslatef(0, 0, 0.25);	
	glScalef(1.125, 1.125, 0.125);

	glPushMatrix();
		glTranslatef(0, 3.5, 0);		
		//glScalef(5.5, 0.5, 5.5);
		//glRotatef(-90, 1, 0, 0);
		polygonPrism(360);
	glPopMatrix();


	glPushMatrix();		
		glTranslatef(-1, 0, 0);		
		glScalef(2, 3.5, 1);
		//glRotatef(-90, 0, 0, 1);
		unitCube();
	glPopMatrix();

	glPopMatrix();
}//archWindow()

//First/bottom layer of the steeple
void steepleLayer0()
{
	for(float angle = (360/16); angle < 360; angle += (360/8))
	{
		float X, Y;
		calcCirclePos(5, angle, X, Y);
			glPushMatrix();
			glTranslatef(X, 2.5, Y);
			glRotatef(angle+90, 0, -1, 0);
			archWindow();
		glPopMatrix();
	}

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dirtyWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

	//top
	glPushMatrix();
		glTranslatef(0, 8.5, 0);		
		glScalef(5.5, 0.5, 5.5);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(8);
	glPopMatrix();

	//body
	glPushMatrix();
		glTranslatef(0, 2.5, 0);		
		glScalef(5, 6, 5);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(8);
	glPopMatrix();

	//base top
	glPushMatrix();
		glTranslatef(0, 2, 0);		
		glScalef(5.5, 0.5, 5.5);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(360);
	glPopMatrix();

	//base
	glPushMatrix();
		glTranslatef(0, 0, 0);		
		glScalef(5.25, 2, 5.25);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(360);
	glPopMatrix();

}//steepleLayer0()

//Used for all upper layers of the steeple
void steepleLayer1()
{
	for(float angle = (360/16); angle < 360; angle += (360/8))
	{
		float X, Y;
		calcCirclePos(4, angle, X, Y);
			glPushMatrix();
			glTranslatef(X, 1.5, Y);
			glScalef(0.8, 0.8, 0.8);
			glRotatef(angle+90, 0, -1, 0);
			archWindow();
		glPopMatrix();
	}

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dirtyWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

	//top
	glPushMatrix();
		glTranslatef(0, 6.3, 0);		
		glScalef(4.5, 0.5, 4.5);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(8);
	glPopMatrix();

	//body
	glPushMatrix();
		glTranslatef(0, 1.5, 0);		
		glScalef(4, 4.8, 4);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(8);
	glPopMatrix();

	//base top
	glPushMatrix();
		glTranslatef(0, 1, 0);		
		glScalef(4.5, 0.5, 4.5);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(8);
	glPopMatrix();

	//base
	glPushMatrix();
		glTranslatef(0, 0, 0);		
		glScalef(4.25, 1, 4.25);
		glRotatef(-90, 1, 0, 0);
		polygonPrism(8);
	glPopMatrix();
}//steepleLayer1()

//Octagonal pyramid at the top of the steeple
void spire()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dirtyWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

	glPushMatrix();
		//glTranslatef(0, 0, 0);		
		glScalef(2, 10, 2);
		glRotatef(-90, 1, 0, 0);
		polygonPyramid(8);
	glPopMatrix();
}

//Puts together previously defined models to make the overall steeple
void steeple()
{
	glPushMatrix();
		//glTranslatef(0, 7.5, 0);		
		//glScalef(5.5, 0.5, 5.5);
		//glRotatef(-90, 1, 0, 0);
		steepleLayer0();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 9, 0);		
		//glScalef(0.75, 1, 0.75);
		//glRotatef(-90, 1, 0, 0);
		steepleLayer1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 15.8, 0);		
		glScalef(0.8, 0.8, 0.8);
		//glRotatef(-90, 1, 0, 0);
		steepleLayer1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 21.24, 0);		
		glScalef(0.64, 0.64, 0.64);
		//glRotatef(-90, 1, 0, 0);
		steepleLayer1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 21.24, 0);		
		glScalef(0.64, 0.64, 0.64);
		//glRotatef(-90, 1, 0, 0);
		steepleLayer1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 25.529, 0);		
		//glScalef(0.64, 0.64, 0.64);
		//glRotatef(-90, 1, 0, 0);
		spire();
	glPopMatrix();
}

//Simple ground for aesthetics
void ground()
{
	GLfloat grassGreen[ ] = {0.0, 0.5, 0.0, 1.0};    /* Green */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grassGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

	glPushMatrix();		
		glTranslatef(0, 0, 0);		
		glScalef(30, 1, 30);
		glRotatef(-90, 1, 0, 0);
		polygon(10);
	glPopMatrix();
}


/* Display callback */
void display(void)
{

	//Sets the eye position based on variables modified by Keyboard events
	if(eyePosRadius >= 15)
	{
	eye[1] = eyePosRadius + eyeOffset;
	calcCirclePos(eyePosRadius, eyePosDegree, eye[0], eye[2]);
	}
	else
	{
		eyePosRadius = 15;
	}

	/* Set the current eye position */
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], 
		lookat[0], lookat[1], lookat[2], 
		0.0, 1.0, 0.0 );

	/* Clear the viewport and zbuffer */
	glClearColor(0.5, 0.5, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//Main models
	steeple();
	ground();


	/* Draw the axes */
	//drawAxis(red, white, blue);

	/* Flush and redraw */
	glFlush( );
	glutSwapBuffers( );
} // display( )

int main(int argc, char **argv)
{
   /* Initialize the window */
   glutInit(&argc, argv);
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize(SCREENSIZE_X, SCREENSIZE_Y);
   glutCreateWindow("IG_Project2_waberv");

   init( );

   /* Register callbacks */
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutSpecialFunc(specialKeys);
   glutDisplayFunc(display);
   glutMainLoop();
}