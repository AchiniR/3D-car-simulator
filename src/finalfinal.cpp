#include <GL/glut.h>  
#include<SOIL.h>
#include <math.h>
#include <string.h>

GLuint texture[1];
GLfloat windowW = 50;
GLfloat windowH = 50;

float theta;
GLfloat angle = 0.0;
void* currentfont;
GLint flag = 0;

int i, r=0, g = 0 , ye = 0, view=0 ;

// vertices for the cube
GLfloat x = 2.0f;
GLfloat y = 2.0f;
GLfloat z = 2.0f;

GLfloat xt = 0.0, rt=0.0 , xt1 = 0.0, rt1 = 0.0;

// variables to move outermost Object Frame (to move all the rendered environment)
GLfloat moveX = 0.0f;
GLfloat moveY = 0.0f;
GLfloat moveZ = 0.0f;

// variables to rotate outermost Object Frame (to move all the rendered environment)
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;


// For animating the rotation of the objects
GLfloat animateRotation = 0.0f;

//variables to move the camera
GLfloat camY = 0.0f;
GLfloat camX = 0.0f;
GLfloat camZ = 0.0f;

// A quadratic object pointer used to draw the sides of the cylinder
GLUquadricObj* qobj;

//An array to store the normal vector data for the faces
GLfloat vNormal[3] = {};



//Function to initialize the lighting properties. you can add upto 8 lights in openGL (0-7)
void initLighting() {

	//Decalring the Ambient, Diffuse components of the LIght_0 and the position in the eye coordinate system
	GLfloat L0_Ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat L0_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L0_postion[] = { 5, 5, 0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

	GLfloat L1_Ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat L1_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L1_Specular[] = { 0.0, 1.0, 0.0, 1.0 };   //Declaration of the specular component of the light_1
	GLfloat L1_postion[] = { -5, 5, 0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, L1_postion);

	//Declaration of the ligt reflecting properties for the materials
	GLfloat specularReflectance[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
	glMateriali(GL_FRONT, GL_SHININESS, 50);


	GLfloat L2_Ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat L2_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L2_Specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat L2_postion[] = { 0, 5, 5, 1.0 };
	GLfloat L2_SpotDirection[] = { 0.0, -1.0, -1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, L2_Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, L2_postion);

	//Creating a spotlight from light_2 by declaring the direction vetor and area that the spotligt can shine(fov of the spotlight)
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, L2_SpotDirection);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);


}



void init() {
	glClearColor(0.0, 0.79, 1.0, 1.0);
	GLfloat globalAmbient[] = { 0.4, 0.4, 0.4, 1.0 };
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//Enable the adding of lights
	glEnable(GL_LIGHTING);


	glShadeModel(GL_SMOOTH);

	// Changing the global Ambient illumination without any lights present
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	initLighting();

	// Enabling the color tracking of each faces of the materials. this enables the color visibility of the materials
	glEnable(GL_COLOR_MATERIAL);

	//Turn on lighting
	glEnable(GL_LIGHT0);
	// glEnable(GL_LIGHT1);
	// glEnable(GL_LIGHT2);

	// enable the normalization of the normal vectors (converting the vector values to the range 0-1)
	glEnable(GL_NORMALIZE);

}




void Road(GLfloat x, GLfloat z, GLfloat l, GLfloat w) {
	glColor3f(0.25f, 0.262f, .266f);

	//road texture

	/*texture[1] = SOIL_load_OGL_texture("road3.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, texture[1]);*/

	glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(x, 0.1, z);

	//glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(x, 0.1, z + l);

	//glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(x + w, 0.1, z + l);

	//glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(x + w, 0.1, z);
	glEnd();
}

void Seperation(GLfloat x, GLfloat y, GLfloat z, GLfloat l) {

	glColor3f(1.0, 1.0, 0.2);
	GLfloat w = 0.50;
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + l);
	glVertex3f(x + w, y, z + l);
	glVertex3f(x + w, y, z);
	glEnd();

}

