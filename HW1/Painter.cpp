#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <GL/freeglut.h>
#include "Figure.cpp"

#ifndef _PAINTER_CPP_
#define _PAINTER_CPP_


#define GRAVITY 9.8f

#define INITCOUNT 5000

#define X_ZERO 0.0f
#define X_MIN -5.0f
#define X_MAX 5.0f
#define Y_ZERO 0.0f
#define Y_MAX 10.0f

#define CIRCLE 0
#define STAR 1
#define SQUARE 2 
#define TRIANGLE 3

#define RED 0
#define GREEN 1
#define BLUE 2

#define RANDOM -1

#define VX_MAX 2.5f
#define VX_MIN  -2.5f
#define VY_MAX 11.0f
#define VY_MIN  6.0f


class Painter {

private :
	int num_figure;
	int figures, colors;
	Figure *f;

public :
	Painter()
	: num_figure(INITCOUNT), figures(RANDOM), colors(RANDOM)
	{
		f = new Figure[num_figure];
		set_velocity();
		set_polygon(figures);
	 }
	void DrawSquare( );
	void DrawStar( );
	void DrawCircle(float r, int num_segments);
	void DrawTriangle( );
	float x_calculate(int i);
	float y_calculate(int i);
	void set_velocity();
	void set_polygon(int fig);
	void set_numfigure(int value);
	void set_colors(int c);
	int get_numfigure();
	void DrawFigure(int index);
	void DrawColor();
	void  DrawFountain();


};


void Painter::DrawSquare( )
{
	glBegin(GL_POLYGON);
	glVertex3f(-0.1f, 0.1f, 0.0);
	glVertex3f(-0.1f, -0.1f, 0.0);
	glVertex3f(0.1f, -0.1f, 0.0);
	glVertex3f(0.1f, 0.1f, 0.0);
	glEnd();
}

void Painter::DrawStar( )
{
	glBegin(GL_POLYGON);  
	glVertex3f(-0.06, 0.0, 0.0);
	glVertex3f(-0.09, -0.1, 0.0);
	glVertex3f(0.0, -0.04, 0.0);
	glVertex3f(0.09, -0.1, 0.0);
	glVertex3f(0.06 , 0.0, 0.0);
	glVertex3f(0.14, 0.06 , 0.0);
	glVertex3f(0.04, 0.06, 0.0);
	glVertex3f(0.0, 0.157, 0.0);
	glVertex3f(-0.04, 0.06, 0.0);
	glVertex3f(-0.14, 0.06, 0.0); 
	glEnd();
}

void Painter::DrawCircle(float r, int num_segments) 
{
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle 
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex3f(x + X_ZERO, y + Y_ZERO,0.0f);
	}
	glEnd();
}

void Painter::DrawTriangle( )
{
	glBegin(GL_POLYGON);
	glVertex3f(-0.1f, -0.1f, 0.0);
	glVertex3f(0.1f, -0.1f, 0.0);
	glVertex3f(0.0f, 0.1f, 0.0);
	glEnd();
}
    
float Painter::x_calculate(int i)
{
	return  ( X_ZERO + (f[i].vx)*(f[i].timer) );
}

float Painter::y_calculate(int i)
{
	return ( Y_ZERO + (f[i].vy)*(f[i].timer) - (0.5f*GRAVITY*(f[i].timer)*(f[i].timer)) );
}

void Painter::set_velocity()
{
	srand((unsigned int)time(NULL));

	for(int i =0; i<num_figure; i++){
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = VX_MAX - VX_MIN;
		float r = random * diff;
		f[i].vx = VX_MIN + r ;

		random = ((float)rand()) / (float)RAND_MAX;
		diff = VY_MAX - VY_MIN;
		r = random * diff;
		f[i].vy =  VY_MIN + r;
	}

}

void Painter::set_polygon(int fig)
{
	switch(fig){
		case CIRCLE :
			figures = CIRCLE;
			for(int i =0;i<num_figure;i++)
				f[i].figure = CIRCLE ;
			break;
		case STAR :
			figures = STAR;
			for(int i =0;i<num_figure;i++)
				f[i].figure = STAR ;
			break;
		case SQUARE :
			figures = SQUARE;
			for(int i =0;i<num_figure;i++)
				f[i].figure = SQUARE ;
			break;
		case TRIANGLE :
			figures = TRIANGLE;
			for(int i =0;i<num_figure;i++)
				f[i].figure = TRIANGLE ;
			break;
		case RANDOM :
			figures = RANDOM;
			srand((unsigned int)time(NULL));
			for(int i =0;i<num_figure;i++)
				f[i].figure = random()%4 ;
			break;
		default :
			break;
	}
}

void Painter::set_numfigure(int value)
{
	delete []f;
	num_figure = value;
	f = new Figure[num_figure];

	set_velocity();
	set_polygon(figures);
}

int Painter::get_numfigure()
{
	return num_figure;
}


void Painter::set_colors(int c)
{
	colors = c;
}


void Painter::DrawFigure(int index)
{
	switch (f[index].figure){
		case CIRCLE :
			DrawCircle(0.1f, 10);
			break;
		case STAR :
			DrawStar( );
			break;
		case SQUARE :
			DrawSquare( );
			break;
		case TRIANGLE :
			DrawTriangle( );
			break;
		default :
			break;
	}
}


void Painter::DrawColor()
{
	float red, green, blue;
	switch(colors){
		case RED :
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case GREEN :
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case BLUE :
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		case RANDOM :
			srand((unsigned int)time(NULL));
			red = ((float)rand()) / (float)RAND_MAX;
			green = ((float)rand()) / (float)RAND_MAX;
			blue = ((float)rand()) / (float)RAND_MAX;
			glColor3f(red, green, blue);
			break;
		default :
			break;
	}
}

void  Painter::DrawFountain()
{
	DrawColor( );
	for(int i=0;i<num_figure;i++){
		// check boundary
		if( (f[i].y_aspect <= Y_MAX) && (f[i].x_aspect >= X_MIN) && (f[i].x_aspect <= X_MAX) ){
			glPushMatrix();
			glTranslatef(f[i].x_aspect, f[i].y_aspect, 0);
			DrawFigure(i);
			glPopMatrix();
		}
	}
	
	for(int i=0;i<num_figure;i++){
		f[i].x_aspect = x_calculate(i);
		f[i].y_aspect = y_calculate(i);
		f[i].timer += 0.01f;

		if( f[i].y_aspect < Y_ZERO) 
			f[i].timer = 0.0f;
	}
}

#endif