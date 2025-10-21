#pragma once


#define SQ(x) ((x) * (x))
#define NORM2SQ(x, y) (SQ(x) + SQ(y))
#define NORM2(x, y) (sqrt(NORM2SQ(x, y)))
#define FLAT(x, y, width) ((y) * (width) + (x))


#define NX_default 16
#define NY_default 9
#define SIZE_PHYSICS_X_MAX_default NX_default
#define SIZE_PHYSICS_Y_MAX_default NY_default
#define INITIAL_X_VELOCITY_default 0.0f
#define INITIAL_Y_VELOCITY_default 0.0f
#define DIVERGENCE_ITERATIONS_DEFAULT 30
#define DT_default 0.1f
// Cosmetic
#define SCREEN_WIDTH_default 1920
#define SCREEN_HEIGHT_default 1080
#define SCREEN_OFFSET_X_default 0
#define SCREEN_OFFSET_Y_default 0
#define CELL_OUTLINE_THICKNESS_default 1.0f
#define CELL_OUTLINE_COLOUR_default sf::Color(100, 100, 100, 255)
#define CELL_FILL_COLOUR_default sf::Color(255, 255, 255, 100)



// // Derived quantities from above
// #define CELL_PHYSICS_DX ((float)SIZE_PHYSICS_X_MAX / NX)
// #define CELL_PHYSICS_DY ((float)SIZE_PHYSICS_Y_MAX / NY)
// #define CELL_SCREEN_DX ((float)SCREEN_WIDTH / NX)
// #define CELL_SCREEN_DY ((float)SCREEN_HEIGHT / NY)


// Renderer parameters
#define FRAME_RATE_LIMIT 60


struct Dimensions{
    int nx;
    int ny;
    int size_physics_x_max;
    int size_physics_y_max;
    int screen_width;
    int screen_height;
    int screen_offset_x;
    int screen_offset_y;

    
};


// #define DT 0.01f
// #define MAX_DIVERGENCE_ITERATIONS 10
// #define DIVERGENCE_TOLERANCE 0.001f
// #define MAX_ADVECTION_SHORTENING_ITERATIONS 100
// The above should all be variable from the interface