#ifndef line_hpp
#define line_hpp

#include <algorithm>
#include "Joint.hpp"

class Line
{
private:
    float StartX, StartY;
	float EndX, EndY;
	float width;
    Line *collideWith = NULL;

public:
    Line(float StartX, float StartY, float EndX, float EndY, float LineWidth);
    void checkCollide(Joint *P);
    Line *getCollideWith() { return collideWith; }
    void setStartX(float xCoord) { StartX = xCoord; }
	void setStartY(float yCoord) { StartY = yCoord; }
    void setEndX(float xCoord) { EndX = xCoord; }
	void setEndY(float yCoord) { EndY = yCoord; }
    float getWidth() { return width; }
    float getStartX() { return StartX; }
	float getStartY() { return StartY; }
    float getEndX() { return EndX; }
	float getEndY() { return EndY; }
    
};



#endif