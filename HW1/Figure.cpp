#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <GL/freeglut.h>

#ifndef _FIGURE_CPP_
#define _FIGURE_CPP_



class Figure {

public :
	int figure;
	float timer;
	float vx, vy ;
	float x_aspect, y_aspect;

	Figure() {
		initvalue();
	 }
	 
	void initvalue();
};

void Figure::initvalue()
{
	timer = 0.0f;
	x_aspect = 0.0f;	
	y_aspect = 0.0f;
}



#endif