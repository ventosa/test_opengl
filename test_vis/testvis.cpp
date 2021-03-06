

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <vector>
#include <unistd.h>

using namespace std;

const int X_COORD = 50;// X - dim should
const int Y_COORD = 50;// Y - be equal
const int NUM_LINES = 31600;
const int NUM_IN_ONE = 100;
const int NUM_POINTS = NUM_IN_ONE * NUM_LINES;

// GLfloat Vertices[NUM_POINTS][2];
GLfloat Vertices[NUM_LINES][NUM_IN_ONE][2];
int x_off = X_COORD / 2;// begin of
int y_off = Y_COORD / 2;// axes

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static int g_yClick = 0;
static BOOL g_bButton1Down = FALSE;

void MouseButton(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
    {
      g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
    //   g_yClick = y - 3 * g_fViewDistance;
	//   sleep(3);
	if (g_bButton1Down) {
		glutReshapeWindow(1200, 600);
		glutPostRedisplay();
		cout << "Time of resize 2 display: " << endl;
		}
    }
}

// void MouseMotion(int x, int y)
// {
//   // If button1 pressed, zoom in/out if mouse is moved up/down.
//   if (g_bButton1Down)
//     {
//       g_fViewDistance = (y - g_yClick) / 3.0;
//       if (g_fViewDistance < VIEWING_DISTANCE_MIN)
//          g_fViewDistance = VIEWING_DISTANCE_MIN;
//       glutPostRedisplay();
//     }
// }

void drawgrid(float SERIF_OFFSET, float SERIF_DISTANCE) {
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.0, y_off);
		glVertex2f(X_COORD, y_off);
		int p = x_off;
		for (int i = x_off; i < X_COORD; i += SERIF_DISTANCE, p -= SERIF_DISTANCE) {
			glVertex2f(i, y_off);
			glVertex2f(i, y_off + SERIF_OFFSET);

			glVertex2f(p, y_off);
			glVertex2f(p, y_off + SERIF_OFFSET);
		}
		//vertical
		int t = y_off;
		glVertex2f(x_off, Y_COORD);
		glVertex2f(x_off, 0.0);

		for (int i = y_off; i < Y_COORD; i += SERIF_DISTANCE, t -= SERIF_DISTANCE) {
			glVertex2f(x_off, i);
			glVertex2f(y_off + SERIF_OFFSET, i);

			glVertex2f(x_off, t);
			glVertex2f(y_off + SERIF_OFFSET, t);
		}
	glEnd();
}

// void native_loop_drawfunc(){
// 	chrono::time_point<std::chrono::system_clock> start;
// 	start = chrono::system_clock::now();
	
// 	float delta = float(X_COORD) / NUM_POINTS;
// 	glBegin(GL_LINE_STRIP);
// 		for (int i = 0; i < NUM_POINTS; i++) {
// 			glVertex2f(Vertices[i][0], Vertices[i][1]);
// 		}
// 	glEnd();
// 	cout << "Time of display: " << (chrono::system_clock::now() - start).count() << endl;
// }

void drawfunc() {
	chrono::time_point<std::chrono::system_clock> start;
	start = chrono::system_clock::now();
	glVertexPointer(2, GL_FLOAT, 0, Vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	// glDrawArrays(GL_LINE_STRIP, 0, NUM_POINTS-1);
	glDrawArrays(GL_LINE_STRIP, 0, 10000);
	glDrawArrays(GL_LINE_STRIP, 30000, 50000);
	glDisableClientState(GL_VERTEX_ARRAY);
	cout << "Time of display: " << (chrono::system_clock::now() - start).count() << endl;
}

void drawLines() {
	chrono::time_point<std::chrono::system_clock> start;
	start = chrono::system_clock::now();
	glEnableClientState(GL_VERTEX_ARRAY);
	for (int i = 0; i < NUM_LINES; i++) {
		glVertexPointer(2, GL_FLOAT, 0, Vertices[i]);
		glDrawArrays(GL_LINE_STRIP, 0, 100);
	// for (int i=0; i<NUM_LINES-1; i++){
		// glDrawArrays(GL_LINE_STRIP, i*NUM_IN_ONE, (i+1)*NUM_IN_ONE-1);
	// }
	// glDrawArrays(GL_LINE_STRIP, (NUM_LINES-1)*NUM_IN_ONE, NUM_POINTS-1);
	// glDrawArrays(GL_LINE_STRIP, NUM_POINTS-1, NUM_POINTS-1);
	// glDrawArrays(GL_LINE_STRIP, 0, 10000);
	// glDrawArrays(GL_LINE_STRIP, 30000, 50000);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	cout << "Time of display: " << (chrono::system_clock::now() - start).count() << endl;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawgrid(0.3, 5);
	// drawfunc();
	drawLines();
	glutSwapBuffers();
	glFlush();
}

// void CreateLine(){
// 	float vfunc[NUM_POINTS];
// 	float ds[NUM_POINTS];
// 	float delta = float(X_COORD) / NUM_POINTS;
// 	for (int i = 0; i < NUM_POINTS; i++) {
// 		ds[i] = 0 + i * delta;
// 		vfunc[i] = sin(ds[i])*(x_off - 1) + y_off+sin(ds[i]*150);
// 		Vertices[i][0] = ds[i];
// 		Vertices[i][1] = vfunc[i];
// 	}
// }

void CreateLines(){
	float ds, dt;
	int cur;
	float delta = float(X_COORD) / NUM_IN_ONE;
	float delta2 = 3.14/float(NUM_LINES);
	for (int k = 0; k < NUM_LINES; k++) {
		for (int i = 0; i < NUM_IN_ONE; i++) {
			ds = 0 + i * delta;
			Vertices[k][i][0] = ds;
			// Vertices[k*NUM_IN_ONE+i][0] = ds;
			// Vertices[k*NUM_IN_ONE+i][1] = sin(ds + k*delta2)*(x_off - 1) + y_off+sin(ds*150);
			Vertices[k][i][1] = sin(ds + k*delta2)*(x_off - 1) + y_off+sin(ds*150);
		}
	}
}

int main(int argc, char** argv) {
	CreateLines();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 300);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("GLUT_TESTING_APP");
	
	glutMouseFunc (MouseButton);
  	// glutMotionFunc (MouseMotion);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, X_COORD, 0.0, Y_COORD, -1.0, 1.0);

	glutDisplayFunc(display);

	// sleep(3);
	// chrono::time_point<std::chrono::system_clock> start;
	// start = chrono::system_clock::now();
	// glutReshapeWindow(400, 200);
	// cout << "Time of resize 1 display: " << (chrono::system_clock::now() - start).count() << endl;
	// sleep(3);
	// start = chrono::system_clock::now();
	// glutReshapeWindow(1200, 600);
	// cout << "Time of resize 2 display: " << (chrono::system_clock::now() - start).count() << endl;
	// sleep(3);
	// start = chrono::system_clock::now();
	// glutReshapeWindow(200, 100);
	// cout << "Time of resize 3 display: " << (chrono::system_clock::now() - start).count() << endl;

	glutMainLoop();
}
