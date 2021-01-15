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
#include "shapes.h"

using namespace std;//array -> y,x

double actWidth_X = 800;
double actheight_Y = 600;

GLint logWidth = 100;
GLint logHeight = 100;

double centerX = actWidth_X / 2, centerY = actheight_Y / 2,

mouseX = centerX, mouseY = centerY,

cellWidth_x = actWidth_X / 8, cellHeight_y = actheight_Y / 8,

boundPercent = 0.1,

pieceBoundX = boundPercent*cellWidth_x, pieceBoundY = boundPercent*cellHeight_y,

pieceWidth_x = cellWidth_x - (cellWidth_x * boundPercent * 2),
pieceHeight_y = cellHeight_y - (cellHeight_y * boundPercent * 2);

int window_posX = 50;
int window_posY = 50;

int flag = 99;

bool startMain = true;

void printString(string data, float x_axis, float y_axis, float r, float g, float b)
{
	int n = data.length();
	char str[10];
	strcpy_s(str, data.c_str());

	glColor3f(r, g, b);
	glRasterPos2d(x_axis, y_axis);
	for (int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	glFlush();
}

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

bool movePiece = false, wait4move = false;

struct data
{
	int cellNo, x, y, pieceUsed;
	double actX, actY;
	double startX, startY;
	bool used;
}cellUsed[64];

struct info
{
	string name;
	int id, atCellNo, movCount, movePosNum;
	double x, y;
	double width_x, height_y;
	bool enabled, moveStatus, placed;
	char movePos, movePosDiag;
}chessPiece[16], chessDefault[16];

void getCellState() {
	/*int num = chessPiece[4].atCellNo;
	for (int i = 0; i < 64; i++) {
		if (cellUsed[i].used) {
			string text = to_string(cellUsed[i].cellNo);
			printString("true", cellUsed[i].startX + 0, cellUsed[i].startY + 20, 0, 0.4, 1);
			printString(text, cellUsed[i].startX + 30, cellUsed[i].startY + 20, 1, 1, 1);
		}
		else {
			printString("false", cellUsed[i].startX + 20, cellUsed[i].startY + 20, 1, 0, 0);
		}

	}
*/
}


void initialize() {
	chessPiece[0].name = "rook1"; chessPiece[1].name = "knight1"; chessPiece[2].name = "bishop1"; chessPiece[3].name = "queen";
	chessPiece[4].name = "king"; chessPiece[5].name = "bishop2"; chessPiece[6].name = "knight2"; chessPiece[7].name = "rook2";
	chessPiece[8].name = "pawn1"; chessPiece[9].name = "pawn2"; chessPiece[10].name = "pawn3"; chessPiece[11].name = "pawn4";
	chessPiece[12].name = "pawn5"; chessPiece[13].name = "pawn6"; chessPiece[14].name = "pawn7"; chessPiece[15].name = "pawn8";

	for (int i = 0; i < 16; i++) {
		chessPiece[i].id = i;
		chessPiece[i].enabled = true;//change
		chessPiece[i].y = floor(i / 8);
		chessPiece[i].x = i % 8;
		chessPiece[i].atCellNo = i;
		chessPiece[i].movCount = 0;
		chessPiece[i].width_x = pieceWidth_x;
		chessPiece[i].height_y = pieceHeight_y;

		chessDefault[i].id = i;
		chessDefault[i].enabled = true;//change
		chessDefault[i].y = floor(i / 8);
		chessDefault[i].x = i % 8;
		chessDefault[i].atCellNo = i;
		chessDefault[i].movCount = 0;
		chessDefault[i].width_x = pieceWidth_x;
		chessDefault[i].height_y = pieceHeight_y;

		cellUsed[i].used = true;//change
	}

	for (int i = 0; i < 64; i++) {
		cellUsed[i].cellNo = i;
		cellUsed[i].actX = (i % 8) * cellWidth_x;

		int num = i, count = -1;
		while (num >= 0)
		{
			num -= 8;
			count++;
		}

		cellUsed[i].actY = count* cellHeight_y;
		cellUsed[i].startX = pieceBoundX + cellUsed[i].actX;
		cellUsed[i].startY = pieceBoundY + cellUsed[i].actY;
		cellUsed[i].x = (i % 8);
		cellUsed[i].y = floor(i / 8);
	}
	startMain = false;
}

void putPieces() {
	if (chessPiece[0].enabled == true)//rook1
		draw_pieceRook(chessPiece[0].enabled, cellUsed[chessPiece[0].atCellNo].startX, cellUsed[chessPiece[0].atCellNo].startY,
					   chessPiece[0].width_x, chessPiece[0].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[1].enabled == true)//knight1
		draw_pieceKnight(chessPiece[1].enabled, cellUsed[chessPiece[1].atCellNo].startX, cellUsed[chessPiece[1].atCellNo].startY,
						 chessPiece[1].width_x, chessPiece[1].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[2].enabled == true)//bishop1
		draw_pieceBishop(chessPiece[2].enabled, cellUsed[chessPiece[2].atCellNo].startX, cellUsed[chessPiece[2].atCellNo].startY,
						 chessPiece[2].width_x, chessPiece[2].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[3].enabled == true)//queen
		draw_pieceQueen(chessPiece[3].enabled, cellUsed[chessPiece[3].atCellNo].startX, cellUsed[chessPiece[3].atCellNo].startY,
						chessPiece[3].width_x, chessPiece[3].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[4].enabled == true)//king
		draw_pieceKing(chessPiece[4].enabled, cellUsed[chessPiece[4].atCellNo].startX, cellUsed[chessPiece[4].atCellNo].startY,
					   chessPiece[4].width_x, chessPiece[4].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[5].enabled == true)//bishop2
		draw_pieceBishop(chessPiece[5].enabled, cellUsed[chessPiece[5].atCellNo].startX, cellUsed[chessPiece[5].atCellNo].startY,
						 chessPiece[5].width_x, chessPiece[5].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[6].enabled == true)//knight2
		draw_pieceKnight(chessPiece[6].enabled, cellUsed[chessPiece[6].atCellNo].startX, cellUsed[chessPiece[6].atCellNo].startY,
						 chessPiece[6].width_x, chessPiece[6].height_y, col1[0], col1[1], col1[2]);

	if (chessPiece[7].enabled == true)//rook2
		draw_pieceRook(chessPiece[7].enabled, cellUsed[chessPiece[7].atCellNo].startX, cellUsed[chessPiece[7].atCellNo].startY,
					   chessPiece[7].width_x, chessPiece[7].height_y, col1[0], col1[1], col1[2]);

	for (int i = 8; i < 16; i++) //pawns
		if (chessPiece[i].enabled == true)
			draw_piecePawn(chessPiece[i].enabled, cellUsed[chessPiece[i].atCellNo].startX, cellUsed[chessPiece[i].atCellNo].startY,
						   chessPiece[i].width_x, pieceHeight_y, col1[0], col1[1], col1[2]);
}

void syncChessData(int id) {
	chessPiece[id].y = floor(chessPiece[id].atCellNo / 8);
	chessPiece[id].x = chessPiece[id].atCellNo % 8;
	cellUsed[chessPiece[id].atCellNo].pieceUsed = id;
}

void reset() {
	for (int i = 0; i < 16; i++) {
		cellUsed[chessPiece[i].atCellNo].used = false;
		chessPiece[i].y = chessDefault[i].y;
		chessPiece[i].x = chessDefault[i].x;
		chessPiece[i].atCellNo = chessDefault[i].atCellNo;
		cellUsed[chessPiece[i].atCellNo].used = cellUsed[chessDefault[i].atCellNo].used;
		syncChessData(i);
	}
}

void addInfo() {
	//chessPiece[4].enabled = true;//king
	//chessPiece[4].atCellNo = 34;
	//syncChessData(4);
	//cellUsed[chessPiece[4].atCellNo].used = true;

	//chessPiece[8].enabled = true;//pawn1
	//syncChessData(8);
	//cellUsed[chessPiece[8].atCellNo].used = true;

	//chessPiece[0].enabled = true;//rook1
	//syncChessData(0);
	//cellUsed[chessPiece[0].atCellNo].used = true;

	//chessPiece[3].enabled = true;//queen
	//chessPiece[3].atCellNo = 27;
	//syncChessData(3);
	//cellUsed[chessPiece[3].atCellNo].used = true;

	//chessPiece[4].enabled = true;//king
	//chessPiece[4].atCellNo = 10;
	//syncChessData(4);
	//cellUsed[chessPiece[4].atCellNo].used = true;

	//chessPiece[2].enabled = true;//bishop1
	//chessPiece[2].atCellNo = 30;
	//syncChessData(2);
	//cellUsed[chessPiece[2].atCellNo].used = true;

	//chessPiece[5].enabled = true;//bishop2
	//chessPiece[5].atCellNo = 20;
	//syncChessData(5);
	//cellUsed[chessPiece[5].atCellNo].used = true;

	//chessPiece[1].enabled = true;//knight
	//chessPiece[1].atCellNo = 27;
	//syncChessData(1);
	//cellUsed[chessPiece[1].atCellNo].used = true;
}

void mainCode(int flag) {
	if (flag == 99) {
		draw_board(actWidth_X, actheight_Y, 8, 8);
		addInfo();
		putPieces();
	}

	//rooks
	if (flag == 0 || flag == 7) {// rooks
		draw_board(actWidth_X, actheight_Y, 8, 8);

		if (!chessPiece[flag].moveStatus)
			draw_pieceRook(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
						   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);

		else {
			switch (chessPiece[flag].movePos) {

			case 'r':
				if ((chessPiece[flag].x + chessPiece[flag].movCount) < 8) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceRook(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
				break;

			case'l':
				if ((chessPiece[flag].x - chessPiece[flag].movCount) >= 0) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceRook(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
				break;

			case'u':
				if ((chessPiece[flag].atCellNo + chessPiece[flag].movCount) < 64) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceRook(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
				break;

			case'd':
				if ((chessPiece[flag].atCellNo + chessPiece[flag].movCount) >= 0) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceRook(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
				break;

			default:
				break;

			}
			chessPiece[flag].moveStatus = false;
			chessPiece[flag].movePos = 's';
			chessPiece[flag].movCount = 0;
		}

		draw_box(cellUsed[chessPiece[flag].atCellNo].startX - (pieceWidth_x * 0.05), cellUsed[chessPiece[flag].atCellNo].startY - (pieceHeight_y * 0.05),
				 1.1* pieceWidth_x, 1.1*pieceHeight_y, col2[0], col2[1], col2[2]);
		draw_box(cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col2[0], col2[1], col2[2]);

		int Xright = chessPiece[flag].x + 1,
			Xleft = chessPiece[flag].x - 1,

			Yup = chessPiece[flag].y + 1,
			Ydown = chessPiece[flag].y - 1;

		int count = 1, cellCount = 8;

		for (int i = Xright; i < 8; i++)
		{
			if ((chessPiece[flag].x + count) < 8 && !(cellUsed[chessPiece[flag].atCellNo + count].used))
				draw_box(cellUsed[chessPiece[flag].atCellNo + count].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count++;
		}

		count = -1;
		for (int i = Xleft; i >= 0; i--)
		{
			if ((chessPiece[flag].x + count) < 8 && !(cellUsed[chessPiece[flag].atCellNo + count].used))
				draw_box(cellUsed[chessPiece[flag].atCellNo + count].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count--;
		}

		for (int i = Yup; i < 8; i++)
		{
			if ((chessPiece[flag].y + count) < 8 && (chessPiece[flag].atCellNo + cellCount) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount].used)
				draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount].startX, cellUsed[chessPiece[flag].atCellNo + cellCount].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count++;
			cellCount += 8;
		}

		count = 1, cellCount = 8;
		for (int i = Ydown; i >= 0; i--)
		{
			if ((chessPiece[flag].y - count) < 8 && (chessPiece[flag].atCellNo - cellCount) >= 0 && !cellUsed[chessPiece[flag].atCellNo - cellCount].used)
				draw_box(cellUsed[chessPiece[flag].atCellNo - cellCount].startX, cellUsed[chessPiece[flag].atCellNo - cellCount].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count++;
			cellCount += 8;
		}

		wait4move = true;
		flag = 99;
		putPieces();
		getCellState();
	}

	//knights
	if (flag == 1 || flag == 6) {
		draw_board(actWidth_X, actheight_Y, 8, 8);

		if (!chessPiece[flag].moveStatus)
			draw_pieceKnight(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
							 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
		else {
			if (chessPiece[flag].movePos == 'u') {
				if (chessPiece[flag].movePosDiag == 'r' || chessPiece[flag].movePosDiag == 'l') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKnight(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
			}

			if (chessPiece[flag].movePos == 'd') {
				if (chessPiece[flag].movePosDiag == 'r' || chessPiece[flag].movePosDiag == 'l') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKnight(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
			}

			if (chessPiece[flag].movePos == 'r') {
				if (chessPiece[flag].movePosDiag == 'u' || chessPiece[flag].movePosDiag == 'd') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKnight(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
			}

			if (chessPiece[flag].movePos == 'l') {
				if (chessPiece[flag].movePosDiag == 'u' || chessPiece[flag].movePosDiag == 'd') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKnight(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
			}

			chessPiece[flag].movePos = 's';
			chessPiece[flag].movePosDiag = 's';
			chessPiece[flag].moveStatus = false;
			chessPiece[flag].movCount = 0;
		}

		draw_box(cellUsed[chessPiece[flag].atCellNo].startX - (pieceWidth_x * 0.05), cellUsed[chessPiece[flag].atCellNo].startY - (pieceHeight_y * 0.05),
				 1.1* pieceWidth_x, 1.1*pieceHeight_y, col2[0], col2[1], col2[2]);
		draw_box(cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col2[0], col2[1], col2[2]);

		//up
		int count = 8;
		while (count < 16 && chessPiece[flag].atCellNo + count < 64)
			count += 8;

		if (count == 16) {
			if ((chessPiece[flag].atCellNo + count + 1) % 8 != 0 && (chessPiece[flag].atCellNo + count + 1) < 64 && !cellUsed[chessPiece[flag].atCellNo + count + 1].used)
				draw_box(cellUsed[chessPiece[flag].atCellNo + count + 1].startX - (pieceWidth_x * 0.05),
						 cellUsed[chessPiece[flag].atCellNo + count + 1].startY - (pieceHeight_y * 0.05),
						 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);

			if ((chessPiece[flag].atCellNo + count - 1) % 8 != 7 && (chessPiece[flag].atCellNo + count - 1) < 64 && !cellUsed[chessPiece[flag].atCellNo + count - 1].used) {
				draw_box(cellUsed[chessPiece[flag].atCellNo + count - 1].startX - (pieceWidth_x * 0.05),
						 cellUsed[chessPiece[flag].atCellNo + count - 1].startY - (pieceHeight_y * 0.05),
						 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);
			}
		}

		//down
		count = -8;
		while (count > -16 && chessPiece[flag].atCellNo + count > 0)
			count -= 8;

		if (count == -16) {
			if ((chessPiece[flag].atCellNo + count + 1) % 8 != 0 && (chessPiece[flag].atCellNo + count + 1) > 0 && !cellUsed[chessPiece[flag].atCellNo + count + 1].used)
				draw_box(cellUsed[chessPiece[flag].atCellNo + count + 1].startX - (pieceWidth_x * 0.05),
						 cellUsed[chessPiece[flag].atCellNo + count + 1].startY - (pieceHeight_y * 0.05),
						 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);

			if ((chessPiece[flag].atCellNo + count - 1) % 8 != 7 && (chessPiece[flag].atCellNo + count - 1) > 0 && !cellUsed[chessPiece[flag].atCellNo + count - 1].used) {
				draw_box(cellUsed[chessPiece[flag].atCellNo + count - 1].startX - (pieceWidth_x * 0.05),
						 cellUsed[chessPiece[flag].atCellNo + count - 1].startY - (pieceHeight_y * 0.05),
						 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);
			}
		}

		//right
		count = 1;
		if ((chessPiece[flag].atCellNo) % 8 != 7) {
			while (count < 2 && chessPiece[flag].atCellNo + count < 64) {
				if ((chessPiece[flag].atCellNo + count) % 8 == 7) {
					break;
				}
				count++;
			}
		}

		if (count == 2) {
			if ((chessPiece[flag].atCellNo + count + 8) < 64 && !cellUsed[chessPiece[flag].atCellNo + count + 8].used)
				draw_box(cellUsed[chessPiece[flag].atCellNo + count + 8].startX - (pieceWidth_x * 0.05),
						 cellUsed[chessPiece[flag].atCellNo + count + 8].startY - (pieceHeight_y * 0.05),
						 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);

			if ((chessPiece[flag].atCellNo + count - 8) >= 0 && !cellUsed[chessPiece[flag].atCellNo + count - 8].used) {
				draw_box(cellUsed[chessPiece[flag].atCellNo + count - 8].startX - (pieceWidth_x * 0.05),
						 cellUsed[chessPiece[flag].atCellNo + count - 8].startY - (pieceHeight_y * 0.05),
						 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);
			}
		}

		//left
		count = -1;
		if ((chessPiece[flag].atCellNo) % 8 != 0) {
			while (count > -2 && chessPiece[flag].atCellNo + count < 64) {
				if ((chessPiece[flag].atCellNo + count) % 8 == 0) {
					break;
				}
				count--;
			}

			if (count == -2) {
				if ((chessPiece[flag].atCellNo + count + 8) < 64 && !cellUsed[chessPiece[flag].atCellNo + count + 8].used)
					draw_box(cellUsed[chessPiece[flag].atCellNo + count + 8].startX - (pieceWidth_x * 0.05),
							 cellUsed[chessPiece[flag].atCellNo + count + 8].startY - (pieceHeight_y * 0.05),
							 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);

				if ((chessPiece[flag].atCellNo + count - 8) >= 0 && !cellUsed[chessPiece[flag].atCellNo + count - 8].used) {
					draw_box(cellUsed[chessPiece[flag].atCellNo + count - 8].startX - (pieceWidth_x * 0.05),
							 cellUsed[chessPiece[flag].atCellNo + count - 8].startY - (pieceHeight_y * 0.05),
							 1.1* pieceWidth_x, 1.1*pieceHeight_y, col9[0], col9[1], col9[2]);
				}
			}
		}

		wait4move = true;
		flag = 99;
		putPieces();
		getCellState();
	}

	//bishops
	if (flag == 2 || flag == 5) {
		draw_board(actWidth_X, actheight_Y, 8, 8);

		if (!chessPiece[flag].moveStatus)
			draw_pieceBishop(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
							 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);

		else {
			if (chessPiece[flag].movePos == 'r') {
				if (chessPiece[flag].movePosDiag == 'u') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceBishop(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}

				if (chessPiece[flag].movePosDiag == 'd') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceBishop(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
			}

			if (chessPiece[flag].movePos == 'l') {
				if (chessPiece[flag].movePosDiag == 'u') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceBishop(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}

				if (chessPiece[flag].movePosDiag == 'd') {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += chessPiece[flag].movCount;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceBishop(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
									 chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
				}
			}

			chessPiece[flag].movePos = 's';
			chessPiece[flag].movePosDiag = 's';
			chessPiece[flag].moveStatus = false;
			chessPiece[flag].movCount = 0;
		}

		draw_box(cellUsed[chessPiece[flag].atCellNo].startX - (pieceWidth_x * 0.05), cellUsed[chessPiece[flag].atCellNo].startY - (pieceHeight_y * 0.05),
				 1.1* pieceWidth_x, 1.1*pieceHeight_y, col2[0], col2[1], col2[2]);
		draw_box(cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col2[0], col2[1], col2[2]);

		int Xright = chessPiece[flag].x + 1,
			Xleft = chessPiece[flag].x - 1,

			Yup = chessPiece[flag].y + 1,
			Ydown = chessPiece[flag].y - 1;

		int count = 1, cellCount = 8;
		//upper right
		int axis_y_count = 1;
		count = 1, cellCount = 8;

		if ((chessPiece[flag].atCellNo % 8) < 7) {
			for (int i = Yup; i < 8; i++) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 7 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count++;
				cellCount += 8;
			}
		}

		//upper left
		axis_y_count = -1;
		count = 1, cellCount = 8;
		if ((chessPiece[flag].atCellNo % 8) > 0) {
			for (int i = Yup; i < 8; i++) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 0 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count--;
				cellCount += 8;
			}
		}

		//lower right
		axis_y_count = 1;
		count = 1, cellCount = -8;

		if ((chessPiece[flag].atCellNo % 8) < 7) {
			for (int i = Ydown; i >= 0; i--) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 7 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count++;
				cellCount -= 8;
			}
		}

		//lower left
		axis_y_count = -1;
		count = 1, cellCount = -8;
		if ((chessPiece[flag].atCellNo % 8) > 0) {
			for (int i = Ydown; i >= 0; i--) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 0 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count--;
				cellCount -= 8;
			}
		}

		wait4move = true;
		flag = 99;
		putPieces();
		getCellState();
	}

	//queen
	if (flag == 3) {
		draw_board(actWidth_X, actheight_Y, 8, 8);

		if (!chessPiece[flag].moveStatus)
			draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
							chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
		else
		{
			if (chessPiece[flag].movePosDiag == 's') {
				switch (chessPiece[flag].movePos) {

				case 'r':
					if ((chessPiece[flag].x + chessPiece[flag].movCount) < 8) {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}
					break;

				case'l':
					if ((chessPiece[flag].x - chessPiece[flag].movCount) >= 0) {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}
					break;

				case'u':
					if ((chessPiece[flag].atCellNo + chessPiece[flag].movCount) < 64) {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}
					break;

				case'd':
					if ((chessPiece[flag].atCellNo + chessPiece[flag].movCount) >= 0) {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}
					break;

				default:
					break;

				}
				chessPiece[flag].moveStatus = false;
				chessPiece[flag].movePos = 's';
				chessPiece[flag].movCount = 0;
			}
			else
			{
				if (chessPiece[flag].movePos == 'r') {
					if (chessPiece[flag].movePosDiag == 'u') {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}

					if (chessPiece[flag].movePosDiag == 'd') {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}
				}

				if (chessPiece[flag].movePos == 'l') {
					if (chessPiece[flag].movePosDiag == 'u') {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}

					if (chessPiece[flag].movePosDiag == 'd') {
						cellUsed[chessPiece[flag].atCellNo].used = false;
						chessPiece[flag].atCellNo += chessPiece[flag].movCount;
						cellUsed[chessPiece[flag].atCellNo].used = true;
						syncChessData(flag);
						draw_pieceQueen(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
										chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
					}
				}

				chessPiece[flag].movePos = 's';
				chessPiece[flag].movePosDiag = 's';
				chessPiece[flag].moveStatus = false;
				chessPiece[flag].movCount = 0;
			}

		}

		draw_box(cellUsed[chessPiece[flag].atCellNo].startX - (pieceWidth_x * 0.05), cellUsed[chessPiece[flag].atCellNo].startY - (pieceHeight_y * 0.05),
				 1.1* pieceWidth_x, 1.1*pieceHeight_y, col2[0], col2[1], col2[2]);
		draw_box(cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col2[0], col2[1], col2[2]);

		int Xright = chessPiece[flag].x + 1,
			Xleft = chessPiece[flag].x - 1,

			Yup = chessPiece[flag].y + 1,
			Ydown = chessPiece[flag].y - 1;

		//right
		int count = 1, cellCount = 8;
		for (int i = Xright; i < 8; i++)
		{
			if ((chessPiece[flag].x + count) < 8 && !(cellUsed[chessPiece[flag].atCellNo + count].used))
				draw_box(cellUsed[chessPiece[flag].atCellNo + count].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count++;
		}

		//left
		count = -1;
		for (int i = Xleft; i >= 0; i--)
		{
			if ((chessPiece[flag].x + count) < 8 && !(cellUsed[chessPiece[flag].atCellNo + count].used))
				draw_box(cellUsed[chessPiece[flag].atCellNo + count].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count--;
		}

		//up
		count = 1, cellCount = 8;
		for (int i = Yup; i < 8; i++)
		{
			if ((chessPiece[flag].y + count) < 8 && (chessPiece[flag].atCellNo + cellCount) < 64 &&
				!cellUsed[chessPiece[flag].atCellNo + cellCount].used) {
				draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount].startX, cellUsed[chessPiece[flag].atCellNo + cellCount].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);
			}

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count++;
			cellCount += 8;
		}

		//upper right
		int axis_y_count = 1;
		count = 1, cellCount = 8;

		if ((chessPiece[flag].atCellNo % 8) < 7) {
			for (int i = Yup; i < 8; i++) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 7 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count++;
				cellCount += 8;
			}
		}

		//upper left
		axis_y_count = -1;
		count = 1, cellCount = 8;
		if ((chessPiece[flag].atCellNo % 8) > 0) {
			for (int i = Yup; i < 8; i++) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 0 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count--;
				cellCount += 8;
			}
		}

		//down
		count = 1, cellCount = 8;
		for (int i = Ydown; i >= 0; i--)
		{
			if ((chessPiece[flag].y - count) < 8 && (chessPiece[flag].atCellNo - cellCount) >= 0 && !cellUsed[chessPiece[flag].atCellNo - cellCount].used)
				draw_box(cellUsed[chessPiece[flag].atCellNo - cellCount].startX, cellUsed[chessPiece[flag].atCellNo - cellCount].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

			else {
				count = 1;
				cellCount = 8;
				break;
			}
			count++;
			cellCount += 8;
		}

		//lower right
		axis_y_count = 1;
		count = 1, cellCount = -8;

		if ((chessPiece[flag].atCellNo % 8) < 7) {
			for (int i = Ydown; i >= 0; i--) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 7 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count++;
				cellCount -= 8;
			}
		}

		//lower left
		axis_y_count = -1;
		count = 1, cellCount = -8;
		if ((chessPiece[flag].atCellNo % 8) > 0) {
			for (int i = Ydown; i >= 0; i--) {
				if ((chessPiece[flag].atCellNo + cellCount + axis_y_count) % 8 != 0 &&
					(chessPiece[flag].atCellNo + cellCount + axis_y_count) < 64 && !cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used) {

					draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
							 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
				}
				else {
					if (!cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].used)
						draw_box(cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startX,
								 cellUsed[chessPiece[flag].atCellNo + cellCount + axis_y_count].startY, pieceWidth_x, pieceHeight_y, col10[0], col10[1], col10[2]);
					break;
				}
				count++;
				axis_y_count--;
				cellCount -= 8;
			}
		}


		wait4move = true;
		flag = 99;
		putPieces();
		getCellState();
	}

	//king
	if (flag == 4) {
		draw_board(actWidth_X, actheight_Y, 8, 8);

		if (!chessPiece[flag].moveStatus)
			draw_pieceKing(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
						   chessPiece[flag].width_x, pieceHeight_y, col1[0], col1[1], col1[2]);

		else {
			switch (chessPiece[flag].movePos)
			{
			case 'r':
				if ((chessPiece[flag].x + 1) < 8) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo++;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKing(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, pieceHeight_y, col1[0], col1[1], col1[2]);
				}
				break;

			case'l':
				if ((chessPiece[flag].x - 1) >= 0) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo--;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKing(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, pieceHeight_y, col1[0], col1[1], col1[2]);
				}
				break;

			case'u':
				if ((chessPiece[flag].y + 1) < 8 && (chessPiece[flag].atCellNo + 8) < 64) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo += 8;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKing(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, pieceHeight_y, col1[0], col1[1], col1[2]);
				}
				break;

			case'd':
				if ((chessPiece[flag].y - 1) >= 0 && (chessPiece[flag].atCellNo - 8) >= 0) {
					cellUsed[chessPiece[flag].atCellNo].used = false;
					chessPiece[flag].atCellNo -= 8;
					cellUsed[chessPiece[flag].atCellNo].used = true;
					syncChessData(flag);
					draw_pieceKing(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
								   chessPiece[flag].width_x, pieceHeight_y, col1[0], col1[1], col1[2]);
				}
				break;

			default:
				break;
			}
			chessPiece[flag].moveStatus = false;
			chessPiece[flag].movePos = 's';
		}

		draw_box(cellUsed[chessPiece[flag].atCellNo].startX - (pieceWidth_x * 0.05), cellUsed[chessPiece[flag].atCellNo].startY - (pieceHeight_y * 0.05),
				 1.1* pieceWidth_x, 1.1*pieceHeight_y, col2[0], col2[1], col2[2]);
		draw_box(cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col2[0], col2[1], col2[2]);

		int Xright = chessPiece[flag].x + 1,
			Xleft = chessPiece[flag].x - 1,

			Yup = chessPiece[flag].y + 1,
			Ydown = chessPiece[flag].y - 1;

		if ((chessPiece[flag].x + 1) < 8 && !cellUsed[chessPiece[flag].atCellNo + 1].used)
			draw_box(cellUsed[chessPiece[flag].atCellNo + 1].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

		if ((chessPiece[flag].x - 1) >= 0 && !cellUsed[chessPiece[flag].atCellNo - 1].used)
			draw_box(cellUsed[chessPiece[flag].atCellNo - 1].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

		if ((chessPiece[flag].y + 1) < 8 && (chessPiece[flag].atCellNo + 8) < 64 && !cellUsed[chessPiece[flag].atCellNo + 8].used)
			draw_box(cellUsed[chessPiece[flag].atCellNo + 8].startX, cellUsed[chessPiece[flag].atCellNo + 8].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

		if ((chessPiece[flag].y - 1) < 8 && (chessPiece[flag].atCellNo - 8) >= 0 && !cellUsed[chessPiece[flag].atCellNo - 8].used)
			draw_box(cellUsed[chessPiece[flag].atCellNo - 8].startX, cellUsed[chessPiece[flag].atCellNo - 8].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

		wait4move = true;
		flag = 99;
		putPieces();
		getCellState();
	}

	//pawns
	if (flag > 7 && flag < 16) {
		draw_board(actWidth_X, actheight_Y, 8, 8);

		if (!chessPiece[flag].moveStatus)
			draw_piecePawn(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
						   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);

		else if (chessPiece[flag].movePos = 'u') {
			if ((chessPiece[flag].y + 1) < 8 && (chessPiece[flag].atCellNo + 8) < 64) {
				cellUsed[chessPiece[flag].atCellNo].used = false;
				chessPiece[flag].atCellNo += 8;
				cellUsed[chessPiece[flag].atCellNo].used = true;
				syncChessData(flag);
				draw_piecePawn(chessPiece[flag].enabled, cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY,
							   chessPiece[flag].width_x, chessPiece[flag].height_y, col1[0], col1[1], col1[2]);
			}
			chessPiece[flag].moveStatus = false;
			chessPiece[flag].movePos = 's';
		}

		draw_box(cellUsed[chessPiece[flag].atCellNo].startX - (pieceWidth_x * 0.05), cellUsed[chessPiece[flag].atCellNo].startY - (pieceHeight_y * 0.05),
				 1.1* pieceWidth_x, 1.1*pieceHeight_y, col2[0], col2[1], col2[2]);
		draw_box(cellUsed[chessPiece[flag].atCellNo].startX, cellUsed[chessPiece[flag].atCellNo].startY, pieceWidth_x, pieceHeight_y, col2[0], col2[1], col2[2]);

		int	Yup = chessPiece[flag].y + 1;

		if ((chessPiece[flag].y + 1) < 8 && (chessPiece[flag].atCellNo + 8) < 64 && !cellUsed[chessPiece[flag].atCellNo + 8].used)
			draw_box(cellUsed[chessPiece[flag].atCellNo + 8].startX, cellUsed[chessPiece[flag].atCellNo + 8].startY, pieceWidth_x, pieceHeight_y, col9[0], col9[1], col9[2]);

		wait4move = true;
		flag = 99;
		putPieces();
		getCellState();

	}

}

void testCode(int flag) {
	if (flag == 99) {
		//draw_board(actWidth_X, actheight_Y, 8, 8);
		addInfo();
		putPieces();
	}
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, actWidth_X, 0, actheight_Y);
}

void displayPiece(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	mainCode(flag);
	//testCode(flag);
	glFlush();
	glutSwapBuffers();
}

void mouseClick(int btnClicked, int state, int click_x, int click_y) {
	mouseX = click_x;
	mouseY = actheight_Y - click_y;

	if (btnClicked == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		for (int i = 0; i < 16; i++) {
			if (chessPiece[i].enabled) {
				if (mouseX > cellUsed[chessPiece[i].atCellNo].startX && mouseX < cellUsed[chessPiece[i].atCellNo].startX + pieceWidth_x  &&
					mouseY > cellUsed[chessPiece[i].atCellNo].startY && mouseY < cellUsed[chessPiece[i].atCellNo].startY + pieceHeight_y) {
					flag = chessPiece[i].id;
					break;
				}
			}
		}

		if (wait4move) {

			//rooks
			if (flag == 0 || flag == 7) {

				int cellNo = chessPiece[flag].atCellNo;
				int count = 1;
				while (cellNo % 8 != 7)
				{
					if ((chessPiece[flag].x + count) < 8) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count].startX && mouseX < cellUsed[chessPiece[flag].atCellNo + count].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo].startY && mouseY < cellUsed[chessPiece[flag].atCellNo].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'r';
							chessPiece[flag].movCount = count;
						}
					}
					count++;
					cellNo++;
				}

				count = -1;
				while (cellNo % 8 != 0) {
					if ((chessPiece[flag].x + count) >= 0) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count].startX && mouseX < cellUsed[chessPiece[flag].atCellNo + count].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo].startY && mouseY < cellUsed[chessPiece[flag].atCellNo].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'l';
							chessPiece[flag].movCount = count;
						}
					}
					count--;
					cellNo--;
				}

				count = 1;
				int cellCount = 8;
				while ((chessPiece[flag].y + count) < 8) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCount].startY &&  mouseY < cellUsed[chessPiece[flag].atCellNo + cellCount].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'u';
						chessPiece[flag].movCount = cellCount;
					}
					count++;
					cellCount += 8;
				}
				count = -1;
				cellCount = -8;
				while ((chessPiece[flag].y + count) >= 0) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCount].startY &&  mouseY < cellUsed[chessPiece[flag].atCellNo + cellCount].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'd';
						chessPiece[flag].movCount = cellCount;
					}
					count--;
					cellCount -= 8;
				}
			}

			//knights
			if (flag == 1 || flag == 6) {
				int count = 8;
				while (count < 16 && chessPiece[flag].atCellNo + count < 64)
					count += 8;

				//up
				if (count == 16) {
					if ((chessPiece[flag].atCellNo + count + 1) % 8 != 0 && (chessPiece[flag].atCellNo + count + 1) < 64 &&
						!cellUsed[chessPiece[flag].atCellNo + count + 1].used)
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count + 1].startX &&
							mouseX < cellUsed[chessPiece[flag].atCellNo + count + 1].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo + count + 1].startY &&
							mouseY < cellUsed[chessPiece[flag].atCellNo + count + 1].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'u';
							chessPiece[flag].movePosDiag = 'r';
							chessPiece[flag].movCount += count + 1;
						}

					if ((chessPiece[flag].atCellNo + count - 1) % 8 != 7 && (chessPiece[flag].atCellNo + count - 1) < 64 &&
						!cellUsed[chessPiece[flag].atCellNo + count - 1].used) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count - 1].startX &&
							mouseX < cellUsed[chessPiece[flag].atCellNo + count - 1].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo + count - 1].startY &&
							mouseY < cellUsed[chessPiece[flag].atCellNo + count - 1].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'u';
							chessPiece[flag].movePosDiag = 'l';
							chessPiece[flag].movCount += count - 1;
						}
					}

				}

				//down
				count = -8;
				while (count > -16 && chessPiece[flag].atCellNo + count > 0)
					count -= 8;

				if (count == -16) {
					if ((chessPiece[flag].atCellNo + count + 1) % 8 != 0 && (chessPiece[flag].atCellNo + count + 1) > 0 &&
						!cellUsed[chessPiece[flag].atCellNo + count + 1].used)
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count + 1].startX &&
							mouseX < cellUsed[chessPiece[flag].atCellNo + count + 1].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo + count + 1].startY &&
							mouseY < cellUsed[chessPiece[flag].atCellNo + count + 1].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'd';
							chessPiece[flag].movePosDiag = 'r';
							chessPiece[flag].movCount += count + 1;
						}

					if ((chessPiece[flag].atCellNo + count - 1) % 8 != 7 && (chessPiece[flag].atCellNo + count - 1) > 0 &&
						!cellUsed[chessPiece[flag].atCellNo + count - 1].used) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count - 1].startX &&
							mouseX < cellUsed[chessPiece[flag].atCellNo + count - 1].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo + count - 1].startY &&
							mouseY < cellUsed[chessPiece[flag].atCellNo + count - 1].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'd';
							chessPiece[flag].movePosDiag = 'l';
							chessPiece[flag].movCount += count - 1;
						}
					}
				}

				//right
				count = 1;
				if ((chessPiece[flag].atCellNo) % 8 != 7) {
					while (count < 2 && chessPiece[flag].atCellNo + count < 64) {
						if ((chessPiece[flag].atCellNo + count) % 8 == 7) {
							break;
						}
						count++;
					}
				}

				if (count == 2) {
					if ((chessPiece[flag].atCellNo + count + 8) < 64 && !cellUsed[chessPiece[flag].atCellNo + count + 8].used) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count + 8].startX &&
							mouseX < cellUsed[chessPiece[flag].atCellNo + count + 8].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo + count + 8].startY &&
							mouseY < cellUsed[chessPiece[flag].atCellNo + count + 8].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'r';
							chessPiece[flag].movePosDiag = 'u';
							chessPiece[flag].movCount += count + 8;
						}
					}


					if ((chessPiece[flag].atCellNo + count - 8) >= 0 && !cellUsed[chessPiece[flag].atCellNo + count - 8].used) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count - 8].startX &&
							mouseX < cellUsed[chessPiece[flag].atCellNo + count - 8].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo + count - 8].startY &&
							mouseY < cellUsed[chessPiece[flag].atCellNo + count - 8].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'r';
							chessPiece[flag].movePosDiag = 'd';
							chessPiece[flag].movCount += count - 8;
						}
					}
				}

				//left
				count = -1;
				if ((chessPiece[flag].atCellNo) % 8 != 0) {
					while (count > -2 && chessPiece[flag].atCellNo + count < 64) {
						if ((chessPiece[flag].atCellNo + count) % 8 == 0) {
							break;
						}
						count--;
					}

					if (count == -2) {
						if ((chessPiece[flag].atCellNo + count + 8) < 64 && !cellUsed[chessPiece[flag].atCellNo + count + 8].used)
						{
							if (mouseX > cellUsed[chessPiece[flag].atCellNo + count + 8].startX &&
								mouseX < cellUsed[chessPiece[flag].atCellNo + count + 8].startX + pieceWidth_x  &&
								mouseY > cellUsed[chessPiece[flag].atCellNo + count + 8].startY &&
								mouseY < cellUsed[chessPiece[flag].atCellNo + count + 8].startY + pieceHeight_y) {
								chessPiece[flag].moveStatus = true;
								wait4move = false;
								chessPiece[flag].movePos = 'l';
								chessPiece[flag].movePosDiag = 'u';
								chessPiece[flag].movCount += count + 8;
							}
						}

						if ((chessPiece[flag].atCellNo + count - 8) >= 0 && !cellUsed[chessPiece[flag].atCellNo + count - 8].used)
						{
							if (mouseX > cellUsed[chessPiece[flag].atCellNo + count - 8].startX &&
								mouseX < cellUsed[chessPiece[flag].atCellNo + count - 8].startX + pieceWidth_x  &&
								mouseY > cellUsed[chessPiece[flag].atCellNo + count - 8].startY &&
								mouseY < cellUsed[chessPiece[flag].atCellNo + count - 8].startY + pieceHeight_y) {
								chessPiece[flag].moveStatus = true;
								wait4move = false;
								chessPiece[flag].movePos = 'l';
								chessPiece[flag].movePosDiag = 'd';
								chessPiece[flag].movCount += count - 8;
							}
						}
					}
				}
			}

			//bishops
			if (flag == 2 || flag == 5) {
				int cellNo = chessPiece[flag].atCellNo;
				int count = 9, cellCountX = 1, cellCountY = 8;

				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 7)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'r';
						chessPiece[flag].movePosDiag = 'u';
						chessPiece[flag].movCount = cellCountX + cellCountY;
						break;
					}

					count += 9;
					cellCountX++;
					cellCountY += 8;
					cellNo += 9;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = -7, cellCountX = 1, cellCountY = -7;
				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 7)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'r';
						chessPiece[flag].movePosDiag = 'd';
						chessPiece[flag].movCount = cellCountY;
						break;
					}

					count -= 7;
					cellCountX++;
					cellCountY -= 7;
					cellNo -= 7;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = 7, cellCountX = -1, cellCountY = 7;
				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 0)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'l';
						chessPiece[flag].movePosDiag = 'u';
						chessPiece[flag].movCount = cellCountY;
						break;
					}

					count += 7;
					cellCountX--;
					cellCountY += 7;
					cellNo += 7;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = -9, cellCountX = -1, cellCountY = -8;
				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 0)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'l';
						chessPiece[flag].movePosDiag = 'd';
						chessPiece[flag].movCount = cellCountX + cellCountY;
						break;
					}

					count -= 9;
					cellCountX--;
					cellCountY -= 8;
					cellNo -= 9;
				}
			}

			//queen
			if (flag == 3) {
				int cellNo = chessPiece[flag].atCellNo;
				int count = 1;
				bool endMov = false;
				while (cellNo % 8 != 7 && !endMov)
				{
					if ((chessPiece[flag].x + count) < 8) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count].startX && mouseX < cellUsed[chessPiece[flag].atCellNo + count].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo].startY && mouseY < cellUsed[chessPiece[flag].atCellNo].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'r';
							chessPiece[flag].movePosDiag = 's';
							chessPiece[flag].movCount = count;
							endMov = true;
							break;
						}
					}
					count++;
					cellNo++;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = -1;
				while (cellNo % 8 != 0 && !endMov) {
					if ((chessPiece[flag].x + count) >= 0) {
						if (mouseX > cellUsed[chessPiece[flag].atCellNo + count].startX && mouseX < cellUsed[chessPiece[flag].atCellNo + count].startX + pieceWidth_x  &&
							mouseY > cellUsed[chessPiece[flag].atCellNo].startY && mouseY < cellUsed[chessPiece[flag].atCellNo].startY + pieceHeight_y) {
							chessPiece[flag].moveStatus = true;
							wait4move = false;
							chessPiece[flag].movePos = 'l';
							chessPiece[flag].movePosDiag = 's';
							chessPiece[flag].movCount = count;
							endMov = true;
							break;
						}
					}
					count--;
					cellNo--;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = 1;
				int cellCount = 8;
				while ((chessPiece[flag].y + count) < 8 && !endMov) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCount].startY &&  mouseY < cellUsed[chessPiece[flag].atCellNo + cellCount].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'u';
						chessPiece[flag].movePosDiag = 's';
						chessPiece[flag].movCount = cellCount;
						endMov = true;
						break;
					}
					count++;
					cellCount += 8;
					cellNo += cellCount;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = -1;
				cellCount = -8;
				while ((chessPiece[flag].y + count) >= 0 && !endMov) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCount].startY &&  mouseY < cellUsed[chessPiece[flag].atCellNo + cellCount].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'd';
						chessPiece[flag].movePosDiag = 's';
						chessPiece[flag].movCount = cellCount;
						endMov = true;
						break;
					}
					count--;
					cellCount -= 8;
					cellNo += cellCount;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = 9;
				int cellCountX = 1, cellCountY = 8;

				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 7 && !endMov)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'r';
						chessPiece[flag].movePosDiag = 'u';
						chessPiece[flag].movCount = cellCountX + cellCountY;
						endMov = true;
						break;
					}

					count += 9;
					cellCountX++;
					cellCountY += 8;
					cellNo += 9;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = -7, cellCountX = 1, cellCountY = -7;
				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 7 && !endMov)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'r';
						chessPiece[flag].movePosDiag = 'd';
						chessPiece[flag].movCount = cellCountY;
						endMov = true;
						break;
					}

					count -= 7;
					cellCountX++;
					cellCountY -= 7;
					cellNo -= 7;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = 7, cellCountX = -1, cellCountY = 7;
				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 0 && !endMov)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'l';
						chessPiece[flag].movePosDiag = 'u';
						chessPiece[flag].movCount = cellCountY;
						endMov = true;
						break;
					}

					count += 7;
					cellCountX--;
					cellCountY += 7;
					cellNo += 7;
				}

				cellNo = chessPiece[flag].atCellNo;
				count = -9, cellCountX = -1, cellCountY = -8;
				while (cellNo < 64 && cellNo >= 0 && cellNo % 8 != 0 && !endMov)
				{
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + cellCountX].startX &&
						mouseX < cellUsed[chessPiece[flag].atCellNo + cellCountX].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + cellCountY].startY &&
						mouseY < cellUsed[chessPiece[flag].atCellNo + cellCountY].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'l';
						chessPiece[flag].movePosDiag = 'd';
						chessPiece[flag].movCount = cellCountX + cellCountY;
						endMov = true;
						break;
					}

					count -= 9;
					cellCountX--;
					cellCountY -= 8;
					cellNo -= 9;
				}
			}

			//king
			if (flag == 4) {//king
				if ((chessPiece[flag].x + 1) < 8) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo + 1].startX && mouseX < cellUsed[chessPiece[flag].atCellNo + 1].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo].startY && mouseY < cellUsed[chessPiece[flag].atCellNo].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'r';
					}
				}

				if ((chessPiece[flag].x - 1) >= 0) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo - 1].startX && mouseX < cellUsed[chessPiece[flag].atCellNo - 1].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo].startY && mouseY < cellUsed[chessPiece[flag].atCellNo].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'l';
					}
				}

				if ((chessPiece[flag].y + 1) < 8) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + 8].startY &&  mouseY < cellUsed[chessPiece[flag].atCellNo + 8].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'u';
					}
				}

				if ((chessPiece[flag].y - 1) >= 0) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo - 8].startY && mouseY < cellUsed[chessPiece[flag].atCellNo - 8].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'd';
					}
				}
			}

			//pawns
			if (flag >= 8 && flag <= 15) {//pawns
				if ((chessPiece[flag].y + 1) < 8) {
					if (mouseX > cellUsed[chessPiece[flag].atCellNo].startX && mouseX < cellUsed[chessPiece[flag].atCellNo].startX + pieceWidth_x  &&
						mouseY > cellUsed[chessPiece[flag].atCellNo + 8].startY &&  mouseY < cellUsed[chessPiece[flag].atCellNo + 8].startY + pieceHeight_y) {
						chessPiece[flag].moveStatus = true;
						wait4move = false;
						chessPiece[flag].movePos = 'u';
					}
				}
			}

		}
	}
	if (btnClicked == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		flag = 99;
	}
	glutPostRedisplay();
}

