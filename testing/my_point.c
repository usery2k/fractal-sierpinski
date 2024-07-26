// my_point.c
#include "my_point.h"

Point crear_punto(int x, int y) {
    Point p = {x, y};
    return p;
}

Point suma_puntos(Point p1, Point p2) {
    return crear_punto(p1.x + p2.x, p1.y + p2.y);
}

Point resta_puntos(Point p1, Point p2) {
    return crear_punto(p1.x - p2.x, p1.y - p2.y);
}

Point mul_escalar(Point p, float s) {
    return crear_punto(p.x * s, p.y * s);
}

Point div_escalar(Point p, float s) {
    if (s != 0) {
        return crear_punto(p.x / s, p.y / s);
    } else {
        // Retornar el punto original si el escalar es 0 para evitar división por cero
        return p;
    }
}