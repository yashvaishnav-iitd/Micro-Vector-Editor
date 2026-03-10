#include "circle.h"
#include <sstream> //For building the SVG string
#include <cmath>
#include <algorithm>


// Pythagorean theorem to check if mouse click is inside
bool Circle::contains (const QPoint &point) const{
	double dist = std::hypot(point.x() - cx, point.y() - cy);
	return dist<=r;
}

// SQuare that perfectly encloses the circle
QRect Circle::getBoundingBox() const{
	return QRect(cx-r, cy-r, 2*r,2*r).normalized();
}

// Resizing logic for the 8 handles
void Circle::setBoundingBox(const QRect &rect, int handle) {
    //Calculate TRUE distances (avoiding the -1 offset of right() and bottom())
    int distL = std::abs(rect.left() - cx);
    int distR = std::abs((rect.x() + rect.width()) - cx); 
    int distT = std::abs(rect.top() - cy);
    int distB = std::abs((rect.y() + rect.height()) - cy); 
    //
    int newR = r;
    if (handle == -1) {
        newR = std::max({distL, distR, distT, distB});
    } 
    else {
        int d1 = 0;
        int d2 = 0;
        bool isCorner = false;
        switch (handle) {
            // --- CORNER HANDLES ---
            case 0: // Top-Left
                d1 = distL; d2 = distT; isCorner = true;
                break;
            case 2: // Top-Right
                d1 = distR; d2 = distT; isCorner = true;
                break;
            case 4: // Bottom-Right
                d1 = distR; d2 = distB; isCorner = true;
                break;
            case 6: // Bottom-Left
                d1 = distL; d2 = distB; isCorner = true;
                break;

            // --- SIDE HANDLES (Simple Direct Assignment) ---
            case 1: newR = distT; break;    //Top-Middle
            case 3: newR = distR; break;    //Right-Middle
            case 5: newR = distB; break;    //Bottom-Middle
            case 7: newR = distL; break;    //Left Midlle
        }
        if (isCorner) {
            // Calculate how much each axis WANTS to change the radius
            int delta1 = std::abs(d1 - r);
            int delta2 = std::abs(d2 - r);
            // Pick the axis that changed the most
            if (delta1 > delta2) {
                newR = d1;
            } else {
                newR = d2;
            }
        }
    }
    r = newR;
    if (r < 5) r = 5;   //Minimum radii for shrinkage possible.
}
