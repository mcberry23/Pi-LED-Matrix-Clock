#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "simulated-display.cpp"
#include "fonts.h"

float redData[16][32];
float greenData[16][32];
float blueData[16][32];
int hours;
int minutes;



void setPixel(int row, int col, GLfloat r, GLfloat g, GLfloat b)
{
	redData[row][col] = r;
	greenData[row][col] = g;
	blueData[row][col] = b;
}

void map6x13Pixels(int (*charData)[13][6], int row, int col, GLfloat r, GLfloat g, GLfloat b){
	for (int ro = row; ro < row+13; ro++){
		for (int co = col; co < col+6; co++){	
			// setPixel(ro,co,r,g,b);
			if ((*charData)[ro-row][co-col] == 1){
				setPixel(ro,co,r,g,b);
			}				
		}
	}
}

void draw6x13Char(int num, int row, int col, GLfloat r, GLfloat g, GLfloat b){
	switch(num){
		case 0:
			map6x13Pixels(&zero_6x13,row,col,r,g,b);
			break;
		case 1:
			map6x13Pixels(&one_6x13,row,col,r,g,b);
			break;
		case 2:
			map6x13Pixels(&two_6x13,row,col,r,g,b);
			break;
		case 3:
			map6x13Pixels(&three_6x13,row,col,r,g,b);
			break;
		case 4:
			map6x13Pixels(&four_6x13,row,col,r,g,b);
			break;
		case 5:
			map6x13Pixels(&five_6x13,row,col,r,g,b);
			break;
		case 6:
			map6x13Pixels(&six_6x13,row,col,r,g,b);
			break;
		case 7:
			map6x13Pixels(&seven_6x13,row,col,r,g,b);
			break;
		case 8:
			map6x13Pixels(&eight_6x13,row,col,r,g,b);
			break;
		case 9:
			map6x13Pixels(&nine_6x13,row,col,r,g,b);
			break;
		case -1:
			map6x13Pixels(&full_6x13,row,col,0,0,0);
			break;
		default:
			map6x13Pixels(&blank_6x13,row,col,r,g,b);
	}
}

void draw6x13CharShadow(int num, int row, int col,GLfloat brightness){
	draw6x13Char(num,row+1,col+1,brightness,brightness,brightness);
	draw6x13Char(num,row,col,0,0,brightness);
}

void drawPixels(){
	int rows = 16;
	int columns = 32;
	GLfloat xPos = -0.6f;
	GLfloat yPos = 0.4f;
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			drawFilledCircle(xPos, yPos, 0.01f, redData[row][column], greenData[row][column], blueData[row][column]);
			xPos += 0.04f;
		}
		xPos = -0.6f;
		yPos -= 0.04f;
	}
	glFlush();
}

void initializeDisplays(int argc, char **argv){
	initializeSimulatedDisplay(argc, argv);
}

void drawLargeTime(){
	glClear(GL_COLOR_BUFFER_BIT);
	// glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	draw6x13CharShadow(-1, 1, 0, 1.0f);
	draw6x13CharShadow(-1, 1, 8, 1.0f);
	draw6x13CharShadow(-1, 1, 17, 1.0f);
	draw6x13CharShadow(-1, 1, 25, 1.0f);
	if (hours < 10){
		draw6x13CharShadow(hours, 1, 8, 1.0f);
	}
	else{
		draw6x13CharShadow(hours/10, 1, 0, 1.0f);
		draw6x13CharShadow(hours%10, 1, 8, 1.0f);
	}	
	draw6x13CharShadow(minutes/10, 1, 17, 1.0f);
	draw6x13CharShadow(minutes%10, 1, 25, 1.0f);
	setPixel(6, 16, 1.0f, 1.0f, 1.0f);
	setPixel(10, 16, 1.0f, 1.0f, 1.0f);
	drawPixels();	
}

void updateLargeTime(int newHours, int newMinutes){
	hours = newHours;
	minutes = newMinutes;
	glutDisplayFunc(drawLargeTime);
	glutMainLoop();
}
