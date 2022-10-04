#ifndef HX711_H_
#define HX711_H_

#include <stdio.h>
#include "pico/stdlib.h"

static const uint pin_dout = 4;
static const uint pin_slk = 5;
static float offset = 0;

void initHx711();

long averageValue();

long getValue();


float getGram(float offset, float scale);

void bitWrite(char *x, char n, char value);

void blink();


#endif /* HX711_H_ */