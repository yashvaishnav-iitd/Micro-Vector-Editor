#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include "graphics_object.h"

// This class represents a rectangle with curved corners, which is one of 
// the specific SVG features we need to support.
class RoundedRectangle: public GraphicsObject{
	public:
		//Neads the left most corner along with width and height. Also it required the curves x radius and y radius to make the curve.
		RoundedRectangle(int x, int y, int w, int h, int rx, int ry);

		//OVerrides
		void draw(QPainter &painter) const override;		// Uses QPainter to actually render the rounded shape on the canvas
		std::string toString() const override;				// Generates the SVG string representation for saving to a file

		// Collision detection to see if a mouse click is inside this shape.
		bool contains (const QPoint &point) const override;

		// Updates the shape's coordinates for moving it around.
		void move(int dx, int dy) override;
        
		// Returns the rectangular area that encloses the entire shape        
		QRect getBoundingBox() const override;

		// Resizes the shape based on which handle (0-7) is being dragged.
        void setBoundingBox(const QRect &rect, int handle) override;

		std::unique_ptr<GraphicsObject> clone() const override; // For creating a clone rounded_rect 

	private:
		// These fields store the geometry. rx and ry are unique to this class
		int x, y , w, h, rx, ry;
};

#endif
