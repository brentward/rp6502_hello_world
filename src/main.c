#include <rp6502.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "controllers.h"

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

void draw()
{
	uint16_t i = 0;
	xreg(2, 0, 1);
    RIA_ADDR0 = 0;
    RIA_STEP0 = 1;
    for (i = 0x1300; --i;)
    {
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
    }
	// wait();
}

void main()
{
	int16_t px, py;
    int8_t vbyte;

	// uint8_t ctrl1_attached = 0;
	// uint8_t ctrl2_attached = 0;
	puts("Hello, people! SNES controller draw!");
	wait();
	ctrl_init();
	draw();
	// read_controllers();
	px = 10;
	py = 10;
	vbyte = 2;
    RIA_STEP0 = 1;

	while (1)
	{
		read_controllers();


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

		// if (!(ctrl1 & A_UNPRESSED))
		// {
		// 	puts("Controller 1 A Pressed");
		// }
		if (!(ctrl1 & B_UNPRESSED))
		{
			vbyte += 1;
			// puts("Controller 1 B Pressed");
		}
		// if (!(ctrl1 & X_UNPRESSED))
		// {
		// 	puts("Controller 1 X Pressed");
		// }

		if (!(ctrl1 & Y_UNPRESSED))
		{
			vbyte -= 1;
			// puts("Controller 1 Y Pressed");
		}

		// if (!(ctrl1 & STA_UNPRESSED))
		// {
		// 	puts("Controller 1 Start Pressed");
		// }

		// if (!(ctrl1 & SEL_UNPRESSED))
		// {
		// 	puts("Controller 1 Select Pressed");
		// }

		if (!(ctrl1 & UP_UNPRESSED))
		{
			py -= 1;		

			// puts("Controller 1 Up Pressed");
		}

		if (!(ctrl1 & DN_UNPRESSED))
		{
			py += 1;
			// puts("Controller 1 Down Pressed");
		}

		if (!(ctrl1 & LT_UNPRESSED))
		{
			px -= 1;
			// puts("Controller 1 Left Pressed");
		}

		if (!(ctrl1 & RT_UNPRESSED))
		{
			px += 1;
			// puts("Controller 1 Right Pressed");
		}
		RIA_ADDR0 = (py * 320) + px;
		RIA_RW0 = vbyte;


		// if (!(ctrl1 & L_UNPRESSED))
		// {
		// 	puts("Controller 1 L Pressed");
		// }

		// if (!(ctrl1 & R_UNPRESSED))
		// {
		// 	puts("Controller 1 R Pressed");
		// }
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

		delay();

	}
}
