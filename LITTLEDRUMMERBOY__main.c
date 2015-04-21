// (c) daniel ford, daniel.jb.ford@gmail.com

// "Little Drummer Boy" robot drummer

#include <p18f4550.h>
#include <adc.h>      
#include <timers.h>
#include <lcd_new.h>
#include <stdlib.h>
#include <delays.h>

#define timer_offset 	65286  	//timer offset for 0.05 ms interrupt
#define BEAT_ST			  10		  //beat positions
#define BEAT			    9
#define TICKS_LOW		  400		  //equates to ~220 bpm
#define TICKS_INIT		1200	  //equates to ~90 bpm
#define TICKS_HIGH		2100	  //equates to ~45 bpm
#define DELAY			    240     //20 ms delay for servo pulse train

#define QUICKPUSH   	1	      //# of interrupts for quick push	
#define KNOB_SCALE		1.66178	//constant to scale knob movements

//beat timing constants
#define BEAT_PULSE		1       //used to send correct # of pulses           
#define WAIT_LENGTH		0       //to send for a single beat

#define LEFT			    0b00000100  //PORTB output constants
#define RIGHT			    0b00001000  //to activate servos
#define BOTH			    0b00001100

#define NAV_LEFT		  0       //constants for interface menus
#define TRK_SWITCH		1
#define PLAY_STOP		  2
#define TEMPO			    3
#define NAV_RIGHT		  4
#define OUT_OF_RANGE	256		

//function prototypes
void ext_isr (void);   					     
void timer_isr (void);
void moveServo(int direction,int which);
void interface_FSM(void);
void write_L_play(int interface);
void write_R_play(int interface);
void write_menu(int interface);
void knob_read(int interface);

//variables used in interface
int b_count=0;					
int quick_press=0,long_press=0;
int state=1;						
int interface=3;
int upper=0,menu=OUT_OF_RANGE;
int m_menu=0;
int pulse_count=0;
int knob=0;
int saveface=0;	
int which=0;
int unblock=0;
int ADCcount=0;		

//variables used in servo movement
int beat_count=0;
int wait_count=0;
int index=0,i=0,j=0;
int hitOnL=0,hitOnR=0,hitOnBoth=0;
long int master_clock=0;				
int startstop=0;
int tempo=TICKS_INIT;

//text for interface
char playholder;						
rom char space=' ';
char inter;
char stopholder;
char menuholder;
char trkholder;
rom char left_arrow='<';
rom char right_arrow='>';
rom char tempo1[]=" TEMPO  ";
rom char tempo2[]=" tempo  ";
char tempostr[5];

//timing arrays with initial drum beat
int beatMapL[32]={	1,0,1,0,	1,0,0,1,	0,1,0,0,	1,0,1,0,
					1,0,0,0,	1,0,0,1,	0,0,1,0,	1,0,0,0	};

int beatMapR[32]={	0,1,0,0,	0,1,0,0,	0,1,0,1,	1,0,1,0,
					1,0,0,0,	1,0,0,1,	0,1,0,0,	1,0,0,0	};

#pragma code _HIGH_INTERRUPT_VECTOR=0x0000008
 
void high_ISR (void){   

//redirect to button interrupt
 
_asm     
    goto ext_isr   
 _endasm
}
 
