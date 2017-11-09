#include "graphics.h"
#include "hal_graphics.h"
#include "buffer.h"
#include "buffer_printf.h"
#include <msp430f5529.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// ----------------------------------------------------------
//|                     Unique Variables                     |
// ----------------------------------------------------------

const char asciiArray[96][6] =
{
     {0x00,0x00,0x00,0x00,0x00,0x00},
     {0x00,0x00,0x06,0x5F,0x06,0x00},
     {0x00,0x07,0x03,0x00,0x07,0x03},
     {0x00,0x24,0x7E,0x24,0x7E,0x24},
     {0x00,0x24,0x2B,0x6A,0x12,0x00},
     {0x00,0x63,0x13,0x08,0x64,0x63},
     {0x00,0x36,0x49,0x56,0x20,0x50},
     {0x00,0x00,0x07,0x03,0x00,0x00},
     {0x00,0x00,0x3E,0x41,0x00,0x00},
     {0x00,0x00,0x41,0x3E,0x00,0x00},
     {0x00,0x08,0x3E,0x1C,0x3E,0x08},
     {0x00,0x08,0x08,0x3E,0x08,0x08},
     {0x00,0x00,0xE0,0x60,0x00,0x00},
     {0x00,0x08,0x08,0x08,0x08,0x08},
     {0x00,0x00,0x60,0x60,0x00,0x00},
     {0x00,0x20,0x10,0x08,0x04,0x02},
     {0x00,0x3E,0x51,0x49,0x45,0x3E},
     {0x00,0x00,0x42,0x7F,0x40,0x00},
     {0x00,0x62,0x51,0x49,0x49,0x46},
     {0x00,0x22,0x49,0x49,0x49,0x36},
     {0x00,0x18,0x14,0x12,0x7F,0x10},
     {0x00,0x2F,0x49,0x49,0x49,0x31},
     {0x00,0x3C,0x4A,0x49,0x49,0x30},
     {0x00,0x01,0x71,0x09,0x05,0x03},
     {0x00,0x36,0x49,0x49,0x49,0x36},
     {0x00,0x06,0x49,0x49,0x29,0x1E},
     {0x00,0x00,0x6C,0x6C,0x00,0x00},
     {0x00,0x00,0xEC,0x6C,0x00,0x00},
     {0x00,0x08,0x14,0x22,0x41,0x00},
     {0x00,0x24,0x24,0x24,0x24,0x24},
     {0x00,0x00,0x41,0x22,0x14,0x08},
     {0x00,0x02,0x01,0x59,0x09,0x06},
     {0x00,0x3E,0x41,0x5D,0x55,0x1E},
     {0x00,0x7E,0x11,0x11,0x11,0x7E},
     {0x00,0x7F,0x49,0x49,0x49,0x36},
     {0x00,0x3E,0x41,0x41,0x41,0x22},
     {0x00,0x7F,0x41,0x41,0x41,0x3E},
     {0x00,0x7F,0x49,0x49,0x49,0x41},
     {0x00,0x7F,0x09,0x09,0x09,0x01},
     {0x00,0x3E,0x41,0x49,0x49,0x7A},
     {0x00,0x7F,0x08,0x08,0x08,0x7F},
     {0x00,0x00,0x41,0x7F,0x41,0x00},
     {0x00,0x30,0x40,0x40,0x40,0x3F},
     {0x00,0x7F,0x08,0x14,0x22,0x41},
     {0x00,0x7F,0x40,0x40,0x40,0x40},
     {0x00,0x7F,0x02,0x04,0x02,0x7F},
     {0x00,0x7F,0x02,0x04,0x08,0x7F},
     {0x00,0x3E,0x41,0x41,0x41,0x3E},
     {0x00,0x7F,0x09,0x09,0x09,0x06},
     {0x00,0x3E,0x41,0x51,0x21,0x5E},
     {0x00,0x7F,0x09,0x09,0x19,0x66},
     {0x00,0x26,0x49,0x49,0x49,0x32},
     {0x00,0x01,0x01,0x7F,0x01,0x01},
     {0x00,0x3F,0x40,0x40,0x40,0x3F},
     {0x00,0x1F,0x20,0x40,0x20,0x1F},
     {0x00,0x3F,0x40,0x3C,0x40,0x3F},
     {0x00,0x63,0x14,0x08,0x14,0x63},
     {0x00,0x07,0x08,0x70,0x08,0x07},
     {0x00,0x71,0x49,0x45,0x43,0x00},
     {0x00,0x00,0x7F,0x41,0x41,0x00},
     {0x00,0x02,0x04,0x08,0x10,0x20},
     {0x00,0x00,0x41,0x41,0x7F,0x00},
     {0x00,0x04,0x02,0x01,0x02,0x04},
     {0x80,0x80,0x80,0x80,0x80,0x80},
     {0x00,0x00,0x03,0x07,0x00,0x00},
     {0x00,0x20,0x54,0x54,0x54,0x78},
     {0x00,0x7F,0x44,0x44,0x44,0x38},
     {0x00,0x38,0x44,0x44,0x44,0x28},
     {0x00,0x38,0x44,0x44,0x44,0x7F},
     {0x00,0x38,0x54,0x54,0x54,0x08},
     {0x00,0x08,0x7E,0x09,0x09,0x00},
     {0x00,0x18,0xA4,0xA4,0xA4,0x7C},
     {0x00,0x7F,0x04,0x04,0x78,0x00},
     {0x00,0x00,0x00,0x7D,0x40,0x00},
     {0x00,0x40,0x80,0x84,0x7D,0x00},
     {0x00,0x7F,0x10,0x28,0x44,0x00},
     {0x00,0x00,0x00,0x7F,0x40,0x00},
     {0x00,0x7C,0x04,0x18,0x04,0x78},
     {0x00,0x7C,0x04,0x04,0x78,0x00},
     {0x00,0x38,0x44,0x44,0x44,0x38},
     {0x00,0xFC,0x44,0x44,0x44,0x38},
     {0x00,0x38,0x44,0x44,0x44,0xFC},
     {0x00,0x44,0x78,0x44,0x04,0x08},
     {0x00,0x08,0x54,0x54,0x54,0x20},
     {0x00,0x04,0x3E,0x44,0x24,0x00},
     {0x00,0x3C,0x40,0x20,0x7C,0x00},
     {0x00,0x1C,0x20,0x40,0x20,0x1C},
     {0x00,0x3C,0x60,0x30,0x60,0x3C},
     {0x00,0x6C,0x10,0x10,0x6C,0x00},
     {0x00,0x9C,0xA0,0x60,0x3C,0x00},
     {0x00,0x64,0x54,0x54,0x4C,0x00},
     {0x00,0x08,0x3E,0x41,0x41,0x00},
     {0x00,0x00,0x00,0x77,0x00,0x00},
     {0x00,0x00,0x41,0x41,0x3E,0x08},
     {0x00,0x02,0x01,0x02,0x01,0x00},
     {0x00,0x3C,0x26,0x23,0x26,0x3C},
};

