#include <iostream>
#include <GL/freeglut.h>
#include <cstring>
#include <cstdlib>
#include "Window.h"

Window::Window(void)
{}

Window::Window(const int width, const int height, const int posX, const int posY, const char* name)
{
	widthOfWindow = width;
	heightOfWindow = height;
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(heightOfWindow, widthOfWindow);  //size of windows
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	this->nameOfWindow = (char*)malloc(sizeof(char)*strlen(name));
	strcpy(nameOfWindow, name);
	windowID = glutCreateWindow(nameOfWindow);
	InitColor();	
}

int Window::GetWidth(void) const
{
	return this->widthOfWindow;
}

int Window::GetHeight(void) const
{
	return this->heightOfWindow;
}

void Window::PutWidth(const int width)
{
	this->widthOfWindow = width;
}

void Window::PutHeight(const int height)
{
	this->heightOfWindow = height;
}

void Window::InitColor(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int Window::GetWindowID(void) const
{
	return windowID;
}

int Window::GetWindowPosX(void) const
{
	return windowPosX;
}

int Window::GetWindowPosY(void) const
{
	return windowPosY;
}