#pragma code _LOW_INTERRUPT_VECTOR=0x0000018
#pragma interruptlow timer_isr
void timer_isr (void){

//increment servo pulse timing variable
pulse_count++;
			
//increment master clock if in play mode, else don't increment			
if(startstop)
master_clock++;
else {
master_clock=0;
index=0;
}

//read beat map and set beat flags
if(	(beatMapL[index]==1) &&	(beatMapR[index]==1) && startstop ){
hitOnBoth=1;
state=3;
unblock=0;
}
else {
hitOnBoth=0;
unblock=1;
}

if( (beatMapL[index]==1) && startstop && unblock ){
hitOnL=1;
state=1;
}
else hitOnL=0;

if( (beatMapR[index]==1) && startstop && unblock ){
hitOnR=1;
state=2;
}
else hitOnR=0;

//increment through beat map at given tempo
if(master_clock>=tempo){
master_clock=0;
index++;
}
if(index>31)
index=0;

//servo PWM FSM
switch(state){

	case 1:	                    //left servo hit state			
	moveServo(BEAT_ST,LEFT);
	if(hitOnL){
	wait_count=0;
	if(wait_count<BEAT_PULSE)
		moveServo(BEAT,LEFT);
	if((wait_count>=BEAT_PULSE) && (wait_count<WAIT_LENGTH))
		moveServo(BEAT,LEFT);
	}
	wait_count++;
	break;

	case 2:				        //right servo hit state
	moveServo(BEAT_ST,RIGHT);
	if(hitOnR){
	wait_count=0;
	if(wait_count<BEAT_PULSE)
		moveServo(BEAT,RIGHT);
	if((wait_count>=BEAT_PULSE) && (wait_count<WAIT_LENGTH))
		moveServo(BEAT,RIGHT);
	}
	wait_count++;
	break;

	case 3:				        //both servos hit state
	moveServo(BEAT_ST,BOTH);
	if(hitOnBoth){
	wait_count=0;
	if(wait_count<BEAT_PULSE)
		moveServo(BEAT,BOTH);
	if((wait_count>=BEAT_PULSE) && (wait_count<WAIT_LENGTH))
		moveServo(BEAT_ST,BOTH);
	}
	wait_count++;
	break;
	
}
	
//interface FSM - button reading and logic section
switch(interface){

	//left track page 1 
	case 3:
	if(upper<=7){
		if(long_press){
			if(beatMapL[upper]==1)
			beatMapL[upper]=0;
			else beatMapL[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){	
		if(long_press){
		upper=24;
		menu=OUT_OF_RANGE;
		interface=9;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){	
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		interface=5;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){	
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		saveface=interface;
		interface=7;
		long_press=0;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=8;
		menu=OUT_OF_RANGE;
		interface=4;
		long_press=0;
		}
	}
	break;

	//left track page 2
	case 4:
	if(upper<=15){
		if(long_press){
			if(beatMapL[upper]==1)
			beatMapL[upper]=0;
			else beatMapL[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		interface=3;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=8;
		menu=OUT_OF_RANGE;
		interface=6;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=16;
		menu=OUT_OF_RANGE;
		interface=8;
		long_press=0;
		}
	}
	break;

	//right track page 1
	case 5:
	if(upper<=7){
		if(long_press){
			if(beatMapR[upper]==1)
			beatMapR[upper]=0;
			else beatMapR[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=24;
		menu=OUT_OF_RANGE;
		interface=11;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		interface=3;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=8;
		menu=OUT_OF_RANGE;
		interface=6;
		long_press=0;
		}
	}
	break;

	//right track page 2
	case 6:
	if(upper<=15){
		if(long_press){
			if(beatMapR[upper]==1)
			beatMapR[upper]=0;
			else beatMapR[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		interface=5;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=8;
		menu=OUT_OF_RANGE;
		interface=4;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=16;
		menu=OUT_OF_RANGE;
		interface=10;
		long_press=0;
		}
	}
	break;
	
	//tempo menu
	case 7:
	if(long_press){
	interface=saveface;
	long_press=0;
	}
	break;
	
	//left track page 3
	case 8:
	if(upper<=23){
		if(long_press){
			if(beatMapL[upper]==1)
			beatMapL[upper]=0;
			else beatMapL[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=8;
		menu=OUT_OF_RANGE;
		interface=6;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=16;
		menu=OUT_OF_RANGE;
		interface=10;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=24;
		menu=OUT_OF_RANGE;
		interface=9;
		long_press=0;
		}
	}	
	break;

	//left track page 4
	case 9:
	if(upper<=31){
		if(long_press){
			if(beatMapL[upper]==1)
			beatMapL[upper]=0;
			else beatMapL[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=16;
		menu=OUT_OF_RANGE;
		interface=8;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=24;
		menu=OUT_OF_RANGE;
		interface=11;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		interface=3;
		long_press=0;
		}
	}	
	break;

	//right track page 3
	case 10:
	if(upper<=23){
		if(long_press){
			if(beatMapR[upper]==1)
			beatMapR[upper]=0;
			else beatMapR[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=8;
		menu=OUT_OF_RANGE;
		interface=6;
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=16;
		menu=OUT_OF_RANGE;
		interface=8;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=24;
		menu=OUT_OF_RANGE;
		interface=11;
		long_press=0;
		}
	}
	break;

	//right track page 4
	case 11:
	if(upper<=31){
		if(long_press){
			if(beatMapR[upper]==1)
			beatMapR[upper]=0;
			else beatMapR[upper]=1;
			long_press=0;
		}
	}
	if(menu==NAV_LEFT){
		if(long_press){
		upper=16;
		menu=OUT_OF_RANGE;
		interface=10;	
		long_press=0;
		}
	}
	if(menu==TRK_SWITCH){
		if(long_press){
		upper=24;
		menu=OUT_OF_RANGE;
		interface=9;
		long_press=0;
		}
	}
	if(menu==PLAY_STOP){
		if(long_press){
			if(startstop==0)
			startstop=1;
			else startstop=0;
			long_press=0;
		}
	}
	if(menu==TEMPO){
		if(long_press){
		saveface=interface;
		upper=0;
		menu=OUT_OF_RANGE;
		long_press=0;
		interface=7;
		}
	}
	if(menu==NAV_RIGHT){
		if(long_press){
		upper=0;
		menu=OUT_OF_RANGE;
		interface=5;
		long_press=0;
		}
	}	
	break;

}

// reset timer to interrupt in 0.05 ms 
    WriteTimer0(timer_offset);
 
// reset timer interrupt flag 
    INTCONbits.TMR0IF=0;
 
}
 
#pragma interrupt ext_isr
void ext_isr (void){

//button ISR
quick_press++;

if(quick_press>QUICKPUSH)
long_press=1;
 
INTCONbits.INT0IF = 0; // clear interrupt flag
 
}

void main(void){

	//initialize A/D converter
	ADCON0bits.ADON=1;		//enable ADC
	ADCON0bits.CHS0=0;		//choose AN0 for input
	ADCON0bits.CHS1=0;
	ADCON0bits.CHS2=0;
	ADCON0bits.CHS3=0;

	ADCON1=0b00001110;		//set AN0 as analog input, all others as dig I/O
                        //set Vrefs as Vss and Vdd
	ADCON2=0b10001001;		//set A/D output as right justified
                        //acquisition time to 4 TAD, clock to Fosc/8

	PIE1bits.ADIE = 0;		//disable ADC interrupt

	//initialize Port B
	TRISB = 0b00000011;		//set RB0-RB1 as input, RB2-RB7 as output 
	UCFG=0;					      //disable UART external transceiver
	PORTB=0;
    
	//initialize Port C and disable multiplexed devices on Port C
  TRISC = 0;                              //set Port C to output
  SSPCON1bits.SSPEN=0;                    //turn off MSSP device
  TXSTA=0;RCSTA=0;                        //disable USART
	CCP1CON=0;								              //disable PWM/CCP module
	T1CON=0;								                //disable Timer 1   

	//initialize Port E
  TRISE = 0;            //set Port E to output           
  PORTE = 255;          //turn LED on

  //configure Timer 0, set prescaler to 1:1
  OpenTimer0(TIMER_INT_ON & T0_SOURCE_INT & T0_16BIT & T0_PS_1_1);

	//configure interrupts
  INTCON2bits.TMR0IP = 0;
  RCONbits.IPEN=1;
  INTCONbits.GIE=1;
  INTCONbits.PEIE=1;
  INTCONbits.INT0IE = 1;					//enable external interrupts 
  INTCON2bits.INTEDG0 = 0;  

  //initialize LCD
	init_lcd();
	clearscreen();
	
	//write timer offset value
  WriteTimer0(timer_offset);

	//write initial tempo display string
	itoa(tempo,tempostr);

	//main while loop
  while(1){ 

    //poll ADC with delay to prevent cursor glitches
    ADCcount++;

    if( ADCcount>2){
      ConvertADC();
      knob = ReadADC();
      knob_read(interface);
    }
    if( ADCcount>4)
      ADCcount=0;

    //call interface FSM display functions
    interface_FSM();	

  }
	CloseTimer0();
}
//servo movement function
void moveServo(int direction,int which){
	if(pulse_count<direction)
	PORTB=which;
	if( (pulse_count>=direction) && (pulse_count<DELAY) )
	PORTB=0;
	if(pulse_count==DELAY)
	pulse_count=0;
}
//inteface FSM display function shell
void interface_FSM(void){

	switch(interface){

	case 3:
	write_L_play(interface);
	break;

	case 4:
	write_L_play(interface);
	break;

	case 5:
	write_R_play(interface);
	break;

	case 6:
	write_R_play(interface);
	break;

	case 7:
	write_menu(interface);
	break;

	case 8:
	write_L_play(interface);
	break;

	case 9:
	write_L_play(interface);
	break;

	case 10:
	write_R_play(interface);
	break;

	case 11:
	write_R_play(interface);
	break;

	}
}
//display functions for left track pages
void write_L_play(int interface){
	char test;
	
	//display beats and rests
	for(i=0;i<8;i++){
		if(interface==3)
		j=i;
		if(interface==4)
		j=i+8;
		if(interface==8)
		j=i+16;
		if(interface==9)
		j=i+24;
		setcursor(0,i);
		if(beatMapL[j]){
			if(upper==j)
			display_char('X');
			else display_char('x');
		} 
		else {
			if(upper==j)
			display_char('O');
			else display_char('o');
		}
	}

	//display navigation elements
	if(menu==0){
		setcursor(1,0);
		display_char(left_arrow);
		setcursor(1,1);
		display_char(left_arrow);
	}
	else{
		setcursor(1,0);
		display_char(left_arrow);
		setcursor(1,1);
		display_char(space);
	}
	
	if(menu==1)
	trkholder='L';
	else trkholder='l';
	setcursor(1,2);
	display_char(trkholder);

	if( (interface==3) || (interface==4) )
	inter='0'+(interface-2);
	else inter='0'+(interface-5);
	setcursor(1,3);
	display_char(inter);

	if(menu==2){
		if(startstop)
		playholder='S';
		else playholder='P';
	}
	else{
		if(startstop)
		playholder='s';
		else playholder='p';
	}
	setcursor(1,4);
	display_char(playholder);

	if(menu==3)
	menuholder='T';
	else menuholder='t';
	setcursor(1,5);
	display_char(menuholder);

	if(menu==4){
		setcursor(1,6);
		display_char(right_arrow);
		setcursor(1,7);
		display_char(right_arrow);
	}
	else{
		setcursor(1,6);
		display_char(space);
		setcursor(1,7);
		display_char(right_arrow);
	}

}
//display functions for right track pages
void write_R_play(int interface){
	
	//display beats and rests
	for(i=0;i<8;i++){
		if(interface==5)
		j=i;
		if(interface==6)
		j=i+8;
		if(interface==10)
		j=i+16;
		if(interface==11)
		j=i+24;
		setcursor(0,i);
		if(beatMapR[j]){
			if(upper==j)
			display_char('X');
			else display_char('x');
		} 
		else {
			if(upper==j)
			display_char('O');
			else display_char('o');
		}
	}

	//display navigation elements
	if(menu==0){
		setcursor(1,0);
		display_char(left_arrow);
		setcursor(1,1);
		display_char(left_arrow);
	}
	else{
		setcursor(1,0);
		display_char(left_arrow);
		setcursor(1,1);
		display_char(space);
	}

	if(menu==1)
	trkholder='R';
	else trkholder='r';
	setcursor(1,2);
	display_char(trkholder);

	if( (interface==5) || (interface==6) )
	inter='0'+(interface-4);
	else inter='0'+(interface-7);
	setcursor(1,3);
	display_char(inter);

	if(menu==2){
		if(startstop)
		playholder='S';
		else playholder='P';
	}
	else{
		if(startstop)
		playholder='s';
		else playholder='p';
	}
	setcursor(1,4);
	display_char(playholder);

	if(menu==3)
	menuholder='T';
	else menuholder='t';
	setcursor(1,5);
	display_char(menuholder);

	if(menu==4){
		setcursor(1,6);
		display_char(right_arrow);
		setcursor(1,7);
		display_char(right_arrow);
	}
	else{
		setcursor(1,6);
		display_char(space);
		setcursor(1,7);
		display_char(right_arrow);
	}

}
//display tempo on tempo menu
void write_menu(int interface){

	int i=0;

	if(interface==7){		
			
		itoa(tempo,tempostr);
	
		setcursor(0,0);
		display_str_ROM(tempo2);
		setcursor(1,0);
		display_char(space);
		setcursor(1,1);
		display_char(space);

		if( tempo<999){
		setcursor(1,2);
		display_str(tempostr);
		setcursor(1,5);
		display_char(space);
		}
		else {
		setcursor(1,2);
		display_str(tempostr);
		}			
		setcursor(1,6);
		display_char(space);
		setcursor(1,7);
		display_char(space);
	}

}
//function to map knob values to cursor placement or tempo
void knob_read(int interface){

//map knob values to navigation elements
int offset;

if( (interface==3) || (interface==5))
offset=0;
if( (interface==4) || (interface==6))
offset=8;
if( (interface==8) || (interface==10))
offset=16;
if( (interface==9) || (interface==11))
offset=24;

if( interface!=7 ){
	if( (knob>0) && (knob<=105)	){
	upper=0+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>105) && (knob<=178)	){
	upper=1+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>178) && (knob<=256)	){
	upper=2+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>256) && (knob<=340)	){
	upper=3+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>340) && (knob<=415)	){
	upper=4+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>415) && (knob<=490)	){
	upper=5+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>490) && (knob<=565)	){
	upper=6+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>565) && (knob<=650)	){
	upper=7+offset;
	menu=OUT_OF_RANGE;
	}
	if( (knob>650) && (knob<=702)	){
	menu=0;
	upper=OUT_OF_RANGE;
	}
	if( (knob>702) && (knob<=780)	){
	menu=1;
	upper=OUT_OF_RANGE;
	}
	if( (knob>780) && (knob<=858)	){
	menu=2;
	upper=OUT_OF_RANGE;
	}
	if( (knob>858) && (knob<=910)	){
	menu=3;
	upper=OUT_OF_RANGE;
	}
	if( (knob>910) && (knob<=1023)	){
	menu=4;
	upper=OUT_OF_RANGE;
	}
}
//in tempo menu, scale knob values to tempo values
if( interface == 7 )
	tempo = TICKS_HIGH-(knob*KNOB_SCALE);

}