void keyClick(unsigned char key, int key_x, int key_ykey) {
	if (key == 'r' || key == 'R') {
		flag = 99;
		reset();
		startMain = true;
		initialize();
	}
	/*
		if (key == 'w' || key == 'W') {
			int count = 8;
			if (!cellUsed[chessPiece[1].atCellNo + count].used && (chessPiece[1].atCellNo + count) < 64 && (chessPiece[1].atCellNo + count) >= 0) {
				cellUsed[chessPiece[1].atCellNo].used = false;
				chessPiece[1].atCellNo+=count;
				cellUsed[chessPiece[1].atCellNo].used = true;
			}
		}

		if (key == 'a' || key == 'a') {
			int count = -1;
			if (!cellUsed[chessPiece[1].atCellNo + count].used && (chessPiece[1].atCellNo + count) < 64 && (chessPiece[1].atCellNo + count) >= 0) {
				cellUsed[chessPiece[1].atCellNo].used = false;
				chessPiece[1].atCellNo += count;
				cellUsed[chessPiece[1].atCellNo].used = true;
			}
		}

		if (key == 's' || key == 'S') {
			int count = -8;
			if (!cellUsed[chessPiece[1].atCellNo + count].used && (chessPiece[1].atCellNo + count) < 64 && (chessPiece[1].atCellNo + count) >= 0) {
				cellUsed[chessPiece[1].atCellNo].used = false;
				chessPiece[1].atCellNo += count;
				cellUsed[chessPiece[1].atCellNo].used = true;
			}
		}

		if (key == 'd' || key == 'D') {
			int count = 1;
			if (!cellUsed[chessPiece[1].atCellNo + count].used && (chessPiece[1].atCellNo + count) < 64 && (chessPiece[1].atCellNo + count) >= 0) {
				cellUsed[chessPiece[1].atCellNo].used = false;
				chessPiece[1].atCellNo += count;
				cellUsed[chessPiece[1].atCellNo].used = true;
			}
		}*/
	glutPostRedisplay();
}

//	8	9	10	11	12	13	14	15
//	0	1	2	3	4	5	6	7

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(actWidth_X, actheight_Y);
	glutInitWindowPosition(window_posX, window_posY);
	glutCreateWindow("Chess");
	myInit();
	if (startMain)
		initialize();
	glutDisplayFunc(displayPiece);
	glutKeyboardFunc(keyClick);
	glutMouseFunc(mouseClick);
	glutMainLoop();
}