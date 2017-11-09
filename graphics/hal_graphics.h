#ifndef _HAL_GRAPHICS_H_
#define _HAL_GRAPHICS_H_

// Display Connections Needed:
//----------------------------
//SLK - Serial Clock
//SI - Serial Input
//A0 - Read/Write Select
//RESET - Reset
//CS - Chip Select
//R - Backlight Red
//G - Backlight Green
//B - Backlight Blue

// Port Macro Functions (Modify these to change ports for a specific processor)
// --------------------
#define SET_SLK_HIGH() (P6OUT |= BIT3) // P6.3
#define SET_SLK_LOW()  (P6OUT &= ~(BIT3)) // ~P6.3
#define SET_SI_HIGH() (P6OUT |= BIT4) //P6.4
#define SET_SI_LOW() (P6OUT &= ~(BIT4)) //~P6.4
#define SET_A0_HIGH() (P6OUT |= BIT0) //P6.0
#define SET_A0_LOW() (P6OUT &= ~(BIT0)) //~P6.0
#define SET_RESET_HIGH() (P6OUT |= BIT1) //P6.1
#define SET_RESET_LOW() (P6OUT &= ~(BIT1)) //~P6.1
#define SET_CS_HIGH() (P6OUT |= BIT2) //P6.2
#define SET_CS_LOW() (P6OUT &= ~(BIT2)) //~P6.2
#define SET_R_HIGH() (P4OUT |= BIT0) //P4.0
#define SET_R_LOW() (P4OUT &= ~(BIT0)) //~P4.0
#define SET_G_HIGH() (P4OUT |= BIT1) //P4.1
#define SET_G_LOW() (P4OUT &= ~(BIT1)) //~P4.1
#define SET_B_HIGH() (P4OUT |= BIT2) //P4.2
#define SET_B_LOW() (P4OUT &= ~(BIT2)) //~P4.2
#define CONFIG_DISP_PORTS_OUT() (P6DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4) // Set SI, SCLK, A0, RESET, and CS to output
#define CONFIG_DISP_PORTS_PULLUP() (P6REN |= BIT1 + BIT1 + BIT2 + BIT3 + BIT4) // Set SI, SCLK, A0, RESET, and CS to pull-up
#define CONFIG_LED_PORTS_OUT() (P4DIR |= BIT0 + BIT1 + BIT2) // Set R, G, and B to output
//#define CONFIG_LED_PORTS_PULLDOWN()

//HAL Structure
typedef struct {
    unsigned char DisplayRAM[128][8]; //128 columns by 8 pages (8 pixels per page)
} hal_graphics_t;

//Display Pixel Grid


#endif //hal_graphics.h
