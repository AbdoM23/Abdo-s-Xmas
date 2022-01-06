#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <Windows.h>
#include <MMSystem.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 0.0f, float eyeY = 2.0f, float eyeZ = 5.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

int counter = 0;
int clock1 = 10;
int time1 = 0;
float fcolorx = 1.0f;
float fcolory = 0.5f;
float fcolorz = 0.0f;
GLdouble x1 = 0.0;
GLdouble z1 = 0.0;
GLdouble g = 0.0;
bool gPressed = false;
bool hide1 = false;
bool hide2 = false;
bool hide3 = false;
int hidden[] = { 0, 0, 0 };

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	if ((x1 >= 0.400000 && x1 <= 0.500000) && (z1 >= -0.100000 && z1 <= 0.100000)) {
		hide1 = true;
	}
	if ((x1 >= -0.700000 && x1 <= -0.600000) && (z1 >= -0.100000 && z1 <= 0.100000)) {
		hide2 = true;
	}
	if ((x1 >= -0.700000 && x1 <= -0.600000) && (z1 >= -1.000000 && z1 <= -0.90000)) {
		hide3 = true;
	}

	switch (key) {
	case 'd':
		if (x1 >= 0.9)
			printf("");
		else
			x1 = x1 + 0.1;
		break;
	case 'a':
		if (x1 <= -0.9)
			printf("");
		else
			x1 = x1 - 0.1;
		break;
	case 's':
		if (z1 >= 0.6)
			printf("");
		else
			z1 = z1 + 0.1;
		break;
	case 'w':
		if (z1 <= -1.6)
			printf("");
		else
			z1 = z1 - 0.1;
		break;
	case 'g':
		if (!gPressed) {
			g += 0.5;
			gPressed = true;
		}
		break;
	case 'h':
		if (gPressed) {
			g -= 0.5;
			gPressed = false;
		}

	}

	switch (key) {
	case 'i':
		camera.moveY(d);
		break;
	case 'k':
		camera.moveY(-d);
		break;
	case 'j':
		camera.moveX(d);
		break;
	case 'l':
		camera.moveX(-d);
		break;
	case 'm':
		camera.moveZ(d);
		break;
	case 'n':
		camera.moveZ(-d);
		break;
	case 'f':
		camera.eye.x = 0.0f;
		camera.eye.y = 1.0f;
		camera.eye.z = 5.0f;
		camera.center.x = 0.0f;
		camera.center.y = 0.0f;
		camera.center.z = 0.0f;
		camera.up.x = 0.0f;
		camera.up.y = 1.0f;
		camera.up.z = 0.0f;
		break;
	case 't':
		camera.eye.x = 0.0f;
		camera.eye.y = 3.11f;
		camera.eye.z = 4.18f;
		camera.center.x = 0.0f;
		camera.center.y = 2.33f;
		camera.center.z = 3.55f;
		camera.up.x = -0.015f;
		camera.up.y = 0.633f;
		camera.up.z = -0.7738f;
		break;
	case'v':
		camera.eye.x = 3.52f;
		camera.eye.y = 2.40f;
		camera.eye.z = 1.77f;
		camera.center.x = 2.59f;
		camera.center.y = 2.04f;
		camera.center.z = 1.77f;
		camera.up.x = 0.0f;
		camera.up.y = 1.0f;
		camera.up.z = 0.0f;
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

GLdouble sColorx = 1.0f;
GLdouble sColory = 0.0f;

void santa() {
	glPushMatrix();
	glTranslated(0.0 + x1, 0.3, 2.5 + z1);
	glRotated(-90, 1, 0, 0);
	glScaled(0.5, 0.5 + g, 0.5);
	glColor3d(sColorx, sColory, 0.0f);
	glutSolidCone(0.5, 1.5, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 0.3, 2.5 + z1);
	glScaled(0.5, 0.1 + g, 0.5);
	glColor3d(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.2, 0.6, 2.5 + z1);
	glRotated(52, 0, 0, 1);
	glScaled(0.05, 0.3 + g, 0.1);
	glColor3d(sColorx, sColory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 - 0.2, 0.6, 2.5 + z1);
	glRotated(-52, 0, 0, 1);
	glScaled(0.05, 0.3 + g, 0.1);
	glColor3d(sColorx, sColory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.12, 0.2, 2.5 + z1);
	glScaled(0.07, 0.5 + g, 0.1);
	glColor3d(sColorx, sColory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + -0.12, 0.2, 2.5 + z1);
	glScaled(0.07, 0.5 + g, 0.1);
	glColor3d(sColorx, sColory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 0.9, 2.5 + z1);
	glScaled(0.20, 0.25 + g, 0.25);
	glColor3d(0.7f, 0.7f, 0.7f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 0.80, 2.5 + z1);
	glScaled(0.35, 0.2 + g, 0.35);
	glColor3d(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.35, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 0.95, 2.5 + z1);
	glScaled(0.35, 0.2 + g, 0.35);
	glColor3d(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.35, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 0.95, 2.5 + z1);
	glRotated(-90, 1, 0, 0);
	glColor3f(sColorx, sColory, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidCone(1.0, 2.0, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 1.15, 2.5 + z1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + -0.045, 0.9, 2.65 + z1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.1, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.045, 0.9, 2.65 + z1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.1, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1 + 0.0, 0.50, 2.5 + z1);
	glScaled(0.55, 0.2 + g, 0.55);
	glColor3d(0.3f, 0.0f, 0.0f);
	glutSolidSphere(0.35, 25, 25);
	glPopMatrix();
}

void present1() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.20, 2.5);
	glScaled(0.5, 0.5 + g, 0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.20, 2.61);
	glScaled(0.1, 0.5 + g, 0.1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.31, 2.5);
	glRotated(90, 0, 0, 1);
	glScaled(0.1, 0.5 + g, 0.1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.31, 2.5);
	glRotated(90, 0, 0, 1);
	glScaled(0.1, 0.1 + g, 0.5);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.35, 2.5);
	glColor3f(0.0f, 1.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPopMatrix();
}

