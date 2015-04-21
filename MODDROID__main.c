// (c) daniel ford, daniel.jb.ford@gmail.com

/********************************* ModDroid eye control code ************************************
/
/	listens to USB port on PIC board and displays images and blink patterns 
/	
/							assignments (all values chars, not integers)
/
/						input from USB			eye image displayed
/							0					calm (normal blink)
/							1					excited (fast blink)
/							2					sad (slow blink)
/							3					scared (fast blink)
/							4					angry (fast blink)
/							5					sleeping (no blink)
/							6					look left (normal blink)
/							7					look right (normal blink)
/							8					eyes off (all blank)
/							9					very excited (flashing)
/							h					heartbeats (flashing)
/
/						default image			sleeping (no blink)
*/

#include <p18f4550.h>
#include <usart.h>
#include <stdio.h>
#include <sw_spi.h>
#include <delays.h>
#include <stdlib.h>
#include "eyepatterns.h"

#define	BLINK_TIME		30
#define BIG_BLINK_TIME	100000
#define RANDOM_SEED		1435

void spi_write(char *data);
void spi_write2(char *data);
void dis_twoeyes(char *buffer_ptr_L, char *buffer_ptr_R);

char eye_storage_L[64], eye_storage_R[64];

void main(){
	char *buffer_ptr_L;
	char *buffer_ptr_R;
	char *eye_ptr;
	char cmd;
	int i=0,j=0,k=0,m=0;
	int MAX=63,ROWMAX=8;

	//configure USART
	OpenUSART(USART_TX_INT_OFF &
				USART_RX_INT_OFF &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_CONT_RX &
				USART_BRGH_HIGH,
				10); //baud rate 115200

	//open SPI port and set Port B to output
	OpenSWSPI();
 	TRISB = 0;

	//clear matrices

	//reorient eyes
	k = 0;
	for(i=0;i<8;i++)
	for(j=0;j<8;j++){
	eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = all_off[i][j];
	eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = all_off[i][j];
	k++;
	}

	buffer_ptr_L = eye_storage_L;
	buffer_ptr_R = eye_storage_R;		
	Delay1KTCYx(10);
	dis_twoeyes(buffer_ptr_L,buffer_ptr_R);

	srand(RANDOM_SEED);			//seed random number generator

	//loop and wait for input to display on eyes
	while( 1 ){

		cmd = ReadUSART();

		switch(cmd){

			//calm
			case '0':
			//reorient eyes
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = calm_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = calm_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = calm_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = calm_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME);
			break;

			//excited
			case '1':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = excited_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = excited_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());		

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = excited_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = excited_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME-rand());
			break;

			//sad
			case '2':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = sad_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = sad_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = sad_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = sad_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME-rand());
			Delay10KTCYx(BLINK_TIME+rand());
			Delay10KTCYx(BLINK_TIME-rand());
			break;

			//scared
			case '3':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = scared_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = scared_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = scared_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = scared_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME);
			break;

			//angry
			case '4':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = angry_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = angry_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());	

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = angry_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = angry_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME);
			break;								

			//sleeping
			case '5':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = sleeping[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = sleeping[i][j];
			k++;
			}						
			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			break;	

			//look left
			case '6':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = look_left_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = look_left_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = look_left_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = look_left_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME);
			break;

			//look right
			case '7':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = look_right_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = look_right_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());	
			Delay10KTCYx(BIG_BLINK_TIME+rand());
			Delay10KTCYx(BIG_BLINK_TIME-rand());

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = look_right_blink_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = look_right_blink_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME);
			break;

			//off
			case '8':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = all_off[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = all_off[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;		
			Delay1KTCYx(10);
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			break;

			//very excited
			case '9':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = excited_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = excited_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay1KTCYx(BIG_BLINK_TIME+rand());		

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = very_excited_1_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = very_excited_1_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay1KTCYx(BLINK_TIME-rand());

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = very_excited_2_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = very_excited_2_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay1KTCYx(BLINK_TIME-rand());
			break;

			//heartbeat
			case 'h':
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = heartbeat_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = heartbeat_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			Delay10KTCYx(BIG_BLINK_TIME/2);	

			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = heart_off_L[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = heart_off_R[i][j];
			k++;
			}

			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);	
			Delay10KTCYx(BLINK_TIME/2);
			break;

			//sleeping
			default:
			k = 0;
			for(i=0;i<8;i++)
			for(j=0;j<8;j++){
			eye_storage_L[k + MAX -( (ROWMAX+1) * (i+j) )] = sleeping[i][j];
			eye_storage_R[k + MAX -( (ROWMAX+1) * (i+j) )] = sleeping[i][j];
			k++;
			}						
			buffer_ptr_L = eye_storage_L;
			buffer_ptr_R = eye_storage_R;
			Delay1KTCYx(50);				
			dis_twoeyes(buffer_ptr_L,buffer_ptr_R);
			break;			

		}
	}

}

//write SPI using default pin assignments
//CS = chip select = RB2
//DIN = data into PIC = RB3
//DOUT = data out from PIC = RB7
//SCK = serial clock = RB6
void spi_write(char *data){
	int i;
	ClearCSSWSPI();
	Delay100TCYx(25);
	for (i=0;i<64;i++){
		WriteSWSPI(data[i]);
	}
	Delay100TCYx(25);
	SetCSSWSPI();
}

//write SPI for second matrix
//all pins same as above except chip select = RB4
void spi_write2(char *data){
	int i;
	PORTBbits.RB4 = 0;
	Delay100TCYx(25);
	for (i=0;i<64;i++){
		WriteSWSPI(data[i]);
	}
	Delay100TCYx(25);
	PORTBbits.RB4 = 1;
}

//write both buffers to matrices with 50 ms delay in between 
void dis_twoeyes(char *buffer_ptr_L, char *buffer_ptr_R){
	spi_write(buffer_ptr_L);
	Delay1KTCYx(50); //delay 50ms
	spi_write2(buffer_ptr_R);
}
