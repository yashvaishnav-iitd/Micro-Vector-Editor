#ifndef LINE_H
#define LINE_H

#include "graphics_object.h"

// This class represents a straight line segment
class Line: public GraphicsObject{
	public :
		//Constructor (takes start(x1,y1) and end(x2,y2) coordinates)
		Line (int x1, int y1, int x2, int y2);
		
		//Overrides
		void draw(QPainter& painter) const override;			// Tells QPainter to draw a line between the two stored points.
		
		std::string toString() const override;					// Generates the SVG <line> tag with x1, y1, x2, and y2 attributes.

		bool contains (const QPoint &point) const override;		// Checks if a click is "near" the line (collision detection).

		void move(int dx, int dy) override;						// Shifts both the start and end points by the mouse delta.
       
		QRect getBoundingBox() const override;					// Returns the bounding box that perfectly encloses the line.

        void setBoundingBox(const QRect &rect, int handle) override;		// Updates the line's endpoints based on which resize handle is dragged.

		std::unique_ptr<GraphicsObject> clone() const override;		//For creating a clone line

	private:
		// Unlike rectangles, lines are defined by two specific coordinates.
		int x1,y1, x2,y2;

};

#endif
