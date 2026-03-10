#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "graphics_object.h"

// This class represents a basic rectangle. 
class Rectangle : public GraphicsObject{
	public : 
		// Constructor that sets up the top-left corner and the size.
		Rectangle (int x, int y, int w, int h);

		//Overrides
		void draw(QPainter& painter) const override ; 			// Tells QPainter to actually draw the rectangle on the screen
		std::string toString() const override;					// Converts the rectangle data into an SVG <rect> string for saving

		bool contains (const QPoint &point) const override;		// Checks if a point (like a mouse click) is inside the rectangle area

		void move(int dx, int dy) override;						// Changes the x and y values when we drag the shape around.
        QRect getBoundingBox() const override;					// Returns the current area the rectangle covers.
        void setBoundingBox(const QRect &rect, int handle) override;	// Updates the position and size based on the 8 resize handles.

		std::unique_ptr<GraphicsObject> clone() const override;		//Used for cloning a shape
	private:
		// Basic geometry variables. x and y are the top-left corner.
		int x, y , w, h;

};

#endif
