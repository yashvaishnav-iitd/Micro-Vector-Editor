#ifndef POLYLINE_H
#define POLYLINE_H

#include "graphics_object.h"
#include <vector>
#include <QPoint>
#include <QPainter>

// This class handles the Freehand tool. Instead of just a start and end point, 
// it stores a whole list of points to track where the mouse moved.
class PolyLine: public GraphicsObject {
	public:
		
		// Constructor that takes in the initial list of points from the mouse drag.
		explicit PolyLine (const std::vector <QPoint> &points);

		//Helper to add points while drawing
        void addPoint (const QPoint &point);

		//Overrides
		void draw (QPainter &painter) const override; 				// Loops through the point vector to draw the connected lines on the canvas.
		
		std::string toString () const override;						// Converts the path into an SVG <polyline> or <path> string for saving.

		bool contains (const QPoint &point) const override;			// Checks if the mouse is near any of the segments in the line.

		void move(int dx, int dy) override;							// Moves every single point in the vector by the same distance.
		
		QRect getBoundingBox() const override;						// Calculates the smallest rectangle that fits all the points in the line.
		
		void setBoundingBox(const QRect &rect, int handle) override;	// Scales all the points in the path if the user resizes the selection box.

		std::unique_ptr<GraphicsObject> clone() const override;		//For creating a clone polyline

	private:
		// The core data: a vector of points that make up the freehand sketch.
		std::vector <QPoint> points;

};

#endif
