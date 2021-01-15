#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sstream>

using namespace std;

void draw_square(int startX, int startY, double widthX, double heightY, double col[])
{
	glColor3f(col[0], col[1], col[2]);
	glBegin(GL_POLYGON);
	glVertex2f(startX, startY);
	glVertex2f(startX + widthX, startY);
	glVertex2f(startX + widthX, startY + heightY);
	glVertex2f(startX, startY + heightY);
	glEnd();
}

void draw_tri(int startX, int startY, double width_x, double height_y, int quadPos, double col[3])
{
	switch (quadPos)
	{
	case 1:
		glColor3f(col[0], col[1], col[2]);
		glBegin(GL_POLYGON);
		glVertex2f(startX, startY);//start
		glVertex2f(startX, startY + height_y);//up
		glVertex2f(startX + width_x, startY);//right
		glEnd();
		break;

	case 2:
		glColor3f(col[0], col[1], col[2]);
		glBegin(GL_POLYGON);
		glVertex2f(startX, startY);//start
		glVertex2f(startX, startY + height_y);//up
		glVertex2f(startX - width_x, startY);//left
		glEnd();
		break;

	case 3:
		glColor3f(col[0], col[1], col[2]);
		glBegin(GL_POLYGON);
		glVertex2f(startX, startY);//start
		glVertex2f(startX, startY - height_y);//down
		glVertex2f(startX - width_x, startY);//left
		glEnd();
		break;

	case 4:
		glColor3f(col[0], col[1], col[2]);
		glBegin(GL_POLYGON);
		glVertex2f(startX, startY);//start
		glVertex2f(startX, startY - height_y);//down 
		glVertex2f(startX + width_x, startY);//right
		glEnd();
		break;

	default:
		break;
	}
}

void draw_pieceRook(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b)
{
	if (Enable) {
		double col[3] = { r,g,b };

		draw_square(startX, startY, width_x, height_y / 5, col);//base

		draw_square(startX + (width_x*0.1), startY + ((4 * height_y) / 5), 0.2*width_x, height_y / 5, col);//top box 1

		draw_square(startX + (width_x*0.3), startY + ((4 * height_y) / 5), 0.11*width_x, height_y *0.15, col);//top box 2

		draw_square(startX + (width_x*0.4), startY + ((4 * height_y) / 5), 0.2*width_x, height_y / 5, col);//top box 3

		draw_square(startX + (width_x*0.6), startY + ((4 * height_y) / 5), 0.1*width_x, height_y *0.15, col);//top box 4

		draw_square(startX + (width_x*0.7), startY + ((4 * height_y) / 5), 0.2*width_x, height_y / 5, col);//top box 5

		draw_square(startX + (width_x / 3), startY + (height_y / 5), width_x / 3, (height_y * 3) / 5, col);//between top and base

		draw_tri(startX + (width_x * 0.66), startY + (height_y / 5), (width_x * 3) / 13, height_y / 8, 1, col);//right triangle

		draw_tri(startX + (width_x / 3), startY + (height_y / 5), (width_x * 3) / 13, height_y / 8, 2, col);//left triangle
	}
}

void draw_piecePawn(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b)
{
	if (Enable) {
		double col[3] = { r,g,b };

		double col1[3] = { 0.24,0.9,0.12 };
		double col2[3] = { 0.4,0.5,0.2 };
		double col3[3] = { 0.57,0.5,0.92 };
		double col4[3] = { 0.7,0.45,0.2 };
		double col5[3] = { 0.27,0.5,0.32 };
		double col6[3] = { 0.67,0.85,0.9 };
		double col7[3] = { 0.49,0.1,0.2 };
		double col8[3] = { 0.657,0.5,0.4 };
		double col9[3] = { 0.78,0.45,0.2 };
		double col10[3] = { 0.217,0.5,0.832 };

		draw_square(startX + (width_x*0.1), startY + ((4 * height_y) / 5), 0.8*width_x, (2 * height_y) / 15, col);//top big box

		draw_square(startX + (0.4 * width_x), startY + ((14 * height_y) / 15), 0.2*width_x, height_y / 15, col);//top small box

		draw_square(startX + (width_x / 3), startY + (height_y / 5), width_x / 3, (height_y * 3) / 5, col);//between top and base

		draw_square(startX, startY, width_x, height_y / 5, col);//base

		draw_tri(startX + (width_x* 0.66), startY + (4 * height_y / 5), (width_x * 1.5) / 13, (2 * height_y) / 8, 4, col);//right upper triangle

		draw_tri(startX + (width_x* 0.66), startY + (height_y / 5), (width_x * 3) / 13, height_y / 8, 1, col);//right lower triangle

		draw_tri(startX + ((width_x / 3)), startY + (4 * height_y / 5), (width_x * 1.5) / 13, (2 * height_y) / 8, 3, col);//left upper triangle

		draw_tri(startX + (width_x / 3), startY + (height_y / 5), (width_x * 3) / 13, height_y / 8, 2, col);//left lower triangle
	}
}

