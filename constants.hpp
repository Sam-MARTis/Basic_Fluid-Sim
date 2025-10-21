#pragma once


#define SQ(x) ((x) * (x))
#define NORM2SQ(x, y) (SQ(x) + SQ(y))
#define NORM2(x, y) (sqrt(NORM2SQ(x, y)))
#define FLAT(x, y, width) ((y) * (width) + (x))


#define NX 10
#define NY 6
#define SIZE_PHYSICS_X_MAX 10
#define SIZE_PHYSICS_Y_MAX 6

#define INITIAL_X_VELOCITY 0.0f
#define INITIAL_Y_VELOCITY 0.0f


// Cosmetic
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define SCREEN_OFFSET_X 0
#define SCREEN_OFFSET_Y 0
#define CELL_OUTLINE_THICKNESS 1.0f
#define CELL_OUTLINE_COLOUR sf::Color(100, 100, 100, 255)
#define CELL_DEFAULT_FILL_COLOUR sf::Color(255, 255, 255, 100)



// Derived quantities from above
#define CELL_PHYSICS_DX ((float)SIZE_PHYSICS_X_MAX / NX)
#define CELL_PHYSICS_DY ((float)SIZE_PHYSICS_Y_MAX / NY)
#define CELL_SCREEN_DX ((float)SCREEN_WIDTH / NX)
#define CELL_SCREEN_DY ((float)SCREEN_HEIGHT / NY)


// Renderer parameters
#define FRAME_RATE_LIMIT 60

// #define DT 0.01f
// #define MAX_DIVERGENCE_ITERATIONS 10
// #define DIVERGENCE_TOLERANCE 0.001f
// #define MAX_ADVECTION_SHORTENING_ITERATIONS 100
// The above should all be variable from the interface