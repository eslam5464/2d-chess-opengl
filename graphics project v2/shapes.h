#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED
#include<iostream>

void draw_square(int startX, int startY, double widthX, double heightY, double col[]);
void draw_tri(int startX, int startY, double width_x, double height_y, int quadPos, double col[3]);
void draw_pieceRook(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b);
void draw_piecePawn(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b);
void draw_pieceKing(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b);
void draw_pieceBishop(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b);
void draw_pieceQueen(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b);
void draw_pieceKnight(bool Enable, int startX, int startY, double width_x, double height_y, double r, double g, double b);
void draw_line(int x1, int y1, int x2, int y2, float r, float g, float b);
void draw_box(float start_X, float start_Y, int Width_X, int Height_Y, float r, float g, float b);
void draw_board(int width_x, int height_y, int row, int column);

#endif //SHAPES_H_INCLUDED