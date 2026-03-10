#include "hexagon.h"
#include <sstream>
#include <cmath>  //For cos, sin ,M_PI
#include <QPolygon> //Useful for 'contains' check

// This function calculates the 6 corners of our hexagon using trignometry
std::vector <QPoint> Hexagon::getPoints() const {
	std::vector <QPoint> points;
	for (int i =0 ; i<6; i++){

		//Angle in radians 60 degrees*i = (pi/3)*i
		//We subtract 30 degrees to make the hexagon point upwards
		double angle = (M_PI/3.0) * i - (M_PI/6.0) ;

		int x = cx + static_cast<int>(r * std::cos(angle));
		int y = cy + static_cast<int>(r * std::sin(angle));

		points.push_back(QPoint(x,y));
	}
	return points;
}

// Returns a square bounding box centered at (cx, cy) with side 2*r
QRect Hexagon::getBoundingBox() const{
	return QRect(cx-r,cy-r, 2*r,2*r).normalized();
}

// Complex resizing logic for the 8 selection handles
void Hexagon::setBoundingBox( const QRect &rect, int handle){
    // Calculate TRUE distances (avoiding the -1 offset of right() and bottom())
    //We avoid using rect.right() because it has a -1 pixel offset in Qt
    int distL = std::abs(rect.left() - cx);
    int distR = std::abs((rect.x() + rect.width()) - cx); 
    int distT = std::abs(rect.top() - cy);
    int distB = std::abs((rect.y() + rect.height()) - cy); 

    int newR = r; 
    if (handle == -1) {
        newR = std::max({distL, distR, distT, distB});
    } 
    else {
        int d1 = 0;
        int d2 = 0;
        bool isCorner = false;

        switch (handle) {
            // // Corner handles: need to track both X and Y movement
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

            // // Side handles: directly sets the radius based on that side
            case 1: newR = distT; break;
            case 3: newR = distR; break;
            case 5: newR = distB; break;
            case 7: newR = distL; break;
        }
        if (isCorner) {
            // // We check which way the mouse moved more (X or Y) and scale by that
            int delta1 = std::abs(d1 - r);
            int delta2 = std::abs(d2 - r);

            // / This keeps the hexagon from squishing weirdly on diagonal drags
            if (delta1 > delta2) {
                newR = d1;
            } else {
                newR = d2;
            }
        }
    }    
    // Safety check so the shape doesn't invert or disappear
    r = newR;
    if (r < 5) r = 5;
}


