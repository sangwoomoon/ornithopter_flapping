#include <avr₩interrupt.h>
#include <avr₩io.h>

volatile long int CH1_in_width = 0;
volatile long int CH3_in_width = 0;
volatile long int CH4_in_width = 0;
volatile long int CH5_in_width = 0;
volatile long int Servo1R_out_width = 0x0566;
volatile long int Servo1L_out_width = 0x0566;
volatile long int Servo2R_out_width = 0x0566;
volatile long int Servo2L_out_width = 0x0566;
volatile long int Servo3_out_width = 0x0566;
volatile long int Servo4R_out_width = 0x0566;
volatile long int Servo4L_out_width = 0x0566;
volatile long int Servo6_out_width = 0x0566;
volatile int j = 0;
volatile int out = 0;
volatile int step = 0;
volatile int period = 0;
volatile int period2 = 0;
volatile int period3 = 0;
volatile int down = 1;
volatile int down2 = 1;
volatile int now_in_flapping = 0;
volatile int step_size = 0;
volatile int flight_mode = 1;



#ifndef outp
 #define outp(data, addr) addr = (data)
#endif
#ifndef inp
 #define inp(addr) (addr)
#endif
#ifndef BV
 #define BV(bit) (1<<(bit))
#endif
#ifndef cbi
 #define cbi(reg,bit) reg &= ~(BV(bit))
#endif
#ifndef sbi
 #define sbi(reg,bit) reg |= (BV(bit))
#endif


SIGNAL(SIG_OVERFLOW1)
{
    if(flight_mode){
        if(now_in_flapping==0){
            if(CH3_in_width<1005){
                period = 18;
                period2 = 9;
                period3 = 9;
                step_size = 26;
                Servo2R_out_width = 1382;
                Servo2L_out_width = 1382;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1089){
                period = 15;
                period2 = 8;
                period3 = 7;
                step_size = 31;
                Servo2R_out_width = 1397;
                Servo2L_out_width = 1367;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1173){
                period = 13;
                period2 = 7;
                period3 = 6;
                step_size = 36;
                Servo2R_out_width = 1400;
                Servo2L_out_width = 1364;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1257){
                period = 11;
                period2 = 6;
                period3 = 5;
                step_size = 41;
                Servo2R_out_width = 1402;
                Servo2L_out_width = 1362;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1341){
                period = 10;
                period2 = 5;
                period3 = 5;
                step_size = 46;
                Servo2R_out_width = 1382;
                Servo2L_out_width = 1382;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1425){
                period = 9;
                period2 = 5;
                period3 = 4;
                step_size = 51;
                Servo2R_out_width = 1407;
                Servo2L_out_width = 1357;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1551){
                period = 8;
                period2 = 4;
                period3 = 4;
                step_size = 57;
                Servo2R_out_width = 1382;
                Servo2L_out_width = 1382;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1697){
                period = 7;
                period2 = 4;
                period3 = 3;
                step_size = 66;
                Servo2R_out_width = 1415;
                Servo2L_out_width = 1349;
                Servo3_out_width = 1382;
            }
            else if(CH3_in_width<1844){
                period = 6;
                period2 = 3;
                period3 = 3;
                step_size = 77;
                Servo2R_out_width = 1382;
                Servo2L_out_width = 1382;
                Servo3_out_width = 1382;
            }
            now_in_flapping = 1;
            Servo1R_out_width = 1151;
            Servo1L_out_width = 1613;
            step = 0;
        }
        if(now_in_flapping){
            if(down){
                Servo1R_out_width += step_size;
                Servo1L_out_width -= step_size;
                step++;
            }
            else{
                Servo1R_out_width -= step_size;
                Servo1L_out_width += step_size;
                step--;
            }
            if(down2){
                Servo3_out_width -= (step_size>>3);
                Servo2R_out_width -= step_size;
                Servo2L_out_width += step_size;
            }
            else{
                Servo3_out_width += (step_size>>3);
                Servo2R_out_width += step_size;
                Servo2L_out_width -= step_size;
            }
            if((step==period2) & (down2 == 1)) down2 = 0;
            else if((step==period3) & (down2 == 0)) down2 = 1;
            if(step==period) down = 0;
            if(step==0){
                now_in_flapping = 0;
                down = 1;
            }
        }
    }
    else{
        Servo3_out_width = (CH3_in_width>>4)+1296;
        Servo1R_out_width = (CH1_in_width>>1)+691;
        Servo1L_out_width = (CH1_in_width>>1)+691;
        Servo2R_out_width = 0x0566;
        Servo2L_out_width = 0x0566;
    }
    if(Servo1R_out_width>=0x07EB) Servo1R_out_width=0x0566;
    if(Servo1L_out_width>=0x07EB) Servo1L_out_width=0x0566;
    if(Servo2R_out_width>=0x07EB) Servo2R_out_width=0x0566;
    if(Servo2L_out_width>=0x07EB) Servo2L_out_width=0x0566;
    if(Servo3_out_width>=0x07EB) Servo3_out_width=0x0566;
    if(Servo4R_out_width>=0x07EB) Servo4R_out_width=0x0566;
    if(Servo4L_out_width>=0x07EB) Servo4L_out_width=0x0566;
    if(Servo6_out_width>=0x07EB) Servo6_out_width=0x0566;
    if(Servo1R_out_width<=0x02E1) Servo1R_out_width=0x0566;
    if(Servo1L_out_width<=0x02E1) Servo1L_out_width=0x0566;
    if(Servo2R_out_width<=0x02E1) Servo2R_out_width=0x0566;
    if(Servo2L_out_width<=0x02E1) Servo2L_out_width=0x0566;
    if(Servo3_out_width<=0x02E1) Servo3_out_width=0x0566;
    if(Servo4R_out_width<=0x02E1) Servo4R_out_width=0x0566;
    if(Servo4L_out_width<=0x02E1) Servo4L_out_width=0x0566;
    if(Servo6_out_width<=0x02E1) Servo6_out_width=0x0566;
    
    outp(0xFF, PORTC);
    out = 1;
    TCNT1H = 0xB0;
    TCNT1L = 0x00;
}
SIGNAL(SIG_INTERRUPT0)
{
    if((PIND&0x04)==0){
        CH1_in_width = TCNT1-CH1_in_width;
        j=1;
    }
    else CH1_in_width = TCNT1;
}
SIGNAL(SIG_INTERRUPT2)
{
    CH3_in_width = TCNT1;
    if(j==1) j=2;
}
SIGNAL(SIG_INPUT_CAPTURE1)
{
    CH3_in_width = TCNT1-CH3_in_width;
    CH4_in_width = TCNT1;
    if(j==2) j=3;
}
SIGNAL(SIG_INTERRUPT1)
{
    if((PIND&0x08)==0){
        CH5_in_width = TCNT1-CH5_in_width;
        if(j==4) j=5;
    }
    else{
        CH4_in_width = TCNT1-CH4_in_width;
        CH5_in_width = TCNT1;
        if(j==3) j=4;
    }
}


