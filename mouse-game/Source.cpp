#include<stdlib.h>
#include <GL/glut.h>
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<string>

//Speed
int FPS = 50;
//Tracker
int start = 0;
int gv = 0;
int level = 0;
//Track Score
int score = 0;
//Move Track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMid = 0;
int roadDivBot = 0;
//Left-Right Index for Mouse
int lrIndex = 0;
//Coming Cats
int cat1 = 0;
int lrIndex1 = 0;

//Display Text
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void startGame() {
	//Road
	glColor3f(0.412, 0.412, 0.412);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//Left
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(23, 100);
	glVertex2f(23, 0);
	glEnd();

	//Right
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(77, 0);
	glVertex2f(77, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//Top
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivTop + 80);
	glVertex2f(48, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 80);
	glEnd();

	roadDivTop--;
	if (roadDivTop < -100) {
		roadDivTop = 20;
		score++;
	}

	//Middle
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivMid + 40);
	glVertex2f(48, roadDivMid + 60);
	glVertex2f(52, roadDivMid + 60);
	glVertex2f(52, roadDivMid + 40);
	glEnd();

	roadDivMid--;
	if (roadDivMid < -60) {
		roadDivMid = 60;
		score++;
	}

	//Bottom
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivMid + 0);
	glVertex2f(48, roadDivMid + 20);
	glVertex2f(52, roadDivMid + 20);
	glVertex2f(52, roadDivMid + 0);
	glEnd();

	roadDivBot--;
	if (roadDivBot < -60) {
		roadDivBot = 60;
		score++;
	}

	//Score Board
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(80, 97);
	glVertex2f(100, 97);
	glVertex2f(100, 98 - 8);
	glVertex2f(80, 98 - 8);
	glEnd();

	//Print Score
	char buffer[50];
	sprintf_s(buffer, "SCORE: %d", score);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(80.5, 95, (void*)font3, buffer);

	//Print Speed
	char buffer1[50];
	sprintf_s(buffer1, "SPEED: %dKm/h", score);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(80.5, 95 - 2, (void*)font3, buffer);

	//Print Level
	if (score % 50 == 0) {
		int last = score / 50;
		if (last != level) {
			level = score / 50;
			FPS = FPS + 2;
		}
	}

	//MOUSE
	//Body
	glColor3f(0.777, 0.777, 0.777);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26, 3);
	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 30, 3);
	glEnd();

	//Nose n mustache
	glColor3f(0, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 27, 8);
	glVertex2f(lrIndex + 29, 8);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(lrIndex + 25, 10);
	glVertex2f(lrIndex + 31, 9);
	glVertex2f(lrIndex + 25, 9);
	glVertex2f(lrIndex + 31, 10);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(lrIndex + 28, 3);
	glVertex2f(lrIndex + 26, 2);
	glVertex2f(lrIndex + 30, 2);
	glVertex2f(lrIndex + 27, 1);
	glEnd();

	//CAT1
	glColor3f(0.9, 0.6, 0.3);

	glBegin(GL_QUADS);

	//body
	glVertex2i(lrIndex1 + 26, cat1 + 100 - 7);
	glVertex2i(lrIndex1 + 38, cat1 + 100 - 7);
	glVertex2i(lrIndex1 + 38, cat1 + 100 - 2);
	glVertex2i(lrIndex1 + 26, cat1 + 100 - 2);
	
	//foot
	glVertex2i(lrIndex1 + 26, cat1 + 100 - 7);
	glVertex2i(lrIndex1 + 26 + 2, cat1 + 100 - 7);
	glVertex2i(lrIndex1 + 26 + 2, cat1 + 100 - 7 - 3);
	glVertex2i(lrIndex1 + 26, cat1 + 100 - 7 - 3);
	glVertex2i(lrIndex1 + 38, cat1 + 100 - 7);
	glVertex2i(lrIndex1 + 38 - 2, cat1 + 100 - 7);
	glVertex2i(lrIndex1 + 38 - 2, cat1 + 100 - 7 - 3);
	glVertex2i(lrIndex1 + 38, cat1 + 100 - 7 - 3);
	glEnd();
	
	glBegin(GL_TRIANGLES);

	//head
	glVertex2i(lrIndex1 + 38 - 3, cat1 + 100 - 2 + 2);
	glVertex2i(lrIndex1 + 38 - 3 + 6, cat1 + 100 - 2 + 2);
	glVertex2i(lrIndex1 + 38 - 3 + 3, cat1 + 100 - 2 - 3);
	
	//ears
	glVertex2i(lrIndex1 + 38 - 3, cat1 + 100 - 2 + 2);
	glVertex2i(lrIndex1 + 38 - 3 + 2, cat1 + 100 - 2 + 2);
	glVertex2i(lrIndex1 + 38 - 3 + 1, cat1 + 100 - 2 + 2 + 1);
	glVertex2i(lrIndex1 + 38 - 3 + 6, cat1 + 100 - 2 + 2);
	glVertex2i(lrIndex1 + 38 - 3 + 6 - 2, cat1 + 100 - 2 + 2);
	glVertex2i(lrIndex1 + 38 - 3 + 6 - 1, cat1 + 100 - 2 + 2 + 1);
	glEnd();
	
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	//tail
	glVertex2i(lrIndex1 + 26, cat1 + 100 - 2);
	glVertex2i(lrIndex1 + 26 - 2, cat1 + 100 - 2 + 5);
	//mustaches
	glVertex2i(lrIndex1 + 38 - 3 + 0, cat1 + 100 - 2 - 2);
	glVertex2i(lrIndex1 + 38 - 3 + 6, cat1 + 100 - 2 + 0);
	glVertex2i(lrIndex1 + 38 - 3 + 0, cat1 + 100 - 2 + 0);
	glVertex2i(lrIndex1 + 38 - 3 + 6, cat1 + 100 - 2 - 2);
	glEnd();

	
	glBegin(GL_POINTS);
	//eyes
	glVertex2i(lrIndex1 + 38 - 3 + 2, cat1 + 100 - 2 + 1);
	glVertex2i(lrIndex1 + 38 - 3 + 4, cat1 + 100 - 2 + 1);
	glEnd();
	
	cat1--;
	if (cat1 < -100) {
		cat1 = 0;
		lrIndex1 = lrIndex;
	}

	//Check Lose
	if ((abs(lrIndex - lrIndex1) < 8) && (cat1 + 100 < 10)) {
		start = 0;
		gv = 1;
	}
}

