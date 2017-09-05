#ifndef WINDOW
#define WINDOW

class Window
{
private:
	int heightOfWindow;
	int widthOfWindow;
	char* nameOfWindow;
	int windowID;
	int windowPosX;
	int windowPosY;

public:
	Window(void);
	Window(const int width, const int height, const int posX, const int posY, const char* name);
	int GetWidth(void) const;
	int GetHeight(void) const;
	void PutWidth(const int width);
	void PutHeight(const int height);
	void InitColor(void);
	int GetWindowID(void) const;
	int GetWindowPosX(void) const;
	int GetWindowPosY(void) const;
};
#endif