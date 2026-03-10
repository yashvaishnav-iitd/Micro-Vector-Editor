#include "polyline.h"
#include <sstream>
#include <QPainterPath>
#include <limits>
#include <algorithm>

// Appends a new coordinate to the vector (used for freehand drawing)
void PolyLine::addPoint (const QPoint& point){
	points.push_back(point);
}

// Hit-testing: Checks if the user clicked on or very near the line
bool PolyLine :: contains (const QPoint &point) const {
	QPainterPath path;
	if (points.empty()) {return false;}

	// Build the path to represent the actual shape
	path.moveTo(points[0]);
	for (size_t i = 1 ; i<points.size(); i++){
		path.lineTo(points[i]);
	}
	// path.contains checks if the click is INSIDE a filled area.
	// path.intersects checks a small 10x10 box around the mouse for the border/line.

	return path.contains(point) || path.intersects(QRectF(point.x()-5,point.y()-5,10,10));
}

// Bounding Box: Finds the smallest rectangle that contains all points
QRect PolyLine::getBoundingBox() const{
	if (points.empty()) {return QRect();}

	// Initialize min/max with the first point's coordinates
	int minX = points[0].x();
	int maxX=points[0].x();

	int minY = points[0].y();
	int maxY = points[0].y();

	// Iterate through all points to find the true boundaries
	for (const auto &p :points){
		minX = std::min(minX,p.x());
		maxX = std::max(maxX,p.x());

		minY = std::min(minY,p.y());
		maxY = std::max(maxY,p.y());
	}
	// Width and height are the differences between max and min
	return QRect(minX, minY, maxX-minX, maxY-minY).normalized();
}

// Scaling Logic: Resizes the entire polyline proportionally
void PolyLine::setBoundingBox(const QRect &newRect, int handle){
	Q_UNUSED(handle); 			//We scale based on the overall rect, regardless of handle


	QRect oldRect = getBoundingBox();
	// Avoid division by zero if the line is just a vertical or horizontal dot
	if (oldRect.width() == 0 || oldRect.height() == 0){return ;}
	double scaleX = static_cast<double>(newRect.width())/oldRect.width();
	double scaleY = static_cast<double>(newRect.height())/oldRect.height();

	for (auto &p : points){
		// Get the point's relative position within the old rectangle
		double relX = p.x() - oldRect.x();
		double relY = p.y() - oldRect.y();
		// Map that relative position to the new rectangle and scale it
		int nx = newRect.x() + qRound(relX * scaleX);
		int ny = newRect.y() + qRound(relY * scaleY);
		
		//Update the point with the new "stretched" coordinate
		p.setX(nx);
		p.setY(ny);
	}
}


