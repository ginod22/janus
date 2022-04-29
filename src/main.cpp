#include "mbed.h"
#include "Motor.h"
#include "uLCD_4DGL.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

Motor RM(p21, p6, p5); // pwm, fwd, rev - RIGHT MOTOR
Motor LM(p22, p7, p8); // pwm, fwd, rev - LEFT MOTOR
PwmOut speaker(p23);
Serial ble(p13, p14); // tx, rx
uLCD_4DGL uLCD(p28, p27, p29); // tx, rx, reset

class microphone
{
public :
    microphone(PinName pin);
    float read();
    operator float ();
private :
    AnalogIn _pin;
};
microphone::microphone (PinName pin):
    _pin(pin)
{
}
float microphone::read()
{
    return _pin.read();
}
inline microphone::operator float ()
{
    return _pin.read();
}
microphone mymicrophone(p16);



volatile char c = '0';
volatile char hit = '0';
volatile unsigned int volume = 0;
volatile unsigned int moving = 0;
volatile unsigned int mic = 0;


void Microphone()
{
    int previous = 0;
    int count = 0;
    int voice = 0;
    int threshold = 0;
    int current = 0;
    volume = 0;

    while (count < 16000) {
        voice = int(abs((mymicrophone - (0.67/3.3)))*500.0);
        wait(1.0/8000.0);
        count = count+1;
    }
    previous = voice;
    threshold = voice + 15;
    led2 = 1;
    led3 = 1;
    count = 0;
    while (((int(voice) < threshold) || (previous >= (current-2))) && (count < 40000)) {
        voice = int(abs((mymicrophone - (0.67/3.3)))*500.0);
        wait(1.0/8000.0);
        current = voice;
        count = count + 1;
        if (current < previous) previous = current;
    }
    if(count>=40000) {
        volume = 0;
    } else {
        volume = 1;
    }
    led2 = 0;
    led3 = 0;
    mic = 1;
}



int main()
{
    speaker.period(1.0/800.0);
    uLCD.text_height(2);
    uLCD.text_width(2);
    uLCD.color(BLUE);
    uLCD.printf("Dashboard");
    uLCD.locate(1,2);
    uLCD.color(GREEN);
    uLCD.printf("PARK");
    uLCD.color(RED);
    uLCD.locate(1,4);
    uLCD.printf("REVERSE");
    uLCD.locate(1,6);
    uLCD.printf("DRIVE");
    while(1) {
        if(ble.getc() == '!') {
            if(ble.getc() == 'B') {
                c = ble.getc();
                hit = ble.getc();
                if(ble.getc() == char(~('!' + 'B' + c + hit))) {
                    switch(c) {
                        case '1': // Button 1 - Honks
                            if (hit == '1') {
                                speaker = 0.5;
                                moving = 5;

                            } else {
                                speaker = 0.0;
                                moving = 0;
                            }
                            break;
                        case '2':
                            if(hit == '1') {
                                LM.speed(1.0);
                                RM.speed(-1.0);
                                moving = 6;
                            } else {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                            }
                            break;
                        case '3': // Button 3 - voice controlled forward mvmt
//                            pc.printf("hit: %c mic: %d", hit, mic);
                            if ((hit == '1') && (mic == 0))
                                Microphone();
                            if ((volume == 1) && (hit == '1')) {
                                LM.speed(1.0);
                                RM.speed(1.0);
                                moving = 1;
                            } else if ((volume == 0) && (hit == '1')) {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                                volume = 0;
                            } else if (hit == '0') {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                                volume = 0;
                                mic = 0;
                            }
                            break;
                        case '4': // Button 4 - voice controlled backward mvmt
                            if ((hit == '1') && (mic == 0))
                                Microphone();
                            if ((volume == 1) && (hit == '1')) {
                                LM.speed(-1.0);
                                RM.speed(-1.0);
                                moving = 3;
                            } else if ((volume == 0) && (hit == '1')) {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                                volume = 0;
                            } else if (hit == '0') {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                                volume = 0;
                                mic = 0;
                            }
                            break;
                        case '5': // UP Arrow
                            if(hit == '1') {
                                LM.speed(1.0);
                                RM.speed(1.0);
                                moving = 1;
                            } else {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                            }
                            break;
                        case '6': // DOWN Arrow
                            if(hit == '1') {
                                LM.speed(-1.0);
                                RM.speed(-1.0);
                                moving = 3;
                            } else {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                            }
                            break;
                        case '7': // LEFT Arrow
                            if(hit == '1') {
                                LM.speed(0.0);
                                RM.speed(1.0);
                                moving = 4;
                            } else {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                            }
                            break;
                        case '8': // RIGHT Arrow
                            if(hit == '1') {
                                LM.speed(1.0);
                                RM.speed(0.0);
                                moving = 2;
                            } else {
                                LM.speed(0.0);
                                RM.speed(0.0);
                                moving = 0;
                            }
                            break;

                    }
                }
            }
        }
        switch(moving) {
            case 0:
                led1 = 0;
                led4 = 0;
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(1,2);
                uLCD.printf("PARK");

                uLCD.color(RED);
                uLCD.locate(1,4);
                uLCD.printf("REVERSE");
                uLCD.locate(1,6);
                uLCD.printf("DRIVE");
                break;
            case 1:
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(1,6);
                uLCD.printf("DRIVE");

                uLCD.color(RED);
                uLCD.locate(1,2);
                uLCD.printf("PARK");
                uLCD.locate(1,4);
                uLCD.printf("REVERSE");
                break;
            case 2:
                led1 = 1;
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(1,6);
                uLCD.printf("DRIVE");

                uLCD.color(RED);
                uLCD.locate(1,2);
                uLCD.printf("PARK");
                uLCD.locate(1,4);
                uLCD.printf("REVERSE");
                break;
            case 3:
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(1,4);
                uLCD.printf("REVERSE");

                uLCD.color(RED);
                uLCD.locate(1,2);
                uLCD.printf("PARK");
                uLCD.locate(1,6);
                uLCD.printf("DRIVE");
                break;
            case 4:
                led4 = 1;
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(1,6);
                uLCD.printf("DRIVE");

                uLCD.color(RED);
                uLCD.locate(1,2);
                uLCD.printf("PARK");
                uLCD.locate(1,4);
                uLCD.printf("REVERSE");
                break;
            case 5:
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(2,4);
                uLCD.printf("HONK!");
                break;
            case 6:
                uLCD.cls();
                uLCD.text_height(2);
                uLCD.text_width(2);
                uLCD.color(BLUE);
                uLCD.printf("Dashboard");
                uLCD.color(GREEN);
                uLCD.locate(2,4);
                uLCD.printf("SPIN!");
                break;

        }

    }
}
