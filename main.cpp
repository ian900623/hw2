#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

DigitalIn pin_up(D5);
DigitalIn pin_down(D3);
DigitalIn pin_sel(D10);
AnalogOut sig(PA_4);
AnalogIn cat(PC_5);

int main()
{
    int while_add = 0;
    int freq = 360;
    float T = 1000 / freq;
    int j = 1;
    float i = 0.0f;
    float ADCdata[500];
    char store = 0;

    uLCD.printf("\nPlease Select the Frequency\n");
    uLCD.color(RED);
    uLCD.locate(0, 6);
    uLCD.printf("%5d Hz", freq);

    while(1) {
        if (pin_up == 1) {
            freq += 20;
            uLCD.locate(0, 6);
            uLCD.printf("%5d Hz", freq);
        }
        if (pin_down == 1) {
            freq -= 20;
            uLCD.locate(0, 6);
            uLCD.printf("%5d Hz", freq);
        }
        if (pin_sel == 1) {
            uLCD.locate(0, 6);
            uLCD.printf("\nConfirm your Frequency.");
            T = 1000.0 / freq;
            store = 1;
        }
        if (i <= 30) sig = i / 30.0f / 1.1f;
        if (i > 30) sig = (100 - i) / 70.0f / 1.1f;
        if (i > 100) i = 0.0f;
        wait_us(T * 10 - 13);
        
        if (store == 1) {
            while_add++;
            if (j == 500) {
               for(int k = 0; k < 500; k++) {
                    printf("%lf\r\n", ADCdata[k]);
                }
                j = 1;
                store = 0;
                while_add = 0;
            }  
            else if (while_add % (100 * freq / 500) == 0) {
               ADCdata[j - 1] = cat;
               j++;
            }         
        }
        i++;
    }
}