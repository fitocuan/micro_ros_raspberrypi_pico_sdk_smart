/*
 * Hx711.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: agu
 */

#include "hx711.h"
#include <stdio.h>

#include "pico/stdlib.h"

void blink(){
	printf("Blinking!\r\n");
	gpio_put(25, true);
	sleep_ms(1000);
	gpio_put(25, false);
	sleep_ms(1000);
}

void initHx711(){

    gpio_init(pin_dout);
    gpio_init(pin_slk);
    gpio_set_dir(pin_dout, GPIO_IN);
    gpio_set_dir(pin_slk, GPIO_OUT);

    gpio_put(pin_slk, true);
    sleep_us(100);
    gpio_put(pin_slk, false);

	printf("Load Cell Init!\r\n");

}

long averageValue()
{

	long sum = 0;
	long c = 0;
	long curr_val = 0;
	for (unsigned char i = 0; i < 2; i++)
	{

		curr_val = getValue();
		if(curr_val> 0 && curr_val != 8388607){
			sum += curr_val;
			c += 1;
		}
		
	}

	return sum / c;
}

void bitWrite(char *x, char n, char value) {
   if (value)
      *x |= (1 << n);
   else
      *x &= ~(1 << n);
}


long getValue()
{
	char data[3] = {0,0,0};

	while (gpio_get(pin_dout))
		;

	for ( char j = 3; j--;)
	{
		for ( char i = 8; i--;)
		{
			gpio_put(pin_slk, true);
			sleep_us(1);
			gpio_put(pin_slk, false);

            char value = gpio_get(pin_dout) ? 1 : 0;

			bitWrite(data + j, i, value);

		} 
	}

	gpio_put(pin_slk, true);
    gpio_put(pin_slk, false);

	data[2] ^= 0x80;

	return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8)
			| (uint32_t) data[0];
}


float getGram(float offset, float scale)
{
	float val = (averageValue() - offset);

	if(val>0.0){
		return (float) val / scale;
	}else{
		return 0;
	}
	
}