// -----------------------
//|Standardized Functions|
// -----------------------

void Graphics_Init(graphics_t * gptr) //Run before using display
{
    // Configure GPIO
    CONFIG_DISP_PORTS_OUT();
    CONFIG_LED_PORTS_OUT();
    //CONFIG_DISP_PORTS_PULLUP();
    SET_RESET_LOW();
    __delay_cycles(240000);   // Delay for 120ms at 2MHz, replace with mulh delay when ready
    SET_RESET_HIGH();
    SET_CS_HIGH();
    SET_A0_HIGH();

    // Initialize Display
    Display_PushCommand(0xA2);  //added 1/9 bias
    Display_PushCommand(0xA0);   //ADC segment driver direction (A0=Normal)
    Display_PushCommand(0xC8);   //added
    Display_PushCommand(0xC0);   //COM output scan direction (C0=Normal)
    Display_PushCommand(0x26);   //resistor ratio
    Display_PushCommand(0x81);   //electronic volume mode set
    Display_PushCommand(0x19);   //electronic volume registerset
    Display_PushCommand(0x2F);   //power control set
    Display_PushCommand(0xAF);   //displayON/OFF - set to ON
    //Display_PushCommand(0xA7);  //displayMode - set to reverse

    // Perform letter boxing
    if(gptr->screen_size == SCREEN_SIZE_320X240) // Scale 320x240 to 128x64
    {
        Graphics_DrawRectangle(gptr,(g_point_t){0,0},(g_point_t){23,63});
        Graphics_DrawRectangle(gptr,(g_point_t){103,0},(g_point_t){127,63});
        Graphics_DrawRectangle(gptr,(g_point_t){24,62},(g_point_t){102,1});
        Graphics_DrawRectangle(gptr,(g_point_t){24,62},(g_point_t){102,63});
    }
    else if(gptr->screen_size == SCREEN_SIZE_160X128) // Scale 160x128 to 128x64
    {
        Graphics_DrawRectangle(gptr,(g_point_t){0,0},(g_point_t){23,63});
        Graphics_DrawRectangle(gptr,(g_point_t){103,0},(g_point_t){127,63});
    }

    Graphics_ClearScreen(gptr);
}