void firstDesign() {
	//Road Background
	glColor3f(0.000, 0.392, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glColor3f(0.604, 0.804, 0.196);
	glVertex2f(100, 50 - 50);
	glVertex2f(0, 50 - 50);
	glEnd();

	//Front Page
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(32 + 58, 50 - 50);
	glVertex2f(32 - 22, 50 - 50);
	glEnd();

	//Middle Road
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(50 + 2, 50 - 50);
	glVertex2f(50 - 2, 50 - 50);
	glEnd();

	//Road SKy
	glColor3f(0.000, 0.749, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glColor3f(0.636, 0.933, 0.933);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glEnd();

	//Menu
	glColor3f(0.098, 0.098, 0.439);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 + 45, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 + 45, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	if (gv == 1) {
		glColor3f(1.000, 0.000, 0.000);
		renderBitmapString(35, 60 + 10, (void*)font1, "GAME OVER");
		glColor3f(1.000, 0.000, 0.000);
		char buffer2[50];
		sprintf_s(buffer2, "Your Score is: %d", score);
		renderBitmapString(33, 60 - 4 + 10, (void*)font1, buffer2);
	}

	glColor3f(1.000, 1.000, 0.000);
	renderBitmapString(30, 80, (void*)font1, "RUN MOUSE RUN");

	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(30, 50 + 10, (void*)font2, "Press SPACE to START");
	renderBitmapString(30, 50 - 3 + 10, (void*)font2, "Press ESC to EXIT");

	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(30, 50 - 6 + 10, (void*)font3, "Press UP to increase speed");
	renderBitmapString(30, 50 - 8 + 10, (void*)font3, "Press DOWN to decrease speed");
	renderBitmapString(30, 50 - 10 + 10, (void*)font3, "Press RIGHT to turn right");
	renderBitmapString(30, 50 - 12 + 10, (void*)font3, "Press LEFT to turn left");

	glColor3f(0.000, 1.000, 1.000);
	renderBitmapString(30 - 5, 50 - 40, (void*)font3, "");
	renderBitmapString(30 - 5, 50 - 43, (void*)font3, "");

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (start == 1) {
		glClearColor(0.000, 0.392, 0.000, 1);
		startGame();
	}
	else
		firstDesign();

	glFlush();
	glutSwapBuffers();
}

void playKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		if (FPS > (50 + (level * 2)))
			FPS = FPS - 2;
		break;
	case GLUT_KEY_UP:
		FPS = FPS + 2;
		break;
	case GLUT_KEY_LEFT:
		if (lrIndex >= 0) {
			lrIndex = lrIndex - (FPS / 10);
			if (lrIndex < 0) {
				lrIndex = -1;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (lrIndex <= 44) {
			lrIndex = lrIndex + (FPS / 10);
			if (lrIndex > 44) {
				lrIndex = 45;
			}
		}
		break;
	default:
		break;
	}
}

void processKeys(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		if (start == 0) {
			start = 1;
			gv = 0;
			FPS = 50;
			roadDivTopMost = 0;
			roadDivTop = 0;
			roadDivMid = 0;
			roadDivBot = 0;
			lrIndex = 0;
			cat1 = 0;
			lrIndex1 = 0;
		}
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 650);
	glutInitWindowPosition(200, 20);
	glutCreateWindow("RUNAWAY MOUSE GAME - GAMETECH B 2020 - 5220600041");

	glutDisplayFunc(display);
	glutSpecialFunc(playKeys);
	glutKeyboardFunc(processKeys);

	glOrtho(0, 100, 0, 100, -1, 1);
	glClearColor(0.184, 0.310, 0.310, 1);

	glutTimerFunc(1000, timer, 0);
	glutMainLoop();

	return 0;
}