#pragma once
#include "Drawing.h"
#include <iostream>
#include <vector>

using namespace std;
// all functions will be inline 

class DrawObject
{
private:
	COLOUR rgbcolour;
protected:
	vector<COORD> coord_Of_Vec;
public:

	DrawObject(COLOUR rgb) { rgbcolour = rgb; }
	COLOUR getColour() { return rgbcolour; } //getColour method that returns the colour of the object
	virtual void draw(Drawing &object) = 0; //pure virtual function
	virtual ~DrawObject() { ; } //this is a virtual destructor because of aggregation

};

class Point : public DrawObject
{
public:

	Point(COLOUR ptcolour, COORD ptcoord) : DrawObject(ptcolour)
	{
		coord_Of_Vec.push_back(ptcoord);
	}
	virtual void draw(Drawing &object)
	{
		COLOUR ptcolour = getColour();
		object.setPixel(coord_Of_Vec[0], ptcolour);
		coord_Of_Vec.pop_back(); //we have to delete this to make sure that the next shape coordinates can certainly be accessed without confusion.
	}
	~Point() { ; }
};

class Line : public DrawObject
{
public:

	Line(COLOUR lncolour, COORD coordStart, COORD coordEnd) :DrawObject(lncolour)
	{
		coord_Of_Vec.push_back(coordStart);
		coord_Of_Vec.push_back(coordEnd);
	}
	virtual void draw(Drawing &object)
	{
		COLOUR lncolour = getColour();
		object.drawLine(coord_Of_Vec[0], coord_Of_Vec[1], lncolour);

		while (coord_Of_Vec.empty() == false) //cause why not 
		{
			coord_Of_Vec.pop_back();
		}
	}
	~Line() { ; }
};

class Shape : public DrawObject
{
	static int shapeCount;
public:


	Shape(COLOUR scolour) : DrawObject(scolour) { shapeCount++; } //sample output requires the addition and destruction of this counter

	virtual void draw(Drawing &object)
	{
		COLOUR scolour = getColour();

		for (int i = 0; i < coord_Of_Vec.size() - 1; i++)
		{
			object.drawLine(coord_Of_Vec[i], coord_Of_Vec[i + 1], scolour);
		}

		object.drawLine(coord_Of_Vec.back(), coord_Of_Vec.front(), scolour); //So to close the shape off, we need this line. 

		while (!coord_Of_Vec.empty())
		{
			coord_Of_Vec.pop_back();
		}
	}
	void coordinate_ADD(COORD coordinate) { coord_Of_Vec.push_back(coordinate); }
	static int getShapes() { return shapeCount; }
	~Shape() { shapeCount--; }

}; int Shape::shapeCount = 0;