void RoadSeperation(int r) {

	glColor3f(1, 1, 1);
	glTranslatef(0.0, 0.2, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	for (i = 0; i < r ; i++)
	{

		glTranslatef(2, 0, 0);
		glRectf(0, 0, 1, 0.5);       //White Bricks on Road
	}

	//glPopMatrix();
}
void carLights(GLfloat x, GLfloat y, GLfloat z, GLfloat s) {

	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y + s, z);
	glVertex3f(x, y + s, z + s);
	glVertex3f(x, y, z + s);
	glEnd();

}

void DrawGrid() {

	glNormal3f(0, 1, 0);

	glColor3f(0, 0.406, 0.039);

	//Grass texture

	/*texture[0] = SOIL_load_OGL_texture("grass2.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, texture[0]);*/

	glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-20, 0, -20);

	//glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(-20, 0, 20);

	//glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(20, 0, 20);

	//glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(20, 0, -20);
	glEnd();

}

void Tree() {
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);

	glPushMatrix();
	glTranslatef(4.75, .25, 3);
	//glRotatef(a, 0, 1, 0);
	glColor3f(0.133333, 0.545098, 0.133333);
	glutSolidCone(1.5, 2, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.75, .25, 4);
	//glRotatef(a, 0, 1, 0);
	glColor3f(0.133333, 0.545098, 0.133333);
	glutSolidCone(1.5, 2, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.75, .25, 5);
	//glRotatef(a, 0, 1, 0);
	glColor3f(0.133333, 0.545098, 0.133333);
	glutSolidCone(1.5, 2, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0.75, 0);
	//glRotatef(90, 1, 0, 0);
	glColor3f(0.823529, 0.411765, 0.117647);
	gluCylinder(quadratic,0.35,0.35,3.0,20,20);
	glPopMatrix();
	glEnd();
}

void signal()
{
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);

	
	//pole
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.250f, 0.250f, 4.0f, 12, 10);
	glPopMatrix();

	//cube
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(0.0, 4.7, 0.0);
	glScalef(1.5, 2.8, 1.5);
	glutSolidCube(0.5);
	glPopMatrix();


	//red
	glPushMatrix();
	glColor3f(r, 0.0f, 0.0f);
	glTranslatef(0.0, 5.1, 0.4);
	gluDisk(quadratic, 0, 0.2, 20, 20);
	glPopMatrix();

	//yellow
	glPushMatrix();
	glColor3f(ye, ye, 0.0f);
	glTranslatef(0.0, 4.6, 0.4);
	gluDisk(quadratic, 0, 0.2, 20, 20);
	glPopMatrix();

	//green
	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.7f);
	glColor3f(0.0f, g, 0.0f);
	glTranslatef(0.0, 4.1, 0.4);
	gluDisk(quadratic, 0, 0.2, 20, 20);
	glPopMatrix();


}

