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

#define DPAD_UNPRESSED  0b0000000000001111

extern uint16_t ctrl1;
uint8_t *ctrl1_ready = (uint8_t *) (&ctrl1) + 0x02;
extern uint16_t ctrl2;
uint8_t *ctrl2_ready = (uint8_t *) (&ctrl2) + 0x02;
#pragma zpsym("ctrl1")
#pragma zpsym("ctrl2")

/* initializes the VIA for connecting 2 (S)NES controllers on Port A*/
extern void ctrl_init();

/* reads 2 bytes of (S)NES controller 1 button press state*/
extern void read_ctrl1();

/* reads 2 bytes of (S)NES controller 2 button press state*/
extern void read_ctrl2();

/* reads 2 bytes of 2 (S)NES controllers button press state**/
extern void read_ctrls();

/* reads 1 bytes of NES controller 1 button press state*/
extern void read_nes_ctrl1();

/* reads 1 bytes of NES controller 2 button press state*/
extern void read_nes_ctrl2();

/* reads 1 bytes from 2 NES controllers button press state**/
extern void read_nes_ctrls();

/* reads 3 bytes from 2 (S)NES controllers on VIA Port A and stores connection information and button state*/
extern void read_controllers();

/* spin CPU for short delay*/
extern void delay();