void present2() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.20, 2.5);
	glScaled(0.5, 0.5 + g, 0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.20, 2.61);
	glScaled(0.1, 0.5 + g, 0.1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.31, 2.5);
	glRotated(90, 0, 0, 1);
	glScaled(0.1, 0.5 + g, 0.1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.31, 2.5);
	glRotated(90, 0, 0, 1);
	glScaled(0.1, 0.1 + g, 0.5);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.35, 2.5);
	glColor3f(0.0f, 1.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPopMatrix();
	//Present2 end
}

void present3() {
	glPushMatrix();
	glTranslated(0.0, 0.0, -0.8);
	glPushMatrix();
	glTranslated(-0.7, 0.20, 2.5);
	glScaled(0.5, 0.5 + g, 0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.20, 2.61);
	glScaled(0.1, 0.5 + g, 0.1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.31, 2.5);
	glRotated(90, 0, 0, 1);
	glScaled(0.1, 0.5 + g, 0.1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.31, 2.5);
	glRotated(90, 0, 0, 1);
	glScaled(0.1, 0.1 + g, 0.5);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, 0.35, 2.5);
	glColor3f(0.0f, 1.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPopMatrix();
}

void Display() {
	setupCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	santa();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslated(-2.5, 0.0, 0.0);
	glColor3f(0.9f, 0.9f, 1.0f);
	glScaled(4.0, 0.1, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	//tree1 start
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, -0.8, 0.1);
	glColor3f(0.0f, 0.5f, 0.0f);
	glScaled(0.35, 0.35 + g, 0.35);
	glutSolidCone(1, 2, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, -0.8, 0.3);
	glColor3f(0.0f, 0.5f, 0.0f);
	glScaled(0.30, 0.30 + g, 0.30);
	glutSolidCone(1, 2, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, -0.8, 0.5);
	glColor3f(0.0f, 0.5f, 0.0f);
	glScaled(0.25, 0.25 + g, 0.25);
	glutSolidCone(1, 2, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, -0.8, 1.0);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glScaled(0.05, 0.05 + g, 0.05);
	glutSolidSphere(1, 25, 25);
	glPopMatrix();
	//tree1 end

	//tree2 start
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, 0.8, 0.1);
	glColor3f(0.0f, 0.5f, 0.0f);
	glScaled(0.35, 0.35 + g, 0.35);
	glutSolidCone(1, 2, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, 0.8, 0.3);
	glColor3f(0.0f, 0.5f, 0.0f);
	glScaled(0.30, 0.30 + g, 0.30);
	glutSolidCone(1, 2, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, 0.8, 0.5);
	glColor3f(0.0f, 0.5f, 0.0f);
	glScaled(0.25, 0.25 + g, 0.25);
	glutSolidCone(1, 2, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.0, 0.8, 1.0);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glScaled(0.05, 0.05 + g, 0.05);
	glutSolidSphere(1, 25, 25);
	glPopMatrix();
	//tree2 end

	//fence centre start
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslated(0.4, 0.5, 0.0);
	glScaled(0.1, 0.1 + g, 2.4);
	glColor3f(fcolorx, fcolory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(1.0, 0.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(0.5, 0.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(0.0, 0.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-0.5, 0.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-1.0, 0.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();
	//fence centre end

	//fence right start
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.4, 1.2, -2.0);
	glScaled(0.1, 0.1 + g, 2.4);
	glColor3f(fcolorx, fcolory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-1.2, 1.0, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-1.2, 1.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-1.2, 2.0, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-1.2, 2.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-1.2, 3.0, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();
	//fence right end

	//fence left start
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.4, -1.2, -2.0);
	glScaled(0.1, 0.1 + g, 2.4);
	glColor3f(fcolorx, fcolory, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(1.2, 1.0, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);;
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(1.2, 1.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(1.2, 2.0, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(1.2, 2.5, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(1.2, 3.0, 0.0);
	glColor3f(fcolorx, fcolory, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();
	//fence left end

	//Torri gate start
	glPushMatrix();
	glTranslated(0.0, 0.5, -0.7);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslated(0.9, 1.5, 0.0);
	glScaled(0.2, 0.1 + g, 1.7);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslated(0.8, 1.5, 0.0);
	glScaled(0.2, 0.1 + g, 1.3);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslated(0.5, 1.5, 0.0);
	glScaled(0.15, 0.1 + g, 1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(0.3, 1.5, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(0.0, 1.5, 0.7);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslated(-0.3, 1.5, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 1.5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	//Torri gate end

	//Snowman start
	glPushMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.2, 1.7);
	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(2.3, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.5, 1.7);
	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(1.5, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.7, 1.7);
	glColor3f(1.0f, 1.0f, 1.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(1.0, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.6, 1.7);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScaled(0.5, 0.2 + g, 0.5);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.45, 0.5, 1.8);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.2 + g, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.52, 0.48, 1.8);
	glColor3f(0.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.52, 0.52, 1.8);
	glColor3f(0.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.45, 0.74, 1.81);
	glColor3f(0.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.1, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.54, 0.74, 1.81);
	glColor3f(0.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.1, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.7, 1.70);
	glColor3f(1.0f, 0.5f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidCone(0.27, 1.8, 25, 25);
	glPopMatrix();

	//hat for later
	glPushMatrix();
	glTranslated(0.5, 0.7, 1.7);
	glRotated(-90, 1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidCone(1.0, 2.0, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.9, 1.7);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScaled(0.1, 0.1 + g, 0.1);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();
	//hat

	glPopMatrix();

	if (!hide1)
		present1();
	else
		hidden[0] = 1;

	if (!hide2)
		present2();
	else
		hidden[1] = 1;

	if (!hide3)
		present3();
	else
		hidden[2] = 1;

	glFlush();
}

void Anim(int) {
	time1 += 1;
	if (time1 % 60 == 0) {
		clock1--;
		if (fcolorx == 1.0f && fcolory == 0.5f) {
			fcolorx = 0.0f;
			fcolory = 1.0f;
		}
		else {
			fcolorx = 1.0f;
			fcolory = 0.5f;
		}
	}

	if (clock1 == 0 && counter < 3)
		exit(0);

	if (counter == 3) {
		sColorx = 0.0f;
		sColory = 1.0f;

		PlaySound(TEXT("sound2.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}

	/*if (counter == 3 && time1 == 800)
		exit(0);*/

	glutTimerFunc(1000 / 60, Anim, 0);
	glutPostRedisplay();
}

void func() {
	counter = 0;

	for (int i = 0; i < 3; i++) {
		counter += hidden[i];
	}
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Abdo's Xmas");
	glutDisplayFunc(Display);
	glutTimerFunc(1000, Anim, 0);
	glutIdleFunc(func);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	PlaySound(TEXT("sound1.wav"), NULL, SND_ASYNC | SND_FILENAME);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutMainLoop();
}