void car(GLfloat r, GLfloat g, GLfloat b) {

	//glutSolidCube(2.0);



	glBegin(GL_QUADS);                /* OBJECT MODULE*/

	/* top of cube*/
	//************************FRONT BODY****************************************
	glColor3f(r, g, b);
	glVertex3f(0.2, 0.4, 0.6);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.2, 0.4, 0.2);

	/* bottom of cube*/
	glVertex3f(0.2, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(0.2, 0.2, 0.2);

	/* front of cube*/
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.2, 0.2, 0.6);
	glVertex3f(0.2, 0.4, 0.6);
	glVertex3f(0.2, 0.4, 0.2);
	glVertex3f(0.2, 0.2, 0.2);

	/* back of cube.*/
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.6, 0.2, 0.2);

	/* left of cube*/
	glVertex3f(0.2, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.2, 0.4, 0.6);

	/* Right of cube */
	glVertex3f(0.2, 0.2, 0.2);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.2, 0.4, 0.2);
	//****************************************************************************
	glVertex3f(0.7, 0.65, 0.6);
	glVertex3f(0.7, 0.65, 0.2);
	glVertex3f(1.7, 0.65, 0.2);        //top cover
	glVertex3f(1.7, 0.65, 0.6);
	//***************************back guard******************************
	glColor3f(r, g, b);            /* Set The Color To Blue*/
	glVertex3f(1.8, 0.5, 0.6);
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.4, 0.6);

	/* bottom of cube*/
	glVertex3f(2.1, 0.2, 0.6);
	glVertex3f(2.1, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.6);
	glVertex3f(1.8, 0.2, 0.6);

	/* back of cube.*/
	glVertex3f(2.1, 0.4, 0.6);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.2, 0.2);
	glVertex3f(2.1, 0.2, 0.6);

	/* left of cube*/
	glVertex3f(1.8, 0.2, 0.2);
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.2, 0.2);

	/* Right of cube */
	glVertex3f(1.8, 0.2, 0.6);
	glVertex3f(1.8, 0.5, 0.6);
	glVertex3f(2.1, 0.4, 0.6);
	glVertex3f(2.1, 0.2, 0.6);
	//******************MIDDLE BODY************************************
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(1.8, 0.2, 0.6);
	glVertex3f(1.8, 0.5, 0.6);

	/* bottom of cube*/
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.6);

	/* back of cube.*/
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.2);
	glVertex3f(1.8, 0.5, 0.2);
	//*********************ENTER WINDOW**********************************
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.77, 0.63, 0.2);
	glVertex3f(0.75, 0.5, 0.2);        //quad front window
	glVertex3f(1.2, 0.5, 0.2);
	glVertex3f(1.22, 0.63, 0.2);

	glVertex3f(1.27, 0.63, .2);
	glVertex3f(1.25, 0.5, 0.2);        //quad back window
	glVertex3f(1.65, 0.5, 0.2);
	glVertex3f(1.67, 0.63, 0.2);

	glColor3f(r, g, b);
	glVertex3f(0.7, 0.65, 0.2);
	glVertex3f(0.7, 0.5, .2);       //first separation
	glVertex3f(0.75, 0.5, 0.2);
	glVertex3f(0.77, 0.65, 0.2);

	glVertex3f(1.2, 0.65, 0.2);
	glVertex3f(1.2, 0.5, .2);       //second separation
	glVertex3f(1.25, 0.5, 0.2);
	glVertex3f(1.27, 0.65, 0.2);

	glVertex3f(1.65, 0.65, 0.2);
	glVertex3f(1.65, 0.5, .2);     //3d separation
	glVertex3f(1.7, 0.5, 0.2);
	glVertex3f(1.7, 0.65, 0.2);

	glVertex3f(0.75, 0.65, 0.2);
	glVertex3f(0.75, 0.63, 0.2);        //line strip
	glVertex3f(1.7, 0.63, 0.2);
	glVertex3f(1.7, 0.65, 0.2);

	glVertex3f(0.75, 0.65, 0.6);
	glVertex3f(0.75, 0.63, 0.6);        //line strip
	glVertex3f(1.7, 0.63, 0.6);
	glVertex3f(1.7, 0.65, 0.6);

	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.77, 0.63, 0.6);
	glVertex3f(0.75, 0.5, 0.6);        //quad front window
	glVertex3f(1.2, 0.5, 0.6);
	glVertex3f(1.22, 0.63, 0.6);

	glVertex3f(1.27, 0.63, .6);
	glVertex3f(1.25, 0.5, 0.6);        //quad back window
	glVertex3f(1.65, 0.5, 0.6);
	glVertex3f(1.67, 0.63, 0.6);

	glColor3f(r, g, b);
	glVertex3f(0.7, 0.65, 0.6);
	glVertex3f(0.7, 0.5, .6);       //first separation
	glVertex3f(0.75, 0.5, 0.6);
	glVertex3f(0.77, 0.65, 0.6);

	glVertex3f(1.2, 0.65, 0.6);
	glVertex3f(1.2, 0.5, .6);       //second separation
	glVertex3f(1.25, 0.5, 0.6);
	glVertex3f(1.27, 0.65, 0.6);

	glVertex3f(1.65, 0.65, 0.6);
	glVertex3f(1.65, 0.5, .6);
	glVertex3f(1.7, 0.5, 0.6);
	glVertex3f(1.7, 0.65, 0.6);
	glEnd();


	//**************************************************************
	glBegin(GL_QUADS);

	/* top of cube*/
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.5, 0.2);        //quad front window
	glVertex3f(0.7, 0.65, 0.2);
	glVertex3f(0.7, 0.65, 0.6);

	glVertex3f(1.7, 0.65, .6);
	glVertex3f(1.7, 0.65, 0.2);        //quad back window
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(1.8, 0.5, 0.6);
	glEnd();


	glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

	  /* top of cube*/
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.7, 0.65, 0.6);       //tri front window
	glVertex3f(0.7, 0.5, 0.6);

	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.7, 0.65, 0.2);       //tri front window
	glVertex3f(0.7, 0.5, 0.2);

	glVertex3f(1.7, 0.65, 0.2);
	glVertex3f(1.8, 0.5, 0.2);       //tri back window
	glVertex3f(1.7, 0.5, 0.2);

	glVertex3f(1.7, 0.65, 0.6);
	glVertex3f(1.8, 0.5, 0.6);       //tri back window
	glVertex3f(1.7, 0.5, 0.6);

	glEnd();
	//************IGNITION SYSTEM**********************************
	/*glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(1.65, 0.2, 0.3);
	glRotatef(90.0, 0, 1, 0);
	gluCylinder(qobj, 0.02, 0.03, .5, 10, 10);
	glPopMatrix();*/
	//********************WHEEL*********************************************

	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 20)
	{
		glVertex3f(0.6, 0.2, 0.62);
		glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 20)
	{
		glVertex3f(0.6, 0.2, 0.18);
		glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 20)
	{
		glVertex3f(1.7, 0.2, 0.18);
		glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 20)
	{
		glVertex3f(1.7, 0.2, 0.62);
		glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
	}
	glEnd();
	glTranslatef(0.6, 0.2, 0.6);
	glColor3f(0, 0, 0);
	glutSolidTorus(0.025, 0.07, 10, 25);

	glTranslatef(0, 0, -0.4);
	glutSolidTorus(0.025, 0.07, 10, 25);

	glTranslatef(1.1, 0, 0);
	glutSolidTorus(0.025, 0.07, 10, 25);

	glTranslatef(0, 0, 0.4);
	glutSolidTorus(0.025, 0.07, 10, 25);
	glPopMatrix();
}