int main(void)
{
    outp(0xFF, DDRC);

    outp(0x02, TCCR1B);

    outp(0x05, MCUCR);
    sbi(MCUCSR, 6);
    sbi(TCCR1B, 6);

    outp(0xE0, GICR);

    outp(0xB0, TCNT1H);
    outp(0x00, TCNT1L);

    outp(0x04, TIMSK);
    sbi(TIMSK, 5);
    sei();
    while(1) {
        if((j>=5)){
            j=0;
            if(CH5_in_width>1382) flight_mode = 1;
            else if(CH5_in_width<1382) flight_mode = 0;

            Servo4R_out_width = 2764-CH3_in_width;
            Servo4L_out_width = CH3_in_width;
            Servo6_out_width = CH3_in_width;

            if(CH3_in_width<=1382) {
                if(CH4_in_width>=1382) Servo4L_out_width +=(CH4_in_width-1382);
                else Servo4R_out_width += (CH4_in_width-1382);
            }
            else{
                if(CH4_in_width>=1382) Servo4R_out_width +=(CH4_in_width-1382);
                else Servo4L_out_width += (CH4_in_width-1382);
            }
        }
        while(out == 1){
            if(Servo1R_out_width<=TCNT1-0xB000) cbi(PORTC, 0);
            if(Servo1L_out_width<=TCNT1-0xB000) cbi(PORTC, 1);
            if(Servo2R_out_width<=TCNT1-0xB000) cbi(PORTC, 2);
            if(Servo2L_out_width<=TCNT1-0xB000) cbi(PORTC, 3);
            if(Servo3_out_width<=TCNT1-0xB000) cbi(PORTC, 4);
            if(Servo4R_out_width<=TCNT1-0xB000) cbi(PORTC, 5);
            if(Servo4L_out_width<=TCNT1-0xB000) cbi(PORTC, 6);
            if(Servo6_out_width<=TCNT1-0xB000) cbi(PORTC, 7);
            if(PINC==0x00) out = 0;
        }
    }
    return 0;
}