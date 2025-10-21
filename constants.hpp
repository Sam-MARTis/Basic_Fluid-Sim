#pragma once


#define SQ(x) ((x) * (x))
#define NORM2SQ(x, y) (SQ(x) + SQ(y))
#define NORM2(x, y) (sqrt(NORM2SQ(x, y)))
#define FLAT(x, y, width) ((y) * (width) + (x))


#define NX 100
#define NY 100
#define SizeX 600
#define SizeY 600
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define DT 0.01f
#define MAX_DIVERGENCE_ITERATIONS 10
#define DIVERGENCE_TOLERANCE 0.001f
#define MAX_ADVECTION_SHORTENING_ITERATIONS 100