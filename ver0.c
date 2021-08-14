/*******************************************************
Project     : Keypad interface with atmega32 and displaying numbers in 7segmentLCD. 
Version     : V10.0
Date        : 6/21/2021
Author      : Ghazaleh99


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
Other components        : Keypad phone - 7segLCD
*******************************************************/

#include <io.h>
#include <mega32.h>
#include <delay.h>
#include <stdbool.h>

#define s1 PORTC.0
#define s2 PORTC.1
#define s3 PORTC.2
#define s4 PORTC.3

#define C0 PIND.0
#define C1 PIND.1
#define C2 PIND.2

#define R0 PORTD.4
#define R1 PORTD.5
#define R2 PORTD.6
#define R3 PORTD.7

/*************************************************** global variables **********************************************************/

unsigned int keypad_pressed_memory[4];
unsigned int seg[12]={0x3F, //Hex value to display the number 0
                        0x06, //Hex value to display the number 1
                        0x5B, //Hex value to display the number 2
                        0x4F, //Hex value to display the number 3
                        0x66, //Hex value to display the number 4
                        0x6D, //Hex value to display the number 5
                        0x7D, //Hex value to display the number 6
                        0x07, //Hex value to display the number 7
                        0x7F, //Hex value to display the number 8
                        0x6F, //Hex value to display the number 9
                        0x77, //Hex value to display the A
                        0x80  //Hex value to display the .
};

unsigned int keypad_pressed(void){

    PORTD = 0xF0;R0=0;    
        if(C0==0){
            delay_ms(5);
            return 1;
        };
    PORTD = 0xF0;R0=0;        
        if(C1==0){
            delay_ms(5);
            return 2;
        };
    PORTD = 0xF0;R0=0;        
        if(C2==0){
            delay_ms(5);
            return 3;
        };
        
    PORTD = 0xF0;R1=0;    
        if(C0==0){
            delay_ms(5);
            return 4;
        };
    PORTD = 0xF0;R1=0;        
        if(C1==0){
            delay_ms(5);
            return 5;
        };
    PORTD = 0xF0;R1=0;               
        if(C2==0){
            delay_ms(5);
            return 6;
        };
        
     PORTD = 0xF0;R2=0;         
        if(C0==0){
            delay_ms(5);
            return 7;
        };
     PORTD = 0xF0;R2=0;    
        if(C1==0){
            delay_ms(5);
            return 8;
        };
     PORTD = 0xF0;R2=0;
        if(C2==0){
            delay_ms(5);
            return 9;
        };
        
     PORTD = 0xF0;R3=0;
        if(C0==0){
            delay_ms(5);
            return 10;
        };
     PORTD = 0xF0;R3=0;
        if(C1==0){
            delay_ms(5);
            return 0;
        };
     PORTD = 0xF0;R3=0;
        if(C2==0){
            delay_ms(5);
            return 11;
        };
     return 12; //nothing pressed
}

void Lcd_showTime(unsigned int i){
    delay_ms(5);
    s4 = s3 = s2 = s1 = 1;
    if (i == 1){
        s1 = 0;
        PORTA=seg[keypad_pressed_memory[0]];
        delay_ms(5);
        s1 = 1; 
    };
    if (i == 2){
        s1 = 0;
        PORTA=seg[keypad_pressed_memory[0]];
        delay_ms(5);
        s1 = 1;
                
        s2 = 0;
        PORTA=seg[keypad_pressed_memory[1]];
        delay_ms(5);
        s2 = 1;
    };
    if (i == 3){
        s1 = 0;
        PORTA=seg[keypad_pressed_memory[0]];
        delay_ms(5);
        s1 = 1;
                
        s2 = 0;
        PORTA=seg[keypad_pressed_memory[1]];
        delay_ms(5);
        s2 = 1;
        
        s3 = 0;
        PORTA=seg[keypad_pressed_memory[2]];
        delay_ms(5);
        s3 = 1;
    };
    if (i == 4){
        s1 = 0;
        PORTA=seg[keypad_pressed_memory[0]];
        delay_ms(5);
        s1 = 1;
                
        s2 = 0;
        PORTA=seg[keypad_pressed_memory[1]];
        delay_ms(5);
        s2 = 1;
        
        s3 = 0;
        PORTA=seg[keypad_pressed_memory[2]];
        delay_ms(5);
        s3 = 1;
        
        s4 = 0;
        PORTA=seg[keypad_pressed_memory[3]];
        delay_ms(5);
        s4 = 1;
    };  
}

/************************************************* End ofglobal variables *****************************************************/

void main(void){

    unsigned int counter = 0 , i = 0;
    unsigned int myKey;
/********************* Input/Output Ports initialization *****************************/
    
    // Port A initialization ------- Segments PORTS
        // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
        DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
        // State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
        PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

    // Port C initialization -------- LCD controller PORTS
        // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
        DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
        // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=1 Bit2=1 Bit1=1 Bit0=1 
        PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization -------- Keypad PORTS
        // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=In 
        DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
        // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=P Bit1=P Bit0=P 
        PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

/********************* End of Input/Output Ports initialization **********************/  
    
    while (1){
        delay_ms(95);
        myKey = keypad_pressed();
        delay_ms(95);
        if (myKey != 12){
            keypad_pressed_memory[counter%4] = myKey;  
            if (i <= 4){ 
                i++; 
                Lcd_showTime(i);
                if (i == 5){
                    i = 4;
                }                
            }
            counter = (counter+1) % 4 ;
        }
        else{
            Lcd_showTime(i);  
        };  
    } 
}