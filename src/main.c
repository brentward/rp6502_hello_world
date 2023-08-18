#include <rp6502.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "controllers.h"

#define BLACK  0
#define RED  1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7
#define GREY 8

#define COLOR_MASK 0b1111

#define WIDTH 320
#define HEIGHT 240 // 180 or 240

static void wait()
{
    uint8_t discard;
    discard = RIA_RX;
    while (RIA_RX_READY)
        discard = RIA_RX;
    while (!(RIA_RX_READY))
        ;
    discard = RIA_RX;
}

static void vmode(uint16_t data)
{
    xreg(data, 0, 1);
}


void clear(uint8_t bgnd_color)
{
	uint16_t i = 0;
	uint8_t vbyte;
	vbyte = (bgnd_color << 4) | bgnd_color;
    RIA_ADDR0 = 0;
    RIA_STEP0 = 1;
	
    // for (i = 0x1300; --i;)
    // {
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    //     RIA_RW0 = 255;
    // }
    // RIA_ADDR0 = 0;
    for (i = 0x1300; --i;)
    {
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
        RIA_RW0 = vbyte;
    }
    RIA_ADDR0 = 0;}

void main()
{
	int16_t px = 0, py =0 ;
    int8_t vbyte = RED;
	int8_t bgnd_vbyte = BLACK;
	int8_t last_color = BLACK;
	uint16_t last_ctrl1 = 0xFFFF;
	// uint8_t ctrl1_attached = 0;
	// uint8_t ctrl2_attached = 0;

	puts("Hello, people! SNES controller draw!");
	wait();
	ctrl_init();
	#if (HEIGHT == 180)
		vmode(2);
	#else
		vmode(1);
	#endif
	clear(bgnd_vbyte);
	RIA_STEP0 = 0;
	while (1)
	{
		read_controllers();
		
		if (((ctrl1 & ~DN_UNPRESSED) != DPAD_UNPRESSED) && !(ctrl1 & L_UNPRESSED))
		{
			RIA_ADDR0 = (px / 2) + (py * (WIDTH / 2));
			RIA_RW0 &= ~(COLOR_MASK << ((px % 2) * 4));
			RIA_RW0 |= (last_color << ((px % 2) * 4));
		}
		// if (ctrl1_attached == !(*ctrl1_ready == 0))
		// {
		// 	ctrl1_attached = !ctrl1_attached;
		// 	printf("Controller 1 attached: %d\n", ctrl1_attached);
		// }
		// if (ctrl2_attached == !(*ctrl2_ready == 0))
		// {
		// 	ctrl2_attached = !ctrl2_attached;
		// 	printf("Controller 2 attached: %d\n", ctrl2_attached);
		// }

		if (!(ctrl1 & A_UNPRESSED))
		{
			if (vbyte < GREY)
			{
				vbyte += 1;
			} else {
				vbyte = BLACK;
			}
		}
		if (((last_ctrl1 & B_UNPRESSED) != ((ctrl1 & B_UNPRESSED))) && !(ctrl1 & B_UNPRESSED))
		{
			if (vbyte < GREY)
			{
				vbyte += 1;
			} else {
				vbyte = BLACK;
			}
		}

		if (!(ctrl1 & X_UNPRESSED))
		{
			if (vbyte > BLACK)
			{
				vbyte -= 1;
			} else {
				vbyte = GREY;
			}
		}

		if (((last_ctrl1 & Y_UNPRESSED) != ((ctrl1 & Y_UNPRESSED))) && !(ctrl1 & Y_UNPRESSED))
		{
			if (vbyte > BLACK)
			{
				vbyte -= 1;
			} else {
				vbyte = GREY;
			}
		}

		if (((last_ctrl1 & SEL_UNPRESSED) != ((ctrl1 & SEL_UNPRESSED))) && !(ctrl1 & SEL_UNPRESSED))
		{
			bgnd_vbyte = vbyte;
		}

		if (!(ctrl1 & UP_UNPRESSED))
		{
			py -= 1;
		}

		if (!(ctrl1 & DN_UNPRESSED))
		{
			py += 1;
		}

		if (!(ctrl1 & LT_UNPRESSED))
		{
			px -= 1;
		}

		if (!(ctrl1 & RT_UNPRESSED))
		{
			px += 1;
		}

		if (py < 0)
		{
			py += HEIGHT;
			px -= 1;
		}
		if (py > HEIGHT - 1)
		{
			py -= HEIGHT;
			px += 1;
		}
		if (px < 0)
		{
			px += WIDTH;
			py -= 1;
		}
		if (px > WIDTH - 1)
		{
			px -= WIDTH;
			py +=1;
		}

		if (((last_ctrl1 & STA_UNPRESSED) != ((ctrl1 & STA_UNPRESSED))) && !(ctrl1 & STA_UNPRESSED))
		{
			clear(bgnd_vbyte);
			RIA_STEP0 = 0;
		} else {
			RIA_ADDR0 = (px / 2) + (py * (WIDTH / 2));
			last_color = (RIA_RW0 >> ((px % 2) * 4)) & COLOR_MASK;
			RIA_RW0 &= ~(COLOR_MASK << ((px % 2) * 4));
			RIA_RW0 |= (vbyte << ((px % 2) * 4));
		}



		// if (!(ctrl2 & A_UNPRESSED))
		// {
		// 	puts("Controller 2 A Pressed");
		// }
		// if (!(ctrl2 & B_UNPRESSED))
		// {
		// 	puts("Controller 2 B Pressed");
		// }
		// if (!(ctrl2 & X_UNPRESSED))
		// {
		// 	puts("Controller 2 X Pressed");
		// }

		// if (!(ctrl2 & Y_UNPRESSED))
		// {
		// 	puts("Controller 2 Y Pressed");
		// }

		// if (!(ctrl2 & STA_UNPRESSED))
		// {
		// 	puts("Controller 2 Start Pressed");
		// }

		// if (!(ctrl2 & SEL_UNPRESSED))
		// {
		// 	puts("Controller 2 Select Pressed");
		// }

		// if (!(ctrl2 & UP_UNPRESSED))
		// {
		// 	puts("Controller 2 Up Pressed");
		// }

		// if (!(ctrl2 & DN_UNPRESSED))
		// {
		// 	puts("Controller 2 Down Pressed");
		// }

		// if (!(ctrl2 & LT_UNPRESSED))
		// {
		// 	puts("Controller 2 Left Pressed");
		// }

		// if (!(ctrl2 & RT_UNPRESSED))
		// {
		// 	puts("Controller 2 Right Pressed");
		// }

		// if (!(ctrl2 & L_UNPRESSED))
		// {
		// 	puts("Controller 2 L Pressed");
		// }

		// if (!(ctrl2 & R_UNPRESSED))
		// {
		// 	puts("Controller 2 R Pressed");
		// }
		if (ctrl1 & R_UNPRESSED)
		{
			delay();
		}
		last_ctrl1 = ctrl1;
	}
}
