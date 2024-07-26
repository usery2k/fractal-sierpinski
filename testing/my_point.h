// my_point.h
#ifndef MY_POINT_H
#define MY_POINT_H

typedef struct {
    int x;
    int y;
} Point;

Point crear_punto(int x, int y);
Point suma_puntos(Point p1, Point p2);
Point resta_puntos(Point p1, Point p2);
Point mul_escalar(Point p, float s);
Point div_escalar(Point p, float s);

#endif