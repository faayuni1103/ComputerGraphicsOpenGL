//************************************************************
// Assignment 3                                              *
// Group 2                                                   *
// - Amirul Shafiq Bin Amirrullah                            *
// - Henry Meshack Okinyi Odongo	                         *
// - Fatin Aimi Ayuni Binti Affindy                          *
// - Abdul Barik Habibi Bin Mohd Iskandar                    *
//                                                           *
// Movement guide:                                           *
// - l: rotate the left arm on x axis                        *
// - r: rotate the right arm on x axis                       *
// - e: translate the eyes from inside to outside            *
// - b: rotate Eve on y axis                                 *
// - x: translate on x axis                                  *
// - y: translate on y axis                                  *
// - z: translate on z axis                                  *
// - p/P: play audio (18 seconds)                            *
// - s/S: stop audio                                         *
// - a/A: enable lighting                                    *
// - n/N: disable lighting                                   *
// - hold left-click button to stop rotation                 *
// - release left-click button to continue rotation          *
// - use uppercase letters to reverse the transformation     *
//************************************************************

#include <GL/glut.h> // Include the GLUT header file
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include "imageloader.h"

float angle = 0.0, increment = 0.5;
static int left = 0, right = 0, body = 0;
static float eye = 0.7, xi = 0.0, yi = 0.0, zi = 0.0;

GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;
GLuint _textureId7;
GLuint _textureId8;
GLuint _textureId9;

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void instruction(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -4, 5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0, 0, 0);
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void initRendering(void)
{
	// this function will initialize the images used

	Image* image1 = loadBMP("image/BGPic.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("image/WallE_EVE.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("image/BNL-metalbox-front.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("image/BNL-metalbox-side.bmp");
	_textureId4 = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("image/CompactTrash.bmp");
	_textureId5 = loadTexture(image5);
	delete image5;
	
	Image* image6 = loadBMP("image/TVscreen.bmp");
	_textureId6 = loadTexture(image6);
	delete image6;

	Image* image7 = loadBMP("image/TVside.bmp");
	_textureId7 = loadTexture(image7);
	delete image7;

	Image* image8 = loadBMP("image/WallE-front.bmp");
	_textureId8 = loadTexture(image8);
	delete image8;

	Image* image9 = loadBMP("image/WallE-side.bmp");
	_textureId9 = loadTexture(image9);
	delete image9;
}

void displayTextureItems(void)
{
	// this function will draw rectangles for ground and background
	// and use texture mapping method to display the bmp files

	//Draw ground
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(0.2f, 0.2f, 0.7f);
	glScaled(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 0.3f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-40.0f, -9.0f, -25.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-40.0f, -9.0f, 20.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(40.0f, -9.0f, 20.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(40.0f, -9.0f, -25.0f);
	glEnd();
	glPopMatrix();
	
	glTranslatef(0.0, -1.5, -1.0);
	//the background picture
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5f, 5.0f, -2.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, -2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, -2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5f, 5.0f, -2.5f);
	glEnd();
	glPopMatrix();
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) // the parameters required for the four points of a surface
{
	// this function will draw a surface

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);	
	glVertex3f(A[0], A[1], A[2]);
	glTexCoord2f(0.0f, 1.0f);	
	glVertex3fv(B);
	glTexCoord2f(1.0f, 1.0f);	
	glVertex3fv(C);
	glTexCoord2f(1.0f, 0.0f);	
	glVertex3fv(D);
	glEnd();
}

void BNLbox(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
	// this function will call the face function to implement the surface textures

	// drawing the front surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V2, V3);
	glPopMatrix();

	// drawing the back surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V4, V5, V6, V7);;
	glPopMatrix();

	// drawing the left surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V4, V7, V3);
	glPopMatrix();

	// drawing the right surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V1, V5, V6, V2);
	glPopMatrix();

	// drawing the bottom surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V2, V3, V7, V6);
	glPopMatrix();

	// drawing the top surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V5, V4);
	glPopMatrix();
}

void CompactTrash(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
	// this function will call the face function to implement the surface textures

	// drawing the front surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V2, V3);
	glPopMatrix();

	// drawing the back surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V4, V5, V6, V7);;
	glPopMatrix();

	// drawing the left surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V4, V7, V3);
	glPopMatrix();

	// drawing the right surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V1, V5, V6, V2);
	glPopMatrix();

	// drawing the bottom surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V2, V3, V7, V6);
	glPopMatrix();

	// drawing the top surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V5, V4);
	glPopMatrix();
}

void Television(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
	// this function will call the face function to implement the surface textures

	// drawing the front surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId6);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V2, V3);
	glPopMatrix();

	// drawing the back surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId7);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V4, V5, V6, V7);;
	glPopMatrix();

	// drawing the left surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId7);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V4, V7, V3);
	glPopMatrix();

	// drawing the right surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId7);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V1, V5, V6, V2);
	glPopMatrix();

	// drawing the bottom surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId7);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V2, V3, V7, V6);
	glPopMatrix();

	// drawing the top surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId7);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V5, V4);
	glPopMatrix();
}

void wallE(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
	// this function will call the face function to implement the surface textures

	// drawing the front surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId8);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V2, V3);
	glPopMatrix();

	// drawing the back surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId9);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V4, V5, V6, V7);;
	glPopMatrix();

	// drawing the left surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId9);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V4, V7, V3);
	glPopMatrix();

	// drawing the right surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId9);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V1, V5, V6, V2);
	glPopMatrix();

	// drawing the bottom surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId9);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V2, V3, V7, V6);
	glPopMatrix();

	// drawing the top surface
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId9);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.6, 0.6, 0.6);
	Face(V0, V1, V5, V4);
	glPopMatrix();
}

