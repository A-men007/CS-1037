#pragma once
#include "Drawing.h"
#include <cstdlib>
#include "Drawable.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <forward_list>

using namespace std;

//assn3.exe test.bmp LW = 200 100 RGB = 127 127 127 
//S RGB = 255 0 0 ROWCOL# = 4 ROWCOLCOORD = (10,10) (10,190) (90,190) (90,10)
//S RGB = 0 255 0 ROWCOL# = 3 ROWCOLCOORD = (50,100) (55,105) (55,95) 
//L RGB = 0 0 255 ROWCOLCOORD = (60,30) (80,100) 
//L RGB = 0 0 255 ROWCOLCOORD = (80,100) (60,170) 
//P RGB = 0 0 0 ROWCOLCOORD = (25,70) 
//P RGB = 0 0 0 ROWCOLCOORD = (25,130)

COLOUR get_colour(char* red, char* green, char* blue);
COORD getCoordinates(char* x, char* y);


int main(int argc, char* argv[])
{
	forward_list<DrawObject*> allObjects;
	COLOUR bck_gnd = get_colour(argv[5], argv[6], argv[7]);								//argv[0] holds the file location, argv[1] holds the "assn3.exe", argv[2] holds "test.bmp"
	Drawing canvas(static_cast<unsigned>(atoi(argv[3])), static_cast<unsigned>(atoi(argv[4])), bck_gnd);

	int number_of_objects = 0;
	int i = 8;																			//every index from this point will be refering to the drawing objects on the canvas. 
	while (argv[i] != nullptr)
	{
		if (*argv[i] == 'S') {															//Step1: get pixel colour info. Step 2: Know how many lines are in the shape Step 3: Parse coordinates to draw lines
			number_of_objects++;
			COLOUR shapeColour = get_colour(argv[i + 1], argv[i + 2], argv[i + 3]);		//parsing the first set of information; the general colour of the shape
			Shape *newShape = new Shape(shapeColour);									//constructing a shape pointer
			for (int k = 0; k < atoi(argv[i + 4]); k++) {									//argv[i+4] is step 2. 
				newShape->coordinate_ADD(getCoordinates(argv[i + 2 * k + 5], argv[i + 2 * k + 6]));
			}
			allObjects.push_front(newShape);											//so now that the construction of our shape is complete, we can add it to our forward_list. 
		}

		else if (*argv[i] == 'L') {														//Step1: get the pixel colour info. Step2: Set the coordinates of the lines to a line object. 
			number_of_objects++;
			COLOUR linecolour = get_colour(argv[i + 1], argv[i + 2], argv[i + 3]);		//parsing the colour info of the line
			COORD lineCoordinateStart = getCoordinates(argv[i + 4], argv[i + 5]);		//parsing the beginning point of the line segment
			COORD lineCoordinateEnd = getCoordinates(argv[i + 6], argv[i + 7]);			//parsing the end point of the line segment
			Line *newLine = new Line(linecolour, lineCoordinateStart, lineCoordinateEnd);//constructing a new Line object with the appropriate parameters
			allObjects.push_front(newLine);												//pushing this constructed object to the object list.
		}

		else if (*argv[i] == 'P') {															//Step1: get the pixel colour info. Step2: Set the coordinates of the point to a point object.
			number_of_objects;
			COLOUR pointColour = get_colour(argv[i + 1], argv[i + 2], argv[i + 3]);		//parsing the colour info of the point 
			COORD pointCoordinate = getCoordinates(argv[i + 4], argv[i + 5]);			//parsing the coordinate info of the point
			Point *newPoint = new Point(pointColour, pointCoordinate);
			allObjects.push_front(newPoint);
		}
		i++;
	}


	cout << "Number of Shapes: " << Shape::getShapes() << endl;				//outputting the number of shapes that the counter has found

	for (int o = 0; o < number_of_objects; o++)								//number_of_objects is the total number of objects that the program has counted
	{
		allObjects.front()->draw(canvas);									//implement the draw method on every front element in the list. 
		delete allObjects.front();											//delete the element in the first element
		allObjects.pop_front();												//decrease the size of list until empty		
	}

	cout << "Number of Shapes: " << Shape::getShapes() << endl;


	if (canvas.saveBMP(argv[2]))
	{
		cout << "test.bmp saved successfully" << endl;
	}

	else { cout << "test.bmp did not save" << endl; }


	char c;
	cin >> c;
}

//HELPER FUNCTIONS

COLOUR get_colour(char * red, char* green, char* blue)
{
	//this converts the char inputs from command arguments to integers. 
	int R = atoi(red);
	int G = atoi(green);
	int B = atoi(blue);
	//now we need to input these three variables into the colour struct in the drawing class.
	//troubleshoot: These numbers need to be unsigned casted from -127 to 128 bits to 0-255 bits. Well obviously, thats how pixels work. 
	COLOUR rgb = { static_cast<unsigned int>(R), static_cast<unsigned int>(G), static_cast<unsigned int>(B) };
	return rgb;
}

COORD getCoordinates(char* x, char* y)					//similar to the function above. This time the casted variables will be placed into the COORD structure
{
	int row = atoi(x);
	int column = atoi(y);								//we do not need to statically cast these variables. its just a size.
	COORD coordinate = { row,column };
	return coordinate;
}