void draw_pieceKing(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b)
{
	if (Enable) {
		double col[3] = { r,g,b };

		draw_square(startX + (width_x*0.45), startY + (height_y - ((2 * height_y) / 30)), 0.1*width_x, (2 * height_y / 30), col);//top upper1 box

		draw_square(startX + (width_x*0.3), startY + (height_y - ((3 * height_y) / 30)), 0.4*width_x, height_y / 30, col);//top upper2 box

		draw_square(startX + (width_x*0.45), startY + (height_y - ((5 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 30, col);//top mid box

		draw_square(startX + (width_x*0.1), startY + (height_y - ((6 * height_y) / 30)), 0.8*width_x, height_y / 30, col);//top lower box

		draw_square(startX + (width_x / 3), startY + (height_y / 5), width_x / 3, (height_y * 3) / 5, col);//between top and base

		draw_square(startX, startY, width_x, height_y / 5, col);//base

		draw_tri(startX + (width_x* 0.66), startY + (height_y / 5), (width_x * 2) / 13, height_y / 6, 1, col);//right lower triangle

		draw_tri(startX + (width_x / 3), startY + (height_y / 5), (width_x * 2) / 13, height_y / 6, 2, col);//left lower triangle

		draw_tri(startX + (width_x*0.45), startY + (height_y - ((5 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 60, 2, col);//left upper top

		draw_tri(startX + (width_x*0.55), startY + (height_y - ((5 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 60, 1, col);//right upper top

		draw_tri(startX + (width_x / 3), startY + (height_y - (height_y / 5)), 0.2*width_x, (2 * height_y) / 30, 3, col);//left lower top

		draw_tri(startX + (width_x* 0.66), startY + (height_y - (height_y / 5)), 0.2*width_x, (2 * height_y) / 30, 4, col);//right lower top

		draw_tri(startX + (width_x*0.45), startY + (height_y - ((2 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 60, 2, col);//2nd left upper top

		draw_tri(startX + (width_x*0.55), startY + (height_y - ((2 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 60, 1, col);//1st left upper top
	}
}

void draw_pieceBishop(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b)
{
	if (Enable) {
		double col[3] = { r,g,b };

		draw_square(startX + (width_x / 3), startY + (height_y / 5), width_x / 3, (height_y * 3) / 5, col);//between top and base

		draw_square(startX, startY, width_x, height_y / 5, col);//base

		draw_tri(startX + (width_x* 0.66), startY + (height_y / 5), (width_x * 2) / 13, height_y / 4, 1, col);//right lower triangle

		draw_tri(startX + (width_x / 3), startY + (height_y / 5), (width_x * 2) / 13, height_y / 4, 2, col);//left lower triangle

		draw_tri(startX + (width_x / 2), startY + ((4 * height_y) / 5), width_x / 6, height_y / 5, 2, col);//upper top left triangle

		draw_tri(startX + (width_x / 2), startY + ((4 * height_y) / 5), width_x / 6, height_y / 5, 1, col);//upper top right triangle

		draw_tri(startX + ((2 * width_x) / 3), startY + ((4 * height_y) / 5), width_x / 7, height_y / 5, 4, col);//down top right triangle

		draw_tri(startX + (width_x / 3), startY + ((4 * height_y) / 5), width_x / 7, height_y / 5, 3, col);//down top left triangle		
	}
}

void draw_pieceQueen(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b) {
	if (Enable) {
		double col[3] = { r,g,b };

		draw_square(startX + (width_x*0.45), startY + (height_y - ((5 * height_y) / 30)), 0.1*width_x, (3 * height_y) / 30, col);//top box

		draw_square(startX + (width_x / 3), startY + (height_y / 5), width_x / 3, (height_y * 3) / 5, col);//between top and base

		draw_square(startX + (width_x*0.1), startY + (height_y - ((6 * height_y) / 30)), 0.8*width_x, height_y / 30, col);//top lower box

		draw_square(startX, startY, width_x, height_y / 5, col);//base

		draw_tri(startX + (width_x* 0.66), startY + (height_y / 5), (width_x * 2) / 13, height_y / 6, 1, col);//right lower triangle

		draw_tri(startX + (width_x / 3), startY + (height_y / 5), (width_x * 2) / 13, height_y / 6, 2, col);//left lower triangle

		draw_tri(startX + (width_x*0.45), startY + (height_y - ((5 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 60, 2, col);//left upper top

		draw_tri(startX + (width_x*0.55), startY + (height_y - ((5 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 60, 1, col);//right upper top

		draw_tri(startX + (width_x / 3), startY + (height_y - (height_y / 5)), 0.2*width_x, (2 * height_y) / 30, 3, col);//left lower top

		draw_tri(startX + (width_x* 0.66), startY + (height_y - (height_y / 5)), 0.2*width_x, (2 * height_y) / 30, 4, col);//right lower top

		draw_tri(startX + (width_x* 0.5), startY + (height_y - ((2 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 30, 1, col);//top right

		draw_tri(startX + (width_x* 0.5), startY + (height_y - ((2 * height_y) / 30)), 0.1*width_x, (2 * height_y) / 30, 2, col);//top left

		draw_tri(startX + (width_x* 0.25), startY + ((5 * height_y) / 6), 0.05*width_x, (2 * height_y) / 30, 2, col);//top left (left)

		draw_tri(startX + (width_x* 0.25), startY + ((5 * height_y) / 6), 0.05*width_x, (2 * height_y) / 30, 1, col);//top left (right)

		draw_tri(startX + (width_x* 0.75), startY + ((5 * height_y) / 6), 0.05*width_x, (2 * height_y) / 30, 2, col);//top right (left)

		draw_tri(startX + (width_x* 0.75), startY + ((5 * height_y) / 6), 0.05*width_x, (2 * height_y) / 30, 1, col);//top right (right)
	}
}

void draw_pieceKnight(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b) {
	double col[3] = { r,g,b };

	double col1[3] = { 0.24,0.9,0.12 };
	double col2[3] = { 0.4,0.5,0.2 };
	double col3[3] = { 0.57,0.5,0.92 };
	double col4[3] = { 0.7,0.45,0.2 };
	double col5[3] = { 0.27,0.5,0.32 };
	double col6[3] = { 0.67,0.85,0.9 };
	double col7[3] = { 0.49,0.1,0.2 };
	double col8[3] = { 0.657,0.5,0.4 };
	double col9[3] = { 0.78,0.45,0.2 };
	double col10[3] = { 0.217,0.5,0.832 };

	draw_square(startX + ((width_x) / 3), startY + (3 * height_y) / 5, width_x / 3, (height_y) / 5, col);//top mid

	draw_square(startX + ((width_x * 2) / 3), startY + (2.5 * height_y) / 5, (1 * width_x) / 3, (1.5 * height_y) / 5, col);//mid right

	draw_square(startX + (width_x / 3), startY + (height_y / 5), width_x / 3, height_y / 5, col);//between top and base

	draw_square(startX, startY, width_x, height_y / 5, col);//base

	draw_tri(startX + ((width_x * 2) / 3), startY + (2 * height_y) / 5, width_x / 3, (height_y) / 5, 2, col);//bottom mid

	draw_tri(startX + ((width_x * 2) / 3), startY + (2.5 * height_y) / 5, (1 * width_x) / 3, (height_y) / 10, 4, col);//bottom right

	draw_tri(startX + ((width_x*2.5) / 3), startY + (height_y - (height_y / 5)), (1.5*width_x) / 3, (height_y) / 5, 2, col);//upper right (on the left)

	//draw_tri(startX + ((width_x*2.5) / 3), startY + (height_y - (height_y / 5)), width_x / 6, (height_y) / 5, 1, col);//upper right 2nd

	draw_tri(startX + (width_x* 0.66), startY + (height_y / 5), (width_x * 0.5) / 13, height_y / 6, 1, col);//right lower triangle

	draw_tri(startX + (width_x / 3), startY + (height_y / 5), (width_x * 2) / 13, height_y / 6, 2, col);//left lower triangle

	//draw_tri(startX + ((width_x) / 3), startY + (height_y - (height_y / 5)), (1.5*width_x) / 6, (height_y) / 5, 1, col);//test

	draw_tri(startX + ((width_x) / 3), startY + (height_y - (2 * height_y / 5)), (1 * width_x) / 6, (height_y) / 5, 2, col);//test

	draw_square(startX, startY, width_x, height_y / 5, col);//base

	draw_tri(startX + (2.5*width_x / 3), startY + (height_y / 5), (2 * width_x) / 3, (3 * height_y) / 5, 2, col);//above base

	//draw_tri(startX + (width_x / 2), startY + ((4 * height_y) / 5), (1 * width_x) / 3, (1.5 * height_y) / 5, 4, col4);//test 
}

void draw_line(int x1, int y1, int x2, int y2, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

void draw_box(float start_X, float start_Y, int Width_X, int Height_Y, float r, float g, float b)
{
	glLineWidth(1.5);
	draw_line(start_X, start_Y, start_X + Width_X, start_Y, r, g, b);
	draw_line(start_X + Width_X, start_Y, start_X + Width_X, start_Y + Height_Y, r, g, b);
	draw_line(start_X + Width_X, start_Y + Height_Y, start_X, start_Y + Height_Y, r, g, b);
	draw_line(start_X, start_Y + Height_Y, start_X, start_Y, r, g, b);
}

void draw_board(int width_x, int height_y, int row, int column)
{
	bool color = true;
	int cell_w = width_x / row, cell_h = height_y / column;

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (color)
				glColor3f(1, 1, 1);
			else
				glColor3f(0, 0, 0);
			color = !color;

			glRecti(i*cell_w, j*cell_h, (i + 1)*cell_w, (j + 1)*cell_h);
		}
		if (column % 2 == 0) color = !color;
	}
}