void drawScene()
{
	// this function will draw 4 new cubes as surrounding objects

	// draw a box (defining front and back surfaces)
	GLfloat V[8][3] = { // 'V' stands for Vertices
		// front surface coordinates
		{-0.5, 0.5, 0.5}, // first point
		{ 0.5, 0.5, 0.5}, // second point
		{ 0.5,-0.5, 0.5}, // third point
		{-0.5,-0.5, 0.5}, // fourth point

		// back surface coordinates
		{-0.5, 0.5,-0.5}, // fifth point
		{ 0.5, 0.5,-0.5}, // sixth point
		{ 0.5,-0.5,-0.5}, // seventh point
		{-0.5,-0.5,-0.5} // eigth point
	};

	glRotatef(90, 0.0, 0.0, 0.5);

	// calling the cube function
	glTranslatef(-0.5f, 0.5f, -0.3f);
	BNLbox(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

	glTranslatef(0.2f, 2.5f, 0.0f);
	CompactTrash(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

	glTranslatef(0.0f, -3.5f, 0.0f);
	Television(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

	glTranslatef(-0.8f, 2.5f, 0.0f);
	wallE(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
}

void eve()
{
	// this function will draw Eve from Wall-E onto the screen

	glPushMatrix();
	glRotated((GLfloat)body, 0.0, 0.5, 0.0);
	glTranslated((GLfloat)xi, (GLfloat)yi, (GLfloat)zi);

	// head
	double yi = 0.1, r = 0.35;

	for (int i = 0; i < 80; i++)
	{
		glPushMatrix();
		glColor3d(0.88, 0.91, 0.91);
		glTranslated(0.0, yi, 0.0);
		glRotated(-90, -1.0, 0.0, 0.0);
		gluCylinder(gluNewQuadric(), r, r, 0.05, 30, 30);
		glPopMatrix();

		yi = yi + 0.003;

		glPushMatrix();
		glColor3d(0.88, 0.91, 0.91);
		glTranslated(0.0, yi, 0.0);
		glRotated(-90, -1.0, 0.0, 0.0);
		gluCylinder(gluNewQuadric(), r, r, 0.05, 30, 30);
		glPopMatrix();

		r = r - 0.0005;
	}

	glPushMatrix();
	glColor3d(0.88, 0.91, 0.91);
	glScaled(1.0, 0.5, 1.0);
	glTranslated(0.0, yi + 0.3, 0.0);
	glutSolidSphere(r, 20, 20);
	glPopMatrix();

	// face
	glPushMatrix();
	glColor3d(0.04, 0.07, 0.07);
	glTranslated(0.0, 0.22, 0.21);
	glRotated(-90, -1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.22, 0.23, 0.12, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.04, 0.07, 0.07);
	glScaled(1.3, 0.65, 0.5);
	glTranslated(0.0, 0.33, 0.67);
	glutSolidSphere(0.155, 20, 20);
	glPopMatrix();

	// right eye
	glPushMatrix();
	glColor3d(0.53, 0.73, 0.9);
	glScaled(0.3, 0.18, 0.5);
	glTranslated(0.25, 1.0, (GLfloat)eye);
	glutSolidSphere(0.23, 20, 20);
	glPopMatrix();

	// left eye
	glPushMatrix();
	glColor3d(0.53, 0.73, 0.9);
	glScaled(0.3, 0.18, 0.5);
	glTranslated(-0.25, 1.0, (GLfloat)eye);
	glutSolidSphere(0.23, 20, 20);
	glPopMatrix();

	// body
	glPushMatrix();
	glColor3d(0.88, 0.91, 0.91);
	glRotated(-90, -1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.35, 0.2, 0.8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.88, 0.91, 0.91);
	glScaled(1.0, 0.5, 1.0);
	glTranslated(0.0, -0.75, 0.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	// right hand
	glPushMatrix();
	glColor3d(0.88, 0.91, 0.91);
	glRotated((GLfloat)right, 0.7, 0.0, 0.0);
	glScaled(0.6, 2.3, 0.5);
	glTranslated(0.7, -0.15, 0.0);
	glutSolidSphere(0.15, 20, 20);
	glPopMatrix();

	// left hand
	glPushMatrix();
	glColor3d(0.88, 0.91, 0.91);
	glRotated((GLfloat)left, -0.7, 0.0, 0.0);
	glScaled(0.6, 2.3, 0.5);
	glTranslated(-0.7, -0.15, 0.0);
	glutSolidSphere(0.15, 20, 20);
	glPopMatrix();

	glPopMatrix();
}

void mike()
{
	// this function will draw Mike from Monster Inc onto the screen
	
	// head
	double yi = 0.1, r = 0.35;

	for (int i = 0; i < 80; i++)
	{

		glPushMatrix();
		glColor3d(0.4, 0.87, 0.41);
		glTranslated(0.0, yi, 0.0);
		glRotated(-90, -1.0, 0.0, 0.0);
		glutSolidSphere(r, 20, 20);
		glPopMatrix();

		r = r - 0.0005;
	}

	// 1 eye (white)
	glPushMatrix();
	glColor3d(0.9, 0.9, 1.0);
	glScaled(0.22, 0.2, 0.3);
	glTranslated(0.0, 0.85, 0.7);
	glutSolidSphere(0.75, 20, 20);
	glPopMatrix();

	// 1 eye pupil
	glPushMatrix();
	glColor3d(0.1, 0.0, 0.1);
	glScaled(0.12, 0.1, 0.3);
	glTranslated(0.0, 1.35, 0.9);
	glutSolidSphere(0.7, 20, 20);
	glPopMatrix();

	// The mouth
	glPushMatrix();
	glColor3d(0.04, 0.07, 0.07);
	glTranslated(0.0, 0.01, 0.21);
	glRotated(-90, -1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.2, 0.15, 0.08, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.04, 0.07, 0.07);
	glScaled(1.0, 0.5, 1.0);
	glTranslated(0.0, -0.11, 0.21);
	glutSolidSphere(0.15, 20, 20);
	glPopMatrix();

	// right hand
	glPushMatrix();
	glColor3d(0.4, 0.87, 0.41);
	glScaled(0.55, 2.3, 0.5);
	glTranslated(0.67, 0.15, 0.2);
	glutSolidCube(0.22);
	glPopMatrix();

	// left hand
	glPushMatrix();
	glColor3d(0.4, 0.87, 0.41);
	glScaled(0.55, 2.3, 0.5);
	glTranslated(-0.66, 0.15, 0.2);
	glutSolidCube(0.22);
	glPopMatrix();

	// left leg
	glPushMatrix();
	glColor3d(0.4, 0.87, 0.41);
	glScaled(0.56, -2.1, 0.5);
	glTranslated(-0.21, 0.2, 0.2);
	glutSolidCube(0.22);
	glPopMatrix();

	// right leg
	glPushMatrix();
	glColor3d(0.4, 0.87, 0.41);
	glScaled(0.56, -2.1, 0.5);
	glTranslated(0.21, 0.2, 0.2);
	glutSolidCube(0.22);
	glPopMatrix();

	// right horn
	glPushMatrix();
	glColor3d(0.33, 0.72, 0.34);
	glTranslated(0.18, 0.37, 0.1);
	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(30, 0.0, 1.0, 0.0);
	glutSolidCone(0.04, 0.08, 10, 10);
	glPopMatrix();

	// left horn
	glPushMatrix();
	glColor3d(0.33, 0.72, 0.34);
	glTranslated(-0.18, 0.37, 0.1);
	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(-30, 0.0, 1.0, 0.0);
	glutSolidCone(0.04, 0.08, 10, 10);
	glPopMatrix();
}

void renderBitmap(float x, float y, float z, void* font, char* string)
{
	// this function will display each characters onto the screen

	char* c;

	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void displayTexts()
{
	// this function will display the text onto the screen

	char buf[100] = { 0 };

	glColor3f(0.29, 0.07, 0.5);
	sprintf_s(buf, "Keyboard Interaction");
	renderBitmap(1.0, 2.6, -3.0, GLUT_BITMAP_HELVETICA_18, buf);

	glColor3f(0.51, 0.05, 0.14);
	sprintf_s(buf, "l: rotate the left arm on x axis");
	renderBitmap(1.0, 2.45, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "r: rotate the right arm on x axis");
	renderBitmap(1.0, 2.3, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "e: translate the eyes from inside to outside");
	renderBitmap(1.0, 2.15, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "b: rotate Eve on y axis");
	renderBitmap(1.0, 2.0, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "x: translate on x axis");
	renderBitmap(1.0, 1.85, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "y: translate on y axis");
	renderBitmap(1.0, 1.70, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "z: translate on z axis");
	renderBitmap(1.0, 1.55, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "p/P: play audio (18 seconds)");
	renderBitmap(1.0, 1.40, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "s/S: stop audio");
	renderBitmap(1.0, 1.25, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "a/A: enable lighting");
	renderBitmap(1.0, 1.10, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "n/N: disable lighting");
	renderBitmap(1.0, 0.95, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "- Hold left-click button to stop rotation -");
	renderBitmap(1.0, 0.80, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "- Release left-click button to continue rotation -");
	renderBitmap(1.0, 0.65, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "- Use uppercase letters to reverse the transformation -");
	renderBitmap(1.0, 0.50, -3.0, GLUT_BITMAP_HELVETICA_12, buf);
}

void lighting()
{
	// this function is to add lighting to the scene

	// add ambient light
	GLfloat ambientColor[] = { 0.48f, 0.48f, 0.48f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	// add positioned light
	GLfloat lightColor0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	// add directed light
	GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

void display(void)
{
	// this function will display all primitives onto the screen.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	
	lighting();

	glTranslatef(-0.4, 0.0, -3.0);
	glRotatef(5, 0.0, 0.5, 0.0);
	//glRotatef(angle, 0.0, 0.5, 0.0);    // to rotate the models automatically
	eve();

	glTranslatef(1.0, -0.2, -0.5);
	glRotatef(-15, 0.0, 0.5, 0.0);
	mike();
	
	glRotatef(10, 0.0, 0.5, 0.0);
	glTranslatef(-0.6, 0.2, 0.0);
	//displayTextureItems();
	
	glTranslatef(1.3, 1.8, 0.0);
	//displayTexts();

	//drawScene();

	glFlush();
	glutSwapBuffers();
}

void init()
{
	// this function will do some initialization for the background color
	// and set the 2d orthographic projection for 2d objects.

	glClearColor(0.6, 0.82, 0.96, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); // Enable lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1); 
	glEnable(GL_NORMALIZE); // Automatically normalize normals
	gluOrtho2D(-50, 50, -50, 50);
}

void timer(int)
{
	// this will be used as a timer to constantly rotate the graphics

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);

	angle += increment;
	if (angle > 360.0)
		angle -= 360.0;
}

void keyboard(unsigned char key, int x, int y)
{
	// this function is for the keyboard interaction

	switch (key) {
	case 'l':
		left = (left + 10) % 360;
		break;

	case 'L':
		left = (left - 10) % 360;
		break;

	case 'r':
		right = (right + 10) % 360;
		break;

	case 'R':
		right = (right - 10) % 360;
		break;

	case 'e':
		eye += 0.01;
		if (eye > 0.7)
			eye = 0.7;
		break;

	case 'E':
		eye -= 0.01;
		if (eye < 0.0)
			eye = 0.0;
		break;

	case 'b':
		body = (body + 5) % 360;
		break;

	case 'B':
		body = (body - 5) % 360;
		break;

	case 'x':
		xi += 0.05;
		if (xi > 3.0)
			xi = 3.0;
		break;

	case 'X':
		xi -= 0.05;
		if (xi < -1.5)
			xi = -1.5;
		break;

	case 'y':
		yi += 0.05;
		if (yi > 0.8)
			yi = 0.8;
		break;

	case 'Y':
		yi -= 0.05;
		if (yi < -0.15)
			yi = -0.15;
		break;

	case 'z':
		zi += 0.05;
		if (zi > 1.0)
			zi = 1.0;
		break;

	case 'Z':
		zi -= 0.05;
		if (zi < -2.5)
			zi = -2.5;
		break;

	case 'p':
	case 'P': // play audio
		PlaySoundA("audio/Evaaaa.wav", NULL, SND_ASYNC | SND_FILENAME);
		break;

	case 's':
	case 'S': // stop audio
		PlaySoundA(NULL, 0, 0);
		break;

	case 'a':
	case 'A': // enable lighting
		glEnable(GL_LIGHTING);
		break;

	case 'n':
	case 'N': // disable lighting
		glDisable(GL_LIGHTING);
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
	glFlush();
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	// this function is use for mouse interaction

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // stop the rotation
		increment = 0.0;
	else // continue the rotation
		increment = 0.5f;
}

void changeSize(int w, int h)
{
	// this function will make sure the window is resizable

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width)
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Set the viewport to be the entire window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset matrix
	glLoadIdentity();

	// Set the correct perspective to view 3d objects
	gluPerspective(45, ratio, 1, 200);

	// Get back to the modelview
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	// this is the main function of this project.
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Eve from Wall-E and Mike from Monster Inc");
	init();
	initRendering();

	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutTimerFunc(0, timer, 0);

	// enter GLUT event processing loop
	glutMainLoop();

	return 1;
}