void Graphics_SetInputScreenSize(graphics_t * gptr, enum screen_size_e screen_size)
{
    gptr->screen_size = screen_size;
}

void Graphics_DrawTile(graphics_t * gptr, g_point_t position, g_pixel_t * tile[], char x, char y)
{
    int i,j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if((*(tile[j]+i)).red > 1 || (*(tile[j]+i)).green > 1 || (*(tile[j]+i)).blue > 1)
                Display_SetRAMCord(gptr,position.x + i,position.y + j);
            else if ((*(tile[j]+i)).transparent == 1)
                Display_ClearRAMCord(gptr,position.x + i,position.y + j);
        }
    }
}

void Graphics_SetBackground(graphics_t * gptr, uint8_t color[3])
{
    // Change variable
    memcpy(gptr->background, color, sizeof(gptr->background));

    // Change actual LED
    if(color[0] > 127) // Red check
        SET_R_LOW();
    else
        SET_R_HIGH();
    if(color[1] > 127) // Green check
        SET_G_LOW();
    else
        SET_G_HIGH();
    if(color[2] > 127) // Blue check
        SET_B_LOW();
    else
        SET_B_HIGH();
}

void Graphics_SetForeground(graphics_t * gptr, uint8_t color[3])
{
    // Change variable
    memcpy(gptr->foreground, color, sizeof(gptr->foreground));

    // Change actual LED
}

