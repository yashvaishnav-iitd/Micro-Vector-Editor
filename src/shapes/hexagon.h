#ifndef HEXAGON_H
#define HEXAGON_H

#include "graphics_object.h"
#include <vector>
#include <QPoint>

// This class represents a regular hexagon
class Hexagon : public GraphicsObject {
	public :
		
		// The constructor uses a center point (cx, cy) and a radius (r).
		Hexagon (int cx, int cy, int r);

		//Overrides

		void draw (QPainter &painter) const override;				// Uses the getPoints() helper to draw the 6 sides of the hexagon.
		
		std::string toString() const override;						// Exports the shape as an SVG <polygon> with the 6 calculated coordinates.

		bool contains (const QPoint &point) const override;			// Checks if a point is inside the hexagon (uses the bounding box for simplicity).

		void move(int dx, int dy) override;							// Updates the center point to move the whole hexagon.

        QRect getBoundingBox() const override;						// Returns the square area that contains the entire hexagon.
                
		void setBoundingBox(const QRect &rect,int handle) override;		// Adjusts the radius and center based on the selection handles.

		std::unique_ptr<GraphicsObject> clone() const override;			//For creating a clone hexagon with same geometry and styles

	private:
		//Centre coordinates and radius
		int cx, cy, r;

		//Helper for getting the 6 points mathematically
		std::vector <QPoint> getPoints() const;

};

#endif
