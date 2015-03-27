//クロック 20MHz
#define F_CPU 20000000


//インクルード
#include <avr/io.h>
#include <util/delay.h>
//#include "clcd.h"
#include "glcd.h"

//エントリーポイント
int main (void)
{
	uint8_t i;
	glcd_init ();
		glcd_page (1);
		glcd_position (8);
	for (i = 0; i < 10; i++)
		glcd_draw (0xf0);
	while (1)
	{
	}



	/*clcd_init (MODE_8BIT | USE_2LINE | DOT_5X8, CDISPLAY_ON | CURSOR_ON | BLINK_ON, AC_INC | COS_OFF);
	while (1)
	{
		clcd_position (LINE1 | 1);
		clcd_str ("abcdefg");
		_delay_ms (500);
	}*/
	return 0;
}
