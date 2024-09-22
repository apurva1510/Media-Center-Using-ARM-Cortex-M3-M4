//----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 //const unsigned char image2[] =  Use this for the image .c files               
#include <LPC17xx.H>                    // NXP LPC17xx definitions            
#include "LPC17xx.h"
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "usbdmain.h"
#include "snake.h"
#include <stdio.h>
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
#include "usbdmain.h"
#include "type.h"
#include "Gallery.h"
#include "stdlib.h"
extern int audio_main (void);

/////////////////////////////////////////////////Flappy Bird////////////////////////////////////////////////////////////////////////////
#define __FI        1                      // Font index 16x24               
#define __USE_LCD   0                                       // Uncomment to use the LCD 

// Define picture variables 
extern unsigned char FlappyBird[];
extern unsigned char TubesLarge[];
extern unsigned char upTubesLarge[];

// Initialize x and y position value of pictures 
int bird_Xaxis = 5;
int bird_Yaxis = 120;
int TopLargeTubeX = 320;
int TopLargeTubeY = 0;
int TopMedTubeX = 400;
int TopMedTubeY = 0;
int TopSmallTubeX = 480;
int TopSmallTubeY = 0;
int BottomLargeTubeX = 480;
int BottomLargeTubeY = 140;
int BottomMedTubeX = 440;
int BottomMedTubeY = 165;
int BottomSmallTubeX = 360;
int BottomSmallTubeY = 190;
int flappyDelay = 0;
char flappyBirdScore[10];
int scoreNum = 0;

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

void flaapyBirdGameOver(){
    int gameExitButton;
            #ifdef __USE_LCD
                GLCD_Clear(Black);                         // Clear graphical LCD display   
                GLCD_SetBackColor(Black);
                GLCD_SetTextColor(Blue);
                GLCD_SetTextColor(Red);
                GLCD_DisplayString(2, 0, __FI, "  Score:  ");
                sprintf(flappyBirdScore, "%d", scoreNum);
                GLCD_DisplayString(2,12, __FI,  (unsigned char*)flappyBirdScore);
                GLCD_DisplayString(3, 0, __FI, "  Game Over          ");
                GLCD_DisplayString(4, 0, __FI, "  Press LEFT         ");
                GLCD_DisplayString(5, 0, __FI, "  To Return to Menu  ");
            #endif
    while(1){
        gameExitButton = get_button();
        if (gameExitButton == KBD_LEFT){
            return;
            }
        }
}


// Reset function to reset all variables to initial values 
void valuesInit(){
    scoreNum = 0;
    bird_Xaxis = 5;
    bird_Yaxis = 120;
    TopLargeTubeX = 320;
    TopLargeTubeY = 0;
    TopMedTubeX = 400;
    TopMedTubeY = 0;
    TopSmallTubeX = 480;
    TopSmallTubeY = 0;
    BottomLargeTubeX = 480;
    BottomLargeTubeY = 140;
    BottomMedTubeX = 440;
    BottomMedTubeY = 165;
    BottomSmallTubeX = 360;
    BottomSmallTubeY = 190;

}