void building(GLfloat v[])
{
	//structure
	glPushMatrix();
	glTranslated(10, 3.5, -15);
	glColor3fv(v);
	glRotated(60, 0, 0, 0);
	glScaled(0.5, 1.0, 0.5);
	glutSolidCube(15.0);
	glPopMatrix();

	//Windows
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslated(6.2, 3.0, -13);
	glRotated(60, 0, 0, 0);
	glRectf(5,5,7,7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(7.7, 3.0, -13);
	glRotated(60, 0, 0, 0);
	glRectf(5, 5, 7, 7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(7.7, 1.5, -13);
	glRotated(60, 0, 0, 0);
	glRectf(5, 5, 7, 7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(6.2, 1.5, -13);
	glRotated(60, 0, 0, 0);
	glRectf(5, 5, 7, 7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(6.2, 0.1, -13);
	glRotated(60, 0, 0, 0);
	glRectf(5, 5, 7, 7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(7.7, 0.1, -13);
	glRotated(60, 0, 0, 0);
	glRectf(5, 5, 7, 7);
	glPopMatrix();

	//Door
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(8.0, -5.0, -9);
	glRotated(90, 0, 1, 0);
	glRectf(5, 5, 7, 7);
	glPopMatrix();

	//Window
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(8.1, 0.1, -10.3);
	glRotated(90, 0, 1, 0);
	glRectf(5, 5, 6.2, 6.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(8.1, 0.1, -8.5);
	glRotated(90, 0, 1, 0);
	glRectf(5, 5, 6.2, 6.2);
	glPopMatrix();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glPushMatrix();

	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(-0.0 + camX, 2.0 + camY, 15.0 + camZ, -2, 0, 0, 0, 1.0, 0);

	// move the object frame using keyboard keys
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
	glColor3f(0.2, 0.20, 0.20);
	DrawGrid();

	//Road
	glPushMatrix();
	glTranslated(-4.5, 0, 0);
	glNormal3f(1.0, 1.0, 0.0);
	Road(-5.0, -20.0, 40.0, 10.0);

	// Side Yellow lines
	Seperation(-5.0, 0.2, -20.0, 40.0);
	Seperation(5.0, 0.2, -20.0, 40.0);

	//white dashed line
	glPushMatrix();
	glTranslated(0.0, 0.0, 22.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	RoadSeperation(20);
	glPopMatrix();

	//Buildings
	GLfloat buildingColor[] = { .929, .832, .715 };
	building(buildingColor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0, 0);
	GLfloat buildingColor1[] = { 1,1,0 };
	building(buildingColor1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	GLfloat buildingColor2[] = { 0.721569,0.52549,0.0431373 };
	building(buildingColor2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-8);
	glRotatef(90, 0, 1, 0);
	GLfloat buildingColor3[] = { 1.0,0,1.0};
	building(buildingColor3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 8);
	glRotatef(90, 0, 1, 0);
	GLfloat buildingColor4[] = { 0.45,0.2,0.2};
	building(buildingColor4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 15);
	glRotatef(90, 0, 1, 0);
	building(buildingColor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 21);
	glRotatef(90, 0, 1, 0);
	building(buildingColor2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 27);
	glRotatef(90, 0, 1, 0);
	building(buildingColor4);
	glPopMatrix();

	//Tree
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3);
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 6);
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 9);
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 12);
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 15);
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 18);
	glRotatef(-90, 1, 0, 0);
	Tree();
	glPopMatrix();

	//side road
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslated(-6.0, 0, 0);
	Road(-5.0, -20.0, 19.5, 10.0);
	// Side Yellow lines
	Seperation(-5.0, 0.2, -20.0, 19.0);
	Seperation(5.0, 0.2, -20.0, 19.0);

	//white dashed line
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	RoadSeperation(9);
	glPopMatrix();
	glPopMatrix();

	//Traffic light
	glPushMatrix();
	signal();
	glPopMatrix();
	
	//Blue car
	glPushMatrix();
	glScalef(2.5, 2.5, 2.0);
	glRotatef(-90+rt, 0, 1, 0);
	glTranslatef(xt, 0, 0.51);
	car(0.0,0.0,1.0);
	glColor3f(1.0, 1.0, 0.0);
	carLights(0.2, 0.22, 0.22, 0.08);
	carLights(0.2, 0.22, 0.5, 0.08);
	glColor3f(1.0, 0.0, 0.0);
	carLights(2.1, 0.3, 0.22, 0.08);
	carLights(2.1, 0.3, 0.5, 0.08);
	glPopMatrix();

	//red car
	glPushMatrix();
	glScalef(2.5, 2.5, 2.0);
	glRotatef(0 + rt1, 0, 1, 0);
	glTranslatef(xt1, 0, -4.0);

	car(1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	carLights(0.2, 0.22, 0.22, 0.08);
	carLights(0.2, 0.22, 0.5, 0.08);
	glColor3f(1.0, 0.0, 0.0);
	carLights(2.1, 0.3, 0.22, 0.08);
	carLights(2.1, 0.3, 0.5, 0.08);
	glPopMatrix();

	//car #3
	glPushMatrix();
	glScalef(2.5, 2.5, 2.0);
	glRotatef(-270, 0, 1, 0);
	glTranslatef(5 + xt, 0, -3.0);

	car(1.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	carLights(0.2, 0.22, 0.22, 0.08);
	carLights(0.2, 0.22, 0.5, 0.08);
	glColor3f(1.0, 0.0, 0.0);
	carLights(2.1, 0.3, 0.22, 0.08);
	carLights(2.1, 0.3, 0.5, 0.08);
	glPopMatrix();

	glPopMatrix();

	glFlush();

}


static void SpecialKeyFunc(int Key, int x, int y){
	switch (Key) {
	//Reverse
	case GLUT_KEY_DOWN:
		xt += 0.5;
		glutPostRedisplay();
		break;
	
	//Forward
	case GLUT_KEY_UP:
		xt -= 0.5;
		glutPostRedisplay();
		break;

	//turn right
	case GLUT_KEY_LEFT:
		rt += 0.5;
		glutPostRedisplay();
		break;
	
	//turn left
	case GLUT_KEY_RIGHT:
		rt -= 0.5;
		glutPostRedisplay();
		break;
	}

}


void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		moveZ += 1;

	if (key == GLUT_KEY_DOWN)
		moveZ -= 1;


	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	//enable and disable fog
	if (key == 'f') {
		GLfloat fogcolour[4] = { 1.0,1.0,1.0,1.0 };

		glFogfv(GL_FOG_COLOR, fogcolour);              /* Define the fog colour */
		glFogf(GL_FOG_DENSITY, 0.1);                   /* How dense */
		glFogi(GL_FOG_MODE, GL_EXP);                   /* exponential decay */
		glFogf(GL_FOG_START, -10.0);                   /* Where wwe start fogging */
		glFogf(GL_FOG_END, -300.0);                       /* end */
		glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
		glEnable(GL_FOG);
	}
	if (key == 'F')
		glDisable(GL_FOG);
	
	//camera angle y axis
	if (key == 'w')
		camY += 0.5;
	if (key == 's')
		camY -= 0.5;

	//rotate y axis
	if (key == 'a')
		rotY += 5.0;
	if (key == 'd')
		rotY -= 5.0;

	//Color lights
	//green light 
	if (key == 'g') {
		g = 1;
		r = 0;
		ye = 0;
	}
	//red light
	if (key == 'r') {
		g = 0;
		r = 1;
		ye = 0;
	}
	//yellow light
	if (key == 'y')
	{
		g = 0;
		r = 0;
		ye = 1;
	}

	//movements for red car
	//right
	if (key == 't') {
		rt1 += 0.5;
		glutPostRedisplay();
	}
	//left
	if (key == 'u') {
		rt1 -= 0.5;
		glutPostRedisplay();
	}
	//up
	if (key == 'h') {
		xt1 -= 0.5;
		glutPostRedisplay();
	}
	//down
	if (key == 'n') {
		xt1 += 0.5;
		glutPostRedisplay();
	}



	if (key == 'k')
		glDisable(GL_LIGHT0);
	if (key == 'K')
		glEnable(GL_LIGHT0);
	if (key == 'l')
		glDisable(GL_LIGHT1);
	if (key == 'L')
		glEnable(GL_LIGHT1);
	if (key == 'j')
		glDisable(GL_LIGHT2);
	if (key == 'J')
		glEnable(GL_LIGHT2);

	glutPostRedisplay();

}

void Timer(int x) {
	animateRotation += animateRotation >= 360.0 ? -animateRotation : 5;
	glutPostRedisplay();

	glutTimerFunc(60, Timer, 1);
}

void changeSize(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(120, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutCreateWindow("OpenGL Setup Test");

	glutInitWindowPosition(150, 150);
	glutInitWindowSize(600, 600);

	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	// keyboard function activation
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeyFunc);

	glutMainLoop();


	return 0;
}

