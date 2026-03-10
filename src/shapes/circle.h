#ifndef CIRCLE_H
#define CIRCLE_H

#include "graphics_object.h"

// This class handles the Circle shape
class Circle : public GraphicsObject {
	public:
		//Circle constructor (To build a circle we need the coordinates of the center and its radius)
		Circle(int cx, int cy, int r);

			
		//Overrides helps in debugging(if I made a typo while writing a function instead of creating a new function for the class without telling me)

		void draw(QPainter& painter) const override;
			
		std::string toString() const override;						// Converts the circle into an SVG <circle> string for saving.

		bool contains(const QPoint &point) const override;			// Uses the distance formula to see if a mouse click is inside the circle.

		void move(int dx, int dy) override;							//shifts the center point (cx, cy) by the movement delta.
        
		QRect getBoundingBox() const override;						// Returns the square box that perfectly fits the circle

		void setBoundingBox(const QRect &rect,int handle) override;			// Updates the center and radius based on resizing handles

		std::unique_ptr<GraphicsObject> clone() const override;			//For cloning a circle (its attributes)

	private:
		int cx, cy, r; //Values to make the circle

};

#endif 