// Game function to initialize and play Flappy Bird game 
void game(){
	int gamebutton;
	#ifdef __USE_LCD
			GLCD_Clear(Cyan);                         // Clear graphical LCD display   
			GLCD_SetBackColor(Cyan);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString(0, 0, __FI, "Flappy Birds    ");
			GLCD_DisplayString(1, 0, __FI, "Goal: Stay Alive       ");
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString(2, 0, __FI, "Select - Play Game     ");
			GLCD_DisplayString(3, 0, __FI, "Controls:  ");
			GLCD_DisplayString(4, 0, __FI, "Select - Bird Flaps  ");
			GLCD_DisplayString(5, 0, __FI, "Left - Quit to Main Menu  ");
	#endif
	

	while(1){ //game inside while loop
								
	gamebutton = get_button();
	if (gamebutton == KBD_SELECT){ //check if Select option picked
	for (flappyDelay = 0; flappyDelay < 1; flappyDelay++){ //for loop to clear screen once
			GLCD_Clear(Cyan); 
	}
			gamebutton = get_button();
	
			
			while(gamebutton != KBD_LEFT){ //entire game held inside while loop waiting for left to be pressed to exit game
							
					// Reset x and y values of tubes once reached end of screen 
					if (TopLargeTubeX < -30){
							TopLargeTubeX = 320;
					}
					
					if (TopMedTubeX < -30){
							TopMedTubeX = 400;
					}
					
					if (TopSmallTubeX < -30){
							TopSmallTubeX = 480;
					}           

					if (BottomLargeTubeX < -30){
							BottomLargeTubeX = 480;
					}

					if (BottomMedTubeX < -30){
							BottomMedTubeX = 440;
					}

					if (BottomSmallTubeX < -30){
							BottomSmallTubeX = 360;
					}


					// Placing pictures on LCD panel 
					GLCD_Bitmap (bird_Xaxis, bird_Yaxis, 30, 30, FlappyBird);
					// Tubes touching the ceiling
					GLCD_Bitmap (TopLargeTubeX, TopLargeTubeY, 30, 100, TubesLarge);
					GLCD_Bitmap (TopMedTubeX, TopMedTubeY, 30, 75, TubesLarge);
					GLCD_Bitmap (TopSmallTubeX, TopSmallTubeY, 30, 50, TubesLarge);
					
					//Tubes touching the floor
					GLCD_Bitmap (BottomLargeTubeX, BottomLargeTubeY, 30, 100, upTubesLarge);
					GLCD_Bitmap (BottomMedTubeX, BottomMedTubeY, 30, 75, upTubesLarge);
					GLCD_Bitmap (BottomSmallTubeX, BottomSmallTubeY, 30, 50, upTubesLarge);

					
					// Incrementing/Decrementing values of tubes and bird 
					gamebutton = get_button();
					bird_Yaxis = bird_Yaxis + 1;
			
					TopLargeTubeX = TopLargeTubeX - 1;
					TopMedTubeX = TopMedTubeX - 1;
					TopSmallTubeX = TopSmallTubeX - 1;
			
					BottomLargeTubeX = BottomLargeTubeX - 1;
					BottomMedTubeX = BottomMedTubeX - 1;
					BottomSmallTubeX = BottomSmallTubeX - 1;

					if (gamebutton == KBD_SELECT){ //select moves bird up 2 pixels
							bird_Yaxis = bird_Yaxis - 2;
					}

					// Tube and Bird collision detection 
					if (TopLargeTubeX <= 35 && TopLargeTubeX >= 30 && bird_Yaxis >= 0 && bird_Yaxis <= 70){
							flaapyBirdGameOver(); //flaapyBirdGameOver function thrown
							valuesInit();    //reset function thrown
							return;
					}

					else if (TopMedTubeX <= 35 && TopMedTubeX >= 30 && bird_Yaxis <= 45){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   
					
					else if (TopSmallTubeX <= 35 && TopSmallTubeX >= 30 && bird_Yaxis <= 20){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}       
					
					else if (BottomLargeTubeX <= 35 && BottomLargeTubeX >= 30 && bird_Yaxis >= 140){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   

					else if (BottomMedTubeX <= 35 && BottomMedTubeX >= 30 && bird_Yaxis >= 165){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   
					
					else if (BottomSmallTubeX <= 35 && BottomSmallTubeX >= 30 && bird_Yaxis >= 190){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   
					
					// Tube and Bird collision for top and bottom of bird 
					else if (TopLargeTubeX < 35 && TopLargeTubeX > 5 && bird_Yaxis <= 70){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}

					else if (TopMedTubeX < 35 && TopMedTubeX > 5 && bird_Yaxis <= 45){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   
					
					else if (TopSmallTubeX < 35 && TopSmallTubeX > 5 && bird_Yaxis <= 20){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}       
					
					else if (BottomLargeTubeX < 35 && BottomLargeTubeX > 5 && bird_Yaxis >= 140){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   

					else if (BottomMedTubeX < 35 && BottomMedTubeX > 5 && bird_Yaxis >= 165){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}                                   
					
					else if (BottomSmallTubeX < 35 && BottomSmallTubeX > 5 && bird_Yaxis >= 190){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}           

					else{ //incrementing score
							scoreNum++;
					}
					
					// Bird collison detection on top and bottom of screen 
					if (bird_Yaxis > 210 || bird_Yaxis < 0){
							flaapyBirdGameOver();
							valuesInit();
							return;
					}

				}
				GLCD_Clear(Yellow);
				return;                     
			}
								
								
			if (gamebutton == KBD_LEFT){ //able to exit game at any time
			GLCD_Clear(Yellow);
					return;
			}
        }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////Snake///////////////////////////////////////////////////////////////////////////////////
#define DELAY_2N 20

int snakePos_X; //horizontal position
int snakePos_Y; //vertical position
int snakeSize; //snakeSize of the body
int currentDirection = 0; //current direction
int previousDirection = 0; //previous direction
int currentJoystkVal = 0; //current joystick val
int previousJoystkVal = KBD_RIGHT; //previous joystick val
char str[20],str1[20],str2[20],str3[20];
int snakeCoordinates[100][2]; //snake coordinates.
int delx, dely; //used to figure out where to turn
int speed; //how fast the snake will move
int xtarget, ytarget; //target coordinates
int collision = 0;
int displayBorder = 0;
int snakescore = 0;

void target(){
	int i;
	xtarget = rand()%9;
	ytarget = rand()%20;
	for(i=0;i<snakeSize;i++){
		if(xtarget == snakeCoordinates[i][0])
			if(ytarget == snakeCoordinates[i][1])
				target();
	}
	GLCD_DisplayChar(xtarget,ytarget,1,0x81);
}

void delay (int count){
	count <<= DELAY_2N;
	while(count--);
}

void setbody(){
	int i; //counting
	
	for(i=0;i<snakeSize;i++){
		switch(currentDirection){
			case 0://right
				snakeCoordinates[i][0] = snakePos_X;
				snakeCoordinates[i][1] = snakePos_Y-i;
				break;
			case 1://left
				snakeCoordinates[i][0] = snakePos_X;
				snakeCoordinates[i][1] = snakePos_Y+i;
				break;
			case 2://down
				snakeCoordinates[i][0] = snakePos_X+i;
				snakeCoordinates[i][1] = snakePos_Y;
				break;
			case 3://up
				snakeCoordinates[i][0] = snakePos_X-1;
				snakeCoordinates[i][1] = snakePos_Y;
				break;
		}
	}
}

void addbody(){
	int n=1;
	snakeSize++;
	snakescore = snakescore + 2*n;
	if(speed != 0)
		speed--;
	n++;
}

void check(){
	int i;
	
	//target check
	if(xtarget == snakeCoordinates[0][0])
		if(ytarget == snakeCoordinates[0][1]){
			addbody();
			target();
		}
		
	//tail collision check
	for(i=1;i<snakeSize;i++){
		if(snakeCoordinates[0][0] == snakeCoordinates[i][0])
			if(snakeCoordinates[0][1] == snakeCoordinates[i][1])
				collision = 1;
	}
	
	//collision to wall
	if(displayBorder == 1){
		//check right wall
		if(snakeCoordinates[0][1] == 19 && snakeCoordinates[1][1] == 18)
			collision = 1;
		//check left wall
		if(snakeCoordinates[0][1] == 0 && snakeCoordinates[1][1] == 1)
			collision = 1;
		//check bottom wall
		if(snakeCoordinates[0][0] == 9 && snakeCoordinates[1][0] == 8)
			collision = 1;
		//check top wall
		if(snakeCoordinates[0][0] == 0 && snakeCoordinates[1][0] == 1)
			collision = 1;
	}
}

void updatebody(){
	int i;
	if(currentDirection == 0){//move right
		for(i=snakeSize;i>0;i--){
			if(i -1 == 0){
				snakeCoordinates[0][1] = snakePos_Y;
				snakeCoordinates[0][0] = snakePos_X;				
			}else{
				GLCD_DisplayChar(snakeCoordinates[i-1][0],snakeCoordinates[i-1][1],1,' ');
				snakeCoordinates[i-1][1] = snakeCoordinates[i-2][1];
				snakeCoordinates[i-1][0] = snakeCoordinates[i-2][0];
			}
		}		
		for(i=1;i<snakeSize;i++){
			GLCD_DisplayChar(snakeCoordinates[0][0],snakeCoordinates[0][1],1,0x8B);
			GLCD_DisplayChar(snakeCoordinates[i][0],snakeCoordinates[i][1],1,0x82);
		}
		delay(speed);
	}else if(currentDirection == 1){//move left
		for(i=snakeSize;i>0;i--){
			if(i -1 == 0){
				snakeCoordinates[0][1] = snakePos_Y;
				snakeCoordinates[0][0] = snakePos_X;				
			}else{
				GLCD_DisplayChar(snakeCoordinates[i-1][0],snakeCoordinates[i-1][1],1,' ');
				snakeCoordinates[i-1][1] = snakeCoordinates[i-2][1];
				snakeCoordinates[i-1][0] = snakeCoordinates[i-2][0];
			}
		}
		for(i=1;i<snakeSize;i++){
			GLCD_DisplayChar(snakeCoordinates[0][0],snakeCoordinates[0][1],1,0x89);
			GLCD_DisplayChar(snakeCoordinates[i][0],snakeCoordinates[i][1],1,0x82);
		}
		delay(speed);
	}else if(currentDirection == 2){//move down
		for(i=snakeSize;i>0;i--){
			if(i -1 == 0){
				snakeCoordinates[0][1] = snakePos_Y;
				snakeCoordinates[0][0] = snakePos_X;				
			}else{
				GLCD_DisplayChar(snakeCoordinates[i-1][0],snakeCoordinates[i-1][1],1,' ');
				snakeCoordinates[i-1][1] = snakeCoordinates[i-2][1];
				snakeCoordinates[i-1][0] = snakeCoordinates[i-2][0];
			}
		}
		for(i=1;i<snakeSize;i++){
			GLCD_DisplayChar(snakeCoordinates[0][0],snakeCoordinates[0][1],1,0x87);
			GLCD_DisplayChar(snakeCoordinates[i][0],snakeCoordinates[i][1],1,0x82);
		}
		delay(speed);
	}else if(currentDirection == 3){//move up
		for(i=snakeSize;i>0;i--){
			if(i-1 == 0){
				snakeCoordinates[0][1] = snakePos_Y;
				snakeCoordinates[0][0] = snakePos_X;				
			}else{
				GLCD_DisplayChar(snakeCoordinates[i-1][0],snakeCoordinates[i-1][1],1,' ');
				snakeCoordinates[i-1][1] = snakeCoordinates[i-2][1];
				snakeCoordinates[i-1][0] = snakeCoordinates[i-2][0];
			}
		}
		for(i=1;i<snakeSize;i++){
			GLCD_DisplayChar(snakeCoordinates[0][0],snakeCoordinates[0][1],1,0x85);
			GLCD_DisplayChar(snakeCoordinates[i][0],snakeCoordinates[i][1],1,0x82);
		}
		delay(speed);
	}
	check();
}

void direction(int joyval){

	switch(joyval){
		case KBD_UP:
			if (previousJoystkVal == KBD_LEFT || previousJoystkVal == KBD_RIGHT){
				snakePos_X--;
				if (snakePos_X < 0){
					snakePos_X = 9;
				}
				currentDirection = 3;
				previousDirection = currentDirection;
				previousJoystkVal = currentJoystkVal;
				updatebody();
			}
			break;
		case KBD_DOWN:
			if (previousJoystkVal == KBD_LEFT || previousJoystkVal == KBD_RIGHT){
				snakePos_X++;
				if (snakePos_X > 9){
					snakePos_X = 0;
				}
				currentDirection = 2;
				previousDirection = currentDirection;
				previousJoystkVal = currentJoystkVal;
				updatebody();
			}
			break;
		case KBD_LEFT:
			if (previousJoystkVal == KBD_UP || previousJoystkVal == KBD_DOWN){
				snakePos_Y--;
				if (snakePos_Y < 0){
					snakePos_Y = 20;
				}
				currentDirection = 1;
				previousDirection = currentDirection;
				previousJoystkVal = currentJoystkVal;
				updatebody();
			}
			break;
		case KBD_RIGHT:
			if (previousJoystkVal == KBD_UP || previousJoystkVal == KBD_DOWN){
				snakePos_Y++;
				if (snakePos_Y > 20 ){
					snakePos_Y = 0;
				}
				currentDirection = 0;
				previousDirection = currentDirection;
				previousJoystkVal = currentJoystkVal;
				updatebody();
			}
			break;
		default:
			switch(currentDirection){
				case 0://right
					snakePos_Y++;
					if (snakePos_Y > 20){
						snakePos_Y = 0;
					}
					updatebody();
					check();
					break;
				case 1://left
					snakePos_Y--;
					if (snakePos_Y < 0){
						snakePos_Y = 20;
					}
					updatebody();
					check();
					break;
				case 2://down
					snakePos_X++;
					if (snakePos_X > 9){
						snakePos_X = 0;
					}
					updatebody();
					check();
					break;
				case 3://up
					snakePos_X--;
					if (snakePos_X < 0){
						snakePos_X = 9;
					}
					updatebody();
					check();
					break;
			}
			break;
	}	
}

void clearsnake(){
	int i;
	for(i=0;i<snakeSize;i++){
		snakeCoordinates[i][0]=1;
		snakeCoordinates[i][1]=1;
	}
}

int snakegame(){
	int joystkDifficulty, joystkOpt;
	int gameMode, modesel;
	int highscore=0;
	int flaapyBirdGameOver, tryagain;
	char scores[60];
	int done=0;
	
	GLCD_Init();
	KBD_Init();
	LED_Init();

	while(!done){
		modesel = 1;
		gameMode = 1;
		tryagain = 1;
		currentDirection = 0;
		previousDirection = 0;
		currentJoystkVal = 0;
		previousJoystkVal = KBD_RIGHT;
		speed = 15;
		snakeSize = 2;
		snakePos_X = 5;
		snakePos_Y = 10;
		GLCD_Clear(Black);
		GLCD_SetBackColor(Black);
		GLCD_SetTextColor(Green);
		GLCD_DisplayString(2,0,1,"Select Border gameMode: ");
		GLCD_DisplayString(4,0,1,"-->  ON             ");
		GLCD_DisplayString(5,0,1,"     OFF            ");
		GLCD_DisplayString(29,0,0,"          press joystick to select the game mode           ");
		while(modesel == 1){
			joystkDifficulty = get_button();
			switch(joystkDifficulty){
				case KBD_DOWN:
					GLCD_DisplayString(4,0,1,"     ON             ");
					GLCD_DisplayString(5,0,1,"-->  OFF            ");
					gameMode = 2;
					break;
				case KBD_UP:
					GLCD_DisplayString(4,0,1,"-->  ON             ");
					GLCD_DisplayString(5,0,1,"     OFF            ");
					gameMode = 1;
					break;
				case KBD_SELECT:
					if(gameMode == 1)
						displayBorder = 1;
					if(gameMode == 2)
						displayBorder = 0;
					modesel = 0;
					GLCD_Clear(Black);
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					break;
			}
		}
		setbody();
		target();	
		while(collision == 0){
			currentJoystkVal = get_button();
			direction(currentJoystkVal);
			sprintf(str,"     snakescore:[%d]",snakescore);
			GLCD_DisplayString(0,0,0,(unsigned char *)str);	
		}
		if(collision == 1){
			GLCD_Clear(Red);
			GLCD_SetBackColor(Black);
			GLCD_SetTextColor(Red);
			if(snakescore>=highscore)
					highscore = snakescore;
			sprintf(scores,"     [snakescore: %d]           [HIGH snakescore: %d]",snakescore,highscore);
			GLCD_DisplayString(0,0,0,(unsigned char *)scores);
			GLCD_DisplayString(2,0,1,"      GAME OVER     ");
			GLCD_DisplayString(7,0,1,"Wanna try again? ");
			GLCD_DisplayString(8,0,1," --> YES");
			GLCD_DisplayString(9,0,1,"     NO ");
			flaapyBirdGameOver = 0;
			while(flaapyBirdGameOver == 0){
				joystkOpt = get_button();
				switch(joystkOpt){
					case KBD_DOWN:
						GLCD_DisplayString(8,0,1,"     YES");
						GLCD_DisplayString(9,0,1," --> NO ");
						tryagain = 0;
						break;
					case KBD_UP:
						GLCD_DisplayString(8,0,1," --> YES");
						GLCD_DisplayString(9,0,1,"     NO ");
						tryagain = 1;
						break;
					case KBD_SELECT:
						if(tryagain == 0){
							GLCD_Clear(Black);
							done =1;
							return 0;
						}
						if(tryagain == 1){
							flaapyBirdGameOver = 1;
							collision = 0;
							displayBorder = 0;
							clearsnake();
						}
						break;
				}
			}
		}
		delay(5);
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------
int main (void) 
{  	// Main Program                       
	int inputSelected = 0; //inputSelected to see which program is user the choosing
										//'1' for Gallery, '2' for audio file, '3' for game
	int joystkVal = 0;   //track the current joystick value
	int joystkPrev = 0;  //track the previous value for the joystick
	
	KBD_Init();

	LED_Init ();
	GLCD_Init();

	GLCD_Clear  (Black);
	SysTick_Config(SystemCoreClock/100); 
	GLCD_SetBackColor(Black);
    GLCD_SetTextColor(Red);
	GLCD_DisplayString (0, 2, 1, "COE 718 Project");
	GLCD_DisplayString (1, 5, 1, "MAIN MENU");
	GLCD_DisplayString (2, 4, 1, "Apurva Patel");

  	for (;;)		//loop forever
	{
		joystkVal = get_button();	//read the joystick
		
		if (joystkVal !=joystkPrev)	//this means that the user used the joystick
			{
			if (joystkVal == KBD_DOWN)
				{
					inputSelected +=1;	//we are have only 3 modes so only 3 values of inputSelected
					inputSelected = inputSelected %5;		//are accepted, overflow is mapped back to beginning
				}
			else if (joystkVal == KBD_UP)
				{
					inputSelected -=1;
					if (inputSelected <=0)
							inputSelected = 1;
				}
			else if(joystkVal == KBD_RIGHT)
				{
					if (inputSelected == 1)
					{
						photo_viewer(1);	//start the Gallery function
						inputSelected = 0;
					}
					else if (inputSelected == 2)
					{
						audio_main();
						delay(10);
						GLCD_Clear(Black);
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (0, 2, 1, "COE 718 Project");
						GLCD_DisplayString (1, 5, 1, "MAIN MENU");
						GLCD_DisplayString (2, 4, 1, "Apurva Patel");									
						inputSelected =0;
					}
					else if (inputSelected == 3)
					{
						GLCD_Clear(Black);
						game();	
						GLCD_Clear(Black);
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (0, 2, 1, "COE 718 Project");
						GLCD_DisplayString (1, 5, 1, "MAIN MENU");
						GLCD_DisplayString (2, 4, 1, "Apurva Patel");
						inputSelected = 0;
					}
					else if(inputSelected ==4)
					{
						GLCD_Clear(Black);
						snakegame();
						GLCD_Clear(Black);
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (0, 2, 1, "COE 718 Project");
						GLCD_DisplayString (1, 5, 1, "MAIN MENU");
						GLCD_DisplayString (2, 4, 1, "Apurva Patel");
						inputSelected = 0;
					}
				}
			joystkPrev = joystkVal;
		}
		
		//this is to update the LCD each time the user interfaces with the joystick
		if (inputSelected == 1)	//for displaying now
			{
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(4,0,1, "Gallery");
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(5,0,1, "Audio");
					GLCD_DisplayString(6,0,1, "Flappy Bird");
					GLCD_DisplayString(7,0,1, "SNAKE");
					
			}
		else if(inputSelected == 2)
			{
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(4,0,1, "Gallery");
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(5,0,1, "Audio");
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(6,0,1, "Flappy Bird");
					GLCD_DisplayString(7,0,1, "SNAKE");
			}
		else if(inputSelected == 3)
			{
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(4,0,1, "Gallery");
					GLCD_DisplayString(5,0,1, "Audio");
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(6,0,1, "Flappy Bird");
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(7,0,1, "SNAKE");
			}
		else if (inputSelected == 4)
			{
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString(4,0,1, "Gallery");
						GLCD_DisplayString(5,0,1, "Audio");
						GLCD_DisplayString(6,0,1, "Flappy Bird");
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(7,0,1, "SNAKE");
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(Red);
			}
		else
			{
					GLCD_SetBackColor(Black);
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(4,0,1, "Gallery");
					GLCD_DisplayString(5,0,1, "Audio");
					GLCD_DisplayString(6,0,1, "Flappy Bird");
					GLCD_DisplayString(7,0,1, "SNAKE");
			}
	}
}


