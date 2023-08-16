#define IS_SNES         0b0000000100000000
#define NA1_UNPRESSED   0b0000001000000000
#define NA2_UNPRESSED   0b0000010000000000
#define NA3_UNPRESSED   0b0000100000000000
#define R_UNPRESSED     0b0001000000000000
#define L_UNPRESSED     0b0010000000000000
#define X_UNPRESSED     0b0100000000000000
#define A_UNPRESSED     0b1000000000000000

#define RT_UNPRESSED    0b0000000000000001
#define LT_UNPRESSED    0b0000000000000010
#define DN_UNPRESSED    0b0000000000000100
#define UP_UNPRESSED    0b0000000000001000
#define STA_UNPRESSED   0b0000000000010000
#define SEL_UNPRESSED   0b0000000000100000
#define Y_UNPRESSED     0b0000000001000000
#define B_UNPRESSED     0b0000000010000000
// #define IS_SNES         0b00000001
// #define NA1_UNPRESSED   0b00000010
// #define NA2_UNPRESSED   0b00000100
// #define NA3_UNPRESSED   0b00001000
// #define R_UNPRESSED     0b00010000
// #define L_UNPRESSED     0b00100000
// #define X_UNPRESSED     0b01000000
// #define A_UNPRESSED     0b10000000
// #define RT_UNPRESSED    0b00000001
// #define LT_UNPRESSED    0b00000010
// #define DN_UNPRESSED    0b00000100
// #define UP_UNPRESSED    0b00001000
// #define STA_UNPRESSED   0b00010000
// #define SEL_UNPRESSED   0b00100000
// #define Y_UNPRESSED     0b01000000
// #define B_UNPRESSED     0b10000000

extern uint16_t ctrl1;
uint8_t *ctrl1_ready = (uint8_t *) (&ctrl1) + 0x02;
extern uint16_t ctrl2;
uint8_t *ctrl2_ready = (uint8_t *) (&ctrl2) + 0x02;
#pragma zpsym("ctrl1")
// #pragma zpsym("ctrl1_ready")
#pragma zpsym("ctrl2")
// #pragma zpsym("ctrl2_ready")

/* initializes the VIA for connecting 2 (S)NES controllers on Port A*/
extern void ctrl_init();

// /* returns true if controller 1 is connected*/
// extern uint8_t ctrl1_ready();
// /* returns true if controller 2 is connected*/
// extern uint8_t ctrl2_ready();
// /* returns true if controller 1 is SNES*/
// extern uint8_t ctrl1_is_snes();
// /* returns true if controller 2 is SNES*/
// extern uint8_t ctrl2_is_snes();
// /* returns 1 byte of controller 1 button press data*/
// extern uint8_t read_ctrl1_nes();

/* reads 2 bytes of controller 1 button press data*/
extern void read_ctrl1();

/* reads 2 bytes of controller 2 button press data*/
extern void read_ctrl2();

/* reads 2 bytes from 2 (S)NES controllers on VIA Port A and stores connection information and button state**/
extern void read_ctrls();

/* reads 1 bytes of controller 1 button press data*/
extern void read_nes_ctrl1();

/* reads 1 bytes of controller 2 button press data*/
extern void read_nes_ctrl2();

/* reads 1 bytes from 2 (S)NES controllers on VIA Port A and stores connection information and button state**/
extern void read_nes_ctrls();

/* reads 3 bytes from 2 (S)NES controllers on VIA Port A and stores connection information and button state*/
extern void read_controllers();

/* spin CPU for short delay*/
extern void delay();