void Graphics_DrawLine(graphics_t* gptr, g_point_t p1, g_point_t p2)
{
    //Bresenham's line algorithm
    volatile int x0 = p1.x, x1 = p2.x;
    volatile int y0 = p1.y, y1 = p2.y;
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    volatile int err = (dx>dy ? dx : -dy)/2, e2;
    while(1)
    {
        Display_SetRAMCord(gptr,x0,y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void Graphics_DrawPixel(graphics_t * gptr, g_point_t p)
{
    Display_SetRAMCord(gptr,p.x,p.y);
}

void Graphics_DrawRectangle(graphics_t * gptr, g_point_t top_left, g_point_t bottom_right)
{
    //CURRENTLY DOES NOT SUPPORT OFF SCREEN COORDINATES
    int i;
    int XLen = bottom_right.x - top_left.x;
    int YLen = bottom_right.y - top_left.y;

    //Top and bottom
    for(i = 0; i < XLen; i++)
    {
        Display_SetRAMCord(gptr,i+top_left.x,top_left.y);
        Display_SetRAMCord(gptr,i+top_left.x,top_left.y+YLen-1);
    }

    //Left and right
    for(i = 1; i < YLen - 1; i++)
    {
        Display_SetRAMCord(gptr,top_left.x,top_left.y+i);
        Display_SetRAMCord(gptr,top_left.x+XLen-1,top_left.y+i);
    }
}

void Graphics_DrawText(graphics_t * gptr, g_point_t position, char * str, ...)
{
    int xPos = position.x;
    int yPos = position.y;

    buffer_t strBuffer; // print_f buffer
    char formattedStr[20] = {'\0'}; // post format string
    va_list vars; // variable argument list

    // Format string with variables using print_f functions
    va_start(vars, str);
    BufferInit(&strBuffer,formattedStr,20);
    Push_vprintf(&strBuffer,str,vars);
    va_end(vars);

    // Loop through string to draw characters on display
    int i,j,k; // Loop iterators
    int length = strlen(formattedStr);
    for(i = 0; i < length; i++) // Each string character
    {
        char c = formattedStr[i];
        for(j = 0; j < 6; j ++) // Each ascii character's column
        {
            for(k = 0; k < 8; k++) // Each ascii character's column's pixel
            {
                int pixel = (asciiArray[c-32][j]) >> k & 0x01;
                if(pixel == 1)
                    Display_SetRAMCord(gptr,xPos+j+(i*6),yPos+k);
                else
                    Display_ClearRAMCord(gptr,xPos+j+(i*6),yPos+k);
            }
        }
    }
}

void Graphics_ClearScreen(graphics_t * gptr)
{
    memset(gptr->hal.DisplayRAM, 0, sizeof(gptr->hal.DisplayRAM[0][0]) * 128 * 64);
    Graphics_UpdateScreen(gptr);
}

void Graphics_UpdateScreen(graphics_t * gptr)
{
    int i,j;
    for(j = 0; j < 8; j++) //Number of screen pages
    {
        Display_PushCommand(0xB0 + (7-j)); //Set page (Pages are opposite on display so reverse page number command)
        Display_PushCommand(0x10); //First column MSB
        Display_PushCommand(0x00); //First column LSB
        for(i = 0; i < 128; i++) //Number of screen columns
        {
            Display_PushData(gptr->hal.DisplayRAM[i][j]); //Push data
        }
    }
}

// -----------------------------------------------------------
//|                     Unique Functions                     |
// -----------------------------------------------------------

void Display_PushCommand(char command)  //Command out for LCD
{
  int i;
  SET_CS_LOW();
  SET_A0_LOW();
  for(i=0;i<8;i++)
  {
    if((command & 0x80) == 0x80) //Checks if first bit is a 1
    {
      SET_SI_HIGH();
      SET_SLK_LOW();
      SET_SLK_HIGH();
    }
    else
    {
      SET_SI_LOW();
      SET_SLK_LOW();
      SET_SLK_HIGH();
    }
    command = command<<1;
  }
  SET_CS_HIGH();
  SET_A0_HIGH();
}

void Display_PushData(unsigned char data) //Data out for LCD
{
  int i;
  SET_CS_LOW();
  for(i=0;i<8;i++)
  {
    if((data & 0x80) == 0x80) // Checks to see if first bit is a 1
    {
      SET_SI_HIGH();
      SET_SLK_LOW();
      SET_SLK_HIGH();
    }
    else
    {
      SET_SI_LOW();
      SET_SLK_LOW();
      SET_SLK_HIGH();
    }
    data = data<<1;
  }
  SET_CS_HIGH();
}

void Display_SetRAMCord(graphics_t * gptr, int X, int Y)
{
    g_point_t scaledCord = Display_ScaleCord(gptr,X,Y);

    unsigned int Page = scaledCord.y >> 3;
    unsigned int Pixel = scaledCord.y - (Page << 3);
    gptr->hal.DisplayRAM[scaledCord.x][Page] = gptr->hal.DisplayRAM[scaledCord.x][Page] | (128 >> Pixel);
}

void Display_ClearRAMCord(graphics_t * gptr, int X, int Y)
{
    g_point_t scaledCord = Display_ScaleCord(gptr,X,Y);

    unsigned int Page = scaledCord.x >> 3;
    unsigned int Pixel = scaledCord.y - (Page << 3);
    gptr->hal.DisplayRAM[scaledCord.x][Page] = gptr->hal.DisplayRAM[scaledCord.x][Page] & ~(128 >> Pixel);
}

g_point_t Display_ScaleCord(graphics_t * gptr, int preX, int preY)
{
    g_point_t scaledPoint;

    if(gptr->screen_size == SCREEN_SIZE_128X64) // Native screen size
    {
        scaledPoint.x = preX;
        scaledPoint.y = preY;
    }
    else if(gptr->screen_size == SCREEN_SIZE_320X240) // Scale 320x240 to 128x64
    {
        scaledPoint.x = (preX << 2) + 24; // 1/4size, centered
        scaledPoint.y = (preY << 2) + 2; // 1/4 size, centered
    }
    else // Scale 160x128 to 128x64
    {
        scaledPoint.x = (preX << 1) + 24; // 1/2 size, centered
        scaledPoint.y = preY << 1; // 1/2 size, centered
    }

    return scaledPoint;
}



