#ifndef _GRAPHICS_H_   /* Include guard */
#define _GRAPHICS_H_

#include <stdint.h>
#include "hal_graphics.h"
#include <stdbool.h>
#include <stdarg.h>

// -----------------------------------------------------------
//|                  Standardized Components                  |
// -----------------------------------------------------------

/** screen sizes where 0,0 is the top left */
enum screen_size_e {
    SCREEN_SIZE_128X64,
    SCREEN_SIZE_320X240,
    SCREEN_SIZE_160X128
};

typedef struct {
    // members TBD
    uint8_t foreground[3];
    uint8_t background[3];
    enum screen_size_e screen_size;
    hal_graphics_t hal;
} graphics_t;

typedef struct {
    uint16_t x;
    uint16_t y;
} g_point_t;

typedef union {
    uint8_t all;
    struct {
        uint8_t red:2;
        uint8_t green:2;
        uint8_t blue:2;
        uint8_t unused:1;
        uint8_t transparent:1;
    };
} g_pixel_t;


void Graphics_Init(graphics_t * gptr);
void Graphics_SetInputScreenSize(graphics_t * gptr, enum screen_size_e screen_size);
void Graphics_DrawTile(graphics_t * gptr, g_point_t position, g_pixel_t * tile[], char x, char y);
void Graphics_SetBackground(graphics_t * gptr, uint8_t color[3]);
void Graphics_SetForeground(graphics_t * gptr, uint8_t color[3]);
void Graphics_DrawLine(graphics_t * gptr, g_point_t p1, g_point_t p2);
void Graphics_DrawPixel(graphics_t * gptr, g_point_t p);
void Graphics_DrawRectangle(graphics_t * gptr, g_point_t top_left, g_point_t bottom_right);
void Graphics_DrawText(graphics_t * gptr, g_point_t position, char * str, ...);
void Graphics_ClearScreen(graphics_t * gptr);
void Graphics_UpdateScreen(graphics_t * gptr);

// -----------------------------------------------------------
//|                     Unique Components                     |
// -----------------------------------------------------------

void Display_PushCommand(char command);
void Display_PushData(unsigned char data);
void Display_SetRAMCord(graphics_t * gptr,int X, int Y);
void Display_ClearRAMCord(graphics_t * gptr,int X, int Y);
g_point_t Display_ScaleCord(graphics_t * gptr, int preX, int preY);

#endif // graphics.h

