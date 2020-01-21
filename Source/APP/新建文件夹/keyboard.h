#ifndef _KEYBORD_H
#define _KEYBORD_H

#define KEY_PORT	LPC_GPIO1
#define KEY_ESC_PWR	0
#define KEY_ENTER	1
#define KEY_LEFT	2
#define KEY_RIGHT	3
#define KEY_DOWN	4
#define KEY_UP		5

#define POWER_ON	1
#define POWER_OFF	0

void KeyBoardINTInit (void);
void KeyBacklightSW (int pwr_on);


#endif

